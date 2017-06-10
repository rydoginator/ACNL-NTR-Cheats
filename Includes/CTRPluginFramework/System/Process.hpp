#ifndef CTRPLUGINFRAMEWORK_PROCESS_HPP
#define CTRPLUGINFRAMEWORK_PROCESS_HPP

#include "ctrulib/svc.h"
#include <string>

namespace CTRPluginFramework
{
    class Process
    {
    public:
         
        /**
         * \brief Get current process handle (already open, don't close it)
         * \return Return current process handle (already open, don't close it)
         */
        static Handle   GetHandle(void);

        /**
         * \brief Get current process ID
         * \return Return current process ID
         */
        static u32      GetProcessID(void);
         
        /**
         * \brief Get the title ID of the current process
         * \return TitleID of the current process 
         */
        static u64      GetTitleID(void);

        /**
         * \brief Get the title ID of the current process as string
         * \param output    std::string to append the titleid to \n
         * output isn't clear
         */
        static void     GetTitleID(std::string &output);

        /**
         * \brief Get the name of the current process
         * \param output    string to output the process name
         */
        static void     GetName(std::string &output);

        /**
         * \brief Get the version of the current process
         * \return The version of the current processs
         */
        static u16      GetVersion(void);

        /**
         * \brief Get the total size of the .text section
         * \return The total size of the .text section
         */
        static u32      GetTextSize(void);

        /**
        * \brief Safely patch the current process (MemPerm check and Invalidate cache)
        * \param addr      The address to start the patch
        * \param patch     The patch values
        * \param length    The length of the patch values in bytes
        * \param original  If defined, the original values will be copied to this buffer (size must be enough)
        * \return  If the patch was successful or not
        */
        static bool     Patch(u32 addr, void *patch, u32 length, void *original = nullptr);
            
        /**
        * \brief Safely patch the current process (MemPerm check and Invalidate cache)
        * \param addr      The address to start the patch
        * \param patch     The patch value
        * \param original  If defined, the original values will be copied to this buffer (size must be enough)
        * \return  If the patch was successful or not
        */
        static bool     Patch(u32 addr, u32 patch, void *original = nullptr);
            
         
        /**
        * \brief Protect the memory by settings Read & Write perm
        * \param addr      Address from start protecting
        * \param size      Size to protect
        * \param perm      The permission to apply (RWX by default)
        * \return If the protection was successful or not
        */
        static bool     ProtectMemory(u32  addr, u32 size, int perm = (MEMPERM_READ | MEMPERM_WRITE |MEMPERM_EXECUTE));
            

        /**
         * \brief Protect the entire region where addr belongs to
         * \param addr      An address
         * \param perm      The permissions that must be applied to the region 
         * \return  If the protection was successful or not
         */
        static bool     ProtectRegion(u32 addr, int perm = (MEMPERM_READ | MEMPERM_WRITE |MEMPERM_EXECUTE));

        /**
         * \brief Protect all regions within the provided range
         * \param startAddress  The address from the range starts
         * \param endAddress    The address from the range ends
         * \param perm          The permissions that muse be applied to the regions
         */
        static void     ProtectRegionInRange(u32 startAddress, u32 endAddress, int perm = (MEMPERM_READ | MEMPERM_WRITE |MEMPERM_EXECUTE));

        /**
         * \brief Safely copy the current process memory (MemPerm check) \n Like a memcpy but safe
         * \param dst   The destination to copy to
         * \param src   The source to copy from
         * \param size  The size to copy in bytes
         * \return 
         */
        static bool     CopyMemory(void *dst, void *src, u32 size);

        /**
         * \brief Check if the address is available and have the specified permissions \n
         * If the address exists but don't have the specified permissions, it tries to change the permissions
         * \param address   The address to check
         * \param perm      The permissions that the address must have
         * \return If the address is valid and have the specified permissions or not
         */
        static bool     CheckAddress(u32 address, u32 perm = MEMPERM_READ | MEMPERM_WRITE);

        /**
         * \brief Safely write 64 bits
         * \param address   Address to write to
         * \param value     The value to write
         * \return True if success, false otherwise
         */
        static bool     Write64(u32 address, u64 value);

        /**
        * \brief Safely write 32 bits
        * \param address   Address to write to
        * \param value     The value to write
        * \return True if success, false otherwise
        */
        static bool     Write32(u32 address, u32 value);

        /**
        * \brief Safely write 16 bits
        * \param address   Address to write to
        * \param value     The value to write
        * \return True if success, false otherwise
        */
        static bool     Write16(u32 address, u16 value);

        /**
        * \brief Safely write 8 bits
        * \param address   Address to write to
        * \param value     The value to write
        * \return True if success, false otherwise
        */
        static bool     Write8(u32 address, u8 value);

        /**
        * \brief Safely write a float value
        * \param address   Address to write to
        * \param value     The value to write
        * \return True if success, false otherwise
        */
        static bool     WriteFloat(u32 address, float value);

        /**
        * \brief Safely write a double value
        * \param address   Address to write to
        * \param value     The value to write
        * \return True if success, false otherwise
        */
        static bool    WriteDouble(u32 address, double value);

        /**
         * \brief Safely read 64 bits
         * \param address   The address to read
         * \param value     The variable to put the value in
         * \return True if success, false otherwise
         */
        static bool     Read64(u32 address, u64 &value);

        /**
        * \brief Safely read 32 bits
        * \param address   The address to read
        * \param value     The variable to put the value in
        * \return True if success, false otherwise
        */
        static bool     Read32(u32 address, u32 &value);

        /**
        * \brief Safely read 16 bits
        * \param address   The address to read
        * \param value     The variable to put the value in
        * \return True if success, false otherwise
        */
        static bool     Read16(u32 address, u16 &value);

        /**
        * \brief Safely read 8 bits
        * \param address   The address to read
        * \param value     The variable to put the value in
        * \return True if success, false otherwise
        */
        static bool     Read8(u32 address, u8 &value);

        /**
        * \brief Safely read a float value
        * \param address   The address to read
        * \param value     The variable to put the value in
        * \return True if success, false otherwise
        */
        static bool     ReadFloat(u32 address, float &value);

        /**
        * \brief Safely read a double value
        * \param address   The address to read
        * \param value     The variable to put the value in
        * \return True if success, false otherwise
        */
        static bool     ReadDouble(u32 address, double &value);
    };
}

#endif