# RL78/F24 MCU CAN device Boot

此工程提供 Classical CAN 更新、App 驗證與完整普通中斷轉送。
`RL78_F24_CAN_Transfer`、`RL78_F24_Boot_loader_CAN` 與 `RL78_F24_Boot_loader_CAN_app` 是三個獨立專案，放在同一父目錄。

## 硬體與分區

| 項目 | 設定 |
| --- | --- |
| MCU | R7F124FPJ5xFB，256 KiB Flash／24 KiB RAM |
| Clock | X1 4 MHz → PLL 80 MHz → CPU／CAN 40 MHz |
| CAN | P10 TX／P11 RX／P12 STB LOW；Classical 500 kbit/s |
| Upgrade IDs | Standard request 0x700／response 0x701；raw 0x720..0x727 |
| Transfer IDs | Standard request 0x710／response 0x711 |
| 診斷 UART | Transfer／App：P15 TX／P16 RX，115200 |
| 板上操作 | SW1 P137 LOW 進 Boot；LED P66／P67 active LOW |
| Image contract | Target 0xF24B、IRQ ABI F2V1、protocol 5／image format 6 |

| Flash／RAM address | 用途 |
| --- | --- |
| 0x00000..0x01FFF | 8 KiB Boot、實體向量與 option bytes |
| 0x02000..0x020FF | App 64 組 4-byte BR 表 |
| 0x02100..0x0217F | 128-byte metadata core |
| 0x02180..0x021FF | 128-byte metadata reserved FF |
| 0x02200 起 | App startup／code／constants |
| App start + image size - 4 | 全映像 CRC32，排除此末端 4 bytes |
| 0x3FC00..0x3FFFF | 保護區，不納入 App 更新 |
| 0xFF710..0xFF71F RAM | no-init handoff；IRQ owner Boot=AA／App=55 |

分區、metadata 格式、MCU 身分、IRQ ABI、政策與 Boot 版本集中於 `image_metadata_config.h`。
CAN 設定位於 `can_boot_config.h`，共用 RAM／owner 位於 `boot_app_handoff.h`。
執行時解析／驗證使用獨立 `image_metadata.c/.h`，比對值由 `image_metadata_profile.c` 提供。
Boot／App 各自編譯共用來源；API 與移植條件見 [Metadata C 模組](https://released.github.io/slide_boot_loader_for_RL78/#device-metadata-parser)。
產生器讀取三份明確來源，不重複維護 CAN ID／速率；詳細設定分工見 [Device 設定](https://released.github.io/slide_boot_loader_for_RL78/#device-app-config)。
最大 App 容量為 252928 bytes；實際 BIN 長度由 map 決定。
封裝檢查保留至少 512 bytes Boot 餘裕，並核對完整向量表、metadata、RAM RFD 執行鏈及 Flash 範圍。

線路資料：[RL78/F24 Target Board](https://www.renesas.com/en/products/microcontrollers-microprocessors/rl78-low-power-8-16-bit-mcus/rtk7f124fpc01000bj-rl78f24-r7f124fpj-target-board)。
接線時依實際 transceiver 規格確認供電／standby，並核對共地、終端與 bitrate。

## PowerShell 建置

使用 Windows PowerShell 5.1／.NET 與 CS+ CC-RL，不需另外安裝腳本執行環境。
在 Boot 專案目錄執行：

```powershell
# Transfer、Boot、App clean rebuild
.\build.ps1 -Kind all
# 只建置 App
.\build.ps1 -Kind app
# 離線 artifact／metadata／IRQ／ROM／RAM 檢查
.\test.ps1
# 可選：加入 production C 模型及 Tool BIN parser；需 MSVC x64
.\test.ps1 -ToolProject <Tool repository>
# 可選：Transfer 錯誤擷取與通訊模型；需 MSVC x64
.\test.ps1 -TransferModels
```

CS+ pre-build 呼叫 `tools/prepare_projects.ps1`，post-build 呼叫 `tools/package_images.ps1`。
App 編輯 `app_image_config.h` 與 `app_irq_handlers.h`；產生器輸出 metadata INC／ASM wrapper、identity 與向量表。
生成檔可檢查，不作為手動編輯入口。

SC 重新產生後，執行 `tools/prepare_projects.ps1 -Kind all` 整理專案再建置；
一般 App 更新使用 `-Kind app`，保留 Boot。
完整編輯、來源登錄、IRQ hex 位址出處及驗證步驟見
[MCU CAN device Metadata／Vector 設定](https://released.github.io/slide_boot_loader_for_RL78/#device-metadata-vector-workshop)。

## 安裝與更新

| 產物 | 使用方式 |
| --- | --- |
| Transfer `<project>.hex` | 燒錄器安裝獨立通訊測試工程，Tool 選 Custom Transfer |
| Boot `boot0000_1FFF.hex` | 燒錄器初裝 Boot |
| App `flash_app_variable_CRC.hex` | 燒錄器初裝 App，已填入 metadata／CRC |
| App 根目錄 `boot_app.hex` | 合併 Boot 與 App 的初裝映像 |
| App `*_update.bin` | Tool CAN TAB 更新 App |
| App `DefaultBuild/app_build_report.html` | 瀏覽器核對實際 BIN metadata、CRC／SHA-256、位址與向量表 |

初裝使用 Boot HEX 與 App HEX。
原始 App MOT 含 device file 自動附入的實體記錄，封裝程式會將其排除。
更新操作見 [CAN device App 更新](https://released.github.io/slide_isp_tool_for_RL78/#mcu-can-device)。

Boot 重置後驗證 metadata、全部 BR entries 與全映像 CRC。
一般中斷經固定完整轉送介面進 App；App 新增 ISR 時，登錄該 App 的來源與 C header，再單獨建置 App。

## 驗證範圍

`app_image_config.h` 的 `APP_IMAGE_VERSION_CONTROL` 預設為 `0U`，允許任意 App 版本。
有效 App 設為 `1U` 時，一般更新接受同版／新版；只比較 App major／minor／patch。
Boot 版本與 App 版本各自獨立，App 最低 Boot 版本由配對契約產生。
設定與產物見 [Device 設定](https://released.github.io/slide_boot_loader_for_RL78/#device-app-config)，
單次降版操作見 [Tool 版本政策](https://released.github.io/slide_isp_tool_for_RL78/#force-old-version)。

三個專案的 clean rebuild、封裝與離線模型已檢查。
500K 正常 App 更新、END CRC、reset 後 APP_READY／live INFO 與 UART counter 已完成實板驗證，
操作與 F13 device 相同；報告及畫面見 [F24 device 更新結果](https://released.github.io/slide_isp_tool_for_RL78/#f24-device-update-example)。
其他速率、IRQ、取消及斷電復原依各條件分別驗證。
CAN 速率修改見 [Device CAN 速率配置](https://released.github.io/slide_boot_loader_for_RL78/#device-can-bitrate)，
Boot／App 同名 ISR 與向量轉送見 [中斷所有權](https://released.github.io/slide_boot_loader_for_RL78/#device-irq-ownership)。
量測、編譯器警告及實際測試結果保留於 `HANDOFF.md`。
