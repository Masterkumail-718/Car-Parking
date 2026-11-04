# Beta 1.7.1 — physics rewrite and project review

## Scope and result

Reviewed the runtime C++ modules, UI/settings paths, DirectInput integration,
configuration, Unreal setup/import scripts, procedural vehicle data, obstacle
inputs, audio inputs, cooking/staging configuration and packaging entry points.
This was a source and asset review, not an Unreal compiler or runtime review.
No Windows executable was produced: Unreal and the Windows toolchain are absent.
A full-source distribution and a fail-fast Windows packaging command are supplied.

## Corrected issues

| Area | Finding and correction |
|---|---|
| Tires | Replaced fixed lateral drag with low-speed contact stabilization blended into slip-angle cornering, load sensitivity, and a combined-force grip limit. |
| Braking | Contact-speed brake budget avoids forcing a stopped tire into reverse; gravity compensation supports low-speed slope holding within available friction. |
| Suspension | Added distinct compression/rebound damping, progressive bump stops and bounded anti-roll load transfer between grounded tires. |
| Contact | Narrow sphere sweeps improve small-edge sampling; reject steep walls and initially penetrating sweeps as support. |
| Steering | Visual wheels now use the same inner/outer Ackermann angles as tire forces. |
| Drivetrain | Engine state advances in small slices; engine braking fades continuously around zero instead of switching abruptly at 0.25 m/s. No idle drive torque. |
| Drag | Replaced arbitrary velocity penalty with aerodynamic drag in SI units; removed the artificial 18 m/s braking wall. |
| Pause | Preserve linear/angular velocity across menus; clear explicitly on level reset. |
| Parking rules | Use total linear speed and reject significant rotation, so sideways motion cannot satisfy the stopped requirement. |
| Wheel saves | Check array lengths, axis/button bounds and finite calibration values before use. Reset invalid calibration rather than indexing invalid data. |
| Tick ordering | Input/game-mode tick is an explicit prerequisite of vehicle tick. |
| Graphics | Set the selected frame cap explicitly and remove the old global 60 FPS default. |
| Vehicle loading | Validate triangle count, index ranges and finite positions; a partial vehicle is no longer marked ready. |
| Asset readiness | Do not start driving with a missing player vehicle; guard missing target/level state. |
| Mirrors | Preserve scheduling remainder rather than losing it every capture. |
| UI/input | Clear key-capture state on leaving bindings; volume can reach 100%; preserve S-curve UI transitions and settings separation. |
| Packaging | Added Shipping build/cook/stage/archive script; setup supports --no-editor so packaging does not launch an editor that locks build files. |
| Converter | Marked the original converter as legacy: it does not preserve later mirror/needle splits. |

## Validation performed

- Portable driving/rules tests compiled with C++17 and warnings as errors: PASS.
- Portable S-curve UI tests: PASS.
- New vehicle dynamics tests: PASS for Ackermann symmetry, suspension damping,
  zero-input forces, airborne contacts, combined grip saturation, slope-hold force,
  and braking without velocity reversal at 30/60/120 Hz.
- All referenced vehicle mesh buffer sizes and triangle indices validated.
- All referenced vehicle and obstacle texture/source paths resolve.
- Audio source WAVs open and contain sample frames.
- Python tool scripts parse; C++ delimiter scan passes.
- Required material/audio/obstacle/vehicle-texture cook directories and raw vehicle
  staging directory are configured.
- Final ZIP integrity and exact payload bytes verified before delivery.

These checks do not demonstrate successful Unreal compilation, collision cooking,
visual correctness, DirectInput operation, handling quality or frame-rate targets.

## Physics limits and assumptions

The new model is a tuned parking-oriented approximation for the existing 1100 kg
car and 2.65 m wheelbase. Tire/suspension constants are not measured Suzuki data.
It retains Chaos rigid-body/chassis collisions and applies tire forces through the
game thread. Chaos substepping is enabled, but tire contacts and forces are NOT
recomputed on each Chaos substep. Engine-only slices do not change that fact.
The tire force tests are isolated calculations, not an integrated Chaos simulation.

There is no independent rotating-wheel drivetrain, measured Pacejka tire dataset,
ABS controller or mechanical differential simulation. Handbrake handling remains
an approximation. Sweeps still need curb/seam testing, including deep penetration
and a wheel moving off a ledge. No FPS claim is made for RX 470 or other hardware.

Dashboard artwork still includes painted needles pending replacement texture.
Mirrors remain fixed-angle captures that omit the player car, not optical ray-traced
mirrors. T248 hardware/force feedback and the future external shifter are untested.

## Required Windows acceptance checks

1. Build/cook with PackageWindows.cmd; capture the first compiler/cook error if any.
2. Launch the Shipping executable and confirm map, materials, audio and mirrors load.
3. At 30, 60 and 120 FPS caps: straight acceleration/braking, left/right slow circles,
   reversing turns, stop/restart, full lock at rest, and steering return.
4. Release throttle in D/R on level ground: no propulsion. Neutral must coast.
5. Brake on a mild slope; verify release rolls downhill and handbrake behavior.
6. Drive over curbs/seams; check wheel travel, stability and no false support on walls.
7. Pause while moving, resume, then retry: resume preserves motion; retry clears it.
8. Verify three distinct collision episodes fail, sustained contact does not repeatedly
   count, and parking cannot complete while sliding or rotating.
9. Test all three transmission modes, clutch stall/restart, calibrated T248 inputs,
   unplug/reconnect and zero force feedback while paused or out of focus.
10. Test graphics Apply/Keep/Revert/timeout and restart persistence; inspect the UI.
11. Run the complete packaged folder on a PC without Unreal installed.

## Building reference

Epic documentation: https://dev.epicgames.com/documentation/en-us/unreal-engine/packaging-your-project
Epic substepping documentation: https://dev.epicgames.com/documentation/en-us/unreal-engine/physics-sub-stepping-in-unreal-engine
