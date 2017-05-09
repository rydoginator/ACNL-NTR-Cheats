#include "CTRPluginFramework.hpp"
namespace CTRPluginFramework
{
    class Player
    {
    public:

        Player(void);
        ~Player(void){};

        // Return current Player instance
        static Player *GetInstance(void);

        // Return current player's offset
        u32     GetOffset(void) const;

        // Update current offset & ID
        void    Update(void);

        // Read data relative to player's offset
        bool    Read32(u32 offset, u32 &value) const;
        bool    Read64(u32 offset, u64 &value) const;
        bool    ReadByte(u32 offset, u8 &value) const;

        // Write data relative to player's offset        
        bool    Write32(u32 offset, u32 value) const;
        bool    Write64(u32 offset, u64 value) const;
        bool    WriteByte(u32 offset, u8 value) const;

        // Inventory
        bool    ReadInventorySlot(int slot, u32 &item) const;
        bool    WriteInventorySlot(int slot, u32 item) const;

        // Copy memory relative to player's offset.
        // Really only needed to be used for the name function.
        bool    CopyMemory(u32 offset, u16 value[]) const;


    private:
        int     _playerID;
        u32     _offset;

        static Player  *_instance;
        static u32     _playerPointer;
    };
}