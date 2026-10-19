# F24 MCU CAN device projects

- Read README.md, HANDOFF.md and SELF_CHECK.md first. This is the 4MHz target
  board with its own Transfer/Boot/App projects.
- image_metadata_config.h owns IMAGE_* geometry/metadata/policy/Boot identity;
  can_boot_config.h owns CAN, boot_app_handoff.h owns RAM/owner. Generators
  read these three explicit sources; do not copy values or use CAN aliases.
  Keep 8KiB Boot/App2000 and
  at least 512 bytes spare; mandatory packaging guards may not be bypassed.
- Do not edit generated smc_gen or vendor RFD. Use common overrides/projections.
- Handwritten embedded C90, block-start declarations, English comments.
- Preserve complete normal IRQ forwarding, App-local registered ISR mappings,
  256-byte metadata/CRC, fail-closed range checks and RAM-only RFD call chain.
- F13/F24 CAN device Boot/App are joint golden samples for future MCU ports.
  Align common metadata/vector/build behavior before introducing another MCU.
  Both devices take priority over F24 host; keep host changes out of this work.
- Independently compile the common image_metadata.c/.h plus the project
  image_metadata_profile.c in Boot/App. Keep local copies identical to Tool
  firmware/common/device_metadata (sync_device_metadata.ps1). Parser has no CAN/
  Flash API; preserve all validation with detailed/compact status options,
  C90/32-bit/endian/alignment guards and existing CRC/launch decisions.
- App users edit app_image_config.h and app_irq_handlers.h. Generate
  metadata INC/wrapper, identity and vector table in App pre-build; reject
  stale linked metadata before packaging. No JSON or manual INC fallback.
- tools/app_config.ps1 is an identical local copy of the golden C-header reader;
  preserve common syntax and strict validation in both independent Boot repos.
- Windows PowerShell5.1/.NET only for prepare/package/test; no Python runtime.
  Preserve Boot ownerAA/App55 and verify compiled dispatch.
- Device magic is CAN plus NUL (0x004E4143). Policy3 uses metadata0x74 for
  APP_IMAGE_VERSION_CONTROL, the sixth App define. A valid installed App
  controls ordinary START; enabled means same/newer only. FORCE_START0E skips
  only ordering for that update. Preserve other gates and no persistent unlock
  or stored version floor; invalid-App recovery is unrestricted by version.
- Boot/App releases are independent; generated minimum Boot is a lower bound,
  not an equality comparison with the App version or build date.
- tools/app_build_report.ps1 matches the common golden report helper.
  Emit App HTML only after linked-image checks; use actual BIN/CRC/hash/vector
  data and distinguish build evidence from live MCU/hardware evidence.
- build.ps1 clean rebuild + post-build audit; test.ps1 for safe offline checks.
- Transfer-only CAN diagnostics use F24_DEVICE_TRANSFER guards in common;
  poll/clear raw C0ERFL bits0..14, never callback TDCV masks. Keep Boot/App
  binaries unchanged by Transfer changes. test.ps1 -TransferModels covers
  production register/protocol logic with UART trace enabled and disabled.
  No COM/flashing/power tests without scope/authorization. Report NOT RUN.
- Sync related Tool MD/web/PDF when changing behavior. Preserve unrelated
  project outputs; App-only configuration must not rewrite Boot images.
