#include "player.hpp"
namespace   CTRPluginFramework
{
    #define READU8(x) *(u8 *)(x)

    u32         g_playerId;
    Player      *Player::_instance = nullptr;

    // Constructor
    Player::Player(void)
    {
        Update();

        if (_instance != nullptr)
            delete _instance;

        _instance = this;
    }

    // Return current player's ID
    int     Player::GetId(void) const
    {
        return (_playerID);
    }

    // Return current player's offset
    u32     Player::GetOffset(void) const
    {
        return (_offset);
    }

    // Update Player's infos
    void    Player::Update(void)
    {
        _playerID = READU8(g_playerId);
        _offset = _playerID * 0xA480;
    }

    // Write data relative to player's offset
    template <typename T>
    bool    Player::Write(u32 offset, T value) const
    {
        u32     size = sizeof(T);
        u32     address = offset + _offset;

        // Check for the address to exists and be editable
        if (!Process::CheckAddress(address))
            return (false);

        return (Process::Patch(address, (u8 *)&value, size));
    }
}