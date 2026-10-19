# F24 MCU CAN device handoff

## Normal App1.0.3 hardware acceptance (2026-10-19)

User JSON/HTML update_20261019_044520 confirms4224B/CRCCF1C72F8,66blocks,
4340ms total and575ms post-reset confirmation. Live App1.0.3/build20261019
matches image identity/geometry/IRQ/policy; CAN_STOP PASS, Host COM retained.
User UART capture shows boot-validated/update-completed/V1 counter0..26.
Normal115200/500K update and App execution are verified, same Tool sequence
as F13. This does not resolve prior post-completion errors or establish
high-rate, precision timer, other IRQ, stress/cancel/disconnect/power acceptance.

Public operation gallery is f24-device-update-example in the ISP guide;
canonical SHARED_CONSOLE_TOOL_DEVICE_MEDIA contains the two public PNGs.
Related MD/site status and4PDFs updated after9PDF review.38focused tests,
310refs/content/mirrors/24safe-clean checks and1366/390 browser PASS;4PDF/
69page render/visual QA. No firmware/source/binary rebuild or agent COM/Flash.

## App runtime log and device tutorial (2026-10-19)

User-supplied update report confirms App1.0.2/4152B/CRC6ABF121D normal CAN500K
update and post-reset APP_READY;4302ms total/65blocks/586ms confirmation.
Post-completion BUS_ERROR/ERROR_PASSIVE remains separate, unqualified evidence.

App-only1.0.3/build20261019 now uses app_runtime_log.h V1/V2 tag and a main-loop
one-second decimal counter, starting0. App-only formatter .c/.h registered in
MTPJ; timer/board/Boot/CAN defaults unchanged. Clean build0errors/5existing
license/device-file warnings;4224B/CRCCF1C72F8. BIN SHA256
DB3BD26F87EAEE2797431DF626597D452382D00112C3214B71BA7587CCD5C81F.
Boot HEX129DF147018D823669203126F67E60A570A336124CB5B261D951BEE45C2D808D
and Transfer HEX remain unchanged; Boot spare514. Nine artifact checks and
production metadata/block/Tool models PASS; strictC90 decimal boundaries,
buffer guards,32-bit wrap and V1/V2 inputs PASS.

Tool DEVICE_METADATA_VECTOR_WORKSHOP owns device-can-bitrate,
device-irq-ownership and device-app-runtime-log. Complete source/timing/mask/
rebuild/install/Tool verification applies to both device samples.34focused
tests, MD/web/source/public/reference/24safe-clean checks PASS;24page6diagram
PDF and1366/390 web inspected. F13 source/artifacts and host/PC binaries not
changed. No new App board run,250K/1M, fault/power tests, COM write or push.

## Transfer CAN diagnostics (2026-10-19)

Transfer main now polls/clears raw C0ERFL bits0..14 before protocol processing,
feeding the existing saturated warning/passive/bus-off counters and250ms
coalesced UART trace. Callback TDCV masks and the high-byte-only vendor getter
are not used for this decoder. Startup prints verified clock configuration,
actual initialization result/stage/global/channel status/filter/P12 latch.
All adapter additions are guarded by F24_DEVICE_TRANSFER; generated/vendor
drivers, protocol packets, identities and Boot/App runtime are unchanged.

Transfer clean rebuild0errors/2license warnings. Boot0/2 and App0/5 clean
rebuilds preserve delivery SHA256 exactly: Boot129DF147018D823669203126F67E60A570A336124CB5B261D951BEE45C2D808D;
App4690E533111BEA3F709F5011D739917C07D1F920E0294EB89D63AC857B3CBF4C.
Boot end1DFD/spare514; no Transfer diagnostics symbols in Boot/App maps.
Nine artifact/negative checks, production metadata/block/Tool parser models,
strict-C90 production CAN/protocol models with trace1/0, and20 Tool source/
public-guide/PDF regressions PASS. Tests cover init failures/waits,15 flags/
write-zero masks, counter saturation/clear, throttle/tick wrap and TX timeout.
Local MD/ISP section/PDF synchronized;10page/4diagram PDF rendered and checked.
Source/reference/anchor/public-content and24safe-clean checks PASS. Source
sync helper has read-only drift and missing-marker tests. Evidence is local
Tool tmp/internal/transfer_diagnostics and Boot tmp/build,tmp/tests/transfer.
No board: physical CAN/ACK/fault/recovery NOT RUN; no COM/flash/Git push.

