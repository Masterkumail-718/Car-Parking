# Ciaz Parking knowledge graph

Last updated 2026-11-07. This document is the portable project handover. Read [AGENTS.md](AGENTS.md) for working rules.

## Current state and handoff

| Item | Current understanding |
| --- | --- |
| Project | Existing Windows C++ parking game for Unreal Engine 5.4.4 |
| Version | Beta 1.7.27, reference Android driving layout |
| Repository | https://github.com/Masterkumail-718/Car-Parking |
| Local checkout | `D:\Games\CiazParking`, branch `main`, remote `origin` |
| Last verified published baseline | 61643ae30751ca30995e67c77dfad2e478005d01, complete Beta 1.7.27 project update |
| Current task | Android drag-to-look and progressive pedals implemented. Next step is to package with the editor closed and verify camera and pedal feel on a phone |
| Handoff status | Beta 1.7.27 published on GitHub main. Android packaging and phone verification remain pending. Calibration hardware feedback remains pending |
| Build status | Updated Beta 1.7.27 Android arm64 Development compiled and linked. Last full package attempt predates these changes and failed on Live Coding. Prior Beta 1.7.26 Windows build retained |
| Documentation status | README, HUD and descriptor updated to 1.7.27 |

The external development history ends at 1.7.7 and calls 1.7.8 the next release. That statement is superseded by the current project and rest-stability update. Recheck source and Git state at each session rather than assuming this snapshot remains current.

## Product intent and constraints

A parking game with believable low-speed handling, supplied vehicle models, cockpit/chase views, wheel input, parking sensors and outlined target bays. The owner supplies models and references and provides Windows gameplay feedback. Current engine loops are generic shared recordings. Additional vehicle-specific audio remains future work.

Minimum hardware target is a sixth-generation i5, RX 470 4 GB and 8 GB RAM. Recommended target is Ryzen 5 2600, RTX 2060 Super 8 GB and 16 GB RAM. Historical goals of 720p Low at 30 FPS and 1080p Medium at 60 FPS remain unbenchmarked.

Configuration uses DX11/SM5 with Lumen, ray tracing, Nanite and virtual shadow maps disabled. Windows targets pin MSVC 14.38.33130. Engine path used by the owner is `D:\Unreal\UE_5.4`.

## System relationships

| System | Owns or depends on | Implementation and evidence |
| --- | --- | --- |
| Vehicle actor | Loads selected profile and meshes, applies physics, drives animation, cameras, sensors, mirrors and audio | [CiazPawn.cpp](Source/CiazParking/CiazPawn.cpp), [CiazPawn.h](Source/CiazParking/CiazPawn.h) |
| Portable dynamics | Suspension, contact forces, Ackermann steering, tire grip, braking and rest stability feed vehicle actor | [VehicleDynamics.h](Source/CiazParking/VehicleDynamics.h) |
| Driving and parking rules | Engine/transmission, steering, calibration, footprints and collision/parking rules feed game mode and vehicle | [ParkingCore.h](Source/CiazParking/ParkingCore.h) |
| Game orchestration | Input, courses, vehicle selection, progression and settings | [ParkingGameMode.cpp](Source/CiazParking/ParkingGameMode.cpp), [ParkingLevels.inl](Source/CiazParking/ParkingLevels.inl) |
| UI | Displays game state and queues actions outside drawing, uses quintic S-curve animation | [ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp), [UIAnimation.h](Source/CiazParking/UIAnimation.h) |
| Persistence | Controls, calibration, selected vehicle/transmission, graphics, FOV, handbrake and unlocks | [ParkingSave.h](Source/CiazParking/ParkingSave.h), local slot `CiazParking` under `Saved/SaveGames` |
| Wheel hardware | Windows DirectInput axes, calibration, paddle shifts and limited feedback feed controls | [WheelDevice.cpp](Source/CiazParking/WheelDevice.cpp) |
| Vehicle assets | Manifests, binary meshes and textures feed runtime loading and editor setup | `Content/VehicleData`, `Content/SwiftData`, [VehicleDataValidation.h](Source/CiazParking/VehicleDataValidation.h) |
| Chassis collision | Ciaz generated convex pieces and Swift JSON hulls feed chassis simulation | [CiazCollision.inl](Source/CiazParking/CiazCollision.inl), [Swift collision](Content/SwiftData/collision.json) |
| Asset generation | Original obstacles, textures and audio feed material/map creation | [setup_unreal.py](Tools/setup_unreal.py), `Tools/ObstacleSource`, `Tools/PBRSource`, `Content/AudioSource` |
| Build and packaging | Editor build precedes asset generation, Shipping packaging cooks and stages content | [SetupProject.cmd](SetupProject.cmd), [PackageWindows.cmd](PackageWindows.cmd), `Config` |

## Vehicles and gameplay

**Suzuki Ciaz 2017** uses the supplied model at about 4.49 m long, 1.90 m parking width and 1,100 kg mass. Authored engine tuning targets 110 mechanical hp at 6,000 RPM and about 145 Nm at 4,200 RPM. Collision uses about 40 convex pieces with wheel-arch relief. Stock clearance is approximately 18.8 cm, with a configurable 0–8 cm ride-height offset shared by both cars through the main menu. Existing 20 cm curbs can strike the body.

**Suzuki Swift 2022** uses a Pakistan-market K12M baseline, 61 kW at 6,000 RPM and 113 Nm at 4,200 RPM. The 930 kg operating mass and suspension/COM settings are provisional. It has five forward ratios, approximately 3.84 m body length, 1.85 m parking width, 48 convex collision pieces and roughly 22.5 cm nominal collision clearance. Its source-detail geometry has 852,081 triangles and 99 sections. The source tread radius is about 32.37 cm. Automatic mode uses the shared stepped transmission. See [Swift notes](Docs/SWIFT_1.7.6.md).

Both vehicles provide animated wheels/steering, speed/RPM needles, headlights, six parking sensors, three budgeted scene-capture mirrors and cockpit/chase cameras. Fuel and temperature indicators remain decorative. Dashboard artwork replacement is pending for Ciaz. Mirror views are fixed-angle approximations.

Twelve courses use supplied parked cars, cones, bollards, barriers, walls and curbs. The three parked car meshes use their render triangles for physics and traces. Success requires the four wheel centres projected onto the ground plane inside the target, appropriate heading, upright orientation, low motion and a two-second hold. Body overhang is allowed. Three distinct collision episodes fail a level. Continuous contact is filtered to avoid counting every frame. Completion unlocks and saves progression.

Transmission modes are automatic with explicit D/N/R, sequential with assisted clutch, and manual with player clutch. Brake must never select reverse. Idle engine speed must not cause propulsion. Keyboard steering holds its angle at rest and returns progressively while moving. The five saved sensitivity levels change active turning speed, with level 3 matching the previous rate. Saved bindings remain authoritative.

Handbrake supports Hold and Toggle, with Toggle retained for older saves. Rear lock/sliding forces and approximately 0.22-second recovery are implemented. The keyboard handbrake also works with wheel driving. Dedicated wheel-button handbrake mapping remains pending.

The owner reports T248 Base SW 2.0 and T3PA pedals. Active axes are steering 0, accelerator 5, brake 1 and clutch 6. Hardware testing of the fix is pending. External shifter support is deferred. Wheel disconnect pauses driving. Vendor-based device detection may be ambiguous with multiple Thrustmaster devices.

UI uses dark cards, mint accents and S-curve transitions. Settings include separate graphics, wheel/control and keyboard screens. Display changes require Keep/Revert with a 15-second rollback. Deferred UI actions avoid changing the viewport during HUD drawing.

## Physics and asset cautions

The chassis is simulated in Unreal with custom per-wheel forces. Portable helpers use SI units and forces convert when applied to Unreal. Suspension includes preload, compression/rebound damping, bump stops and anti-roll support. Tire handling includes combined grip, load sensitivity, low-speed stabilization, braking and drag.

The full tire/contact solver runs per game frame even though Chaos substepping is enabled. Independent unsprung mass, linkage dynamics and wheel inertia are not simulated. Handling, curb behavior and frame-rate sensitivity require integrated driving tests.

`Tools/prepare_vehicle.py` is a legacy Ciaz converter that can overwrite later gauge/mirror splits. Inspect and preserve those splits before any conversion. Swift preparation uses `Tools/prepare_swift.py`. Original editable models and reference videos should be preserved separately from optimized runtime data.

Runtime meshes use little-endian magic `0x43505A31`, vertex/index counts, eight float32 values per vertex for position/normal/UV, then uint32 indices. Coordinates are centimetres, X forward, Y right, Z up. Animation groups are -1 body, 0–3 wheels, 4 steering, 5 speed, 6 RPM and 7–9 mirrors. Moving parts with multiple materials must share pivots.

## Release and decision history

