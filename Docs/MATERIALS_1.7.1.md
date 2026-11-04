# Beta 1.7.1 — materials update

## Install

This is a full source project, including the previous physics/UI/settings work.
Close Unreal, back up your project, and extract the CiazParking folder.
Run `SetupProject.cmd "D:\Unreal\UE_5.4"`. Setup is required: it imports the new
textures, creates material assets and updates the map. Rebuilding C++ alone will
not create M_Asphalt or M_Paint. Run Standalone Game after setup completes.
For a Windows executable, use PackageWindows.cmd as described in README.md.

## Asphalt

Source: **Asphalt 02**, Rob Tuytel / Poly Haven.
https://polyhaven.com/a/asphalt_02
License: CC0-1.0 — https://polyhaven.com/license

The original downloaded 1K PNG maps are included under Tools/PBRSource/Asphalt02:
- BaseColor: sRGB colour, default texture compression.
- NormalDX: linear DirectX normal, normal-map compression.
- ORM: linear masks, R = ambient occlusion, G = roughness, B = metallic (zero).

SOURCE.json records exact download URLs, original file SHA-256 hashes, resolution,
license and the asset's 3 metre tile width. No external download is needed at setup.
The downloaded material is implemented as an Unreal material graph; it is not an
imported Blender shader.

Ground material M_Asphalt uses world XY coordinates at one tile per 300 cm, so the
60 x 44 metre slab does not stretch its textures. It uses world-space normals for
that horizontal plane. A fourth sample of the same colour texture at a larger
scale applies subtle tonal variation. This reduces obvious repetition but does
not eliminate recurring cracks. It is specifically a flat-ground shader, not a
triplanar material for walls, arbitrary slopes or rotated objects.

Four texture lookups, three unique 1024x1024 textures, mipmaps and streaming.
No displacement, parallax, tessellation, extra geometry or per-frame material work.
The source PNGs total about 6.6 MB on disk; cooked GPU memory is determined by the
platform compression and resident mip levels, and has not been measured here.

## Other surfaces

- Player body paint: separate clear-coat shading model, .28 base roughness and
  .15 metallic; uses Unreal's default coat inputs. UE 5.4 Python does not expose
  those custom-data material properties, so no unsupported enum names are used.
- Chrome: metallic 1, roughness .19.
- Rubber: roughness .88, metallic 0 and lower specular.
- Fabric/headliner: roughness .88, metallic 0 and lower specular.
- Dashboard/plastic: roughness .76; steering trim .68; dielectric response.
- Light lenses: .24 roughness; preserved opaque source artwork.
- Player glass: .10 roughness, .16 opacity and a restrained tint.
- Obstacle materials: more distinct concrete/rubber, paint, metal and glass values.
  Parked-car windows remain opaque to avoid unnecessary translucency costs.
- Eleven duplicate vehicle texture imports removed. Shared source images now
  reference the same imported texture asset (35 unique images total).
- Vehicle images capped at 1K; normal and mask maps are linear, colour maps sRGB.

The supplied base-colour artwork and UVs are preserved. Apart from asphalt, no
new artist-authored normal/roughness maps were invented. Mixed tire/rim atlases
remain dielectric until separate surface masks are supplied. Baked dashboard
needles are still present pending the replacement dashboard texture.

## Validation and limits

Python syntax, all existing mesh/texture/audio paths, material parameter ranges,
asphalt file hashes/dimensions/channels, shared texture references, ground
assignment and cook-directory coverage pass local checks. ZIP bytes are verified.
New graph connections fail setup explicitly if Unreal rejects a connection.

Unreal shader compilation, rendering and hardware performance are NOT tested here.
RX 470 suitability is a design target, not a benchmark. Check paint reflections,
glass visibility, asphalt normal direction/tiling, dashboard readability and FPS
in Standalone on Low and Medium. Lighting and asset UVs still limit realism; this
material update is not a guarantee of photorealism.
