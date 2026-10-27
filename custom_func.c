#include "platform.h"
#include "device_board.h"
#include "can_boot_transport.h"
#include "user_def.h"
#include "sw_crc32.h"

unsigned char CAN_BootInstalledValid(void)
{
    unsigned long size, entry;
    unsigned short offset;
    const unsigned char __far *table;
    if (ImageMetadataValidate((const unsigned long __far *)APP_MANIFEST_ADDRESS) !=
        IMAGE_METADATA_OK)
    {
        return 0U;
    }
    size = *(const unsigned long __far *)(APP_MANIFEST_ADDRESS + IMAGE_MANIFEST_SIZE_OFFSET);
    if (caculate_crc32_checksum(APP_FLASH_START, size - 4UL) !=
        *(const unsigned long __far *)(APP_FLASH_START + size - 4UL))
    {
        return 0U;
    }
    table = (const unsigned char __far *)APP_FLASH_START;
    for (offset = 0U; offset < 256U; offset += 4U)
    {
        if (table[offset] != 0xECU)
        {
            return 0U;
        }
        entry = (unsigned long)table[offset + 1U] | ((unsigned long)table[offset + 2U] << 8) |
                ((unsigned long)table[offset + 3U] << 16);
        if (entry < APP_FLASH_START + 0x200UL || entry >= APP_FLASH_START + size - 4UL)
        {
            return 0U;
        }
    }
    return 1U;
}

static unsigned char __saddr g_custom_flash_status, g_custom_timed;

void hardware_init(void)
{
    unsigned long request;
    unsigned char valid;
    request = *(volatile unsigned long __far *)(BOOT_APP_SHARED_RAM_ADDRESS + 12UL);
    *(volatile unsigned long __far *)(BOOT_APP_SHARED_RAM_ADDRESS + 12UL) = 0UL;
    g_custom_timed = (unsigned char)(request == BOOT_APP_RESET_TO_BOOT_SIGNATURE);
    if (!Device_BoardInit())
    {
        for (;;)
        {
            BSP_NOP();
        }
    }
#if CAN_BOOT_DEBUG_UART
    Device_Log("F24 CAN DEVICE BOOT: X1=4M PLL80 CPU/CAN40 Classical500K\r\n");
#endif
    valid = CAN_BootInstalledValid();
    if (valid && !g_custom_timed && (P13 & 0x80U))
    {
        Device_Jump();
    }
    if (!CAN_BootInit())
    {
#if CAN_BOOT_DEBUG_UART
        Device_Log("CAN init failed; no Flash operation\r\n");
#endif
        for (;;)
        {
            Device_Heartbeat();
        }
    }
    g_custom_flash_status = Device_FlashInit();
    P6 &= 0xBFU;
    g_custom_timed = (unsigned char)(valid && g_custom_timed);
}

void loop(void)
{
    signed long result;

    result = CAN_BootReceive(APP_FLASH_START, g_custom_flash_status, g_custom_timed);
    if (result > 0L)
    {
#if CAN_BOOT_DEBUG_UART
        Device_Log("END CRC OK; resetting to revalidate app\r\n");
#endif
        *(volatile unsigned long __far *)(BOOT_APP_SHARED_RAM_ADDRESS + 8UL) =
            BOOT_APP_UPDATE_COMPLETE_SIGNATURE;
        Device_Reset();
    }
    if (result == CAN_BOOT_RESULT_TIMEOUT && CAN_BootInstalledValid())
    {
        Device_Jump();
    }
    g_custom_timed = 0U;
#if CAN_BOOT_DEBUG_UART
    Device_Log("Boot session stopped; recovery mode, result=");
    Device_LogHex((unsigned long)result);
    Device_Log("\r\n");
#endif
}
