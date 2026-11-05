"""Render static menu previews from the unmodified runtime meshes.

Blender --background --factory-startup --python Tools/UI/render_menu_vehicles.py
The preview uses studio lighting, not the in-game material renderer.
"""
import json
import struct
from pathlib import Path

import bpy
import numpy as np
from mathutils import Vector

ROOT = Path(__file__).resolve().parents[2]
OUTPUT = ROOT / 'Saved/MenuVehicleRenders'
OUTPUT.mkdir(parents=True, exist_ok=True)


def material(spec, folder):
    mat = bpy.data.materials.new(spec['name'])
    mat.use_nodes = True
    shader = mat.node_tree.nodes.get('Principled BSDF')
    color = spec.get('color', [.5, .5, .5])
    shader.inputs['Base Color'].default_value = (*color[:3], 1)
    shader.inputs['Metallic'].default_value = spec.get('metallic', 0)
    shader.inputs['Roughness'].default_value = max(.15, spec.get('roughness', .5))
    if spec.get('paint'):
        shader.inputs['Coat Weight'].default_value = .3
    texture = folder / 'Textures' / spec.get('texture', '')
    if spec.get('texture') and texture.is_file():
        node = mat.node_tree.nodes.new('ShaderNodeTexImage')
        node.image = bpy.data.images.load(str(texture), check_existing=True)
        mat.node_tree.links.new(node.outputs['Color'], shader.inputs['Base Color'])
    if spec.get('glass'):
        shader.inputs['Base Color'].default_value = (.035, .055, .07, 1)
        shader.inputs['Roughness'].default_value = .13
        shader.inputs['Metallic'].default_value = .25
        shader.inputs['Transmission Weight'].default_value = .35
    return mat


def light(name, position, power, size, target):
    data = bpy.data.lights.new(name, 'AREA')
    data.energy, data.shape, data.size = power, 'DISK', size
    obj = bpy.data.objects.new(name, data)
    bpy.context.collection.objects.link(obj)
    obj.location = position
    obj.rotation_euler = (Vector(target) - obj.location).to_track_quat('-Z', 'Y').to_euler()


def render(key, folder_name):
    bpy.ops.wm.read_factory_settings(use_empty=True)
    folder = ROOT / 'Content' / folder_name
    manifest = json.loads((folder / 'vehicle.json').read_text())
    materials = [material(spec, folder) for spec in manifest['materials']]
    all_points = []
    for part in manifest['parts']:
        print(f'Assembling {key}: {part["file"]}', flush=True)
        raw = (folder / part['file']).read_bytes()
        magic, vertex_count, index_count = struct.unpack_from('<III', raw)
        assert magic == 0x43505A31
        attributes = np.frombuffer(raw, '<f4', vertex_count * 8, 12).reshape(-1, 8)
        indices = np.frombuffer(raw, '<u4', index_count, 12 + vertex_count * 32).reshape(-1, 3)
        # Undo Unreal's left-handed frame and clockwise winding, preserving original proportions.
        points = (attributes[:, :3] + np.array(part['pivot'])) / 100
        points[:, 1] *= -1
        normals = attributes[:, 3:6].copy()
        normals[:, 1] *= -1
        mesh = bpy.data.meshes.new(part['file'])
        mesh.from_pydata(points.tolist(), [], indices.tolist())
        mesh.update()
        mesh.normals_split_custom_set_from_vertices(normals.tolist())
        uv = mesh.uv_layers.new(name='UVMap')
        values = attributes[indices.reshape(-1), 6:8].copy()
        values[:, 1] = 1 - values[:, 1]
        uv.data.foreach_set('uv', values.reshape(-1))
        for polygon in mesh.polygons:
            polygon.use_smooth = True
        obj = bpy.data.objects.new(part.get('name', part['file']), mesh)
        bpy.context.collection.objects.link(obj)
        obj.data.materials.append(materials[part['material']])
        all_points.append(points)
    bounds = np.concatenate(all_points)
    low, high = bounds.min(0), bounds.max(0)
    center = (low + high) / 2
    floor = float(low[2])
    bpy.ops.mesh.primitive_plane_add(size=200, location=(0, 0, floor - .01))
    ground = bpy.context.object
    ground.is_shadow_catcher = True
    scene = bpy.context.scene
    scene.render.engine = 'CYCLES'
    scene.cycles.samples = 32
    scene.cycles.use_denoising = True
    scene.cycles.max_bounces = 5
    scene.render.film_transparent = True
    scene.world = bpy.data.worlds.new('Studio environment')
    scene.world.color = (.32, .32, .32)
    target = (float(center[0]), 0, float(center[2]))
    light('Softbox key', (2, 4, 5), 1100, 5, target)
    light('Softbox rim', (-2, -3, 4), 1400, 4, target)
    light('Front fill', (5, -2, 2.5), 700, 3, target)
    camera_data = bpy.data.cameras.new('Menu camera')
    camera = bpy.data.objects.new('Menu camera', camera_data)
    bpy.context.collection.objects.link(camera)
    # Front three-quarter, nose on screen-left, looking slightly down.
    camera.location = Vector(target) + Vector((6, 8, 2.2))
    camera.rotation_euler = (Vector(target) - camera.location).to_track_quat('-Z', 'Y').to_euler()
    camera_data.type = 'ORTHO'
    camera_data.ortho_scale = 5.2
    scene.camera = camera
    scene.render.resolution_x = 1024
    scene.render.resolution_y = 448
    scene.render.resolution_percentage = 100
    scene.render.image_settings.file_format = 'PNG'
    scene.render.image_settings.color_mode = 'RGBA'
    scene.view_settings.view_transform = 'AgX'
    scene.render.filepath = str(OUTPUT / f'{key}Preview.png')
    bpy.ops.render.render(write_still=True)
    print(f'MENU PREVIEW: {key}, {len(manifest["parts"])} source sections, 1024x448 RGBA')


for key, folder in [('Ciaz', 'VehicleData'), ('Swift', 'SwiftData')]:
    render(key, folder)
