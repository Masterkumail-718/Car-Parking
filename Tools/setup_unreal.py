"""Executed by UnrealEditor-Cmd 5.4.4. Builds materials, audio assets and map."""
import unreal, pathlib, traceback, json
ROOT=pathlib.Path(unreal.Paths.project_dir()).resolve()
ASSET=unreal.AssetToolsHelpers.get_asset_tools()
EDIT=unreal.MaterialEditingLibrary
def log(s):unreal.log('[CiazSetup] '+s)
def save(a):
 if not a or not unreal.EditorAssetLibrary.save_loaded_asset(a,False):raise RuntimeError('Failed to save generated asset: '+str(a))
def wire(source,pin,destination,input_name):
 if not EDIT.connect_material_expressions(source,pin,destination,input_name):raise RuntimeError('Material connection failed: '+str(pin)+' -> '+str(input_name))
def surface(source,pin,property_name):
 if not EDIT.connect_material_property(source,pin,property_name):raise RuntimeError('Material output connection failed: '+str(property_name))
def import_asset(path,dest,name):
 task=unreal.AssetImportTask()
 task.set_editor_property('filename',str(path));task.set_editor_property('destination_path',dest)
 task.set_editor_property('destination_name',name);task.set_editor_property('automated',True)
 task.set_editor_property('replace_existing',True);task.set_editor_property('save',True)
 ASSET.import_asset_tasks([task])
 paths=task.get_editor_property('imported_object_paths')
 if not paths:raise RuntimeError('Import failed: '+str(path))
 return unreal.load_asset(paths[0])
def expr(m,cls,name=None,value=None):
 e=EDIT.create_material_expression(m,cls)
 if name:e.set_editor_property('parameter_name',name)
 if value is not None:e.set_editor_property('default_value',value)
 return e
def material(name,glass=False,target=False,texture=False):
 path='/Game/Materials/'+name
 if unreal.EditorAssetLibrary.does_asset_exist(path):
  m=unreal.load_asset(path);EDIT.delete_all_material_expressions(m)
 else:m=ASSET.create_asset(name,'/Game/Materials',unreal.Material,unreal.MaterialFactoryNew())
 m.set_editor_property('two_sided',glass)
 m.set_editor_property('blend_mode',unreal.BlendMode.BLEND_TRANSLUCENT if glass else unreal.BlendMode.BLEND_OPAQUE)
 tint=expr(m,unreal.MaterialExpressionVectorParameter,'Tint',unreal.LinearColor(.65,.65,.65,1))
 output=tint
 if texture:
  tx=expr(m,unreal.MaterialExpressionTextureSampleParameter2D,'BaseTexture')
  tx.set_editor_property('texture',unreal.load_asset('/Game/Materials/T_White'))
  mul=expr(m,unreal.MaterialExpressionMultiply)
  wire(tx,'RGB',mul,'A');wire(tint,'',mul,'B')
  output=mul
 surface(output,'',unreal.MaterialProperty.MP_BASE_COLOR)
 if target:
  surface(tint,'',unreal.MaterialProperty.MP_EMISSIVE_COLOR)
 else:
  specular=expr(m,unreal.MaterialExpressionScalarParameter,'Specular',.5)
  surface(specular,'',unreal.MaterialProperty.MP_SPECULAR)
  rough=expr(m,unreal.MaterialExpressionScalarParameter,'Roughness',.5)
  metal=expr(m,unreal.MaterialExpressionScalarParameter,'Metallic',0.)
  surface(rough,'',unreal.MaterialProperty.MP_ROUGHNESS)
  surface(metal,'',unreal.MaterialProperty.MP_METALLIC)
 if glass:
  opacity=expr(m,unreal.MaterialExpressionScalarParameter,'Opacity',.22)
  surface(opacity,'',unreal.MaterialProperty.MP_OPACITY)
 EDIT.recompile_material(m);save(m);return m
def vehicle_materials():
 interior=material('M_Interior',texture=True)
 interior.set_editor_property('two_sided',True)
 EDIT.recompile_material(interior);save(interior)
 path='/Game/Materials/M_Mirror'
 mirror=unreal.load_asset(path) if unreal.EditorAssetLibrary.does_asset_exist(path) else ASSET.create_asset('M_Mirror','/Game/Materials',unreal.Material,unreal.MaterialFactoryNew())
 EDIT.delete_all_material_expressions(mirror)
 mirror.set_editor_property('shading_model',unreal.MaterialShadingModel.MSM_UNLIT)
 mirror.set_editor_property('two_sided',True)
 tx=expr(mirror,unreal.MaterialExpressionTextureSampleParameter2D,'MirrorTexture')
 tx.set_editor_property('texture',unreal.load_asset('/Game/Materials/T_White'))
 surface(tx,'RGB',unreal.MaterialProperty.MP_EMISSIVE_COLOR)
 EDIT.recompile_material(mirror);save(mirror)
 unreal.EditorAssetLibrary.make_directory('/Game/VehicleTextures')
 manifest=json.loads((ROOT/'Content/VehicleData/vehicle.json').read_text())
 seen_textures=set()
 for index,entry in enumerate(manifest['materials']):
  if not entry['texture']:continue
  if entry['texture'] in seen_textures:
   duplicate='/Game/VehicleTextures/T_Vehicle_%02d'%index
   if unreal.EditorAssetLibrary.does_asset_exist(duplicate):unreal.EditorAssetLibrary.delete_asset(duplicate)
   continue
  seen_textures.add(entry['texture'])
  texture=import_asset(ROOT/'Content/VehicleData/Textures'/entry['texture'],'/Game/VehicleTextures','T_Vehicle_%02d'%index)
  texture.set_editor_property('srgb',True)
  texture.set_editor_property('max_texture_size',1024)
  texture.set_editor_property('compression_settings',unreal.TextureCompressionSettings.TC_DEFAULT)
  texture.set_editor_property('mip_gen_settings',unreal.TextureMipGenSettings.TMGS_FROM_TEXTURE_GROUP)
  texture.set_editor_property('lod_group',unreal.TextureGroup.TEXTUREGROUP_WORLD)
  save(texture)

