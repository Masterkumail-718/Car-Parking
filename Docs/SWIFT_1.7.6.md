# Beta 1.7.6 — Suzuki Swift 2022

Adds the supplied Swift alongside the existing Ciaz. Choose VEHICLE on the main menu; selection persists. The existing levels and controls work with either car. No SUV assets are included yet.

## Install

Use Unreal Engine 5.4.4, as with the previous builds. Back up your current project and extract this full project into a fresh folder. Close Unreal Editor and run:

    SetupProject.cmd "D:\Unreal\UE_5.4"

This builds the C++ editor module and generates both cars' materials, textures and the map. Re-running setup is required, not merely replacing Source. Keep your existing Saved/SaveGames only if you want to retain progress and settings. Old saves select Ciaz by default. Select Swift from the main menu after setup succeeds.

## Vehicle model and optimization

The supplied 852,081 triangles become 267,669 triangles (68.6% reduction), 169,321 exported vertices and 99 material/animation sections. Body and wheel detail is simplified per material; the dashboard decal material, needle meshes and mirror surfaces are retained. Exact duplicate position/normal/UV vertices are welded; identical texture payloads share files. Images are capped at 1024 and imported with streaming mipmaps. Original FBX is not duplicated in this build. Keep your uploaded source archive.

There is no automatic distance LOD system in this update. Material-local simplification uses nearest-source attribute transfer; close inspection of UV seams is still needed in Unreal. Triangle reduction alone does not establish FPS on the RX 470. Three mirror captures retain the game's existing quality-dependent resolution and cadence.

Body paint is red with a dark roof; windows, light lenses, rubber, fabric, plastics and metal have separate roughness/metalness treatment. Packed maps use green roughness and blue metalness, never as colour or AO. Non-metal surfaces remain dielectric even where a packed source channel is white. OpenGL normals are converted to DirectX; procedural-mesh UV tangents are generated during loading. Interior decals use alpha masking. Mirror faces receive independent full-frame reflected UVs.

## Handling reference and assumptions

Baseline is the Pakistan-market K12M 1.2-litre Swift, not Swift Sport. Engine anchors: 61 kW at 6,000 RPM and 113 Nm at 4,200 RPM. Torque between these points is an authored curve, not a measured dyno trace. Five manual ratios: 3.545, 1.904, 1.240, 0.914, 0.717; reverse 3.272; final drive 4.388. Ciaz retains its 110-hp tune.

Operating mass is provisionally 930 kg (855 kg GL reference plus 75 kg driver). The 855 kg reference comes from the same-generation 2023 Pakistan brochure; the exact 2022 variant has not been confirmed. Later brochures give different weights. Front load fraction 61%, COM height, spring/damper rates, anti-roll and tire cornering stiffness are tuning assumptions. They are not factory suspension measurements.

The supplied mesh is normalized to 3.84 m length, with approximately 2.449 m axle spacing, 1.492 m track and 1.85 m mirror-inclusive parking width. Tire radius is 30.495 cm (185/55R16 nominal). Small differences from the brochure's 3.845 m length and 1.515/1.520 m track remain to fit this particular model. Physics uses the actual exported wheel centres. Underbody clearance is approximately 16 cm at nominal ride height.

Automatic, sequential assisted clutch and manual clutch modes all remain available. Automatic is the game's stepped automatic using these manual gear ratios, not a CVT simulation. Existing engine audio is shared; it is not an authentic recorded K12M engine. No idle propulsion is introduced.

## Animation, collision and shared features

All four wheels are split spatially from the combined source wheel meshes. Steering rotates around a fitted rim-plane axis and centre. The left gauge is RPM, the right is speed; all material sections of each needle animate together. Pivot points use the needle-hub diameter and the axis follows the dial plane. Current maps use 0–8,000 RPM and 0–220 km/h, with a 270-degree sweep. Small fuel/temperature indicators remain decorative; there is no fuel-consumption or coolant-temperature simulation.

The Swift has its own 48-piece compound convex collision body, with central underbody and relieved side wheel arches. Collision is not a scaled Ciaz body. Independent contact traces and suspension are tuned for the Swift's mass, axle spacing and weight distribution. Low curbs can be climbed when wheel support and actual bumper/body clearance allow; tall curbs can still strike the chassis. This remains the existing ray-sampled tire/contact approximation, not deformable tires or fully articulated suspension linkage geometry.

Cockpit/chase mouse cameras, interior FOV, rear/side mirrors, six parking sensors, headlights, rear-wheel handbrake lock/release, Hold/Toggle control, three-impact failure and ten levels are shared. Parking success now checks the selected vehicle's own footprint. Levels are not rescaled, so some will be easier in the shorter hatchback. Mirror views use the existing fixed-angle capture approximation.

## Validation and remaining checks

Portable C++ tests passed for existing rules, controls, UI easing, tire forces, suspension and handbrake, plus Swift power, torque, gearing, no-creep, shift guards, Ackermann symmetry, preload and footprint. Asset audits check mesh buffers, texture references, grouped wheel pivots, both complete gauge groups, normalized gauge axes, collision hull validity and wheel-arch voids. Offline geometry/texture previews were inspected.

Unreal Engine and the Windows toolchain are unavailable in the build environment. This package has NOT been compiled in Unreal, shader-compiled, driven on a T248, packaged as an EXE or benchmarked. Unreal-specific material API and integrated vehicle behavior still need validation on your PC.

First driving checks: change cars and restart; check mirrors and cockpit visibility; compare dashboard speed with HUD and RPM with engine state; turn steering at rest; reverse with sensors; drive slowly over a low curb one wheel at a time; brake straight; test handbrake lock/recovery; test both handbrake modes; park fully inside an outline. Check needle sweep and steering centre closely in cockpit view.

## Specification sources

Pak Suzuki, Swift brochure 10 November 2023 (same-generation reference):
https://suzukipakistan.com/media/Brochure%20Automobile/Swift%20brochure%2010.11.2023.pdf

Pak Suzuki model specification page:
https://suzukipakistan.azurewebsites.net/products/automobile-detail?automobile=Swift

These are reference specifications, not proof of measured handling fidelity. Supplied model and texture rights remain with their original owner/source.
