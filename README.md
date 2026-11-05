# Ciaz Parking - Beta 1.7.26

Tires leave skid marks on the asphalt when they lose grip.

## Beta 1.7.25

The garage menu and driving HUD theme now extends to every screen, including level select, pause and results, graphics, camera, controls, key bindings, and Android touch controls.

## Beta 1.7.24

The driving HUD uses the supplied reference layout with live goal direction, collision count, parking sensors, speed, gear and steering. Settings > Graphics includes independent UI antialiasing, enabled by default.

## Beta 1.7.23

The intro menu now uses the approved minimal garage design: flat buttons, cyan accents, a selected-vehicle preview, and a clean ride-height slider. Existing menu actions and saved settings are retained.

## Beta 1.7.22

Ciaz and Swift instrument dials and red animated needles illuminate with the headlights (L by default, or your saved binding). Switching headlights off removes the backlight. Edited Ciaz artwork removes the duplicate painted speed/RPM pointers; the animated needles remain. Original supplied atlases are preserved. See [instrument notes](Docs/INSTRUMENTS_1.7.22.md).

## Beta 1.7.21

Poly Haven Concrete Wall 001 now covers the walls with 2K colour, normal and AO/roughness maps at a consistent 1.5 m world scale. Short-range ambient occlusion, conventional shadows and lower sky fill improve proximity cues. Screen-space contact shadows are disabled to prevent patterned wall artifacts. Settings > Graphics retains the Ambient occlusion toggle; enable it if an older saved profile has it off. Low post-processing no longer silently disables that toggle. Existing DX11/SM5 rendering and saved graphics selections are preserved. See [graphics notes](Docs/GRAPHICS_1.7.21.md).

## Beta 1.7.20

Settings > Interior Camera adjusts the seat view forward/back, left/right and up/down in 2 cm steps, pitch/yaw in 2 degree steps, and field of view from 70 to 150 degrees. Changes preview in the cockpit and save immediately. Reset Camera restores the selected car's default position and rotation and 85-degree FOV. Position offsets (up to 60 cm each way) and rotation settings are shared between vehicles; mouse look remains available while driving.

## Beta 1.7.19

A persistent top-center arrow points toward the parking goal relative to the current camera view, using the supplied Pointer Arrow FBX silhouette. At the goal center it indicates the required parking heading.

## Beta 1.7.18

The Swift cockpit camera sits 35 cm farther back and 6 cm higher for more room around the steering wheel.

## Beta 1.7.17

Android driving uses on-screen accelerator and brake pedals on the left. Choose steering buttons or a drag-to-turn wheel under Controls. Tap D, N or R to select direction, then release the handbrake to drive.

### Package and publish the Android APK

Install the Android platform component and configure the Android SDK for Unreal Engine 5.4.4. Sign in to GitHub CLI with `gh auth login` using an account with write access to `Masterkumail-718/Car-Parking`. Close Unreal Editor. Double-click `PackageAndroid.cmd` to use the default Unreal path and enter a release tag when prompted. After completion or failure, the command prompt stays open until you close it or type `exit`. You can also pass a fresh tag and engine path from a terminal.

