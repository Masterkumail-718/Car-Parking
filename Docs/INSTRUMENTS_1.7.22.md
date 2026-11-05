# Beta 1.7.22 instrument lighting

Both Ciaz and Swift use dedicated runtime instrument material instances. The existing headlight toggle updates their Backlight parameter immediately, from zero to authored strength 1.2. Dial markings emit warm white through a brightness/UV-region mask; needle meshes emit red. Bodywork, shared atlas regions and exterior materials retain their original materials. Ciaz decorative fuel/temperature needle meshes also illuminate, without adding fuel/temperature simulation.

[build_instruments.py](../Tools/build_instruments.py) generates the shared lit material and imports the two atlas copies under `/Game/Materials/Instruments`. Regular setup calls it after Swift material creation. Runtime source assets, mesh animation groups and save formats are preserved. The main moving gauge needles remain; no new light components, captures or per-frame material updates were added.

[InstrumentSource](../Tools/InstrumentSource) contains the runtime artwork copies. Ciaz_Dials.png uses built-in imagegen edits to remove the long main pointers in the two lower dial islands of dash221.4_baseColor.png. The final edit is composited only over those two circular dial regions; the rest of the original atlas remains. Generated dial lettering may differ slightly within the edited regions. The original is unchanged in Content/VehicleData/Textures. Swift_Dials.png is a byte-identical copy of Sticker_baseColor.png, whose main dial faces were already free of painted moving pointers; the generated alternative was not applied because it altered unrelated lettering. Small fuel/temperature artwork remains.

Imagegen prompt: Remove only the long baked-in main speedometer/tachometer needles, reconstruct matching dark dial faces, preserve numbers, ticks, rims, small fuel/temperature needles, all other atlas artwork, orientation and UV layout. Built-in imagegen was used, not the fallback CLI. Ciaz and Swift were inspected separately.

Validation and remaining checks are recorded in [knowledge-graph.md](../knowledge-graph.md). Use the existing setup/build workflows; preserve local saves. Visual brightness is authored tuning and performance has not been benchmarked.

Ciaz follow-up: the mask includes the outer numeral/tick band, and dim source markings receive a Ciaz-only luminance lift with 3x gain. Swift retains its accepted original brightness response. See the knowledge graph for save/verification status.
