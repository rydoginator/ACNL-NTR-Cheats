#ifndef CTRPLUGINFRAMEWORK_SYSTEM_HOOK_H
#define CTRPLUGINFRAMEWORK_SYSTEM_HOOK_H

#include "types.h"

namespace CTRPluginFramework
{
    union   HookStatus
    {
        struct
        {
            bool    isEnabled : 1;  ///< Hold the hook's status
            bool    useLinkRegisterToReturn : 1;    ///< Enable the use of bx lr to return from callback. LR will be properly restored after the callback is executed | Default: true
            bool    ExecuteOverwrittenInstructionBeforeCallback : 1;    ///< If the instruction overwriten by the hook (target) must be executed before the callback | Default: true
            bool    ExecuteOverwrittenInstructionAfterCallback : 1;     ///< If the instruction overwritten by the hook (target) must be executed after the callback | Default: false
        };
        u32     raw;
    };

    enum class HookResult
    {
        Success,
        InvalidAddress,     ///< The target address was not reachable
        AddressAlreadyHooked,   ///< A hook is already enabled to the same address
        TooManyHooks,       ///< You attained the maximum of enabled hooks (current limit: 91)
        HookParamsError,     ///< The parameters of your hook seems off
        TargetInstructionCannotBeHandledAutomatically ///< The target's instruction is position dependant (PC) hence using ExecuteOverwrittenInstructionBeforeCallback or ExecuteOverwrittenInstructionAfterCallback is impossible.
    };

    struct  Hook
    {
        HookStatus  flags{};  ///< See HookStatus
        u32         targetAddress;  ///< The address to hook from
        u32         returnAddress;  ///< The address to return to after callback | Default: targetAddress + 4
        u32         callbackAddress;   ///< The address of the callback
        u32         overwrittenInstr;
        u32         index;

        Hook();

        /**
         * \brief Initialize hook target and callback
         * \param targetAddr The address to hook from
         * \param callbackAddr The callback to be called by the hook
         * \param returnAddr Optional return address. If not passed (0) then the return address is targetAddr + 4
         */
        void        Initialize(u32 targetAddr, u32 callbackAddr, u32 returnAddr = 0);

        /**
         * \brief Apply the hook
         * \return Return the result of the operation (see HookResult for more infos)
         */
        HookResult  Enable(void);

        /**
         * \brief Disable the hook
         */
        void        Disable(void);
    };
}

#endif
