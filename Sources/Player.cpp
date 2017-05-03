#include "Player.hpp"
namespace   CTRPluginFramework
{


    u32     g_playerPointer;
    Player      *Player::_instance = nullptr;

    // Constructor
    Player::Player(void)
    {
        Update();

        if (_instance != nullptr)
            delete _instance;

        _instance = this;
    }

    // Return current Player's instance
    Player  *Player::GetInstance(void)
    {
        return (_instance);
    }

    

    // Return current player's offset
    u32     Player::GetOffset(void) const
    {
        return (_offset);
    }

    // Update Player's infos
    void    Player::Update(void)
    {
        Process::Read32(g_playerPointer, _offset);
    }


    // Write data relative to player's offset
    //template <typename T>
    bool    Player::Write(u32 offset, u32 value) const
    {
        u32     size = sizeof(value);
        u32     address = offset + _offset;

        // Check for the address to exists and be editable
        if (!Process::CheckAddress(_offset))
            return (false); 
        return (Process::Patch(address, (u8 *)&value, size));
    }

    bool    Player::Read(u32 offset, u32 &value) const
    {
        u32     address = offset + _offset;

        if (!Process::CheckAddress(_offset))
            return (false);
        return (Process::Read32(address, value));
    }


    bool    Player::WriteSlot(int slot, u32 item)
    {
        if (!Process::CheckAddress(_offset))
            return (false); 
        return (Write(0x6BD0 + (slot * 4), item));
    }

    bool    Player::ReadSlot(int slot, u32 &item) const
    {
        if (!Process::CheckAddress(_offset))
            return (false);
        return (Read(0x6BD0 + (slot * 4), item));

    }

    bool    Player::CopyMemory(u32 offset, u16 value[]) const
    {
        u32     address = offset + _offset;

        if (!Process::CheckAddress(_offset))
            return (false);
        return (Process::CopyMemory((void *) address, value, 0x14));
    }
}