| Stage | Durable result |
| --- | --- |
| Prototype to 1.1 | Initial editable game, custom driving, wheel input, ten courses and saved progression. Early material-header and deferred graphics-action fixes |
| 1.2–1.3 | Mouse cameras, speed-dependent steering return, corrected steering-wheel pivot and cockpit FOV |
| 1.4–1.6 | Supplied obstacle courses, fitted chassis collision and animated speed/RPM needles |
| 1.7 | Functional mirrors, removal of idle propulsion and improved interior materials |
| 1.7.1 | Animated UI, separate settings, graphics rollback, physics review and packaging workflow |
| 1.7.2 | PBR materials iteration. Historical archive retained a 1.7.1 filename |
| 1.7.3–1.7.5 | Curb/suspension work, 110 hp tuning, rear handbrake behavior and Hold/Toggle selection |
| 1.7.6 | Swift added with its own profile and assets |
| 1.7.7 | Loader/schema, calibration, UI lifecycle, reset and setup validation fixes |
| 1.7.8 | Rest-stability fix blends shoulder contact load points and reduces low-speed stopping gain to 0.5 |
| 1.7.10 | Three static parked-car obstacles use render-mesh collision |
| 1.7.11 | Main-menu ride height, keyboard steering sensitivity and parking bounds based on the four wheel centres |
| 1.7.12 | Barrier bend added as Level 11, with progression and menus using the loaded course count |
| 1.7.13 | Level 11 barrier and parked-car clearance reduced, rear shortcut closed, and finish bay tightened |
| 1.7.14 | Level 11 ends its outer and inner parked-car rows with Car3 and Car2 in place of eight cones |
| 1.7.15 | Restored full Swift source geometry, wheel proportions and texture resolution |
| 1.7.16 | Added Level 12, Full house, with the supplied FBX for painted bay lines |
| 1.7.17 | Android-only buttons or touch wheel, left-side pedals and touch menu navigation |
| 2026-11-04 | Project linked and initial import pushed to GitHub main. Owner approved durable context files and relevant sub-agent delegation |

The historical preference was to advance beta versions after meaningful development iterations. Context-only maintenance keeps the game version unchanged.

## Verification evidence and limits

Historical [1.7.7 audit](Docs/AUDIT_1.7.7.md) and [results](Docs/AUDIT_1.7.7_TEST_RESULTS.json) report seven portable C++ suites passing with GCC C++17, warnings as errors, AddressSanitizer and UndefinedBehaviorSanitizer. Leak detection was disabled by the earlier environment. Both vehicle asset audits passed, with tire/drivetrain stress coverage. These are recorded historical runs.

[1.7.8 fix notes](Docs/FIX_1.7.8.md) report 896 portable rest-stability combinations covering both cars, 30–240 FPS, jitter, brakes, gears and estimated roll inertia. The fix addresses discontinuous shoulder load placement and excessive low-speed correction gain. Its `ShoulderWeight` and `LowSpeedStopGain` code is present in the local source. Unreal verification remains outstanding in the supplied record.

Portable checks live in `Tests`, including `rest_stability_tests.cpp`, drivetrain/dynamics/suspension/handbrake/UI suites, and Python asset audits. Inspect individual test prerequisites before running them.

During this context task, only documents, configuration, source references and Git state were inspected. No portable test suite, Unreal compilation, shader generation, cooking, gameplay, T248 feedback test or GPU benchmark was run. Earlier owner builds do not establish verification of the current cumulative version.

## Build reference for future authorized work

Close Unreal before setup. `SetupProject.cmd "D:\Unreal\UE_5.4"` builds the editor module, generates materials/assets and map, then opens the editor. A second argument `--no-editor` skips opening it. Source-only copying may miss required generated assets. Preserve `Saved/SaveGames` when migrating.

`PackageWindows.cmd "D:\Unreal\UE_5.4"` runs the setup/Shipping workflow. The expected output launcher is `Packaged\Windows\CiazParking.exe`. Distribution requires the complete output folder and applicable runtime prerequisites. The supplied record does not establish a successful current Shipping build.

## Outstanding work awaiting user direction

- Verify calibration on the owner hardware.
- Compile and test the current Unreal project, including both cars, parking completion, collisions, progression, graphics rollback and reset behavior.
- Validate parked-car stability, rear grip, slopes, curb interaction and handbrake recovery with gameplay evidence.
- Exercise T248 calibration, input, feedback and disconnect/reconnect behavior.
- Benchmark target hardware and inspect Swift seams, draw calls, mirror cost and potential distance LODs.
- Integrate replacement Ciaz dashboard artwork and inspect a future SUV model when supplied.
- Guide standalone packaging and later distribution/mobile exploration when requested.

## Source provenance and continuity

Owner-supplied references read on 2026-11-04 were `CiazParking_Beta_1.7.8_Rest_Stability_Update/README.md` and `CiazParking_Complete_Development_History_Prototype_to_Beta_1.7.7.md` from Downloads. Their essential project context is captured here so a future account can continue from the repository. Their historical directions do not replace current user authorization.

Local source, configuration, [rest-stability notes](Docs/FIX_1.7.8.md), [audit](Docs/AUDIT_1.7.7.md) and other `Docs` records supply implementation detail. Consult the relevant code before changing a system. Update this document and the handoff status after meaningful work, including what was tested and what remains unresolved.

## Calibration fix, 2026-11-04

Validation already checks only four assigned axes. Old defaults 0/1/2/5 included an inactive axis on the owner device. Defaults and malformed-save fallback now use 0/5/1/6. Uncalibrated legacy-default saves migrate; custom and calibrated mappings are preserved. Travel errors identify the affected control and axis. HUD clarifies unused axes are ignored. Changes are local and unpublished. Unreal 5.4 editor Development Win64 build passed with exit code 0. All seven build actions completed, including linking. Git diff whitespace check passed. Independent code review found no blocking issues. Hardware testing remains pending. If assignments were already 0/5/1/6, another calibration check was the blocker; improved diagnostics will identify it.

Controls/Wheel follow-up for Beta 1.7.9. The HUD now shows four named meters driven by the saved assignments and hides unassigned raw slots. Assignment buttons show the DirectInput field and axis index. Slots 2, 3, 4 and 7 are Z, Rx, Ry and Slider 2, inactive on the owner's setup. Unreal editor Development Win64 build passed. In-game visual and hardware checks are pending.

## Swift archive comparison, 2026-11-04

The owner supplied `Suzuki Swift.zip` (SHA-256 `26c56fee1f99a52522bcbe2cbf6616636e62911f52a3596123e07ae626807584`). The archive contains an FBX 7400 model and textures. Ran [prepare_swift.py](Tools/prepare_swift.py) against the extracted FBX in ignored staging. All 99 converted mesh buffers match [the installed Swift data](Content/SwiftData/vehicle.json) byte for byte. All 33 exported textures have identical decoded pixels, all 68 material definitions match, and all 48 collision hulls match within 0.00001 cm. Wheel pivots are exact. The steering pivot and gauge/steering axes differ only in floating-point rounding. Kept the existing Swift assets and Beta 1.7.9 because the supplied archive produces the same runtime model.

Fresh checks passed. `Tests/audit_swift.py` passed against both the existing and staged asset sets. `Tests/audit_project.py` passed against the checkout. The 68 Unreal material packages and 13 manifest base-texture packages are present. This task did not run Unreal, gameplay, hardware or performance checks. The local knowledge-graph edit is uncommitted and unpublished. Next actionable step for a different Swift is to supply an archive with different geometry or textures and repeat the staged comparison.

## Parked-car mesh collision, 2026-11-04

[The obstacle importer](Tools/import_obstacles.py) uses Complex as Simple for Car1, Car2 and Car3 and skips automatic simple collision generation on their FBX imports. The obstacle components already spawn static with query and physics blocking. The three existing mesh packages were updated directly in Unreal 5.4.4. The editor removed their old simple hulls and rebuilt and saved their collision bodies, so current checkouts use the new collision without reimport. The curb corner retains its existing mesh collision. The asset audit and Git whitespace check passed. The commandlet world trace returned no hits. A follow-up unattended editor script verified all LOD0 sections have collision enabled and compared 81 simple and complex component rays per model after rebuilding the bodies. All hit locations and misses matched. Car1 had 75 hits and six misses, Car2 had 77 hits and four misses, and Car3 had 74 hits and seven misses. The same script checked the other obstacle collision modes. Next step is an in-game low-speed contact check. This task does not change C++ or measure performance. Changes are uncommitted and unpublished.

## Level 11 parked-car rows, 2026-11-05

[ParkingLevels.inl](Source/CiazParking/ParkingLevels.inl) and [level_layouts.json](Docs/level_layouts.json) replace four outer cones with Car3 at (1181, 2296) and four inner cones with Car2 at (643, 2052), both at yaw −90°. These placements follow the updated diagram and use the tightened 1.7.13 row alignment. The existing rear shortcut barrier, spawn, and finish remain in place. Level 11 has eight parked cars and 142 obstacles overall.

The layout checks passed for all eleven courses. A source-to-JSON comparison matched both car rows, and neither added car footprint overlaps another obstacle. The same approximate steering search found a route for Ciaz and Swift footprints. The asset audit and Git whitespace check passed. UnrealBuildTool's normal Development Editor Win64 build stopped before compiling because Live Coding was active. Next step is to compile via Ctrl+Alt+F11 in Unreal or close the editor and rebuild, then drive Level 11. No integrated, hardware or performance checks ran. Work is local, uncommitted and unpublished.

## Level 11 difficulty tuning, 2026-11-05

