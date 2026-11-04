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
