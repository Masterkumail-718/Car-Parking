# Validation status

## Passed in the authoring environment
- Standalone C++17 rules compiled with GCC 13, warnings as errors.
- Automatic braking never changes direction selector.
- Forward/reverse direction guards.
- Manual clutch requirement, stall state and restart guard.
- Sequential gear selection.
- Progressive steering, hold on release, opposite steering and centering.
- One collision per contact episode, re-impact after separation, failure at three.
- Full vehicle footprint and heading checks, stationary hold and failure precedence.
- 447,992 triangles converted into 73 render batches.
- Binary lengths, index bounds, finite attributes, unit normals and clockwise winding.
- Four consistent wheel pivots and a separately rotating steering assembly.
- Approximately 449 cm length and 265 cm wheelbase.
- Texture references resolve; images decode and fit the 1024-pixel maximum.
- Six audio files contain valid mono 16-bit PCM.
- Unreal project JSON, Python syntax and local source include references.

## Not yet run
Unreal 5.4.4 is not installed here. No claim is made that the Unreal module has compiled, the editor setup script has run, a Windows package has been produced, the car has been driven in-engine, or the target FPS has been reached.

## Windows acceptance sequence
1. Run SetupProject.cmd; confirm the module builds and Parking map opens.
2. Start Standalone Game; inspect car sections, UV orientation, glass and wheel positions.
3. Stop with S in automatic mode; verify it never selects reverse.
4. Hold D, release, verify angle remains; hold X to centre.
5. Select manual first gear with clutch; release at rest and check stall/restart.
6. Verify suspension settles, tires grip, and brakes hold at zero.
7. Scrape continuously: one collision. Separate and strike again: a new collision.
8. Reach three impacts: immediate failure, even during parking validation.
9. Park partially outside or backward: no completion. Align and stop: completion after 2 s.
10. Check sensor direction, beep frequency and continuous very-close tone.
11. Complete every level and confirm a navigable route.
12. Restart; check progress, bindings and settings persist.
13. Calibrate the physical T248; verify all pedals, paddles and manual clutch.
14. Test low force feedback, correct centering, pause, focus loss and unplugging.
15. Package Windows and repeat gameplay tests outside the editor.
16. Benchmark RX 470 4 GB / 8 GB RAM at 720p Low and RTX 2060 Super at 1080p Medium. Record CPU SKU, driver, average FPS, 1% low, peak RAM and VRAM.
17. Tune handling, cameras and sensors against the owner's reference videos.

## Test commands
Portable rules:

    g++ -std=c++17 -Wall -Wextra -Werror Tests/core_tests.cpp -o core_tests
    ./core_tests

Asset validator, Python with numpy and Pillow:

    python Tests/validate_assets.py

These checks do not substitute for Unreal or physical-wheel validation.