[ParkingLevels.inl](Source/CiazParking/ParkingLevels.inl) and [level_layouts.json](Docs/level_layouts.json) reduce the straight entry clearance from 516 to 406 cm, pull the bend and parked-car/cone rows inward, and reduce the bay from 310 × 530 to 270 × 500 cm. Five outer bend barriers are 350 cm long so the tighter curve does not overlap their ends. A crosswise barrier replaces the two rear cones and closes the shortcut behind the spawn. The revised course has 148 obstacles.

[validate_levels.py](Tests/validate_levels.py) passed with the Unreal bundled Python for all eleven spawn and bay footprints. Additional checks matched the documented and runtime obstacle layouts and found no overlaps among the Level 11 interior obstacles. An approximate geometric search with 449 × 190 cm and 384 × 185 cm car footprints and assumed 580 and 540 cm rear-axle turning radii respectively found a forward route through the bend and a forward/reverse finish approach. Git whitespace check passed. These checks do not simulate Chaos or steering inputs. Next step is an in-game drive with both cars to assess the difficulty. Work is local, uncommitted and unpublished.

The project asset audit passed. The final UnrealBuildTool run with `CiazParkingEditor Win64 Development -Project=CiazParking.uproject -WaitMutex -NoPCH -MaxParallelActions=2` compiled and linked the editor module successfully using the pinned MSVC installation. No in-game, hardware or performance test ran.

## Level 11 introduction, 2026-11-04

[ParkingLevels.inl](Source/CiazParking/ParkingLevels.inl) and [level_layouts.json](Docs/level_layouts.json) record Barrier bend from the owner's Level 11 diagram. The plan uses an approximate 2 cm per image pixel with up mapped to +X and right mapped to +Y. Level 11 uses a 58 m square ground slab, 21 barriers, six parked cars, ten cones and 112 perimeter wall sections. Its barrier footprints are scaled to 400 × 150 cm using the supplied mesh, keeping its height. The finish bay faces toward the top of the plan. The shared course count drives save validation, Continue, level selection and the next-level action. A save with 10 unlocked courses can unlock 11 by completing Level 10.

UnrealBuildTool passed with `CiazParkingEditor Win64 Development -Project=CiazParking.uproject -WaitMutex -NoPCH -MaxParallelActions=2` using the installed MSVC 14.38.33130 toolchain path. The first compiler run rejected the qualified vector constant in the lambda's default argument. The rebuild passed after replacing it with an explicit zero initializer.

The spawn and full finish bay footprint checks passed for all eleven layouts using the Unreal bundled Python and [validate_levels.py](Tests/validate_levels.py). A separate comparison matched the 149 Level 11 obstacle placements between C++ and JSON. A sampled forward/reverse geometric search with an assumed 540 cm rear-axle turning radius and a 450 × 190 cm car footprint found a clear route through the bend to the bay. The project asset audit and Git whitespace check passed. Next step is to drive the turn and final approach in both cars, complete Level 10, then reload and confirm Level 11 remains unlocked. No hardware or performance measurements were made. Work is local and unpublished.

## Vehicle settings and parking, 2026-11-04

The main menu shows a stock-to-+8 cm slider directly below vehicle selection. It saves one-centimetre selections on release and applies to both cars at level start. Older saves inherit the configured pawn height. Keyboard settings offer five saved turning rates from 0.35 to 0.95 normalised units per second, with 0.65 at level 3. Wheel input and the keyboard's return and centre-key behaviour retain their previous logic.

[ParkingGameMode.cpp](Source/CiazParking/ParkingGameMode.cpp) projects each suspension-adjusted wheel centre into the bay plane using the loaded vehicle geometry. [ParkingCore.h](Source/CiazParking/ParkingCore.h) checks those four points against the rotated marker. The alignment limit, upright and stationary checks, collision gate and two-second hold still apply. [Portable core tests](Tests/core_tests.cpp) exercise overhang, one wheel out, a rotated marker and all five keyboard rates. MSVC 14.38 portable core, dynamics, Swift and rest stability suites passed. The project asset audit and Git whitespace check passed. Unreal 5.4.4 Development Editor Win64 built and linked successfully using `-NoPCH -MaxParallelActions=2` after the original parallel PCH build stalled. Added the existing wheel timing code's explicit PlatformTime include for the no-PCH build. Next step is to exercise slider persistence, steering selection and bay overhang in-game. No integrated playtest, hardware test or performance measurement ran. Changes are uncommitted and unpublished.

## Android packaging launcher follow-up

Found the cooked APK under `Packaged/Android/52b8c9d739874e51b16d94e3ed746552/CiazParking-arm64.apk` and a byte-identical copy under `Binaries/Android/CiazParking-arm64.apk`. Both are 232.4 MiB, contain `assets/main.obb.png`, and hash to SHA-256 `7E41221D8C24506276E4F2FF227A064247DAE2CA6F07C583F137EC08B2A07114`. The owner provided a GitHub asset link, but this local lookup did not independently verify the remote asset. Next step is device testing. Source changes remain uncommitted.

Gradle's direct-build `assembleDebug` subsequently succeeded and produced an APK under `Binaries/Android`. ZIP inspection confirmed it lacks `assets/main.obb.png` because the direct build did not cook and stage game content. Use [PackageAndroid.cmd](PackageAndroid.cmd) for the complete cooked APK. Added ignore entries for the five Java files Unreal generated under `Build/Android/src`.

Android Clang reported `-Werror,-Wmisleading-indentation` on the nested corner loops in [ParkingCore.h](Source/CiazParking/ParkingCore.h). Added explicit loop blocks and separated the final return, preserving the footprint calculation. Refreshed the existing user SDK/JDK environment into the build process, then ran UnrealBuildTool `CiazParking Android Development -Project=CiazParking.uproject -WaitMutex`. All seven native actions compiled and linked with Clang 14.0.6. Portable touch and core tests passed. The initial post-link step selected absent SDK 33 and Build-Tools 37.0.0, so [AndroidEngine.ini](Config/Android/AndroidEngine.ini) now selects the installed SDK 34 and Build-Tools 34.0.0 documented for UE 5.4.4. Scoped Git whitespace check passed with `cr-at-eol` for the tracked CRLF ignore file. The full cooked package and GitHub upload still need verification. No version change. Changes are local and unpublished.

The owner reached the release prompt and reported an invalid tag error. Git accepts `android-v1.7.17`. The old script suppressed the Git diagnostic and treated any Git failure as invalid syntax. It now resolves Git on PATH, at the default Git for Windows path, or at the installed Codex runtime path, and reports a missing Git executable separately. The mock packaging fixture accepted the example tag and reached simulated publication with Git deliberately removed from PATH. The real engine Android target file is now present. No actual package or release was run in this check. Changes are local and unpublished.

Fresh packaging diagnosis reproduced exit 1 before Turnkey. Epic Launcher manifest and Build.version confirm the selected engine is the correct installed UE 5.4.4, but `Engine/Binaries/Android/UnrealGame.target` is absent. The previous direct UnrealBuildTool log independently reports missing Android target files. Standard Android Studio and SDK locations, Studio registry entries, and process/user/machine Android SDK, NDK and JDK environment variables were absent. GitHub CLI was not found on PATH or at its usual install path, which separately blocks the combined package-and-upload command. Compared the official UE 5.4.4 requirements against the installed SetupAndroid.bat and found that its no-argument defaults still select SDK 33 and Build-Tools 33.0.1. [README](README.md) now records explicit SDK 34, Build-Tools 34.0.0, CMake 3.22.1 and NDK 25.1.8937393 arguments and a standalone Turnkey verification command. Next step is installing the Android target component and configuring the SDK. No install, package, or release ran in this diagnosis.

The owner reported that pressing a key still closed the window. Replaced the one-key pause with a persistent `cmd /d /k` prompt on both interactive outcomes. Verified that the no-argument failure path accepted a command and stayed open until `exit`, that the explicit-tag failure returned 1 without opening a prompt, and that `--help` returned 0. The Unreal Android target remains missing. No APK or release was created.

Double-clicking [PackageAndroid.cmd](PackageAndroid.cmd) previously exited immediately because the release tag was missing. A no-argument launch now runs preflight checks, prompts for a fresh tag when prerequisites are ready, and pauses at success or failure. Explicit CLI invocations retain non-interactive exit codes. Verified that the no-argument path pauses and shows the missing Unreal Android component, `--help` exits successfully, and the mock explicit-tag path still reaches simulated publication. The Android component remains the next blocker. No actual APK or release was created. Changes are local and unpublished.

## Android APK packaging and publication, 2026-11-05

[PackageAndroid.cmd](PackageAndroid.cmd) takes a fresh GitHub release tag and an optional Unreal path. It checks the Android installation, map and marking assets, GitHub CLI authentication, and availability of the checkout's base commit on `Masterkumail-718/Car-Parking`. It runs Turnkey SDK verification and UAT `BuildCookRun` with Android ETC2 Development, archives to a unique directory under `Packaged/Android`, and uploads one verified APK to a prerelease with `gh release create`. Release notes disclose that the APK can include local changes beyond the base commit. The script does not commit or push source changes. GitHub CLI requires repository write access.

[AndroidEngine.ini](Config/Android/AndroidEngine.ini) sets package ID `com.ciazparking.game`, embeds game data in the APK, disables bundle generation and disables Android File Server for the sideload build. [AndroidGame.ini](Config/Android/AndroidGame.ini) puts the raw Ciaz and Swift data into Android UFS staging so the APK contains the data read by the existing loader. Windows staging retains its NonUFS directories.

