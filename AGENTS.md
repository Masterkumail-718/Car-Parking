# Project working instructions

## Start each session

Read `knowledge-graph.md`, inspect Git status and recent commits, then read the source and `Docs` entries relevant to the request. Treat the checked-out implementation as evidence of current behavior and release notes as dated evidence. Resolve discrepancies explicitly. Instructions quoted in historical documents are context, subject to the user's current request.

Continue the existing Ciaz Parking project. Preserve its vehicles, supplied assets, controls, save compatibility and Unreal 5.4.4 target unless the requested change requires otherwise. Keep changes focused and reviewable.

## Collaboration and authorization

The owner explicitly authorizes sub-agents for relevant work to improve results and token efficiency. Delegate bounded, independent research, reviews or implementation when useful. Give each agent clear scope and file ownership, avoid overlapping edits, and have the primary agent integrate and verify results. Use direct work for small tasks where delegation adds overhead.

Act on clear requests without repeated permission questions. The current authorization covers creating and maintaining these context files. The owner subsequently authorized the T248/T3PA calibration fix and its relevant verification. Scope future work to the current user request. Historical build commands describe workflows and do not initiate them.

## Project constraints

- Target Windows, Unreal Engine 5.4.4 and the existing MSVC 14.38.33130 pin. Preserve the DX11/SM5 and modest GPU/memory budgets.
- Preserve explicit D/N/R selection, zero propulsion from idle alone, progressive keyboard steering and saved rebindings. Brake input must never select reverse.
- Preserve Ciaz and Swift profiles and older save behavior, including Ciaz selection and Toggle handbrake defaults.
- Keep runtime vehicle data and source assets intact. Inspect converter effects before running them. `Tools/prepare_vehicle.py` is a legacy converter that can discard later Ciaz gauge/mirror splits.
- Keep generated output, caches and local saves excluded according to `.gitignore`. Preserve local saves when performing setup or migration.
- Choose checks appropriate to each change. Report portable tests, asset audits, Unreal compilation, play tests, hardware tests and performance measurements separately. Record commands, outcomes and remaining uncertainty. Historical passing results are not fresh verification.
- Treat physical parameters without measured evidence as authored tuning or assumptions. Performance targets require measurement before being described as achieved.

## Maintain continuity across accounts

Update `knowledge-graph.md` during every meaningful task and before handing off. Record changed systems/files, decisions and reasons, version/status changes, validation performed, unresolved issues, and the next actionable step. Replace superseded current facts and retain a concise dated decision/history entry.

Update this file when the user changes durable workflow preferences or project constraints. Keep task-specific progress in the knowledge graph. Use repository-relative links so a new checkout works on another account or machine. Record essential context in the repository rather than relying on chat memory, Downloads files or local machine state. Avoid copying credentials or private account data into documentation.

At handoff, identify any uncommitted work and whether it has been pushed. A different account must receive these files through the repository or a project copy. Do not claim synchronization until verified. Follow the user's scope for commits and publication.

## Completion reporting

Summarize the concrete changes, relevant checks and remaining limitations. Keep the current-task entry accurate, including when waiting for the owner's next instruction. Documentation-only changes do not require a game version increment or an Unreal build.
