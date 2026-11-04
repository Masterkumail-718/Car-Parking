"""Executed inside setup_unreal.py; build portable UE 5.4 material assets."""
def build_pbr():
 def link(source,output,destination,input_name):
  if not EDIT.connect_material_expressions(source,output,destination,input_name):
   raise RuntimeError('PBR material connection failed: '+output+' -> '+input_name)
 def output(source,pin,property_name):
  if not EDIT.connect_material_property(source,pin,property_name):
   raise RuntimeError('PBR material output connection failed: '+str(property_name))
 # Clear coat is restricted to the player's painted body, not all scene objects.
 paint=material('M_Paint',texture=True)
 paint.set_editor_property('shading_model',unreal.MaterialShadingModel.MSM_CLEAR_COAT)
 # UE 5.4's Python MaterialProperty enum does not expose the custom-data
 # inputs used for coat amount/roughness. Use the engine's clear-coat defaults.
 EDIT.recompile_material(paint);save(paint)
 dest='/Game/Materials/Asphalt';unreal.EditorAssetLibrary.make_directory(dest)
 textures={}
 for name,srgb,compression in [('BaseColor',True,unreal.TextureCompressionSettings.TC_DEFAULT),('NormalDX',False,unreal.TextureCompressionSettings.TC_NORMALMAP),('ORM',False,unreal.TextureCompressionSettings.TC_MASKS)]:
  texture=import_asset(ROOT/'Tools/PBRSource/Asphalt02'/('Asphalt02_'+name+'.png'),dest,'T_Asphalt_'+name)
  texture.set_editor_property('srgb',srgb)
  texture.set_editor_property('compression_settings',compression)
  texture.set_editor_property('max_texture_size',1024)
  texture.set_editor_property('mip_gen_settings',unreal.TextureMipGenSettings.TMGS_FROM_TEXTURE_GROUP)
  texture.set_editor_property('lod_group',unreal.TextureGroup.TEXTUREGROUP_WORLD_NORMAL_MAP if name=='NormalDX' else unreal.TextureGroup.TEXTUREGROUP_WORLD)
  texture.set_editor_property('address_x',unreal.TextureAddress.TA_WRAP)
  texture.set_editor_property('address_y',unreal.TextureAddress.TA_WRAP)
  texture.set_editor_property('never_stream',False)
  save(texture);textures[name]=texture
 path='/Game/Materials/M_Asphalt'
 m=unreal.load_asset(path) if unreal.EditorAssetLibrary.does_asset_exist(path) else ASSET.create_asset('M_Asphalt','/Game/Materials',unreal.Material,unreal.MaterialFactoryNew())
 EDIT.delete_all_material_expressions(m)
 m.set_editor_property('blend_mode',unreal.BlendMode.BLEND_OPAQUE)
 m.set_editor_property('shading_model',unreal.MaterialShadingModel.MSM_DEFAULT_LIT)
 m.set_editor_property('two_sided',False)
 # The ground is a flat horizontal slab. World XY UVs avoid stretching caused
 # by the 60x44 metre cube scale; sampled normals use that same world basis.
 m.set_editor_property('tangent_space_normal',False)
 position=expr(m,unreal.MaterialExpressionWorldPosition)
 xy=expr(m,unreal.MaterialExpressionComponentMask)
 xy.set_editor_property('r',True);xy.set_editor_property('g',True)
 xy.set_editor_property('b',False);xy.set_editor_property('a',False)
 link(position,'',xy,'')
 scale=expr(m,unreal.MaterialExpressionScalarParameter,'TileScale',1./300.)
 uv=expr(m,unreal.MaterialExpressionMultiply)
 link(xy,'',uv,'A');link(scale,'',uv,'B')
 def sample(name,kind,coords):
  node=expr(m,unreal.MaterialExpressionTextureSampleParameter2D,'Asphalt'+name)
  node.set_editor_property('texture',textures[name]);node.set_editor_property('sampler_type',kind)
  link(coords,'',node,'UVs');return node
 color=sample('BaseColor',unreal.MaterialSamplerType.SAMPLERTYPE_COLOR,uv)
 normal=sample('NormalDX',unreal.MaterialSamplerType.SAMPLERTYPE_NORMAL,uv)
 masks=sample('ORM',unreal.MaterialSamplerType.SAMPLERTYPE_MASKS,uv)
 # One additional colour lookup adds subtle large-scale variation; no noise,
 # parallax, displacement, tessellation, or multi-layer blending.
 macro_uv=expr(m,unreal.MaterialExpressionMultiply);macro_uv.set_editor_property('const_b',.137)
 link(uv,'',macro_uv,'A')
 macro=sample('BaseColor',unreal.MaterialSamplerType.SAMPLERTYPE_COLOR,macro_uv)
 variation=expr(m,unreal.MaterialExpressionMultiply);variation.set_editor_property('const_b',.15)
 link(macro,'R',variation,'A')
 lift=expr(m,unreal.MaterialExpressionAdd);lift.set_editor_property('const_b',.90)
 link(variation,'',lift,'A')
 result=expr(m,unreal.MaterialExpressionMultiply)
 link(color,'RGB',result,'A');link(lift,'',result,'B')
 output(result,'',unreal.MaterialProperty.MP_BASE_COLOR)
 output(normal,'RGB',unreal.MaterialProperty.MP_NORMAL)
 output(masks,'R',unreal.MaterialProperty.MP_AMBIENT_OCCLUSION)
 output(masks,'G',unreal.MaterialProperty.MP_ROUGHNESS)
 output(masks,'B',unreal.MaterialProperty.MP_METALLIC)
 spec=expr(m,unreal.MaterialExpressionScalarParameter,'Specular',.35)
 output(spec,'',unreal.MaterialProperty.MP_SPECULAR)
 EDIT.recompile_material(m);save(m)
 log('PBR asphalt and paint materials created.')