`PackageAndroid.cmd --help` passed. `PackageAndroid.cmd android-v1.7.17` stopped at the missing Android target component before publishing. GitHub CLI was also absent from PATH. In an ignored sandbox fixture, mock UAT and GitHub CLI calls verified the script aborts on packaging failure or a missing embedded OBB and reaches publication only for a valid APK structure. No actual APK, GitHub release or device test was produced. Next step is to install Unreal's Android platform component, configure the Android SDK, sign in to GitHub CLI, and run the command with a fresh tag. No game version change was made for this packaging workflow.

## Android touch controls, 2026-11-05

[ParkingTouch.h](Source/CiazParking/ParkingTouch.h) defines shared hit areas, per-finger ownership and wheel rotation. [ParkingGameMode.cpp](Source/CiazParking/ParkingGameMode.cpp) and [ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp) gate touch input and rendering with `PLATFORM_ANDROID`. [AndroidInput.ini](Config/Android/AndroidInput.ini) disables Unreal's stock virtual joysticks for Android. The two modes are selectable in Controls and persist in an additive save field that defaults to buttons. Both layouts use multitouch accelerator and brake on the left and steering on the right. Android uses the existing automatic transmission with explicit D/N/R and a toggle handbrake. Brake takes precedence over accelerator, and reversing still requires deliberate selection. Pause and application backgrounding release held driving inputs. Windows retains its mouse, keyboard, transmission and DirectInput paths.

[touch_tests.cpp](Tests/touch_tests.cpp) and the existing core tests passed under the pinned MSVC with `/std:c++17 /EHsc /W4 /WX`. Project asset audit and scoped Git whitespace checks passed. The normal Unreal Win64 editor build ran header generation but stopped because Live Coding was active. The Android Development target stopped before compilation because this Unreal installation lacks Android target files. Next step is to enable Unreal's Android platform component and test a build on a touchscreen device, including simultaneous steering and braking, menu taps, mode persistence and pause/resume. Work is local, uncommitted and unpublished.

MSVC `/Zs` checks against Unreal 5.4.4 headers passed for the GameMode and HUD with the normal desktop branch and with the Android branch enabled in temporary source copies under `Saved`. The forced-branch check caught an exported constant declaration and a shadowed member name, both fixed before rechecking. This check does not link or substitute for an Android build.

## Level 12, 2026-11-05

[ParkingLevels.inl](Source/CiazParking/ParkingLevels.inl) and [level_layouts.json](Docs/level_layouts.json) define four rows split into three blocks, with 59 parked cars, two cones, 96 perimeter wall segments and 88 marking strips. The lower-right spawn points into the main aisle and the upper-left finish faces down the plan. Dimensions were estimated from the diagram and fitted to the existing car meshes. The existing save and progression flow unlocks Level 12 after Level 11.

[Marking.fbx](Tools/ObstacleSource/Marking.fbx) matches the owner source byte for byte. The targeted Unreal commandlet import generated [the 200 × 10 × 0.25 cm marking mesh](Content/Obstacles/SM_Marking.uasset) and [its material](Content/Obstacles/Materials/MI_Marking_Marking.uasset). The importer reported zero errors and one missing smoothing-group warning. The regular setup imports the same source via [the obstacle importer](Tools/import_obstacles.py). Runtime strips are resized to fit the bays and use no collision or shadow.

The Unreal bundled Python ran [the layout validator](Tests/validate_levels.py) and the project asset audit successfully. A sampled geometric search found a route for both car footprints through the aisle and into the bay using assumed 430 and 400 cm turning radii. Git whitespace checks passed. Next step is an in-game drive and visual check of markings and finish alignment. No hardware or performance measurements ran. Changes are local, uncommitted and unpublished.

The C++ and JSON parked-car placements matched, and all 59 parked car footprints clear other solid objects. The final UnrealBuildTool run with `CiazParkingEditor Win64 Development -Project=CiazParking.uproject -WaitMutex -NoPCH -MaxParallelActions=2` compiled and linked using the pinned MSVC path. The first run caught a missing brace around a logging macro and a local name that shadowed a game mode member. Both were corrected before the passing rebuild.

## Full-detail Swift replacement, 2026-11-05

The owner showed distorted body panels and confirmed that the model should be used as supplied, without simplification. The 2026-11-04 byte-for-byte comparison established that the old converter was reproducible. It did not establish that its 267,669-triangle output was faithful to the FBX. Beta 1.7.15 removes simplification, nearest-vertex UV transfer, wheel resizing and texture downsampling from [the Swift converter](Tools/prepare_swift.py). The same archive yields 852,081 triangles, 521,229 vertices and 99 animated/material sections. Axis conversion, origin placement, exact duplicate corner welding, mirror render-target UVs and DirectX normal convention remain necessary runtime adaptations. Paint tints now follow the FBX diffuse values. The existing Unreal material system interprets the supplied maps. The physical wheel radius follows the source tread, and the chassis collision is regenerated in its translated frame.

[The runtime loader](Source/CiazParking/CiazPawn.cpp) builds tangents by indexed triangles using the exported normals. This avoids the earlier positional overlap scan on full-detail sections. Unreal 5.4.4 Development Editor Win64 built and linked using the pinned toolchain with `-NoPCH -MaxParallelActions=2`. The Swift and project asset audits passed. A targeted Unreal commandlet reimport verified and saved both original 2048-pixel paint maps. Standalone DX11 started with Swift selected using an isolated copy of the saved profile. A separate Unreal runtime object listing confirmed 99 Swift visual sections and one chassis component. The original save hash matched after the isolated run. The game window closed during visual capture, so close-up exterior verification remains pending. Next step is to inspect the body from the front and rear in a normal gameplay session. No driving or performance benchmark was run. Changes are uncommitted and unpublished.


## Wheel force-feedback response, 2026-11-05

The owner requested reversed force direction and a more responsive return. [ParkingCore.h](Source/CiazParking/ParkingCore.h) now shares the keyboard return-rate curve with a portable `WheelCenteringForce` helper. [ParkingGameMode.cpp](Source/CiazParking/ParkingGameMode.cpp) uses positive rather than negative steering demand before applying the existing saved feedback-invert toggle. Moving-speed gain rises at 0.22 per m/s instead of 0.08 and reaches unity rather than 0.8, keeping the saved strength and absolute 35% ceiling. At 1 m/s the demand is 2.75 times the previous value. This is authored tuning, not measured hardware response. Stationary return remains zero, consistent with keyboard hold at rest. Wheel input remains directly tied to calibrated physical position.

[WheelDevice.cpp](Source/CiazParking/WheelDevice.cpp) now supplies a nonzero one-axis Cartesian direction for the constant-force effect. The previous vector was zero. Existing force shutdown, foreground guard, calibration, save fields and invert setting are preserved. No assets, saves or packaging were changed. Version remains Beta 1.7.17; the older 1.7.8 in DefaultGame.ini is pre-existing metadata drift.

Fresh portable checks: pinned MSVC `/std:c++17 /EHsc /W4 /WX` compiled and ran [feedback_tests.cpp](Tests/feedback_tests.cpp) and [core_tests.cpp](Tests/core_tests.cpp), outputs under ignored `Saved`. Feedback coverage includes requested polarity, stronger low-speed gain, reverse-speed symmetry, invert, zero strength, stationary/centred demand, saturation and nonfinite inputs. Both passed. Unreal bundled Python ran `Tests/audit_project.py`: passed. Scoped `git diff --check`: passed. Unreal 5.4.4 `CiazParkingEditor Win64 Development -Project=D:/Games/CiazParking/CiazParking.uproject -WaitMutex -NoPCH -MaxParallelActions=2` compiled and linked successfully (13 actions) using MSVC 14.38.33130. The sandboxed attempt could not access the engine; the authorized elevated retry passed. Read-only review found no additional correctness issues.

Next actionable step is a physical T248 test: compare release return at low and moderate driving speeds, check both steering directions and the saved invert toggle, then verify zero force when paused, out of focus or disconnected. No playtest, hardware test or performance measurement has run. Current changes and the earlier accumulated project work are local, uncommitted and unpublished.




## Mouse-look sensitivity, 2026-11-05

Added five saved mouse-look sensitivity levels under Settings > Controls / Wheel > Keyboard Bindings, alongside keyboard steering sensitivity. [ParkingSave.h](Source/CiazParking/ParkingSave.h) adds `MouseSensitivity=3`, retaining the original speed for new and older saves. [ParkingGameMode.cpp](Source/CiazParking/ParkingGameMode.cpp) clamps loaded values to 1–5, persists menu selections and scales both mouse axes by 0.5x, 0.75x, 1x, 1.25x or 1.5x before the existing cockpit/chase camera path. Mouse deltas remain independent of frame time, and camera angle limits and look-back behavior remain intact. [ParkingGameMode.h](Source/CiazParking/ParkingGameMode.h) reserves actions 641–645; [ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp) shows the selected level and default. [README.md](README.md) documents the menu path and range. No version increment; Beta 1.7.17 retained.

