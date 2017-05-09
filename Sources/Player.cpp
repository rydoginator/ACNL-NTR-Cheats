#include "Player.hpp"
#include "RAddress.hpp"
#include "Offsets.hpp"

namespace   CTRPluginFramework
{
    Player      *Player::_instance = nullptr;
    u32         Player::_playerPointer = 0;

    // Constructor
    Player::Player(void)
    {
        // Set _playerPointer
        AutoRegion address(USA_PLAYER_POINTER, EUR_PLAYER_POINTER, JAP_PLAYER_POINTER);
        
        _playerPointer = address();

        // Read _offset
        Update();

        if (_instance != nullptr)
            delete _instance;
        // Init _instance for GetInstance()
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
        Process::Read32(_playerPointer, _offset);
    }

    /*
     * Read
     */

    bool    Player::Read32(u32 offset, u32 &value) const
    {
        return (Process::Read32(offset + _offset, value));
    }

    bool    Player::Read64(u32 offset, u64 &value) const
    {
        return (Process::Read64(offset + _offset, value));
    }

    bool    Player::ReadByte(u32 offset, u8 &value) const
    {
        return (Process::Read8(offset + _offset, value));
    }

    /*
     * Write
     */

    bool    Player::Write32(u32 offset, u32 value) const
    {
        return (Process::Write32(offset + _offset, value));
    }

    bool    Player::Write64(u32 offset, u64 value) const
    {
        return (Process::Write64(offset + _offset, value));
    }

    bool    Player::WriteByte(u32 offset, u8 value) const
    {
        return (Process::Write8(offset + _offset, value));
    }

    /*
     * Inventory
     */
    bool    Player::ReadInventorySlot(int slot, u32 &item) const
    {
        return (Read32(0x6BD0 + (slot * 4), item));
    }

    bool    Player::WriteInventorySlot(int slot, u32 item) const
    {
        return (Write32(0x6BD0 + (slot * 4), item));
    }

    bool    Player::CopyMemory(u32 offset, u16 value[]) const
    {
        u32     address = offset + _offset;

        if (!Process::CheckAddress(_offset))
            return (false);
        return (Process::CopyMemory((void *) address, value, 0x14));
    }
}
