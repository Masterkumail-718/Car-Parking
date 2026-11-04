"""Build Swift-specific cooked PBR materials. Executed by setup_unreal.py."""
def build_swift():
 folder=ROOT/'Content/SwiftData'
 manifest=json.loads((folder/'vehicle.json').read_text())
 unreal.EditorAssetLibrary.make_directory('/Game/SwiftMaterials')
 unreal.EditorAssetLibrary.make_directory('/Game/SwiftTextures')
 textures={}
 for entry in manifest['materials']:
  for role in ['texture','normal','packed']:
   fn=entry.get(role,'')
   if not fn or (fn,role) in textures:continue
   name='T_'+pathlib.Path(fn).stem
   tex=import_asset(folder/'Textures'/fn,'/Game/SwiftTextures',name)
   tex.set_editor_property('srgb',role=='texture')
   tex.set_editor_property('max_texture_size',1024)
   compression=unreal.TextureCompressionSettings.TC_NORMALMAP if role=='normal' else (unreal.TextureCompressionSettings.TC_MASKS if role=='packed' else unreal.TextureCompressionSettings.TC_DEFAULT)
   tex.set_editor_property('compression_settings',compression)
   tex.set_editor_property('mip_gen_settings',unreal.TextureMipGenSettings.TMGS_FROM_TEXTURE_GROUP)
   tex.set_editor_property('lod_group',unreal.TextureGroup.TEXTUREGROUP_WORLD_NORMAL_MAP if role=='normal' else unreal.TextureGroup.TEXTUREGROUP_WORLD)
   save(tex);textures[(fn,role)]=tex
 for index,entry in enumerate(manifest['materials']):
  name='M_Swift_%02d'%index;path='/Game/SwiftMaterials/'+name
  m=unreal.load_asset(path) if unreal.EditorAssetLibrary.does_asset_exist(path) else ASSET.create_asset(name,'/Game/SwiftMaterials',unreal.Material,unreal.MaterialFactoryNew())
  EDIT.delete_all_material_expressions(m)
  glass=entry['glass'];masked=entry['name'] in ['Decals','SW_stitsk']
  m.set_editor_property('blend_mode',unreal.BlendMode.BLEND_TRANSLUCENT if glass else (unreal.BlendMode.BLEND_MASKED if masked else unreal.BlendMode.BLEND_OPAQUE))
  m.set_editor_property('two_sided',glass or entry['interior'])
  m.set_editor_property('shading_model',unreal.MaterialShadingModel.MSM_CLEAR_COAT if entry['paint'] else unreal.MaterialShadingModel.MSM_DEFAULT_LIT)
  tint=expr(m,unreal.MaterialExpressionVectorParameter,'Tint',unreal.LinearColor(*entry['color'],1))
  output=tint
  def sample(role):
   fn=entry.get(role,'')
   if not fn:return None
   tx=expr(m,unreal.MaterialExpressionTextureSampleParameter2D,{'texture':'BaseTexture','normal':'NormalTexture','packed':'PackedTexture'}[role]);tx.set_editor_property('texture',textures[(fn,role)])
   tx.set_editor_property('sampler_type',unreal.MaterialSamplerType.SAMPLERTYPE_NORMAL if role=='normal' else (unreal.MaterialSamplerType.SAMPLERTYPE_MASKS if role=='packed' else unreal.MaterialSamplerType.SAMPLERTYPE_COLOR))
   return tx
  tx=sample('texture')
  if tx:
   output=expr(m,unreal.MaterialExpressionMultiply);wire(tx,'RGB',output,'A');wire(tint,'',output,'B')
   if masked:surface(tx,'A',unreal.MaterialProperty.MP_OPACITY_MASK)
  surface(output,'',unreal.MaterialProperty.MP_BASE_COLOR)
  normal=sample('normal')
  if normal:surface(normal,'RGB',unreal.MaterialProperty.MP_NORMAL)
  packed=sample('packed')
  for parameter,prop in [('Roughness',unreal.MaterialProperty.MP_ROUGHNESS),('Metallic',unreal.MaterialProperty.MP_METALLIC),('Specular',unreal.MaterialProperty.MP_SPECULAR)]:
   value=expr(m,unreal.MaterialExpressionScalarParameter,parameter,entry[parameter.lower()]);out=value
   if packed and parameter in ['Roughness','Metallic']:
    channel='G' if parameter=='Roughness' else 'B'
    mod=packed;socket=channel
    if parameter=='Roughness':
     # Preserve per-material calibrated roughness, modulated by supplied map.
     mul=expr(m,unreal.MaterialExpressionMultiply);mul.set_editor_property('const_b',.5);wire(packed,channel,mul,'A')
     add=expr(m,unreal.MaterialExpressionAdd);add.set_editor_property('const_b',.5);wire(mul,'',add,'A');mod=add;socket=''
    out=expr(m,unreal.MaterialExpressionMultiply);wire(value,'',out,'A');wire(mod,socket,out,'B')
   surface(out,'',prop)
  if glass:
   opacity=expr(m,unreal.MaterialExpressionScalarParameter,'Opacity',entry['opacity']);surface(opacity,'',unreal.MaterialProperty.MP_OPACITY)
  EDIT.recompile_material(m);save(m)
  if entry['texture']:
   tn='T_'+pathlib.Path(entry['texture']).stem;entry['texture_asset']='/Game/SwiftTextures/'+tn+'.'+tn
 (folder/'vehicle.json').write_text(json.dumps(manifest,indent=2))
 log('Swift textures and materials ready')
