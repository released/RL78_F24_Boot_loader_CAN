# RL78/F24 CAN boot loader

CAN self-programming boot loader for Renesas RL78/F24 R7F124FPJ5xFB.

Start with the [Boot/App porting guide (zh-TW)](https://released.github.io/slide_boot_loader_for_RL78/#boot-app-porting)
and [C-header device workshop](https://released.github.io/slide_boot_loader_for_RL78/#device-metadata-vector-workshop)
for startup, linker, metadata and App IRQ authoring.

## Fixed reusable IRQ contract

Boot owns all 61 normal physical vectors `0x04..0x7C` through generated
assembly. Owner `0xAA` selects Boot handlers; `0x55` forwards to the fixed
App table. Reset stays in Boot; physical BRK `0x7E` is not forwarded.

The timer uses TAU0 channel 1, vector `0x2E` (`INTTM01`).
Compatible App projects add ISRs in their own `app_irq_handlers.h` and CS+
source list, then rebuild/update App only. Each ISR is global, uses
`#pragma interrupt` without `vect=` and returns RETI. Boot/App are separate
links, so both can use `Device_TimerIsr` as a function name.

Compatibility includes MCU/Flash, IRQ ABI, no-init RAM/startup, metadata/CRC
and CAN INFO/ENTER behavior. Unused interrupt sources stay masked; default
RETI does not acknowledge their causes. See [interrupt ownership](https://released.github.io/slide_boot_loader_for_RL78/#device-irq-ownership).

## Status

Normal Classical 500K update, END CRC, post-reset APP_READY/live identity and
the App UART counter are verified. See the [update result and UART captures](https://released.github.io/slide_isp_tool_for_RL78/#f24-device-update-example).
Other rates, additional IRQs, stress, cancellation, disconnect and power loss
have separate acceptance records.

Boot UART defaults off (`CAN_BOOT_DEBUG_UART=0U`). Compact metadata diagnostics
default to `BAD_IMAGE` (`IMAGE_METADATA_DETAILED_STATUS=0U`), retaining all
validation checks. Optional diagnostic controls depend on live capabilities;
this Boot does not advertise read-only VERIFY. App supplies APP_READY after
initialization and an observed timer IRQ.

## Public examples and checkout layout

- [CAN Transfer benchmark](https://github.com/released/RL78_F24_CAN_Transfer).
- [This Boot project](https://github.com/released/RL78_F24_Boot_loader_CAN).
- [Matching App project](https://github.com/released/RL78_F24_Boot_loader_CAN_app).
- [Tool operation](https://released.github.io/slide_isp_tool_for_RL78/#mcu-can-device).

Keep all three checkouts under the same parent using their exact names;
remove `-main` after ZIP extraction. Transfer/App use their own SC output
and this Boot project `common/` board sources and `tools/` helpers.
App also shares the image/CAN/RAM contracts.

Build Boot before App for an initial combined `boot_app.hex`.
A compatible App-only release does not rebuild Boot. Boot MOT/map are needed
when refreshing the combined installation image, not for App-only packaging.

## Hardware and CAN settings

| Item | Setting |
| --- | --- |
| MCU | R7F124FPJ5xFB; 256 KiB code flash, 24 KiB RAM |
| Clock | X1 4 MHz -> PLL 80 MHz -> CPU/CAN 40 MHz |
| CAN | Classical, standard 11-bit IDs, 500 kbit/s |
| Timing | BRP register 3; 20 TQ; TSEG1=15, TSEG2=4, SJW=1; sample point 80% |
| Pins | P10 TX / P11 RX; P12 LOW for normal transceiver operation |
| Update IDs | Request `0x700` / response `0x701`; raw data `0x720..0x727` |
| Image contract | Target `0xF24B`, IRQ ABI F2V1, CAN protocol 5, image format 6 |
| Debug UART0 | Transfer/App: 115200 8-N-1, P15 TX / P16 RX |
| Recovery input | SW1 on P137, active LOW |
| LEDs | P66 / P67, active LOW |

Board reference: [RL78/F24 Target Board](https://www.renesas.com/en/products/microcontrollers-microprocessors/rl78-low-power-8-16-bit-mcus/rtk7f124fpc01000bj-rl78f24-r7f124fpj-target-board).
Verify transceiver supply/standby, common ground and termination.
A logged P12 state is not a supply-voltage measurement.

CAN processing polls FIFO/TX results; the interval timer has a live ISR.
`common/f24_device_config.h` is the compiler preinclude for clock/timing
overrides. `can_boot_config.h` owns protocol IDs, rate declarations and filters.
For 250K/500K/1M, follow the [device bitrate procedure](https://released.github.io/slide_boot_loader_for_RL78/#device-can-bitrate),
rebuild and install the matching Boot/App. The Tool dropdown does not
reconfigure device firmware.

## Memory layout and metadata

| Range | Purpose |
| --- | --- |
| `0x00000..0x01FFF` | 8 KiB Boot, physical vectors and option bytes |
| `0x02000..0x020FF` | 64 four-byte App branch entries |
| `0x02100..0x0217F` | 128-byte metadata core |
| `0x02180..0x021FF` | 128 reserved bytes, `0xFF` |
| `0x02200..linked end` | App startup/code/constants |
| Final four image bytes | Little-endian CRC32, excluded from its calculation |
| `0x3FC00..0x3FFFF` | Protected last 1 KiB, outside the update range |
| `0xFF710..0xFF71F` RAM | No-init owner and one-shot handoff/update/ENTER signatures |

App capacity is `0x3DC00` (252928) bytes, not a required length. Packaging
derives the four-byte-aligned image length from linked sections and appends
CRC32. Boot packaging enforces 8 KiB and at least 512 bytes of unused space.

| File | Ownership |
| --- | --- |
| `image_metadata_config.h` | Format, MCU/Flash, policy, IRQ ABI and Boot identity |
| `can_boot_config.h` | CAN routing, compiled rate declarations and protocol |
| `boot_app_handoff.h` | No-init RAM, owner and signatures |
| App `app_image_config.h` | App release identity and version policy |
| App `app_irq_handlers.h` | App-local physical-vector-to-ISR mapping |

`image_metadata.c/.h` is independently compiled for metadata decode/validation;
`image_metadata_profile.c` provides expected fields. CAN staging and Flash
operations remain separate. See [metadata APIs](https://released.github.io/slide_boot_loader_for_RL78/#device-metadata-parser)
and the [byte/address reference](https://released.github.io/slide_boot_loader_for_RL78/#flash-metadata-can-reference).

## Boot decision

After board initialization, Boot validates metadata, all 64 branch entries
and CRC32 over the declared image except its trailer. Branches must target
code inside the image. App starts only when these checks pass and neither
the ENTER signature nor active SW1 requests Boot.

Invalid images, SW1 and App ENTER retain Boot. Clock failure blocks
progression; CAN initialization failure in recovery prevents programming.
ENTER from a valid App enables 30-second inactivity before accepted START.
Accepted request traffic refreshes the timer; expiry revalidates App before
returning. Invalid-App recovery and entry only through SW1 do not enable it.

After accepted START, timeout, ABORT or fatal update errors retain Boot.
Successful END validates metadata/CRC, records update provenance and resets.
Reset repeats installed-image checks before handoff. The
[device Boot flow](https://released.github.io/slide_boot_loader_for_RL78/#f24-can-device)
contains the full gate/timeout details.

CAN v5 stages all 256 metadata bytes in RAM: RESET `0x0A`, ordered METADATA
`0x08` chunks and SEAL `0x09` before START. Data uses 64-byte blocks: BEGIN
`0x0B`, raw frames on `0x720..0x727`, COMMIT `0x0C` and one ACK.
CRC/sequence checks precede writes; replaying the last committed block does
not rewrite Flash. See the [CAN update walkthrough](https://released.github.io/slide_isp_tool_for_RL78/#can-update-walkthrough).

## Build and artifacts

Use Windows PowerShell 5.1/.NET and CS+/CC-RL, without Python or SRecord.
Run from this Boot directory:

```powershell
.\build.ps1 -Kind all
# Boot only; use -Kind app for an App-only release.
.\build.ps1 -Kind boot
.\test.ps1
```

The helper prepares projects, invokes clean builds, checks the CS+ summary
and packages outputs. CS+ pre/post-build hooks run `tools/prepare_projects.ps1`
and `tools/package_images.ps1`. After SC regeneration, reconcile the selected
project before building; normal App work uses `-Kind app` to preserve Boot.

| File | Purpose |
| --- | --- |
| `DefaultBuild/boot0000_1FFF.hex` | Programmer-installed Boot-only image |
| `DefaultBuild/RL78_F24_Boot_loader_CAN.mot` / `.map` | Local compiler/section/RFD checks and combined-image input |
| App root `boot_app.hex` | Initial combined Boot/App installation |
| App `DefaultBuild/RL78_F24_Boot_loader_CAN_app_update.bin` | Tool CAN App update |

Git distribution retains only the Boot HEX in DefaultBuild; `tmp/` logs/tests
remain local. [Publication](https://github.com/released/simple_renesas_isp_tool/blob/main/docs/GITHUB_PUBLISH_zh-TW.md)
archives other outputs. Rebuild after pruning before artifact tests or
combined-image regeneration.

## Recovery and limitations

Full-image CRC reads use 32-bit byte-address arithmetic across 64 KiB Flash
boundaries. See the [CRC address reference](https://released.github.io/slide_boot_loader_for_RL78/#image-crc-linear-address)
for image ranges, trailer addresses and porting checks.

- The F24 RFD library executes the required programming code from RAM;
  packaging verifies its execution/reference ranges.
- Updates exclude Boot and the last 1 KiB. An App erase block is 1 KiB.
- CRC32 detects corruption, not authenticity. Signatures, encryption and a
  second-image rollback bank are not provided.
- The valid installed App controls normal version ordering:
  `APP_IMAGE_VERSION_CONTROL=0U` permits any version; `1U` permits same/newer.
  Compare App major/minor/patch, not build date or Boot version. Invalid-App
  recovery has no independent persistent version floor.
- Intentional downgrade uses the [single-update maintenance operation](https://released.github.io/slide_isp_tool_for_RL78/#force-old-version);
  other identity/policy/partition/IRQ/CRC gates remain active.
- Integrated debug testing starts from reset through Boot. Retain physical
  vectors/option bytes when loading App symbols. Build/model results and
  normal update evidence do not establish every debugger, IRQ or power test.

## Main files

| File | Responsibility |
| --- | --- |
| `boot_main.c` | Installed-image gates, recovery and handoff |
| `can_boot_transport.c` / `can_boot_block.inc` | CAN staging and block state machine |
| `image_metadata.c` / `.h` / `image_metadata_profile.c` | Independent metadata validator and expected fields |
| `image_metadata_config.h` / `can_boot_config.h` / `boot_app_handoff.h` | Image, CAN and RAM contracts |
| `common/device_board.c` / `common/device_can.c` / `common/f24_clock.c` | Board, timer, CAN polling and bounded clock setup |
| `f24_flash.c` / `RFDRL78T02/` | Flash wrapper and RFD library |
| `sw_crc32.c` / `.h` | Full-image CRC32 |
| `tools/prepare_projects.ps1` / `tools/package_images.ps1` | Project/vector generation and packaging |

Measurements and compiler warnings are in `HANDOFF.md`. The
[acceptance matrix](https://released.github.io/slide_isp_tool_for_RL78/#update-confirmation)
separates normal update evidence from high-rate and fault testing.
