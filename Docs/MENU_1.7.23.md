# Beta 1.7.23 minimal intro menu

The main menu recreates the owner's approved minimal mockup: a blurred garage backdrop, restrained cyan primary action, five flat menu buttons, and one selected-vehicle panel. The controls are drawn and hit-tested by [ParkingHUD.cpp](../Source/CiazParking/ParkingHUD.cpp), not baked into an image. Start/Continue, Level Select, Settings, Controls and Quit retain their existing deferred actions. Change retains vehicle action 30. Ride height retains its 0–8 cm integer steps and save-on-release behavior. Other screens retain their existing layout.

The layout scales within a centred 1280×720 design canvas. The background fills the viewport with aspect-preserving crop, including 4:3 and ultrawide windows. Vehicle preview proportions are preserved. Mouse and Android menu touch use the same existing design-space pointer coordinates.

Menu labels use Unreal's runtime Roboto composite font, held by a constructor/CDO asset reference so its faces are included in cooking. Slate rasterizes regular/bold glyphs from the outlines at the actual output size; physical text positions are pixel-aligned. Small font atlases are not enlarged, and the initial distance-field trial was replaced because small labels looked too heavy. Rounded cards and the circular slider thumb use native Canvas triangle geometry instead of the legacy stepped-corner helper. These changes address the pixelated text and corner finish seen in the initial runtime review. The regular level-start hint is suppressed on the intro; error and status notices remain visible.

[Content/UI](../Content/UI) contains a generated, background-only garage PNG and static transparent previews rendered from the actual project Ciaz and Swift runtime meshes. Existing vehicle geometry, textures and authored colours are preserved; the previews depict the stock stance and do not dynamically render suspension adjustments. The selected name and preview change together. There are no additional scene captures or per-frame vehicle preview rendering costs. Performance and GPU memory have not been benchmarked.

The garage was created with the built-in imagegen tool: empty defocused dark indoor garage, cool overhead lamps and softly reflective floor, quiet negative space, no vehicles, people, lettering, panels or logos. [render_menu_vehicles.py](../Tools/UI/render_menu_vehicles.py) regenerates both 1024×448 RGBA vehicle preview PNGs with Blender in factory-startup background mode. It reads runtime mesh files and manifests without modifying them. Studio lighting and glass are preview approximations rather than exact Unreal material parity.

[build_menu.py](../Tools/build_menu.py) imports only the three textures under `/Game/UI`. It can run through UnrealEditor-Cmd with `-ExecutePythonScript`, or as part of regular [setup](../Tools/setup_unreal.py). Textures use UI compression, sRGB and no mipmaps, capped at 2048 for the backdrop and 1024 for previews. [DefaultGame.ini](../Config/DefaultGame.ini) explicitly includes `/Game/UI` in cooking. Both PNG sources and generated `.uasset` textures must travel with the repository/project copy.

Validation outcomes and remaining acceptance steps are maintained in [knowledge-graph.md](../knowledge-graph.md). No save fields, input bindings, vehicle physics or engine/toolchain targets were changed for this menu.

[Actual 1280�720 DX11 runtime screenshot](Menu_1.7.23.png). The screenshot was captured in-game with F9 after the final native-font build, not generated from the mockup.

In Beta 1.7.26, the owner supplied replacement Ciaz and Swift splash PNGs. The menu uses those two transparent images through the existing preview texture slots. The historical Blender preview script writes to ignored Saved/MenuVehicleRenders.
