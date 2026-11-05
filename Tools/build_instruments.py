"""Shared lit instrument material, executed with setup_unreal.py helpers.

Dedicated runtime instances keep illumination off exterior uses of shared atlases.
Atlas values: 0 = animated needle, 1 = Ciaz cluster, 2 = Swift cluster.
The authored UV circles exclude atlas backgrounds, speakers and metallic rims.
"""
def build_instruments(reimport_textures=True):
 dest='/Game/Materials/Instruments'
 unreal.EditorAssetLibrary.make_directory(dest)
 for source,name in [('Ciaz_Dials.png','T_Ciaz_Dials'),('Swift_Dials.png','T_Swift_Dials')]:
  if not reimport_textures:continue
  texture=import_asset(ROOT/'Tools/InstrumentSource'/source,dest,name)
  texture.set_editor_property('srgb',True)
  texture.set_editor_property('compression_settings',unreal.TextureCompressionSettings.TC_DEFAULT)
  texture.set_editor_property('max_texture_size',1024)
  texture.set_editor_property('mip_gen_settings',unreal.TextureMipGenSettings.TMGS_FROM_TEXTURE_GROUP)
  texture.set_editor_property('lod_group',unreal.TextureGroup.TEXTUREGROUP_WORLD)
  texture.set_editor_property('never_stream',False)
  save(texture)
 path='/Game/Materials/M_Instrument'
 m=unreal.load_asset(path) if unreal.EditorAssetLibrary.does_asset_exist(path) else ASSET.create_asset('M_Instrument','/Game/Materials',unreal.Material,unreal.MaterialFactoryNew())
 EDIT.delete_all_material_expressions(m)
 m.set_editor_property('blend_mode',unreal.BlendMode.BLEND_OPAQUE)
 m.set_editor_property('shading_model',unreal.MaterialShadingModel.MSM_DEFAULT_LIT)
 m.set_editor_property('two_sided',True)
 tint=expr(m,unreal.MaterialExpressionVectorParameter,'Tint',unreal.LinearColor(1,1,1,1))
 texture=expr(m,unreal.MaterialExpressionTextureSampleParameter2D,'BaseTexture')
 texture.set_editor_property('texture',unreal.load_asset('/Game/Materials/T_White'))
 base=expr(m,unreal.MaterialExpressionMultiply)
 wire(texture,'RGB',base,'A');wire(tint,'',base,'B')
 surface(base,'',unreal.MaterialProperty.MP_BASE_COLOR)
 for name,value,prop in [('Roughness',.75,unreal.MaterialProperty.MP_ROUGHNESS),('Metallic',0.,unreal.MaterialProperty.MP_METALLIC),('Specular',.35,unreal.MaterialProperty.MP_SPECULAR)]:
  node=expr(m,unreal.MaterialExpressionScalarParameter,name,value)
  surface(node,'',prop)
 uv=expr(m,unreal.MaterialExpressionTextureCoordinate)
 atlas=expr(m,unreal.MaterialExpressionScalarParameter,'VehicleAtlas',0.)
 strength=expr(m,unreal.MaterialExpressionScalarParameter,'Backlight',0.)
 color=expr(m,unreal.MaterialExpressionVectorParameter,'EmissionColor',unreal.LinearColor(1,1,1,1))
 mask=expr(m,unreal.MaterialExpressionTextureSampleParameter2D,'BacklightMask')
 mask.set_editor_property('texture',unreal.load_asset('/Game/Materials/T_White'))
 emission=expr(m,unreal.MaterialExpressionCustom)
 emission.set_editor_property('output_type',unreal.CustomMaterialOutputType.CMOT_FLOAT3)
 names=['BaseRGB','UV','Atlas','Color','Strength','Mask']
 inputs=[]
 for name in names:
  pin=unreal.CustomInput();pin.set_editor_property('input_name',name);inputs.append(pin)
 emission.set_editor_property('inputs',inputs)
 emission.set_editor_property('description','Headlight-linked instrument backlight, source atlas marks only')
 emission.set_editor_property('code',r'''
float2 u = frac(UV);
float region = 1.0;
if (Atlas > 0.5 && Atlas < 1.5)
{
    float a = length(u - float2(0.624, 0.128));
    float b = length(u - float2(0.871, 0.128));
    float c = length(u - float2(0.150, 0.851));
    float d = length(u - float2(0.450, 0.851));
    region = max(max(1.0-smoothstep(0.116,0.120,a),1.0-smoothstep(0.116,0.120,b)),
                 max(1.0-smoothstep(0.145,0.148,c),1.0-smoothstep(0.145,0.148,d)));
}
else if (Atlas >= 1.5)
{
    float a = length(u - float2(0.090, 0.546));
    float b = length(u - float2(0.265, 0.546));
    float c = length(u - float2(0.445, 0.897));
    float d = length(u - float2(0.620, 0.897));
    float cluster = max(max(1.0-smoothstep(0.072,0.077,a),1.0-smoothstep(0.072,0.077,b)),
                        max(1.0-smoothstep(0.074,0.080,c),1.0-smoothstep(0.074,0.080,d)));
    float display = step(0.855,u.x)*step(u.x,0.995)*step(0.795,u.y)*step(u.y,0.990);
    region = max(cluster,display);
}
float brightness = dot(BaseRGB,float3(0.2126,0.7152,0.0722));
// Preserve the accepted Swift response. Ciaz's photographed grey markings need
// a lower threshold and independent luminance lift, including the outer tick band.
float markings = smoothstep(0.16,0.36,brightness);
float3 lit = BaseRGB * markings * region;
if (Atlas > 0.5 && Atlas < 1.5)
{
    markings = smoothstep(0.008,0.060,brightness);
    lit = saturate(BaseRGB / max(brightness,0.030)) * markings * region * 3.0;
}
// Needle sections have dark source artwork; emit their authored red light directly.
float3 emission = Atlas < 0.5 ? float3(1,1,1) : lit;
return emission * Color * max(Strength,0.0) * Mask;
''')
 for source,pin,name in [(base,'','BaseRGB'),(uv,'','UV'),(atlas,'','Atlas'),(color,'','Color'),(strength,'','Strength'),(mask,'R','Mask')]:
  wire(source,pin,emission,name)
 surface(emission,'',unreal.MaterialProperty.MP_EMISSIVE_COLOR)
 EDIT.recompile_material(m);save(m)
 log('Headlight-linked instrument material ready (Ciaz and Swift).')
