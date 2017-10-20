#include "cheats.hpp"
#include "Helpers.hpp"
#include "CTRPluginFramework/Utils/Utils.hpp"


namespace CTRPluginFramework
{
    static const u8 	v1plugin[] = {
        0x86, 0xFF, 0xFF, 0xEB,
        0x18, 0x10, 0x8F, 0xE2,
        0xD0, 0x00, 0xC1, 0xE1,
        0xC7, 0x07, 0x00, 0xEB, //< BL svcSleepThread
        0x74, 0xFF, 0xFF, 0xEB,
        0xD0, 0xFA, 0xFF, 0xEB,
        0xF9, 0xFF, 0xFF, 0xEA
    };
    static const u8 	v2plugin[] = {
        0x1F, 0x05, 0x00, 0xEB,
        0x08, 0x00, 0x95, 0xE5,
        0x00, 0x10, 0xA0, 0xE3,
        0x7B, 0x0B, 0x00, 0xEB, //< BL svcSleepThread
        0x7B, 0x01, 0x00, 0xEB,
        0xEF, 0xFF, 0xFF, 0xEA
    };
    void    ExitThread(void)
    {
        svcExitThread();
    }

    struct PluginLoaderInfos
    {
        u32 plgCount;
        u32 plgBufferPtr[32];
        u32 plgSize[32];
        u32 arm11BinStart;
        u32 arm11BinSize;
        u32 tid[2];
        u32 gamePluginPid;
        u32 gamePluginMenuAddr;
    };

    extern "C" u32      __c_bss_start;

    void    CloseOthersPluginsThreads(u32 address)
    {
        u32     bss = (u32)&__c_bss_start;
        Hook    hook[5]; //< Five plugins seems enough case ?
        PluginLoaderInfos   *plgLoaderInfos = reinterpret_cast<PluginLoaderInfos*>(address);

        if (plgLoaderInfos->plgCount == 1)
            return; ///< Only one plugin loaded which is this one

        for (int i = 0; i < plgLoaderInfos->plgCount; i++)
        {
            if (bss >= plgLoaderInfos->plgBufferPtr[i]
                && bss < plgLoaderInfos->plgBufferPtr[i] + plgLoaderInfos->plgSize[i])
                continue; ///< This is the current plugin

            u8  *startPlg = reinterpret_cast<u8 *>(plgLoaderInfos->plgBufferPtr[i]);
            u32 sizePlg = plgLoaderInfos->plgSize[i];

            // Search for v1 pattern
            u8  *location = memsearch(startPlg, v1plugin, sizePlg, sizeof(v1plugin));

            // If we didn't found the pattern, try v2
            if (location == nullptr)
                location = memsearch(startPlg, v2plugin, sizePlg, sizeof(v2plugin));

            // If we found a pattern
            if (location != nullptr)
            {
                // Go to svcSleepThread call
                location += 12;

                // Init our hook
                hook[i].Initialize(reinterpret_cast<u32>(location), reinterpret_cast<u32>(ExitThread));
                // Enable it
                hook[i].Enable();
            }
        }
    }
}
