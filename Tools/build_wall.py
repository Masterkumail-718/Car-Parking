"""Wall PBR graph and shared daylight setup; called by setup_unreal.py.

World projection keeps the 150 cm scanned detail consistent on scaled/rotated
wall segments, including their tops. Normal output is explicitly world space.
"""
def build_wall():
 dest='/Game/Materials/ConcreteWall';unreal.EditorAssetLibrary.make_directory(dest)
 textures={}
 for name,srgb,compression in [('BaseColor',True,unreal.TextureCompressionSettings.TC_DEFAULT),('NormalDX',False,unreal.TextureCompressionSettings.TC_NORMALMAP),('ARM',False,unreal.TextureCompressionSettings.TC_MASKS)]:
  tex=import_asset(ROOT/'Tools/PBRSource/ConcreteWall001'/('ConcreteWall001_'+name+'.png'),dest,'T_ConcreteWall_'+name)
  for prop,value in [('srgb',srgb),('compression_settings',compression),('max_texture_size',2048),('never_stream',False),('mip_gen_settings',unreal.TextureMipGenSettings.TMGS_FROM_TEXTURE_GROUP),('lod_group',unreal.TextureGroup.TEXTUREGROUP_WORLD_NORMAL_MAP if name=='NormalDX' else unreal.TextureGroup.TEXTUREGROUP_WORLD),('address_x',unreal.TextureAddress.TA_WRAP),('address_y',unreal.TextureAddress.TA_WRAP)]:
   tex.set_editor_property(prop,value)
  save(tex);textures[name]=tex
 path='/Game/Materials/M_ConcreteWall'
 m=unreal.load_asset(path) if unreal.EditorAssetLibrary.does_asset_exist(path) else ASSET.create_asset('M_ConcreteWall','/Game/Materials',unreal.Material,unreal.MaterialFactoryNew())
 EDIT.delete_all_material_expressions(m)
 m.set_editor_property('tangent_space_normal',False)
 size=expr(m,unreal.MaterialExpressionConstant3Vector)
 size.set_editor_property('constant',unreal.LinearColor(150,150,150,1))
 def projected(name,normal=False):
  obj=expr(m,unreal.MaterialExpressionTextureObject)
  obj.set_editor_property('texture',textures[name])
  fn=expr(m,unreal.MaterialExpressionMaterialFunctionCall)
  asset=unreal.load_asset('/Engine/Functions/Engine_MaterialFunctions01/Texturing/'+('WorldAlignedNormal' if normal else 'WorldAlignedTexture'))
  if not asset:raise RuntimeError('Missing world projection material function')
  fn.set_material_function(asset)
  wire(obj,'',fn,'TextureObject')
  wire(size,'',fn,'TextureSize')
  if normal:
   # UE 5.4 WorldAlignedNormal defaults WorldSpace to false (tangent output).
   # This material disables tangent-space normals, so request world output explicitly.
   world_space=expr(m,unreal.MaterialExpressionStaticBool)
   world_space.set_editor_property('value',True)
   wire(world_space,'',fn,'WorldSpace')
  return fn
 color=projected('BaseColor');normal=projected('NormalDX',True);arm=projected('ARM')
 surface(color,'XYZ Texture',unreal.MaterialProperty.MP_BASE_COLOR)
 surface(normal,'XYZ Texture',unreal.MaterialProperty.MP_NORMAL)
 for channel,prop in [('r',unreal.MaterialProperty.MP_AMBIENT_OCCLUSION),('g',unreal.MaterialProperty.MP_ROUGHNESS),('b',unreal.MaterialProperty.MP_METALLIC)]:
  mask=expr(m,unreal.MaterialExpressionComponentMask)
  for c in ['r','g','b','a']:mask.set_editor_property(c,c==channel)
  wire(arm,'XYZ Texture',mask,'')
  surface(mask,'',prop)
 spec=expr(m,unreal.MaterialExpressionConstant);spec.set_editor_property('r',.35)
 surface(spec,'',unreal.MaterialProperty.MP_SPECULAR)
 EDIT.recompile_material(m);save(m)
 mi=unreal.load_asset('/Game/Obstacles/Materials/MI_Wall_Wall')
 if mi:EDIT.set_material_instance_parent(mi,m);save(mi)
 log('Concrete Wall 001 material saved (150 cm world projection).')

def tune_daylight(light,skyc):
 # Restrained fill preserves wall-side and vehicle-ground contrast.
 # Screen-space rays produced false stippled wall shadows (Level 12 A/B verified).
 light.set_editor_property('contact_shadow_length',0.)
 light.set_editor_property('dynamic_shadow_distance_movable_light',12000.)
 light.set_editor_property('dynamic_shadow_cascades',3)
 light.set_editor_property('shadow_bias',.35)
 skyc.set_editor_property('intensity',.8)