## Independent metadata runtime module (2026-10-17)

Boot/App separately compile portable image_metadata.c/.h and project-specific
image_metadata_profile.c. The core includes image_metadata_config.h only:
no CAN driver/header, Flash writer or reset dependency. CAN metadata staging
and SEAL remain in can_boot_metadata.inc. Boot/END use full256-byte validation;
App INFO reads use bounded LE32 decoding, not a full-image validation claim.
CRC/version-floor/Flash/launch checks remain in their existing layers.
F13/F24 share identical core C/header maintained through the Tool sync script;
profile/config and hardware remain project-local. CS+ preparation registers
separate compilation units once. F24 compact BAD_IMAGE results are retained;
IMAGE_METADATA_DETAILED_STATUS is nonserialized and does not alter acceptance.

Final clean Boot0errors/2warnings, App0/5. End1DFD/spare514 with512guard;
RFD RAM reference guards PASS. App4152bytes/CRC6ABF121D. Executable bytes
change with the extraction; format/layout/protocol/IRQ ABI/version unchanged.
Nine PS checks and production C/Tool fault models,12 portable strict-C90
combinations and shared54 regressions PASS. Native Debug/Release and final
independent App A/B builds PASS, original Boot SHA256 unchanged. MD/local
web/three PDFs50pages/6diagrams and visual review synchronized. F24 host
and Tool runtime untouched. No board: physical CAN/Flash/IRQ/power NOT RUN.
No COM writes, commit/push or website publication. Detailed evidence is in
Tool tmp/internal/metadata_parser, app_ab and web_review.

## Metadata header ownership (2026-10-17)

image_metadata_config.h owns IMAGE_* format/MCU/Flash/policy/IRQ/Boot identity;
can_boot_config.h owns CAN only, boot_app_handoff.h owns BOOT_APP_* RAM/owner.
Consumers, explicit three-header reader, tests and CS+ header registrations
are aligned with the F13 golden workflow; App release/IRQ inputs are unchanged.
Boot clean build0errors/2warnings, App0/5; both delivery SHA256 unchanged.
Boot end1DFD/spare514 and RAM-only RFD guards pass. Nine PS checks and production
C/Tool parser models, standalone C90 headers, shared51 regressions and native
Debug/Release PASS. Independent A/B App clean builds preserve original Boot.
Related MD/web/three PDFs synced and visually checked. Hardware NOT RUN;
no host/Tool runtime edits, COM writes, Git push or website publication.

## Version policy and Boot budget (2026-10-17)

Boot1.1.0/App1.0.2 use CAN+NUL magic and UPD1 policy3; sixth App define
APP_IMAGE_VERSION_CONTROL defaults0, metadata0x74. Installed valid App enables
same/newer-only normal START; invalid-App recovery has no stored floor.
FORCE_START0E skips only ordering for one transaction; other contract/Flash
checks remain. Tool's public3036 confirmation is not authentication.
Boot/App versions/builds are independent. Input comments and shared MD/web/PDF
document legal values, policy operation and minimum Boot compatibility.

Clean Boot0errors/2warnings, App0/5; App BIN3988B/CRC00110089.
Boot last1DFD/spare514 passes unchanged8KiB/min512 guards;14 RAM functions/
19 references checked. Deduplicated INFO constants and shared write exit keep
this budget without removing validation. Tool native Debug/Release models,
nine PS checks,63 regressions and independent App A/B policy1/0 builds pass.
A/B does not change original Boot HEX SHA. ROM comparison vs F13 is an internal
map/object measurement in Tool tmp/internal/version_policy, not an App reserve
issue. Hardware unavailable; CAN/RFD/IRQ/power NOT RUN. No publication.