Fresh checks: `Tests/audit_project.py` with Unreal bundled Python passed; scoped Git whitespace check passed. Unreal 5.4.4 `CiazParkingEditor Win64 Development -Project=D:/Games/CiazParking/CiazParking.uproject -WaitMutex -NoPCH -MaxParallelActions=2` compiled and linked successfully (9 actions) using pinned MSVC 14.38.33130. No new portable tests were added for this simple saved scalar/UI change. No in-game mouse, menu visual, save/restart, hardware or performance testing ran. Next step is to verify both camera modes at levels 1/3/5 and restart to confirm persistence. All current and prior accumulated work remains local, uncommitted and unpublished. Force-feedback physical acceptance remains pending.



## Interior FOV limits, 2026-11-05

Owner requested a minimum 70-degree and maximum 150-degree view setting. [CiazPawn.h](Source/CiazParking/CiazPawn.h) defines shared interior FOV limits used by the runtime setter in [CiazPawn.cpp](Source/CiazParking/CiazPawn.cpp), saved-value validation and slider actions in [ParkingGameMode.cpp](Source/CiazParking/ParkingGameMode.cpp), and the graphics slider mapping/fill in [ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp). Existing values below 70 clamp to 70 on load; the default remains 85. Existing save fields are retained. Chase and mirror camera settings remain as before; this request updates the existing interior FOV setting.

[ParkingGameMode.h](Source/CiazParking/ParkingGameMode.h) reserves slider actions 700–780. Extending the old 400-based range would collide with save-on-release action 480 at the new maximum. The release action stays 480 and still persists the selection. HUD help explicitly displays 70–150 degrees. Beta 1.7.17 retained.

Fresh validation: scoped Git whitespace check and `Tests/audit_project.py` with Unreal bundled Python passed. The first Win64 editor build rejected two static constants declared together in an exported class (C2487); declarations were separated and the Unreal 5.4.4 rebuild passed (7 actions) using pinned MSVC 14.38.33130: `CiazParkingEditor Win64 Development -Project=D:/Games/CiazParking/CiazParking.uproject -WaitMutex -NoPCH -MaxParallelActions=2`. [README.md](README.md) documents the new range. No in-game visual check, save/restart test, hardware test or performance measurement ran. Next step is to drag both endpoints, check 70/150 labels and camera appearance, release at 150, restart, and confirm persistence. All work remains local, uncommitted and unpublished.

## Swift cockpit camera, 2026-11-05

The owner reported that the full-detail Swift camera was too close to the steering wheel. [ConfigureVehicle](Source/CiazParking/CiazPawn.cpp) now places the Swift eye at (-20, 33, 46) cm instead of (15, 33, 40), moving 35 cm rearward and 6 cm upward. The forward axis is +X and the source steering hub is near (25.4, 32.7, 15.6), so the former camera sat only about 10 cm behind the hub. This is authored camera placement. Unreal 5.4.4 Development Editor Win64 compiled and linked successfully using the pinned MSVC toolchain with -NoPCH -MaxParallelActions=2. The project asset audit and whitespace check for the changed source and version files passed. The broader checkout whitespace check reports existing CRLF differences in the Swift vehicle manifest. In-game framing acceptance remains pending. Changes are uncommitted and unpublished.


## Mirror brightness, 2026-11-05

Owner reported dark mirror views. [CiazPawn.cpp](Source/CiazParking/CiazPawn.cpp) now overrides exposure compensation to +0.4 EV with full post-process blend weight on each of the three scene captures, shared by Ciaz and Swift. This is a modest authored brightness adjustment before the LDR tone mapping; the main camera, mirror angles, resolution and capture cadence are unchanged. No material regeneration is needed. Beta 1.7.18 retained for this small tuning change.

Fresh validation: Unreal 5.4.4 CiazParkingEditor Win64 Development compiled and linked successfully with `-WaitMutex -NoPCH -MaxParallelActions=2` and the pinned MSVC directory. Initial sandbox build could not access the engine; the elevated retry passed. Unreal bundled Python `Tests/audit_project.py` passed, as did `git diff --check -- Source/CiazParking/CiazPawn.cpp`. No portable gameplay tests, playtest, hardware test or performance measurement ran. Next step: inspect all three mirrors in both cars in gameplay and confirm the brightness is comfortable. This change and earlier accumulated work remain local, uncommitted and unpublished.


## Parking goal pointer, 2026-11-05

Owner requested an arrow at the top middle throughout driving and supplied Pointer Arrow.fbx. [ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp) draws a fixed mint pointer at the top centre using the active player camera yaw and the horizontal vector from the vehicle to the current bay. Ahead/right/behind map to up/right/down, including cockpit mouse look, chase orbit and look-back. Within 1 cm of the bay centre, the pointer uses the required parking heading so it remains defined and visible. Menus retain their existing full-screen presentation. The pointer skips the HUD reveal fade. The desktop controls hint moved right to avoid overlap.

[The original FBX](Tools/UI/Pointer%20Arrow.fbx) is preserved in the repository. [export_arrow.py](Tools/UI/export_arrow.py) projects its upper cap into eight Canvas triangles in [GoalArrow.inl](Source/CiazParking/GoalArrow.inl), avoiding scene captures, runtime FBX loading or material/cooking dependencies. Blender 5.1 ran the exporter successfully with --background --factory-startup. Beta advances to 1.7.19 in the HUD, descriptor and README; the pre-existing DefaultGame.ini 1.7.8 metadata drift is retained.

Fresh validation: project asset/source audit passed; scoped HUD whitespace check passed. Unreal 5.4.4 CiazParkingEditor Win64 Development compiled and linked successfully using the pinned MSVC 14.38.33130 directory and -WaitMutex -NoPCH -MaxParallelActions=2. The initial build caught a missing GWhiteTexture declaration; including GlobalRenderResources.h fixed it. Direct HUD compilation and the full rebuild passed. Read-only independent review found no blockers. No portable gameplay suite, in-game visual/play test, hardware test or performance measurement has run for this change. Docs/VALIDATION.md's statement that Unreal is unavailable describes the historical authoring environment, superseded by fresh build evidence in this graph. Next step is to verify pointer direction in both cameras, look-back, retry and level changes. This task and earlier accumulated work are local, uncommitted and unpublished; no commit or push was requested.

## Interior camera controls, 2026-11-05

Beta 1.7.20 adds Settings > Interior Camera in [ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp), with live cockpit preview through a lighter overlay. Direction buttons move the view along vehicle axes in 2 cm steps (offset range -60 to +60 cm), adjust pitch/yaw offsets in 2 degree steps, and change the existing 70-150 degree FOV by one degree. Reset restores zero offsets and 85-degree FOV. Pitch offsets are bounded to -50/+65 degrees so the default -5 degree pitch stays within existing head-look limits; yaw offsets use -135/+135 degrees. Large offsets may put the camera through interior geometry and are user adjustments, not measured ergonomic positions.

[ParkingSave.h](Source/CiazParking/ParkingSave.h) adds zero-default translation/rotation fields, preserving older saves. [ParkingGameMode.cpp](Source/CiazParking/ParkingGameMode.cpp) validates nonfinite/out-of-range loaded values, saves each adjustment and applies settings at startup and vehicle changes. [CiazPawn.cpp](Source/CiazParking/CiazPawn.cpp) adds offsets to each car's authored cockpit position, preserves saved orientation across level resets, and retains temporary mouse look and chase controls. Settings are shared across vehicles, matching the existing shared FOV. Opening this menu deliberately selects cockpit view. README, HUD and project descriptor identify Beta 1.7.20. Existing DefaultGame.ini metadata drift remains unrelated.

Fresh asset audit (`Tests/audit_project.py` with Unreal bundled Python) and scoped source/version whitespace checks passed. Unreal 5.4.4 `CiazParkingEditor Win64 Development -Project=D:/Games/CiazParking/CiazParking.uproject -WaitMutex -NoPCH -MaxParallelActions=2` compiled and linked successfully using pinned MSVC 14.38.33130. Initial compilation caught a shadowed HUD row coordinate; renaming it fixed the error and the rebuild passed. No portable gameplay suite, in-game preview or save/restart test, Android build, hardware test or performance measurement ran. Next step is to check each direction, reset and persistence in both vehicles. Current and earlier work remain local, uncommitted and unpublished.

## Concrete walls and proximity shading, 2026-11-05

Beta 1.7.21 replaces the flat grey wall with Poly Haven Concrete Wall 001 by Dimitrios Savva and Rico Cilliers (CC0). Original 2048-square BaseColor, DirectX normal and packed ARM PNGs, exact URLs and SHA-256 hashes are included under [ConcreteWall001](Tools/PBRSource/ConcreteWall001/SOURCE.json). [build_wall.py](Tools/build_wall.py) uses engine world-aligned colour, normal and mask functions at the scan's 150 cm width, with world-space normal output. The existing MI_Wall_Wall receives the new parent; no obstacle mesh/collision/placement changes. [setup_unreal.py](Tools/setup_unreal.py) builds the wall after obstacle import; [import_obstacles.py](Tools/import_obstacles.py) preserves that parent on subsequent targeted wall imports. Targeted asset generation updated the material, three textures and Parking map without regenerating unrelated vehicle assets.

