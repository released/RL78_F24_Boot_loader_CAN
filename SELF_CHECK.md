# Verification gates

## CRC64KiB address carry (2026-10-22)

- [x] CRC sources identical across three devices;integer carry,unchanged CRC.
- [x]109native boundary/BIN checks,target carry/reload and unsafe mutation gate.
- [x] Boot/App clean0errors;spare512;9artifact/negative checks and actual PC/
  parser/RAM models PASS. Generated minimum-Boot/CRC/combined images updated.
- [ ] Physical cross64KiB Flash update/reset/APP_READY NOT RUN.

## English README structure (2026-10-19)

- [x] Transfer/Boot/App entry points English, aligned with F13 organization
  and independently checked against F24 sources, artifacts and web anchors.
- [x] Five read-only README tests PASS; no source/binary/build/hardware change.

## Publication data exclusion (2026-10-19)

- [x] User-approved removal of15 tmp paths from Git index; all local files
  remain with identical SHA256. Project-specific .gitignore added to all
  three F24 projects; eight release deliveries and actual HEADs unchanged.
- [x] Script-owned staged output removals cleared selectively with backed-up
  indices; files remain in the original recoverable publication archive.
- [x] Six-repo read-only preview PASS; pending tmp removals accepted without
  accepting pre-staged source changes. No commit/push or hardware operation.

## User normal App update acceptance (2026-10-19)

- [x] App1.0.3/4224B/CRCCF1C72F8 normal500K update,66blocks,END/CRC,
  APP_READY/live comparison and CAN_STOP confirmed by user's saved report.
- [x] UART capture confirms boot-validated/update-completed/V1 counter0..26.
- [x] Two public PNGs/16operation images, MD/web/4refreshedPDFs synchronized;
  38focused tests/310refs/24safe-clean/browser and69page PDF review PASS.
- [ ] Other rates/IRQ/stress/cancel/disconnect/power and prior post-completion
  errors remain separate. No agent COM/flashing/compilation/publication.

## App counter / device CAN rate / IRQ ownership (2026-10-19)

- [x] App-only1.0.3/20261019 clean0errors/5existing warnings;4224B/CRCCF1C72F8;
  V1 observation tag and main-loop decimal counter, no ISR UART work.
- [x] Boot HEX SHA256 unchanged/spare514; Transfer HEX unchanged; nine checks
  and production C/Tool models PASS. Native C90 V1/V2 formatting bounds/wrap PASS.
- [x] Both-device driver/mask/paired build/program/Tool tutorial and separate
  link same-name ISR/AA55/no-vect explanation; MD/web/PDF synchronized.
- [x]34focused tests,304refs/public-content/24safe-clean and1366/390 browser
  PASS; PDF24pages/6diagrams rendered and visually reviewed.
- [x] User evidence confirms preceding App1.0.2 normal500K update/CRC/App;
  later BUS_ERROR/ERROR_PASSIVE is not hidden or counted as fault-free acceptance.
- [x] App1.0.3 normal update/physical UART counter verified by later user report.
- [ ] Precision IRQ timing,250K/1M and fault/power
  NOT RUN. No agent COM/Flash, F13/host runtime edits or publishing.

## Transfer diagnostics isolation (2026-10-19)

- [x] Main-loop capture/clear of raw15 Classical flags; saturated counters,
  last flags,250ms UART throttle and actual startup stage/status/STB output.
- [x] Transfer clean0errors/2warnings; Boot0/2 and App0/5 rebuilt with identical
  delivery hashes; Boot spare514 and no Transfer diagnostics map symbols.
- [x] Nine artifact/contract checks and production metadata/block/Tool models;
  strict-C90 Transfer register/protocol tests with trace1/0 PASS.
- [x]20 source/sync/public-guide/PDF regressions and MD/ISP mirror, local refs,
  content and24safe-clean checks PASS. Updated10page/4diagram PDF inspected.
- [ ] Physical CAN/ACK, error injection/recovery and timing NOT RUN; no board,
  COM writes, device Flash operations, publishing or host firmware changes.

## Portable metadata C module (2026-10-17)

- [x] Portable C/header plus project profile separately compiled by Boot/App;
  CAN staging separate, Boot complete validation and App bounded LE32 reads.
- [x] Common-source equality/C90 dependency boundaries/CS+ once-only entries;
  serialized contract, CRC/Flash/launch gates and compact status preserved.
- [x] Final clean Boot0errors/2warnings, App0/5; end1DFD/spare514 with512guard,
  RFD RAM guards and App4152bytes/CRC6ABF121D PASS.
- [x] Nine PS checks, production C/Tool models,12 strict-C90 combinations,
  shared54 regressions, native Debug/Release and both App A/B builds PASS;
  original Boot SHA256 unchanged by App-only builds.
- [x] MD/local web/PDF synchronization;50pages/6diagrams visual/render QA,
  four browser routes/25diagrams,248refs and24safe-clean scripts PASS.
- [ ] Physical CAN/Flash/IRQ/power NOT RUN: no board. No F24 host/Tool runtime
  edits, EXE rebuild, COM write, commit/push or website publication.

## Independent image metadata header (2026-10-17)

- [x] IMAGE_* image contract / CAN transport / BOOT_APP_* RAM headers separated;
  explicit reader and Boot/App consumers/CS+ entries aligned.
- [x] Boot0errors/2warnings, App0/5; Boot HEX/App BIN SHA256 unchanged;
  end1DFD/spare514 and RFD RAM guards preserved.