## Commented inputs and App HTML (2026-10-17)

App image/IRQ headers document edit conditions and INTTM01 vector2E source.
tools/app_build_report.ps1 matches the F13/common PowerShell helper; App
post-package emits DefaultBuild/app_build_report.html with actual BIN metadata,
CRC/hash/all byte addresses and full64slot table. Build Error0/Warning5;
App BIN and Boot HEX SHA256 unchanged. Shared tests and MD/web/PDF synchronized.
Browser/hardware NOT RUN. Version policy not yet implemented; no Boot runtime
or Flash mapping change. Evidence in Tool tmp/internal/device_build_report.

## C-header golden authoring (2026-10-17)

F13/F24 CAN device Boot/App are joint reference baselines. App editing inputs
are app_image_config.h and app_irq_handlers.h, registered in CS+; local
tools/app_config.ps1 is identical to the common header reader. Pre-build,
post-build and independent App A/B workflow use these headers only.
JSON inputs removed after preserving their values in headers and source ZIPs
under the Tool tmp/internal/c_header_golden directory. No JSON fallback.

App clean build without Python on PATH: Error0/Warning5,3948B/CRC02A02C02,
BIN SHA unchanged. Strict C90 header fixture and nine PowerShell checks plus
production C/PC models PASS. Independent App A/B clean builds pass, original
Boot HEX hash unchanged. Shared golden tooling/tests and MD/web/PDF aligned.
Physical CAN/RFD/IRQ/power acceptance NOT RUN; no publication.

## Generated artifacts and App readiness (2026-10-17)

App pre-build now emits ftable.inc, app_identity.h, app_irq_table.inc and
ftable_RL78_F24.asm; Boot dispatch is f24_boot_vectors.asm. App deliveries use
flash_app_variable_CRC.hex, flash2000_3FBFF.hex, *_update.bin and boot_app.hex/bin.
Transfer delivery uses the project-stem HEX. Obsolete generated outputs are
recoverably archived under the Tool tmp/internal/update_observability folder.

App INFO1B reports initialization/clock/CAN/timer readiness, Boot handoff,
completed update and reset flags. App version1.0.1, BIN3948B/CRC02A02C02.
All three clean builds pass with existing warnings; Boot HEX hash unchanged,
highest1DFD/spare514. Nine PowerShell checks and production C/PC models PASS.
Independent temporary App A/B projects compile/package with distinct IRQ
mappings; original Boot HEX hash unchanged. Physical CAN/RFD/IRQ tests NOT RUN.

## PowerShell build and unified IRQ owner (2026-10-16)

Production prepare/package/test now use Windows PowerShell5.1/.NET.
New tools: device_common.ps1, prepare_projects.ps1, package_images.ps1 and
test_device.ps1; build.ps1/test.ps1 and all three MTPJ pre/post hooks call them.
Original Python helpers are archived in the Tool's disposable
tmp/internal/public_editorial/python_reference, with complete before-state ZIP;
no required source or build dependency uses that archive.

Boot owner remainsAA; App owner is55. A clean rebuild without any Python
command on PATH passed all three projects: Transfer Error0/Warning2,
Boot Error0/Warning2, App Error0/Warning5. Boot extent1DFD/spare514,
14 RAM Flash functions/19 references; App3876B/CRC B4BEBC0C.

Comparison against the before-state archive parses HEX records to bytes:
Boot changed exactly303/337 fromA5 to55 (dispatch compare and handoff store).
App/Transfer HEX byte content is unchanged; App update BIN SHA-256 unchanged.
HEX text hashes differ because the .NET packager groups records differently.