The shared daylight now uses 0.8 sky fill (formerly 1.05), three shadow cascades over 120 m, shadow bias 0.35 and contact-shadow length 0 (the initial 0.08 setting was removed after the artifact investigation below). [ParkingGameMode.cpp](Source/CiazParking/ParkingGameMode.cpp) adds an unbound runtime post-process volume with world-space SSAO radius 70 cm, intensity 0.85, power 1.4 and quality 60. The saved AO switch now also overrides AmbientOcclusionMaxQuality after scalability, so Low post-processing cannot silently disable enabled AO. Selecting any preset enables AO; loading existing saves preserves the saved switch, including Off. Contact shadows are now disabled at every shadow quality after the verified artifact correction below. Anisotropy uses 4/8/16 at Low/Medium/High textures. DX11/SM5, existing 1 GB texture pool, vehicles, controls and save fields are preserved. The wall graph uses roughly nine texture samples and three streamed 2K maps; GPU cost remains unmeasured. These settings are authored visual tuning. Screen-space effects do not provide off-screen occlusion or a guaranteed metric wall clearance. Mirrors retain their reduced shading budget.

README, HUD and project descriptor identify 1.7.21; [graphics notes](Docs/GRAPHICS_1.7.21.md) and credits document source and regeneration. Pre-existing DefaultGame.ini 1.7.8 version metadata is unchanged. Fresh checks: downloaded PNG dimensions and source SHA-256 hashes passed; Unreal bundled Python `Tests/audit_project.py` passed; scoped Git whitespace checks passed. Unreal 5.4.4 DX11 PythonScript commandlet ran targeted wall generation and lighting update successfully, reporting zero errors/warnings, zero map-check errors/warnings and zero remaining shader jobs. An earlier function-inspection probe used an unavailable Python helper; actual graph construction and compilation then passed. `Build.bat CiazParkingEditor Win64 Development -Project=D:/Games/CiazParking/CiazParking.uproject -WaitMutex -NoPCH -MaxParallelActions=2` compiled/linked successfully using pinned MSVC 14.38.33130 (five actions). Read-only independent review found no blockers.

Standalone DX11/SM5 launched using isolated `Saved/GraphicsReview/User` profile. A computer-use screenshot confirmed the new wall texture renders in the cockpit camera settings view; the runtime log had no material/compilation errors. The owner save SHA-256 matched before/after launch and the test save was created under the isolated directory. The test game remains open. This is a rendering smoke check, not a close-wall driving test. Next actionable step: compare wall clearance in cockpit/chase views, toggle AO at Low/Medium, inspect opposite wall normals and shadow stability, and measure frame time on target hardware. No portable physics suite, hardware test, Shipping/Android build or performance benchmark was run for this graphics-only change. All current and earlier accumulated work remains local, uncommitted and unpublished; no commit/push requested.

## Wall shadow artifact correction, 2026-11-05

Owner screenshots showed stippled dark bands and trails on Level 12 walls after 1.7.21. The running DX11/SM5 game reproduced the exact distant-wall pattern. A live same-view comparison with only `r.ContactShadows 0` removed it immediately; a subsequent closer wall/camera view was also clean. This identifies the new screen-space contact-shadow pass as the source, rather than the concrete textures or saved anti-aliasing choice. The earlier smoke check did not expose this regression.

[ParkingGameMode.cpp](Source/CiazParking/ParkingGameMode.cpp) now enforces contact shadows Off after all scalability applications. [DefaultEngine.ini](Config/DefaultEngine.ini) also defaults the pass Off, and [build_wall.py](Tools/build_wall.py) writes sun contact-shadow length zero so regenerated maps and the editor agree. The existing Parking map was updated with zero length through a targeted commandlet. SSAO, conventional cascaded shadows, Poly Haven material, saved graphics choices and controls remain. Beta 1.7.21 retained for this focused regression fix. README and graphics notes replace the superseded contact-shadow claims.

Fresh project asset audit and scoped whitespace checks passed. Initial map save failed with error 32 because the running game held it open, and initial compilation stopped because Live Coding was active. Game and editor were closed normally with no unsaved-content prompt. The repeated map commandlet passed after closing (zero-length assertion and map save). Unreal 5.4.4 Win64 Development Editor rebuilt and linked successfully with the pinned MSVC 14.38.33130 directory, `-WaitMutex -NoPCH -MaxParallelActions=2` (13 actions, about 166 seconds). The live Level 12 A/B is fresh visual evidence; no second driving test was required for this same single-setting correction. Next step: owner checks normal play and graphics Apply after restart; target-GPU performance remains unmeasured. No hardware or performance benchmark, portable physics suite, Shipping or Android build ran. Changes and earlier accumulated work remain local, uncommitted and unpublished.

## Wall normal-space lighting correction, 2026-11-05

Owner identified a brightly lit wall whose visible face points away from the sun. Inspection exported Unreal 5.4.4's actual WorldAlignedNormal function: its WorldSpace static switch defaults false and selects a world-to-tangent transform. The wall material disabled tangent-space normals, so it interpreted tangent output as world direction. Earlier documentation/review claiming the graph already provided correct world output was incomplete and is superseded by this inspection.

[build_wall.py](Tools/build_wall.py) now explicitly connects a True static bool to the normal function's WorldSpace input, matching `tangent_space_normal=False`. The generated [wall material](Content/Materials/M_ConcreteWall.uasset) was rebuilt and saved; colour, texture scale, AO, ordinary shadows, vehicles and saves are unchanged. Contact shadows remain disabled. [Graphics notes](Docs/GRAPHICS_1.7.21.md) document the required explicit switch. Beta 1.7.21 retained for the focused material correction.

Fresh verification: Unreal 5.4.4 DX11 targeted material generation/compilation passed with zero errors/warnings and zero remaining shader jobs. Export of the resulting material confirmed the True WorldSpace input connection and disabled tangent-space-normal flag. Unreal bundled Python `Tests/audit_project.py` and scoped Git whitespace checks passed. A fresh standalone DX11/SM5 launch with a copy of the owner profile under ignored `Saved/WallNormalReview/User` loaded Level 12. Camera orbit showed the sun-away wall faces dark and sun-facing faces light, with the normal detail visible and without the prior stippled contact-shadow artifacts. Runtime log had no material errors. Owner save SHA-256 remained unchanged. The isolated test game remains open for inspection.

No new C++ compilation was necessary for this material-only change. No portable physics suite, hardware/performance benchmark, Shipping or Android build ran. Next step is owner visual acceptance during normal gameplay; no further implementation work is pending for this report. All changes and earlier accumulated work remain local, uncommitted and unpublished.

## Publish accumulated work, 2026-11-05

Owner explicitly requested pushing all unpushed changes. Scope includes the complete accumulated Beta 1.7.21 checkout: vehicle/source assets, controls/camera and wheel fixes, Level 11/12, Android packaging/touch support, goal pointer, concrete materials and both graphics corrections, tests, ignore rules and portable context files. Historical local/unpublished statements above describe their original task handoffs and are superseded once publication is verified here. Fresh `git fetch origin` found main equal to the base commit (0 ahead/0 behind); no integration was needed. Fresh `Tests/audit_project.py` passed with Unreal bundled Python. No tracked or newly included file is 50 MiB or larger. Local saves, build outputs, packages and caches remain excluded. Prior build/play/hardware limits above remain; publication does not establish additional gameplay or performance verification.

Publication verified: commit `181db0a01d22c4b94ac17e0785c1b6a6fa7be9d1` contains 355 changed files and was pushed to `origin/main`. `git ls-remote origin refs/heads/main` matched local HEAD exactly. This follow-up documentation commit records that verified result; the final chat handoff verifies its own publication. No new game version increment or build was needed for the publication record.

## Instrument backlighting and Ciaz follow-up, 2026-11-05

Beta 1.7.22 adds dedicated instrument MIDs to [CiazPawn.cpp](Source/CiazParking/CiazPawn.cpp), held in a reflected InstrumentMaterials array. The existing saved headlight binding updates Backlight from zero to 1.2 immediately, shared by both cars. Animated groups 5/6 and Ciaz decorative needle pieces receive red emission; Ciaz material32 and Swift material1 dial artwork use isolated instances of new M_Instrument. UV/brightness masks restrict illumination to dial markings; other shared-atlas exterior materials stay unchanged. No per-frame material work or new light components. Existing gauge animation and save fields are retained. [build_instruments.py](Tools/build_instruments.py) integrates after Swift setup and imports [runtime atlas copies](Tools/InstrumentSource). Original vehicle artwork stays intact.

At owner request, built-in imagegen removed Ciaz's two long baked main pointers. Only its two lower circular dial islands were composited into the new atlas; unrelated source artwork was preserved. Lettering inside those generated islands can differ slightly. Swift's main gauge faces were already pointer-free, so its final atlas copy is byte-identical to the source instead of applying the generated candidate. Small fuel/temperature artwork remains. [Instrument notes](Docs/INSTRUMENTS_1.7.22.md) record paths, prompt and provenance. README/HUD/project descriptor identify 1.7.22.

Fresh original instrument validation: Win64 Development Editor compiled and linked with pinned MSVC14.38.33130 and -NoPCH -MaxParallelActions=2 (eight actions, then four for version metadata). DX11 targeted instrument generation passed zero errors/warnings; project audit and scoped whitespace checks passed. Isolated Saved/InstrumentReview/User copied the owner profile for a Ciaz cockpit smoke check; red animated needles and source artwork rendered. Owner input was active; automated toggle attempts were rejected, so no automated on/off acceptance is claimed. Owner stopped Computer Use via Escape, ending automation for that turn.

