#include "Helpers/Hook.hpp"
#include "CTRPluginFramework/System/Process.hpp"
#include <cstring>

static void  generate_jump_code(u32 jump_addr, u32 *jump_code)
{
    jump_code[0] = 0xE51FF004; // LDR   PC, [PC, #-4]
    jump_code[1] = jump_addr;
}

Hook::Hook(void)
{
    isInitialized = false;
    isEnabled = false;
    targetAddress = 0;
    afterHookAddress = 0;
    memset(targetCode, 0, 8);
    memset(jumpCode, 0, 8);
    memset(returnCode, 0, 16);
}

void    Hook::Initialize(u32 address, u32 callbackAddr)
{
    if (isInitialized)
        return;

    isEnabled = false;
    targetAddress = address;
    afterHookAddress = address + 8;

    // Backup original code
    if (!CTRPluginFramework::Process::CopyMemory(targetCode, (void *)address, 8))
        goto error;

    // Generate jump instruction
    generate_jump_code(callbackAddr, jumpCode);

    // Create return code
    if (!CTRPluginFramework::Process::CopyMemory(returnCode, (void *)address, 8))
        goto error;

    generate_jump_code(targetAddress + 8, &returnCode[2]);

    isInitialized = true;
    return;

error:
    isInitialized = false;
}

void    Hook::DeInitialize(void)
{
    if (!isInitialized)
        return;

    if (isEnabled)
        Disable();

    isInitialized = false;
}

void    Hook::Enable(void)
{
    if (isEnabled || !isInitialized)
        return;

    if (CTRPluginFramework::Process::CheckAddress(targetAddress, 7))
        if (CTRPluginFramework::Process::CopyMemory((void *)targetAddress, jumpCode, 8))
            isEnabled = true;
}

void    Hook::Disable(void)
{
    if (!isEnabled || !isInitialized)
        return;

    if (CTRPluginFramework::Process::CheckAddress(targetAddress, 7))
        if (CTRPluginFramework::Process::CopyMemory((void *)targetAddress, targetCode, 8))
            isEnabled = false;
}