- [x] Nine PS checks, production C/Tool model, C90 independent header compile,
  shared51 regressions and native Debug/Release PASS.
- [x] Independent App A/B clean builds preserve original Boot; MD/web/three
  PDFs synchronized, rendered and visually checked.
- [ ] CAN/RFD/IRQ/power hardware NOT RUN; no board or publication.

## Version policy / force START (2026-10-17)

- [x] Policy3, CAN+NUL, six-field C-header generation and defaultflag0.
- [x] Full valid installed-image CRC before policy baseline; same/newer normal
  updates, older normal rejection and command-local force without saved state.
- [x] Clean Boot Error0/Warning2; App0/5,3988B/CRC00110089. Boot end1DFD,
  spare514 >=512;14 Flash RAM functions/19 references pass closure checks.
- [x] Nine PS checks + production C/PC models;63 shared regressions and native
  Debug/Release models PASS. Both independent A/B policy/IRQ builds PASS;
  original Boot SHA unchanged by App-only builds. MD/web/PDF synchronized.
- [ ] Hardware CAN/RFD/IRQ/power/high-speed checks NOT RUN: no board available.

## Device App HTML (2026-10-17)

- [x] Commented C input headers and identical standalone PS5.1 report helper.
- [x] App clean build Error0/Warning5; BIN and Boot HEX SHA256 unchanged.
- [x] Actual BIN CRC/hash,256 byte addresses,64 vector rows and negative report
  cases tested; shared workshop MD/web/PDF synchronized.
- [ ] HTML browser/hardware checks NOT RUN; no version-policy runtime change.

## C-header golden authoring (2026-10-17)

- [x] App image/IRQ configuration uses two C headers; CS+ registration,
  pre/post hooks and no-Python build verified. No JSON input/fallback.
- [x] Same local reader as F13; strict literal/guard/duplicate/IRQ validation.
- [x] Clean App build Error0/Warning5; strict C90 header fixture PASS.
- [x] Nine PS checks + production C/PC models and independent A/B builds PASS.
- [x] Original Boot and packaged App SHA-256 unchanged.
- [ ] Physical CAN/RFD/IRQ/reset/power tests NOT RUN.

## Artifact naming and readiness checks (2026-10-17)

- [x] Three clean builds PASS; generated registrations and delivery names align
  with the device App workflow. Boot HEX hash unchanged; spare514.
- [x] App INFO1B health support; final BIN3948B/CRC02A02C02.
- [x] Nine PowerShell artifact checks plus production C/PC models PASS.
- [x] Independent App A/B clean compile/link/package with different IRQ
  mappings; original Boot HEX SHA-256 unchanged.
- [ ] Physical readiness/IRQ/RFD/CAN/power and post-update acceptance NOT RUN.

## Current PowerShell / AA55 checks

- [x] All three clean rebuilds complete with Python removed from process PATH.
- [x] Pre/post hooks, metadata generation, S-record/map parsing and HEX/BIN
  packaging use Windows PowerShell5.1/.NET only.
- [x] Owner BootAA/App55; real HEX changes only dispatcher compare/store bytes.
- [x] Nine PowerShell checks PASS, including stale JSON, invalid mappings,
  read-only generation, ROM/RAM/vector/partition corruption and S-record CRC.
- [x] Optional production C/PC models PASS; App BIN and App/Transfer HEX content
  match the archived baseline.
- [ ] Physical CAN/RFD/reset/IRQ/power-fault acceptance NOT RUN.

- [x] JSON-only App identity + IRQ inputs; generated metadata INC linked at
  App+100h. Strict schema/contract and stale linked metadata rejection tested.
- [x] App-only clean rebuild after migration; same BIN size and CRC, no Boot
  writes. Temporary App schema/IRQ/output checks and existing safe tests PASS.
- [x] Clean rebuild Transfer, Boot, App; mandatory post-build audit PASS.
- [x] Boot8KiB / spare512 / App2000 / code2200 / last1KiB protected.
- [x] 256-byte metadata reserve, actual-size BIN and tail CRC generated.
- [x] Physical vector ownership, full App table, real timer RETI bytes checked.
- [x] Actual dispatcher stack/register model covers all normal vectors,
  four IRQ-owner values and four register banks.
- [x] App-local mapping A/B and invalid entries; no Boot file changes.
- [x] RFD ROM/RAM copies, RAM function addresses, map-visible references,
  stack and handoff overlap guards; deliberate corruption tests rejected.
- [x] Production C RAM helpers: wrong metadata/role/rate/ABI/reserved, malformed
  staging, CRC failure, out-of-order/duplicate/conflicting/missing segments,
  partial block lengths and replay boundaries. No simulated Flash writes.
- [x] Production Tool parser accepts actual F24 BIN and rejects bad CRC;
  policy rejects I2C/Misc routes. PC runtime sources unchanged.
- [ ] Register-level CAN backend model / actual F24 bus traffic NOT RUN.
- [ ] RFD erase/write, board reset/recovery, post-update App, cancel/timeout,
  disconnect and power-fault acceptance NOT RUN on hardware.
- [ ] A separate user App project with additional IRQs compiled/flashed on
  hardware NOT RUN; map generation test is not that acceptance test.

Run build.ps1 then test.ps1; optional -ToolProject adds production PC parser.
Any source/SC change invalidates previous build evidence until rebuilt.