Owner subsequently reported Ciaz RPM dark and speedometer dim, and explicitly confirmed Swift is fine. The initial global brightness follow-up did not save: the running game locked T_Ciaz_Dials. The current correction preserves Swift's accepted .16-.36 threshold and source-colour emission. Ciaz only uses .008-.060 threshold, luminance-normalized markings and 3x emission gain; lower dial mask radius expands from .128-.133 to .145-.148 (upper .102-.106 to .116-.120) to include printed outer numbers/ticks. Direct binary mesh inspection verified active Ciaz centres at wrapped UV (.150,.850) and (.450,.849), matching those lower dial regions. Targeted material-only regeneration can skip texture reimports. The first current save attempt also hit Windows error32 on M_Instrument while the game was open. Owner was asked to close game/editor; material save and fresh visual acceptance are pending. Fresh Python project audit and scoped whitespace checks pass. No new C++ build is needed for this shader-only follow-up. No hardware, benchmark, Shipping or Android checks ran. All 1.7.22 changes remain local, uncommitted and unpushed.

Owner confirmed game/editor closed. The targeted Ciaz material-only commandlet then saved and compiled successfully (Saved/brighten_ciaz_only.py, DX11, Unreal 5.4.4), reporting zero errors/warnings and zero remaining shader jobs. Ciaz outer marking coverage and luminance lift are now in the generated M_Instrument asset. Swift retains its accepted original shader response. No new runtime visual check was performed after this save; next step is owner cockpit inspection with headlights on. 1.7.22 work remains local, uncommitted and unpushed.


## Minimal intro menu, 2026-11-06

Owner approved the simplified menu image and requested recreating it in the project intro screen. [ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp) replaces only main-menu Screen 1 with the mockup layout: cyan primary Start/Continue, flat secondary actions, a dark translucent vehicle panel, selected model name/preview, Change action, and ride-height slider. Main menu text uses measured font height and the existing 1280x720 scaling. Background fill crops to the viewport aspect instead of stretching. Existing action IDs, deferred mutation, save compatibility and menu touch coordinates are retained. Other menus and the driving goal pointer remain intact.

[Menu notes](Docs/MENU_1.7.23.md) record asset provenance and regeneration. The background is a new imagegen garage-only asset. Vehicle previews are rendered from actual runtime mesh data with Blender rather than substituting generated cars. [build_menu.py](Tools/build_menu.py) imports three UI textures and is integrated into setup; `/Game/UI` is explicitly cooked. No vehicle data, physics, driving controls or save schemas were changed. Version is Beta 1.7.23 in HUD, README and descriptor. Pre-existing 1.7.8 DefaultGame.ini metadata drift is retained.

Validation so far: source/asset audit and scoped whitespace check passed. Blender rendered both actual vehicle previews successfully and they were visually inspected. PNG dimensions/format and exporter syntax passed; previews are 1024x448 RGBA. Targeted Unreal texture import (Tools/build_menu.py, -run=pythonscript -nullrhi) saved all three T_*.uasset files with zero errors/warnings. The first C++ compile caught incorrect Canvas blend enums for AHUD::DrawTexture; those were fixed and the full Win64 Development Editor build passed with the pinned MSVC directory. Initial isolated DX11 live inspection showed overly bright panels, scaled bitmap font softness and stepped corners. Owner also requested matching the approved finishing. Native rounded triangle geometry, circular slider thumb, darker colours and measured title spacing address that feedback. The first polish build passed; its live 1280x720 check confirmed rounded shapes and Ciaz-to-Swift name/preview switching. Distance-field lettering still looked too heavy at small sizes, so the final menu uses Roboto regular/bold outlines rasterized through Slate at actual physical output sizes, with pixel-aligned positions and a constructor/CDO font cook reference. The regular level hint is hidden on the intro while other notices remain. Independent read-only code and installed-engine API reviews found no blockers. Final native-font build and follow-up HUD refinement build passed using Unreal 5.4.4 CiazParkingEditor Win64 Development -WaitMutex -NoPCH -MaxParallelActions=2 with MSVC 14.38.33130. Final isolated DX11/SM5 1280x720 windowed inspection confirmed clean antialiased typography and rounded controls. Ciaz/Swift switching changed model name and preview together; selected Swift persisted across restart. Both 0 and +8 cm slider endpoints responded, and Settings/Back returned correctly. F9 saved an actual runtime screenshot at [Docs/Menu_1.7.23.png](Docs/Menu_1.7.23.png). The final runtime log contained no Error/Fatal lines. The owner save SHA-256 matched before and after all checks. The disposable QA profile under Saved/MenuReview used its own copied save and 1280x720 windowed graphics; the original save was not edited. No portable physics suite, hardware test, Shipping/Android package or performance benchmark has run for this menu. Next step is owner acceptance of the finished menu; final native-font ultrawide/high-DPI appearance and Android touch remain untested. The isolated test window was closed after verification. Changes are local, uncommitted and unpushed, alongside the existing 1.7.22 work; no commit or publication requested.

## Reference HUD extraction, 2026-11-06

Owner requested extracting the UI from a supplied Gemini parking screenshot. Built-in imagegen produced [transparent HUD reference](Docs/UI/ExtractedHUD.png), retaining the six widget groups and removing gameplay/cockpit imagery. This is an AI reconstruction with minor visual differences, not a pixel-exact segmentation or a runtime HUD implementation. Prompt: extract only the level card, goal arrow, collision counter, sensor card, speed/gear card and steering bar, preserving their layout, text, colours and backplates on actual transparency. Visual inspection confirmed all six groups and no gameplay backdrop; System.Drawing verified 32-bit ARGB and transparent centre (Python launcher unavailable). No game code/assets or version were changed, and no Unreal build or gameplay test was needed. New artifact and context update remain local/uncommitted/unpushed alongside pre-existing work. Next step: owner's review or further UI instructions.


HUD reference follow-up, 2026-11-06: owner requested a white collision-count zero and parking-brake sign beside speed. Built-in imagegen edited the prior extraction into [HUD v2](Docs/UI/ExtractedHUD-v2.png), keeping the original. Prompt changed only the collision zero to white (retaining red /3) and added a red circled P with side arcs beside speed, widening the speed card for spacing. Visual inspection confirmed both requested changes; System.Drawing confirmed 32-bit alpha and transparent empty space. Image-only change; no runtime implementation/build required. Latest artifact is v2; all work remains local/uncommitted/unpushed. Awaiting owner's next instruction.


## Driving HUD and UI antialiasing, 2026-11-06

Owner requested implementing the supplied transparent [HUD v2 reference](Docs/UI/ExtractedHUD-v2.png). The second screenshot was placement context. [ParkingDrivingHUD.cpp](Source/CiazParking/ParkingDrivingHUD.cpp) recreates the six widget groups in the 1280x720 design space. UV regions from the supplied artwork provide the arrow, pin, star, car, steering wheel and parking brake icons. The rounded panels and live labels, sensor segments, speed, gear and steering position are rendered by Canvas. Sensor colors retain the existing 250/90/35 cm display thresholds. Side segments are decorative because the car has six front/rear sensors. The parking brake icon follows its actual state. The compact layout omits the previous RPM and transmission-mode readouts. Hold and engine stall messages remain available. Android keeps its touch controls and places the two lower HUD panels above them.

[build_menu.py](Tools/build_menu.py) imports the reference into T_DrivingHUD in the existing cooked UI directory. Targeted UnrealEditor-Cmd Python import saved the texture with zero errors or warnings. Source PNG retains original alpha and size. Setup now also imports the atlas. Native Roboto renders labels at output resolution.

Settings > Graphics adds UI anti-aliasing as entry 14 (zero-based). Existing 14-entry graphics saves retain their selections and append On. New presets default On. The same Apply/Keep/Revert transaction manages the option. It controls the one-pixel feather on Canvas shape edges independently of scene AA. Texture filtering and font rasterization remain intrinsic to their assets. Beta 1.7.24 in README, HUD and descriptor.

Initial source/asset audit and scoped whitespace check passed. First Win64 compile caught a transmission label table that was still needed by Controls, which was restored there. Rebuild passed. An isolated DX11 1280x720 Level 12 run showed all six widgets and live speed, gear, collision count, parking brake and sensor changes. The source car crop was tightened to remove example green pixels and collision text spacing adjusted after that inspection. Owner requested centering the gear digit, so MenuText now uses native Canvas font centering on both axes for the badge. Final Win64 Development Editor build passed with Unreal 5.4.4 and the pinned MSVC 14.38.33130 directory, using -WaitMutex -NoPCH -MaxParallelActions=2. The final isolated test game launched, but the owner stopped Computer Use with Escape before final visual or AA Apply/Keep/Revert checks. Next step is verify the centered 1 in-game and toggle Graphics > UI anti-aliasing on the disposable profile. No Android package, hardware test or performance measurement ran. Changes are uncommitted and unpushed.


## Notification styling, 2026-11-06

The owner reported that the collision notification still used the old wide grey bar. [ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp) now draws shared notifications with the driving HUD's outlined navy pill, content-based width, and centered native Roboto text. Collision notices use a soft red label. The pill fits between the top-center goal badge and the right sensor card and uses the existing UI antialiasing option and reveal timing.