Nine production PowerShell artifact/negative tests PASS with Python absent
from PATH. Optional production C RAM metadata/block/CRC and unmodified Tool
parser/policy tests PASS. The independent dispatcher stack model was also
run against the rebuilt AA/55 image, covering all normal vectors/four banks.
No COM/device Flash/hardware IRQ or bus traffic, Git upload or host changes.
Reader documentation uses MCU CAN device flows and points to JSON key sources.

Current implementation: Transfer + 8KiB CAN Boot + independent App, Classical
500K. Source/clean builds and safe host models only; hardware NOT RUN.

## Build evidence

JSON-only App authoring (2026-10-16): app_image.json uses the same five-field
schema as F13 CAN device; app_irq_handlers.json remains App-local. App pre-build
now generates app_metadata.generated.inc and its registered ASM wrapper, plus
identity and vectors. Post-build compares linked metadata against JSON/Boot
contract before size/CRC patching; stale linked data is rejected. Clean App
rebuild Error:0/Warning:5, same 3876-byte BIN/CRC B4BEBC0C. No Boot rebuild,
host changes or device writes. Step-by-step reader route is the Tool's
DEVICE_METADATA_VECTOR_WORKSHOP_zh-TW.md / device-metadata-vector-workshop web
section. Invalid JSON and App-only generation are tested in temporary projects.

- CC-RL V1.15.01, Olite/goptimize/symbol-delete. Three clean builds Error:0.
- Boot ROM highest non-monitor byte 0x1DFD, extent 7678 bytes, spare 514 bytes
  before App2000. This includes RFD ROM load copies and fixed Boot records;
  it is address-space extent, not just C code instruction size.
- No Boot UART logging. Transfer/App independent UART115200 remains enabled.
- Boot full normal vectors04..7C; App 64-entry BR table and RETI/RETB defaults.
- Map audit:14 Flash helper/RFD functions in RAM,19 map-visible RAM references,
  four equal-size ROM/RAM copy pairs; 4KiB stack, handoff RAM excluded.
- Current App BIN3876 bytes, CRC32 B4BEBC0C. These are measurements, not fixed
  capacity/version assumptions or public web titles.
- Transfer/Boot each have2 W0561017 license warnings; App additionally has3
  W0561520 device-file option warnings. No compile errors; no paid-only -Os.
- Seven artifact/IRQ stack model tests + production C metadata/block/CRC fault
  model + unmodified Tool BIN parser/policy checks PASS. These do NOT execute
  actual RFD hardware, simulate whole MCU power loss, or measure CAN throughput.

## Changed responsibilities

Boot owns protocol, pre-erase metadata seal, block CRC/replay, RFD and final
launch gates. common owns 4MHz clock/pins/polled Classical CAN. App owns its
image identity, local interrupt mapping, INFO/ENTER and heartbeat. Transfer
owns non-destructive Custom Transfer710/711, separate from Upgrade700/701.
Source names F13_Crc32Bytes/F13_CRC_HOST_TEST are retained from the copied,
table-free F13 CRC implementation; they do not select F13 geometry or driver.

prepare_projects.ps1 reconciles registered sources and generates projections;
App-only mode preserves App-registered user source files and does not write
Boot. Existing scaffold source files are retained uncompiled. Original input
shell backup is disposable Tool tmp evidence, never a build dependency.

## Next hardware work

Verify board IC2 supply/standby, 4MHz X1/PLL and CAN500K on Transfer first.
Then initial-program Boot HEX + packaged App HEX, inspect App UART115200,
Tool live identity, ENTER/reset/update, retry/abort/timeout and power-fault
matrix. Save Tool log + PCAN trace + post-reset App evidence. Do not claim
F24 hardware validation based on F13 logs or host-model success.

Do not directly flash raw App MOT (auto-generated physical records included).
Use packaged App *_flash.hex or CAN *_update.bin only. No source push or
hardware write was performed by this implementation turn.
