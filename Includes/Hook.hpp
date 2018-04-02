#ifndef HOOK_H
#define HOOK_H

#include "types.h"

union   HookStatus
{
    struct
    {
        bool    isInitialized : 1;
        bool    isEnabled : 1;
        bool    isPcSavingHook : 1;
    };
    u32     raw;
};
struct  Hook
{
    HookStatus  flags;
    u32         targetAddress;
    u32         afterHookAddress;
    u32         targetCode[3];
    u32         jumpCode[3];
    u32         returnCode[5];

    Hook();
    void        Initialize(u32 targetAddr, u32 callbackAddr, bool savePC = false);
    void        DeInitialize(void);
    void        Enable(void);
    void        Disable(void);
};

#endif