def run():
 marker_path=ROOT/'Saved/SetupComplete.txt'
 if marker_path.exists():marker_path.unlink()
 for folder in ['/Game/Materials','/Game/Audio','/Game/Maps']:unreal.EditorAssetLibrary.make_directory(folder)
 import_asset(ROOT/'Tools/White.png','/Game/Materials','T_White')
 material('M_Car',texture=True);material('M_Glass',glass=True,texture=True)
 material('M_Solid');material('M_Target',target=True)
 vehicle_materials()
 exec(compile((ROOT/'Tools/build_pbr.py').read_text(),str(ROOT/'Tools/build_pbr.py'),'exec'),globals())
 build_pbr()
 exec(compile((ROOT/'Tools/build_swift.py').read_text(),str(ROOT/'Tools/build_swift.py'),'exec'),globals())
 build_swift()
 exec(compile((ROOT/'Tools/import_obstacles.py').read_text(),str(ROOT/'Tools/import_obstacles.py'),'exec'),globals())
 import_obstacles()
 for p in sorted((ROOT/'Content/AudioSource').glob('*.wav')):
  a=import_asset(p,'/Game/Audio',p.stem)
  a.set_editor_property('looping',p.stem in ['EngineIdle','EngineLoad','SensorTone'])
  save(a)
 level=unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
 actors=unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
 if unreal.EditorAssetLibrary.does_asset_exist('/Game/Maps/Parking'):
  if not level.load_level('/Game/Maps/Parking'):raise RuntimeError('Could not load Parking map')
  for actor in actors.get_all_level_actors():
   if actor.get_actor_label().startswith('CP_'):actors.destroy_actor(actor)
 else:
  if not level.new_level('/Game/Maps/Parking'):raise RuntimeError('Could not create Parking map')
 sun=actors.spawn_actor_from_class(unreal.DirectionalLight,unreal.Vector(0,0,1400),unreal.Rotator(-55,-25,0))
 sun.set_actor_label('CP_Sun')
 light=sun.get_component_by_class(unreal.DirectionalLightComponent)
 light.set_editor_property('mobility',unreal.ComponentMobility.MOVABLE)
 light.set_editor_property('intensity',3.5)
 light.set_editor_property('atmosphere_sun_light',True)
 sky=actors.spawn_actor_from_class(unreal.SkyLight,unreal.Vector(0,0,1000))
 sky.set_actor_label('CP_SkyLight')
 skyc=sky.get_component_by_class(unreal.SkyLightComponent)
 skyc.set_editor_property('mobility',unreal.ComponentMobility.MOVABLE)
 skyc.set_editor_property('intensity',1.05)
 skyc.set_editor_property('lower_hemisphere_is_black',False)
 atmosphere=actors.spawn_actor_from_class(unreal.SkyAtmosphere,unreal.Vector(0,0,0))
 atmosphere.set_actor_label('CP_Atmosphere')
 skyc.recapture_sky()
 # A hidden cube ensures the basic mesh dependency is included during cooking.
 marker=actors.spawn_actor_from_class(unreal.StaticMeshActor,unreal.Vector(0,0,-500))
 marker.static_mesh_component.set_static_mesh(unreal.load_asset('/Engine/BasicShapes/Cube'))
 marker.set_actor_hidden_in_game(True)
 marker.set_actor_label('CP_CookDependency_Cube')
 world=unreal.EditorLevelLibrary.get_editor_world()
 gm=unreal.load_class(None,'/Script/CiazParking.ParkingGameMode')
 if not gm:raise RuntimeError('CiazParking module is not built')
 world.get_world_settings().set_editor_property('default_game_mode',gm)
 if not level.save_current_level():raise RuntimeError('Map save failed')
 unreal.EditorAssetLibrary.save_directory('/Game',False,True)
 (ROOT/'Saved').mkdir(exist_ok=True)
 (ROOT/'Saved/SetupComplete.txt').write_text('Unreal setup completed. Open CiazParking.uproject and use Standalone Game.\n')
 log('SUCCESS: materials, audio and Parking map saved.')
try:run()
except Exception:
 unreal.log_error(traceback.format_exc())
 raise
