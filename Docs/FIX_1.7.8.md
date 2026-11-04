# Beta 1.7.8 - parked car no longer rocks

**Symptom:** a stationary car shimmered/rolled slightly, and the 2-second "hold still" counter kept restarting.

**Cause (reproduced in a portable harness, not yet in Unreal):** two interacting problems in the wheel model.
1. The contact point was the lowest of nine probes. Two are shoulder probes at +/-8 cm, so a 0.01 degree roll moved the ~2.7 kN wheel load sideways by 16 cm - a bang-bang roll kick every frame.
2. The low-speed "cancel contact velocity in one frame" force assumed each wheel carries 1/4 of the car. A contact patch sits well below the centre of mass, so the same force also rolls the body; at full gain it overshoots and rings, worse at lower frame rates and lower roll inertia.

**Fix**
- `CiazPawn.cpp`: the load point now moves continuously with how much lower each shoulder is (full shift only at >= 2 cm difference, so curbs still work). `VehicleDynamics::ShoulderWeight`.
- `VehicleDynamics.h`: `LowSpeedStopGain = 0.5` on the low-speed lateral hold, brake stop and locked-wheel skid terms. Slope compensation is unchanged; cornering above ~0.5 m/s is unchanged.

**Evidence (portable harness, flat plane, real tire/suspension code):** 1.7.7 rocks at 1-12 deg/s and never completes a 2 s hold at most frame rates; 1.7.8 holds still (< 0.001 deg/s) in all 896 combinations of both cars, 30-240 fps, frame jitter, handbrake, brake, gear and roll inertia 200-1000 kg m^2. The completion limits are < 0.04 m/s and < 1.5 deg/s.

**Not verified:** Unreal itself. Chassis inertia and Chaos substepping are estimated in the harness. If the car still shimmers, send a clip plus the car (Ciaz/Swift) and frame rate.

Tests: `Tests/rest_stability_tests.cpp` (new). `dynamics_tests` and `power_handbrake_tests` now expect the 0.5 gain instead of an exact one-frame stop.
