"""Run from setup_unreal.py after base materials have been created (UE 5.4.4)."""
import json,re

def import_obstacles():
 source=ROOT/'Tools/ObstacleSource'
 catalog=json.loads((source/'materials.json').read_text())
 dest='/Game/Obstacles'
 for folder in [dest,dest+'/Materials',dest+'/Textures']:
  unreal.EditorAssetLibrary.make_directory(folder)
 textures={}
 for p in sorted((source/'Textures').iterdir()):
  tex=import_asset(p,dest+'/Textures','T_'+p.stem)
  tex.set_editor_property('max_texture_size',1024)
  if 'Palette' in p.name:
   tex.set_editor_property('filter',unreal.TextureFilter.TF_NEAREST)
  save(tex);textures[p.name]=tex
 def norm(name):return re.sub('[^a-z0-9]','',str(name).lower())
 report=[]
 for entry in catalog:
  key=entry['key'];name='SM_'+key
  options=unreal.FbxImportUI()
  options.set_editor_property('automated_import_should_detect_type',False)
  options.set_editor_property('mesh_type_to_import',unreal.FBXImportType.FBXIT_STATIC_MESH)
  options.set_editor_property('import_mesh',True)
  options.set_editor_property('import_as_skeletal',False)
  options.set_editor_property('import_materials',False)
  options.set_editor_property('import_textures',False)
  data=options.get_editor_property('static_mesh_import_data')
  for prop,value in [('combine_meshes',True),('auto_generate_collision',True),
                     ('transform_vertex_to_absolute',True),('convert_scene',True),
                     ('convert_scene_unit',True),('generate_lightmap_u_vs',True)]:
   data.set_editor_property(prop,value)
  task=unreal.AssetImportTask()
  for prop,value in [('filename',str(source/entry['file'])),('destination_path',dest),
                     ('destination_name',name),('automated',True),('replace_existing',True),
                     ('save',True),('options',options)]:task.set_editor_property(prop,value)
  ASSET.import_asset_tasks([task])
  mesh=unreal.load_asset(dest+'/'+name)
  if not isinstance(mesh,unreal.StaticMesh):raise RuntimeError('Missing obstacle mesh: '+key)
  materials={}
  for spec in entry['materials']:
   matname='MI_'+key+'_'+re.sub('[^A-Za-z0-9_]','_',spec['name'])
   matpath=dest+'/Materials/'+matname
   mi=unreal.load_asset(matpath) if unreal.EditorAssetLibrary.does_asset_exist(matpath) else ASSET.create_asset(matname,dest+'/Materials',unreal.MaterialInstanceConstant,unreal.MaterialInstanceConstantFactoryNew())
   EDIT.set_material_instance_parent(mi,unreal.load_asset('/Game/Materials/M_Car'))
   low=spec['name'].lower();colour=spec['color'];texture=spec['texture']
   if texture and texture not in textures:raise RuntimeError('Unresolved texture: '+texture)
   # FBX does not contain Blender's procedural concrete graph: use supplied image.
   if texture:colour=[1.,1.,1.]
   # Opaque parked-car glass avoids expensive translucency and hides absent interiors.
   if 'glass' in low or 'window' in low:colour=[.035,.065,.085]
   EDIT.set_material_instance_vector_parameter_value(mi,'Tint',unreal.LinearColor(*colour,1.))
   EDIT.set_material_instance_texture_parameter_value(mi,'BaseTexture',textures.get(texture,unreal.load_asset('/Game/Materials/T_White')))
   roughness=.9 if any(x in low for x in ['concrete','curb','rubber','tire']) else (.16 if any(x in low for x in ['glass','window']) else (.3 if any(x in low for x in ['paint','rim','metal']) else .75))
   EDIT.set_material_instance_scalar_parameter_value(mi,'Roughness',roughness)
   EDIT.set_material_instance_scalar_parameter_value(mi,'Specular',.5)
   EDIT.set_material_instance_scalar_parameter_value(mi,'Metallic',.6 if any(x in low for x in ['metal','rim']) else 0.)
   save(mi);materials[norm(spec['name'])]=mi
  for i,slot in enumerate(mesh.get_editor_property('static_materials')):
   names=[slot.get_editor_property('imported_material_slot_name'),slot.get_editor_property('material_slot_name')]
   mi=next((materials[norm(n)] for n in names if norm(n) in materials),None)
   if mi is None:raise RuntimeError('Unmapped material slot on '+key+': '+str(names))
   mesh.set_material(i,mi)
  if key=='CurbCorner':
   body=mesh.get_editor_property('body_setup')
   body.set_editor_property('collision_trace_flag',unreal.CollisionTraceFlag.CTF_USE_COMPLEX_AS_SIMPLE)
  save(mesh)
  box=mesh.get_bounding_box();size=box.max-box.min
  if size.z<=0 or max(size.x,size.y)<=0:raise RuntimeError('Invalid dimensions: '+key)
  if key in ['Curb','CurbCorner'] and not 19<size.z<21:raise RuntimeError('Curb scale import failed: '+key)
  report.append({'mesh':key,'imported_size_cm':[size.x,size.y,size.z]})
  log('Obstacle ready: '+key)
 (ROOT/'Saved').mkdir(exist_ok=True)
 (ROOT/'Saved/ObstacleImportReport.json').write_text(json.dumps(report,indent=2))
