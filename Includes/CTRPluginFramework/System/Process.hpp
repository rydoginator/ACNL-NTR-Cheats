#ifndef CTRPLUGINFRAMEWORK_PROCESS_HPP
#define CTRPLUGINFRAMEWORK_PROCESS_HPP

#include "ctrulib/svc.h"

namespace CTRPluginFramework
{
    class Process
    {
        public:
            // Return current process handle (already open, don't close it)
            static Handle   GetHandle(void);
            // Return current process ID
            static u32      GetProcessID(void);
            // Copy current process ID in output as string
            static void     GetProcessID(char *output);  
            // Return current process title ID          
            static u64      GetTitleID(void);
            // Copy current process title ID in output as string
            static void     GetTitleID(char *output);
            // Copy current process name in output
            static void     GetName(char *output);
            // Return the status of the process (should always return 1)
            static u8       GetProcessState(void);

            // Safely patch the current process
            // The original data in the target address can be obtained by passing a pointer to a buffer
            static bool     Patch(u32 addr, u8 *patch, u32 length, u8 *original = nullptr);
            // Protect the memory by settings Read & write perm
            static bool     ProtectMemory(u32  addr, u32 size, int perm = (MEMPERM_READ | MEMPERM_WRITE |MEMPERM_EXECUTE));
            // Protect the entire region where addr belongs to
            // Return false if the addr doesn't exists or if the protect operation failed
            static bool     ProtectRegion(u32 addr, int perm = (MEMPERM_READ | MEMPERM_WRITE |MEMPERM_EXECUTE));

            // Protect all regions within the provided range
            static void     ProtectRegionInRange(u32 startAddress, u32 endAddress, int perm = (MEMPERM_READ | MEMPERM_WRITE |MEMPERM_EXECUTE));
            // Safely copy the current process memory
            static bool     CopyMemory(void *dst, void *src, u32 size);

            // Check if the address is available and have the corresponding permission
            // If the address exists but don't have the requiered permissions, it tries to change the permission
            // Return true if it exists and possess the permissions, else return false
            static bool     CheckAddress(u32 address, u32 perm = MEMPERM_READ | MEMPERM_WRITE);

            // Safely write 64 bits, return true on success, false otherwise
            static bool     Write64(u32 address, u64 value);
            // Safely write 32 bits, return true on success, false otherwise
            static bool     Write32(u32 address, u32 value);
            // Safely write 16 bits, return true on success, false otherwise
            static bool     Write16(u32 address, u16 value);
            // Safely write 8 bits, return true on success, false otherwise
            static bool     Write8(u32 address, u8 value);
            // Safely write a float value, return true on success, false otherwise
            static bool     WriteFloat(u32 address, float value);

            // Safely read 64 bits, return true on success, false otherwise
            static bool     Read64(u32 address, u64 &value);
            // Safely read 32 bits, return true on success, false otherwise
            static bool     Read32(u32 address, u32 &value);
            // Safely read 16 bits, return true on success, false otherwise
            static bool     Read16(u32 address, u16 &value);
            // Safely read 8 bits, return true on success, false otherwise
            static bool     Read8(u32 address, u8 &value);
            // Safely read float value, return true on success, false otherwise
            static bool     ReadFloat(u32 address, float &value);
    };
}

#endif