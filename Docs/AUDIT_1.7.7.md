# Beta 1.7.7 — project audit and fixes

Audited from the complete Beta 1.7.6 archive. This is a source/asset audit with executable portable tests, not an Unreal build certification. No software audit can guarantee the absence of all bugs.

## Scope

Reviewed the pawn and vehicle loaders, vehicle dynamics and transmission helpers, collision setup, parking rules, game mode, level definitions, save data, HUD/settings navigation, DirectInput wheel integration, Unreal material/import scripts, project/plugin/module configuration, Windows setup/packaging scripts and packaged asset references for both cars. Source delimiters and all setup Python files were checked. Existing generated collision data and both vehicle binary formats were inspected by automated audits. No empty implementation stubs were identified in the active runtime path.

## Fixed in this build

1. Vehicle manifests previously accessed required fields without validating their schema. Added bounded structural checks for materials, mesh entries, pivots, groups, material indices and nonzero gauge/steering axes. Bad manifests now stop loading before those required-field reads.
2. Missing/malformed Swift collision JSON could leave a visibly loaded car without its chassis collision. Added hull structure, finite-coordinate and nonzero-volume validation; driving now requires successful collision loading.
3. Missing Swift materials silently substituted Ciaz/default materials. Missing required materials, colour textures or the three mirror captures now mark vehicle loading incomplete and block starting. Setup must succeed before driving.
4. Mesh loading accepted empty buffers and checked only positions for non-finite values. Empty geometry and invalid normals/UVs are rejected as well.
5. Level reset zeroed numerical steering/spin state while visual wheel components retained their previous pose until the next physics tick. Extracted and immediately called wheel visual updates on reset; sensor distances and timing are also reset/refreshed.
6. Input/tick/UI actions could dereference an unavailable car after a spawn/load failure. Added state guards and blocked resuming incomplete, failed or completed attempts without starting/retrying a level.
7. A HUD click queued for the following tick could act after navigation changed screens. Deferred actions now retain the originating screen and are ignored if it changed.
8. Steering calibration accepted full-lock/off-centre 'rest' values and partially pressed pedals. Finish now checks the steering centre band and pedal endpoints. Previously saved invalid/duplicate-axis calibration is disabled until recalibrated. Saved force-feedback strength is finite-checked and clamped.
9. DirectInput setup ignored acquisition/cooperative-level failures and retained partially initialized resources until a later reconnect. Failures now clean up immediately, disconnected input readings clear, and non-finite force commands stop feedback. The driver's previous autocentre setting is restored on normal disconnect or failed effect creation when it was successfully read. This does not guarantee restoration after a process crash or USB power loss.
10. A vehicle stopped on its side/roof could satisfy the planar parking test. Completion now also requires the vehicle to be sufficiently upright.
11. A graphics preset argument shadowed the game mode's Level member. Renamed it to avoid MSVC shadow warnings. Added screen/null guards around preset and video-confirm operations.
12. Several material graph connection/save results were ignored. Failed wiring or asset saving now aborts setup instead of writing a misleading completion marker.
13. The general asset audit covered only Ciaz meshes. It now covers both vehicle manifests and both sets of required cook/stage directories.

## Validation performed

Seven portable C++ test executables compiled with GCC C++17, -Wall -Wextra -Werror, AddressSanitizer and UndefinedBehaviorSanitizer. All passed. Leak detection was disabled because this execution environment blocks /proc task enumeration; this was an environment limitation, not a clean leak-test result.

Coverage includes direction/shift/clutch guards, zero idle propulsion, progressive steering and return, handbrake hold/toggle and rear skid/recovery, collision episodes and parking rules, 110-hp Ciaz and 61-kW Swift power anchors, Ackermann symmetry, suspension settling/preload, Swift footprint, UI easing, and new calibration rejection cases. The new stress test also passed 100,000 tire-force/friction-bound cases and 60,000 drivetrain steps. These tests execute the portable physics/rules helpers, not Chaos or Unreal's full game loop.

Both asset audits passed: mesh headers/sizes/indices, all referenced colour texture files, Swift packed/normal maps and animation pivots, convex collision validity and wheel-arch voids, obstacle FBX/texture presence, WAV readability, Python syntax, C++ delimiter sanity, and cook/stage paths. Test output is recorded in AUDIT_1.7.7_TEST_RESULTS.json.

The final full-project ZIP is checked for CRC errors and compared byte-for-byte against its packaged inputs.

## Still requires your Windows/Unreal environment

Unreal Engine 5.4.4, MSVC/Windows SDK and the T248 are unavailable here. UHT, actual Unreal C++ compilation, Python API execution inside the editor, shader compilation, cooking/Shipping packaging, D3D11 quality-setting behavior, mirror output, force feedback, collision callbacks, integrated suspension handling and RX 470/8 GB performance remain unverified. The new Unreal-specific error paths also need execution there; source inspection is not a replacement for that.

The Windows targets retain the existing MSVC 14.38.33130 requirement. If that toolchain is not installed, Unreal's build will report the missing compiler. No engine upgrade is required by this update.

## Known implementation limits, not silently claimed complete

- Tires/contact forces remain frame-updated ray samples; the full suspension/contact solver is not executed in a Chaos substep callback. Strong frame-rate sensitivity and curb stability need driving tests.
- Rear wheel locking/recovery is a force approximation, not an independent wheel-inertia solver. Airborne wheel spin is not simulated independently.
- Swift automatic mode uses the game's stepped transmission, not a physical CVT; both cars share generic engine audio.
- Mirrors use fixed-angle scene captures, not view-dependent optical reflection geometry.
- Swift has no distance LODs; its 268k-triangle mesh and 99 sections still need GPU/CPU benchmarking. Simplified texture seams require close inspection.
- Fuel/temperature needles remain decorative. No SUV is included yet.
- The wheel detector still selects a Thrustmaster device by vendor; a device-selection UI for systems with several Thrustmaster controllers is not implemented. Handbrake binding remains keyboard-based.

## Build and smoke test

Extract into a fresh folder, close the editor and run:

    SetupProject.cmd "D:\Unreal\UE_5.4"

Then test both cars: switch cars and restart; reset while steering is turned; select each transmission; check no throttle creep; calibrate at full lock to confirm rejection, then correctly calibrate; disconnect/reconnect the wheel; test both handbrake modes; pause/resume; change graphics and exercise Keep/Revert/timeout; verify mirrors/needles/sensors; hit three distinct obstacles; finish a level and unlock the next; cross a low curb diagonally.

When ready for a standalone build, PackageWindows.cmd builds/cooks/packages the full project. This archive itself is source, not a packaged executable.

API references checked during review:
https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ee417536(v=vs.85)
https://dev.epicgames.com/documentation/unreal-engine/API/Plugins/ProceduralMeshComponent/UKismetProceduralMeshLibrary

The DirectInput zero Cartesian direction for a single-axis effect is intentional per Microsoft's documentation; it was checked and retained.
