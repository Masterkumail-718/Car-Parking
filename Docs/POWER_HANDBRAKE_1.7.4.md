# Beta 1.7.4 — 110 hp and rear-wheel handbrake lock

Close Unreal and back up the existing project. Extract this complete project and
run SetupProject.cmd "D:\Unreal\UE_5.4". All earlier materials, settings, suspension
and curb changes are included. Test in Standalone Game.

## Engine
The custom torque curve peaks at 110 mechanical horsepower (82.03 kW) at 6000 RPM.
Peak torque is approximately 145 Nm at 4200 RPM. This is an authored gameplay tune,
not a claim about measured output of a particular 2017 Ciaz engine variant.
The existing 86% drivetrain efficiency means less power reaches the driven front
wheels. There is still no idle propulsion. Automatic shift points now vary with
throttle, allowing full throttle to reach the power band instead of always
upshifting at 3100 RPM. Fuel cut begins at 6400 RPM.

## Handbrake
The existing parking-brake binding (Space by default) remains a toggle: press to
engage, press again to release. Rebinding still works.

Engaging locks the rear wheels in the model and stops their visual rotation.
Rear tire forces switch from rolling cornering forces to a shared sliding-friction
force opposing the complete contact-patch velocity. It acts at the rear contacts,
so a turning car can lose rear grip and develop oversteer through chassis physics.
Front steering and front-wheel drive remain active. A straight pull does not
inject sideways force or scripted yaw. Sliding grip is load-sensitive, reaching
72% of rolling grip above the low-speed transition; it is an approximation for
dry road tires, not measured tire data or a universal surface coefficient.

Low-speed static hold is preserved. Releasing the handbrake blends the rear tires
back to rolling grip over 0.22 seconds and restores visual rolling speed. There is
no forced drift animation, teleport, angle clamp or artificial yaw impulse.

## Validation and limits
Portable tests pass for the 110 hp curve maximum, forward/reverse skid opposition,
combined skid-force limits, lower rear cornering grip when locked, zero lateral
force in a straight pull, unchanged front-tire forces, low-speed holding and
unsupported tires. Existing driving, suspension, UI and asset audits also pass.

Unreal compilation and integrated handling have not been tested here. The car may
need grip/recovery tuning after actual driving tests at 30/60/120 FPS. Tire forces
still update on the game thread. Rear lock is an immediate binary constraint,
not a simulated cable, brake-disc torque or independent wheel-inertia solver.
Release rotation is blended, not derived from a full rotating-wheel drivetrain.
A slide depends on speed, steering, load and available grip; pulling at walking
speed is not intended to guarantee a drift.

Test on open ground: accelerate in D, turn, engage Space briefly, then release
Space and countersteer. Compare a straight pull and a low-speed parking stop.
Test reverse separately and ensure front-wheel steering is retained. Check wheel
rotation from chase view and that the parked car holds on a modest slope.