For the installed UE 5.4.4 build, enable **Android** under the engine tile's **Options > Target Platforms** in the Epic Games Launcher. Then install Android Studio Flamingo 2022.2.1 Patch 2 with the SDK command-line tools. Epic specifies SDK 34, Build-Tools 34.0.0, NDK r25b and OpenJDK 17 for this version. The installed `SetupAndroid.bat` still defaults to SDK 33 and Build-Tools 33.0.1, so pass the versions explicitly. [Epic's UE 5.4.4 Android requirements](https://dev.epicgames.com/documentation/en-us/unreal-engine/android-development-requirements-for-unreal-engine?application_version=5.4)

```bat
"D:\Unreal\UE_5.4\Engine\Extras\Android\SetupAndroid.bat" android-34 34.0.0 3.22.1 25.1.8937393
```

After SDK setup, verify it from a new terminal before packaging.

```bat
"D:\Unreal\UE_5.4\Engine\Build\BatchFiles\RunUAT.bat" Turnkey -command=VerifySdk -platform=Android -project="D:\Games\CiazParking\CiazParking.uproject" -unattended
```

```bat
PackageAndroid.cmd android-v1.7.17 "D:\Unreal\UE_5.4"
```

The command builds a standalone Android ETC2 Development APK for sideloading, keeps it under `Packaged\Android`, and attaches it to a GitHub prerelease. The release uses the current commit as its base and the APK includes the local checkout's changes. If the map or marking asset is missing, run `SetupProject.cmd` first.

## Beta 1.7.16

Level 12, Full house, adds a crowded parking lot with four rows of marked bays. Start in the lower right and park in the open bay in the upper left. Complete Level 11 to unlock it.

## Beta 1.7.15

The Swift uses the full geometry and source-resolution textures from the supplied FBX archive.

## Beta 1.7.14

Level 11 replaces the two cone rows near the finish with parked cars.

## Beta 1.7.13

Level 11 has a tighter barrier bend, closer parked-car rows, and a smaller finish bay.

## Beta 1.7.12

Level 11, Barrier bend, adds a right-hand bend between concrete barriers, two rows of parked cars and cones, and a perpendicular finish bay. Complete Level 10 to unlock it.

## Beta 1.7.11

The main menu saves a vehicle height adjustment from stock to +8 cm. Keyboard settings offer five steering speeds, with level 3 matching the previous speed. Settings > Controls / Wheel > Keyboard Bindings also offers five saved mouse-look sensitivity levels for cockpit and chase cameras (0.5x to 1.5x; level 3 retains the original speed). Settings > Graphics provides an interior FOV slider from 70 to 150 degrees (default 85). Parking checks all four wheel centres against the bay marker and still requires alignment and a stationary hold.

# Beta 1.7.10

The three parked obstacle cars use their own mesh triangles for collision.

# Beta 1.7.9

T248 / T3PA calibration uses steering axis 0, accelerator 5, brake 1 and clutch 6. Uncalibrated legacy defaults migrate automatically. Custom assignments remain editable. Only assigned controls require travel. Turn fully both ways and fully press each pedal, then centre the wheel and release pedals before Finish.

# Ciaz Parking — Beta 1.7.7

Full cumulative project: Ciaz + Swift. Read Docs/AUDIT_1.7.7.md for fixes, test results and known limitations. Close Unreal and rerun SetupProject.cmd before playing. Unreal compilation and gameplay testing are still required on Windows.

# Ciaz Parking — Beta 1.7.6

Includes Ciaz and Suzuki Swift 2022. Run SetupProject.cmd again to generate the new assets. Read Docs/SWIFT_1.7.6.md for installation, assumptions and testing limitations. Select the vehicle from the main menu.

# Ciaz Parking — Beta 1.7.5 handbrake controls

This is the complete source project for Unreal Engine 5.4.4, including the supplied
vehicle/obstacle data and previous UI/settings updates. It is **not a compiled game**.

## Handbrake control mode

Settings > Controls / Wheel > Handbrake now switches between Toggle and Hold.
The choice is saved and uses your rebound parking-brake key (Space by default).
Toggle remains the default for existing saves. Switching mode releases the brake.
In Hold mode, release the assigned key to release the rear wheels and restore grip.
This mode also applies to keyboard handbrake input while using the T248.

## Power and handbrake update

110 hp crank-power target, revised automatic shift points, locked rear-wheel
skid forces and progressive grip recovery are included. See
Docs/POWER_HANDBRAKE_1.7.4.md for details and testing limits.

## Curb and suspension update

Wheel-arch collision relief, tire-radius curb contact sampling and independent
corner damping/preload are included. Stock ride height is retained; optional
lift is configurable. Read Docs/CURBS_SUSPENSION_1.7.3.md before testing.

## Build a Windows executable

1. Close Unreal Editor. Back up your existing project and extract this folder.
2. Open Command Prompt in the folder containing CiazParking.uproject.
3. Run `PackageWindows.cmd "D:\Unreal\UE_5.4"`.
4. After a successful build, run `Packaged\Windows\CiazParking.exe`.

Keep the entire Windows folder together when copying the game. The executable
needs its cooked content and supporting files. An optional second argument to
PackageWindows.cmd chooses a different output directory.

Requires Unreal 5.4.4, Visual Studio 2022 C++ build tools (the targets retain the
existing MSVC 14.38.33130 pin), and a Windows SDK. The build command creates assets,
compiles the Shipping target, cooks the map, and packages prerequisites. It stops
on errors. Build/cook and the resulting executable could not be tested in the
Linux development environment, which has no Unreal engine or Windows toolchain.

For editor testing, run `SetupProject.cmd "D:\Unreal\UE_5.4"` instead.

## Materials update

This build includes CC0 Asphalt 02 PBR maps, world-space ground tiling, clear-coat
paint, surface-specific material values, and shared vehicle texture imports.
Run SetupProject.cmd to generate the new materials. See Docs/MATERIALS_1.7.1.md.

## Physics review changes

- Load-sensitive combined tire grip and slip-angle cornering.
- Low-speed lateral stabilization and brake forces limited to prevent reversing
  wheel-contact velocity in one step when grip is sufficient.
- Compression/rebound damping, progressive bump stops and axle anti-roll support.
- Narrow footprint sweeps for tire contact, with steep-wall rejection.
- Consistent Ackermann steering between force calculation and wheel visuals.
- Smooth engine braking through zero speed; no idle propulsion.
- Aerodynamic drag with explicit units; removed the artificial high-speed force wall.
- Pause/resume preserves velocity; restarts clear it intentionally.
- Save-data validation, total-speed parking checks, frame-cap correction,
  mesh-buffer validation, and improved mirror scheduling.

Read `Docs/REVIEW_1.7.1.md` for scope, limitations and the Windows test checklist.
