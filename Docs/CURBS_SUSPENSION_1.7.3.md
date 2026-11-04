# Beta 1.7.3 — curb contact, chassis collision and suspension

## Install
Close Unreal and back up your existing project. Extract this complete CiazParking
folder. From the folder containing CiazParking.uproject run:

    SetupProject.cmd "D:\Unreal\UE_5.4"

Use Standalone Game to test. This includes the previous materials, physics,
controls and graphics updates. Executable packaging remains PackageWindows.cmd.

## Changes
- Rebuilt the chassis collision into 40 convex pieces: central underbody,
  outer body sections with approximate wheel-arch cutouts, and mirrors.
  The previous broad hulls filled wheel-well space. The outer silhouette and
  central floor/bumper collision are retained; the underbody is not made intangible.
- Each tire now samples its lower circular profile with seven longitudinal rays
  and two shoulder rays. The tire can encounter the curb top before its hub reaches
  the edge. The arc contact reaction generates resistance and lift through forces.
- Independent compression history and filtered damping velocity for all four
  suspension corners. Different front/rear spring and damping values, preload,
  progressive bump stops, rebound travel and bounded anti-roll transfer.
- Static spring preload supports the intended model ride height instead of losing
  roughly seven centimetres to the former zero-preload suspension's sag.
- A modest forward centre-of-mass offset matches the 55/45 front/rear static-load
  approximation. Forces applied at each contact create body pitch and roll.
- Visual wheel positions follow their own suspension travel, including droop
  when unsupported. Pause/reset clears stale damper history.
- Version labels and project metadata now read Beta 1.7.3.

## Clearance and optional lift
The supplied geometry has approximately 19 cm of nominal central underbody
clearance at stock height. This is an estimate from the model, not a verified
specification for a real Suzuki Ciaz. Bumper approach angle, suspension compression,
curb height and the direction of approach also affect whether the body strikes.
The existing roughly 20 cm curbs can therefore still hit the stock car.

To test additional clearance, edit Config/DefaultGame.ini:

    [/Script/CiazParking.CiazPawn]
    RideHeightOffsetCm=6.0

Default is 0.0; supported lift is 0–8 cm. This raises the chassis relative to the
wheel centres and updates the visible wheel positions. Restart the game after
changing it. It is not a teleport over obstacles or a collision-disable switch.
Try stock height and a 6 cm lift at low speed, approaching forwards, backwards and
at an angle. Even a lifted car may catch its underbody between raised surfaces.
Actual chassis contact should still count as a collision. Tire support alone is
not reported as a chassis impact.

## Validation
- Collision geometry tests: wheel-centre spaces clear; central chassis and front
  bumper still solid; no artificially lowered/removed central underbody.
- Independent corner response and static preload tests pass.
- Quarter-car settling tests pass at 30, 60 and 120 Hz.
- Tire arc calculations detect a 12 cm curb ahead of the hub and keep flat-ground
  contact at the intended radius.
- Existing driving, tire dynamics and UI animation regression tests pass.
- Project asset/source audit and ZIP integrity checks pass.

Unreal compilation, collision cooking, actual curb traversal, handling and FPS
have NOT been tested here. The tests above cover geometry and isolated equations,
not an integrated Chaos vehicle simulation.

## Remaining approximations / testing
The wheel arches use conservative segmented cutouts, not exact per-triangle body
collision. Test shallow objects near the arch lips for excessive clearance. Forty
convex pieces and 36 contact rays per driving frame cost more than the previous
collision/contact setup; profile on the RX 470 target before claiming performance.

This remains a game-thread contact model driving a Chaos chassis, not a mechanical
multi-body suspension with separate unsprung wheel rigid bodies. Tire forces are
not recalculated during every Chaos substep. Test frame-rate sensitivity, curbs,
seams, diagonal crossings, one-wheel bumps, descents, parking brake holds and body
settling in Standalone. Avoid judging a sharp curb solely at high speed.