The isolated QA instance was closed to release Unreal's Live Coding lock. Win64 Development Editor compiled and linked with Unreal 5.4.4 and pinned MSVC 14.38.33130 using -WaitMutex -NoPCH -MaxParallelActions=2. Scoped Git whitespace check passed, and the owner save hash matched. Beta 1.7.24 retained for this styling follow-up. No new gameplay or visual check ran. Next step is to view a collision notification and a longer level hint in-game. Changes remain local, uncommitted and unpushed.


## Unified UI theme, 2026-11-06

The owner requested extending the approved garage menu and driving HUD theme throughout the game. [ParkingUITheme.h](Source/CiazParking/ParkingUITheme.h) holds the shared navy, rim, cyan, text, inactive and status colors. [ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp) shares the garage chrome, runtime Roboto font, outlined panels, button styles and slider drawing across the main menu, level selection, pause, settings, graphics, interior camera, controls, keyboard bindings and both result screens. The interior camera page retains the live cockpit preview with open space between the control groups. The Android branch applies the palette and font to touch buttons and wheel graphics. [ParkingDrivingHUD.cpp](Source/CiazParking/ParkingDrivingHUD.cpp) uses the shared palette for the established driving widgets. Notifications retain their compact pills. The existing UI AA setting still drives Canvas edge feathering, and menu actions, touch hit areas and save fields are retained. Beta 1.7.25 is reflected in the HUD, README and descriptor.

Fresh project source/asset audit and scoped whitespace check passed. Unreal 5.4.4 CiazParkingEditor Win64 Development compiled and linked with the pinned MSVC 14.38.33130 directory using -WaitMutex -NoPCH -MaxParallelActions=2 after renaming a palette value that conflicted with a local hover flag. The main and Graphics screens were visually inspected in the isolated 1280x720 DX11 run, including the UI AA row and FOV slider. The owner was interacting with the game window, so it remains open with the disposable Saved/ThemeReview profile for further inspection. Other screens were reviewed in source but were not visually checked in this run. No Android package or performance test ran. Next step is owner visual feedback across the remaining screens. Changes are local, uncommitted and unpushed.

## Tire skid marks, 2026-11-06

[VehicleDynamics.h](Source/CiazParking/VehicleDynamics.h) exposes a visual slip signal from friction saturation, rear handbrake lock and rear grip recovery. The tire forces are unchanged. [CiazPawn.cpp](Source/CiazParking/CiazPawn.cpp) draws 15 cm dark strips between each slipping tire's asphalt contact samples. One instanced mesh per car recycles the oldest segment after 1,024 marks. Marks clear on level reset and tire trails break on pause, airborne contact and grip recovery. The thresholds and visual appearance are authored tuning.

An isolated MSVC 14.38 check covered rolling, stationary, airborne, forward and reverse drive saturation, lateral slip, hard braking and handbrake lock. Existing dynamics and power/handbrake suites also passed. Unreal 5.4.4 Win64 Development Editor compiled and linked with -NoPCH -MaxParallelActions=2. The Unreal commandlet saved and verified instanced mesh support on M_Solid, and setup now preserves that flag. The scoped Git whitespace check passed. No driving, packaging or performance tests ran. Next step is to inspect visibility and continuity during an in-game skid. Changes are local, uncommitted and unpushed.



## Supplied start menu vehicle images, 2026-11-06

Replaced the Blender previews with the owner's Suzuki Ciaz Splash.png and Suzuki Swift Splash.png in [Content/UI](Content/UI). The copied PNGs matched the originals byte for byte and retained alpha. The existing vehicle selection chooses T_CiazPreview or T_SwiftPreview and fits the texture to the preview panel with its aspect ratio preserved. The historical Blender renderer now outputs to ignored Saved/MenuVehicleRenders so it cannot overwrite the supplied images.

Unreal 5.4.4 targeted import ran with Tools/build_menu.py CiazPreview SwiftPreview under -run=pythonscript -nullrhi. Both textures saved with zero errors and warnings. The project audit and scoped whitespace check passed. Beta 1.7.26 retained for this asset swap. No C++ build, live visual check, packaging, or performance measurement ran. Next step is owner visual confirmation of both previews via Change on the main menu. Changes remain local, uncommitted and unpushed.


## Beta 1.7.26 publication, 2026-11-06

The owner requested pushing the complete local Beta 1.7.26 project to GitHub. This snapshot includes the accumulated instrument lighting, unified UI and HUD, supplied menu images, tire skid marks, and associated Unreal assets and source files. The remote main tip before publication matched the local baseline at 4bd688a. The source and asset audit and Git whitespace check passed. This is a repository update. No new build or packaged release was created for this request.

GitHub main was verified at bf21f19721b43cb505a439aa393b0f8b2ae775c9 after the push.


## Android driving layout, 2026-11-07

The owner requested a mobile HUD based on a landscape driving reference. [ParkingTouch.h](Source/CiazParking/ParkingTouch.h) moves the wheel or left/right pads to the left, places the pedals and D/N/R selector on the right, and defines circular parking brake and top-right camera and pause hit targets. [ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp) draws those controls from the same layout coordinates with a translucent wheel, rotating spokes, and a highlighted gear pill. [ParkingDrivingHUD.cpp](Source/CiazParking/ParkingDrivingHUD.cpp) draws the compact speed and gear pill above steering, the top-right sensors, and the centered arrow without the desktop GOAL badge. The mobile layout uses the existing centered 1280x720 design space. The road and parking bay art in the reference were outside the UI scope.

Later that day, the owner's `Beta1.7.27` run of [PackageAndroid.cmd](PackageAndroid.cmd) passed Turnkey SDK verification for NDK r25b. The subsequent Android ETC2 Development `BuildCookRun` failed at the build stage because Live Coding was active. UnrealBuildTool and AutomationTool exited with code 6, and the script stopped before producing an APK or creating the prerelease. Diagnosis is based on the supplied log and script. No rerun or device test was performed.

New save profiles start in touch-wheel mode. Existing serialized steering choices remain valid, and the Android Controls menu retains button mode. Existing touch ownership, brake priority, explicit D/N/R selection, input cancellation, and desktop driving behavior are preserved. No save fields or new assets added.

Fresh MSVC 14.38 C++17 touch suite passed with the relocated targets, including gear isolation, multi-touch, wheel wrap and viewport mapping. The source and asset audit and scoped whitespace check passed. Unreal 5.4.4 Android arm64 Development compiled and linked with NDK r25b. The initial Build.bat invocation also ran its default local Gradle debug packaging step using existing staged data. The final source was rebuilt successfully with CiazParking Android Development -Architecture=arm64 -SkipDeploy -WaitMutex -NoPCH -MaxParallelActions=2. No fresh cook, phone playtest, Windows rebuild or performance measurement ran. No APK was published. Next step is to verify appearance and simultaneous inputs on an Android device. The changes remain local, uncommitted and unpushed.

## Android camera drag and pedals, 2026-11-07

[ParkingTouch.h](Source/CiazParking/ParkingTouch.h) gives the first finger starting off the driving controls ownership of camera motion until release or cancellation. Other fingers can steer and operate pedals simultaneously. [ParkingGameMode.cpp](Source/CiazParking/ParkingGameMode.cpp) feeds layout-space deltas to the existing cockpit and chase camera, keeping its limits and pausing chase auto-centering while the look finger is down. The existing accelerator ramps to full in about 0.45 seconds and cuts immediately on release or brake. The clutch ramps in over 0.25 seconds and releases over about 0.83 seconds. These timings are authored tuning.

[ParkingHUD.cpp](Source/CiazParking/ParkingHUD.cpp) exposes Manual Clutch under Android Controls using the existing transmission save field and displays CLUTCH in that mode. D and R use the existing clutch threshold and direction guard. N can restart a stalled engine at low speed, as shown in [ParkingDrivingHUD.cpp](Source/CiazParking/ParkingDrivingHUD.cpp). Android keeps Automatic for default profiles and older sequential saves. [README.md](README.md) describes the controls. Version remains the local Beta 1.7.27.

MSVC 14.38 C++17 touch, core, and power/handbrake tests passed. The touch tests cover crossing control boundaries, simultaneous inputs, camera ownership, release and cancellation. The source and asset audit and Git whitespace check passed. Unreal 5.4.4 Android arm64 Development compiled and linked using UnrealBuildTool with -Architecture=arm64 -SkipDeploy -WaitMutex -NoPCH -MaxParallelActions=2 and NDK r25b. No APK packaging, phone playtest, Windows rebuild, or performance measurement ran. Next step is to verify the gestures, pedal feel, and manual stall/restart on a phone. Changes remain local, uncommitted and unpushed alongside earlier work.

## Beta 1.7.27 publication, 2026-11-07

The owner requested pushing the local project. GitHub main was verified at 61643ae30751ca30995e67c77dfad2e478005d01 after publishing the complete Beta 1.7.27 checkout, including the Android driving layout, camera drag, progressive pedals, and tracked Unreal asset updates. The source and asset audit and staged whitespace check passed. This publication supersedes earlier local-only handoff notes. The next step is Android packaging with the editor closed and a phone playtest.
