#include "Player.hpp"
#include "RAddress.hpp"
#include "Offsets.hpp"
#include "ctrulib/util/utf.h"

namespace   CTRPluginFramework
{
    Player      *Player::_instance = nullptr;
    u32         Player::_playerPointer = 0;

    // Constructor
    Player::Player(void)
    {
        // Set pointers
        _coordinatePointer = reinterpret_cast<u32 *>(AutoRegion(USA_COORDINATES_POINTER, EUR_COORDINATES_POINTER, JAP_COORDINATES_POINTER)());
        _thought = reinterpret_cast<u16 *>(AutoRegion(USA_THOUGHT_ADDR, EUR_THOUGHT_ADDR, JAP_THOUGHT_ADDR)());
        _playerPointer = AutoRegion(USA_PLAYER_POINTER, EUR_PLAYER_POINTER, JAP_PLAYER_POINTER)();

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

    u32     Player::GetInventoryAddress(void) const
    {
        return (_offset + 0x6BD0);
    }

    /*
     * Coordinates
     */

    #define COORDINATES_OFFSET 0x24

    Coordinates Player::GetCoordinates(void) const
    {
        // If pointer isn't null
        if (*_coordinatePointer)
            return (*(reinterpret_cast<Coordinates *>(*_coordinatePointer + COORDINATES_OFFSET)));
        // Else return a zero filled struct
        Coordinates zero = { 0.f, 0.f, 0.f};
        return (zero);
    }

    void    Player::SetCoordinates(Coordinates pos) const
    {
        // If pointer isn't null
        if (*_coordinatePointer)
            *(reinterpret_cast<Coordinates *>(*_coordinatePointer + COORDINATES_OFFSET)) = pos;
    }

    void    Player::SetCoordinates(float x, float y, float z) const
    {
        // If pointer is null
        if (!*_coordinatePointer)
            return;

        reinterpret_cast<Coordinates *>(*_coordinatePointer + COORDINATES_OFFSET)->x = x;
        reinterpret_cast<Coordinates *>(*_coordinatePointer + COORDINATES_OFFSET)->y = y;
        reinterpret_cast<Coordinates *>(*_coordinatePointer + COORDINATES_OFFSET)->z = z;
    }

    void    Player::SetCoordinatesX(float x) const
    {
        // If pointer is null
        if (!*_coordinatePointer)
            return;

        reinterpret_cast<Coordinates *>(*_coordinatePointer + COORDINATES_OFFSET)->x = x;
    }

    void    Player::SetCoordinatesY(float y) const
    {
        // If pointer is null
        if (!*_coordinatePointer)
            return;

        reinterpret_cast<Coordinates *>(*_coordinatePointer + COORDINATES_OFFSET)->y = y;
    }

    void    Player::SetCoordinatesZ(float z) const
    {
        // If pointer is null
        if (!*_coordinatePointer)
            return;

        reinterpret_cast<Coordinates *>(*_coordinatePointer + COORDINATES_OFFSET)->z = z;
    }

    void    Player::AddToCoordinates(float xDiff, float yDiff, float zDiff) const
    {
        // If pointer is null
        if (!*_coordinatePointer)
            return;

        Coordinates *coord = reinterpret_cast<Coordinates *>(*_coordinatePointer + COORDINATES_OFFSET);
        
        coord->x += xDiff;
        coord->y += yDiff;
        coord->z += zDiff;
    }

    /*
     * Thought
     */

    void    Player::ThinkTo(u16 item) const
    {
        u32     patch = 0xE1A00000;

        *_thought = item;
        Process::Patch(0x002160BC, reinterpret_cast<u8 *>(&patch), 4); // nop the instruction that overwrites external thought bubbles
    }

    void    Player::UnThink(void) const
    {
        u32     original = 0xA000049;
        u32     value = 0;

        Process::Read32(0x002160BC, value);
        if (value == original)
            return;

        *_thought = 0x7FFE;
        Process::Patch(0x002160BC, reinterpret_cast<u8 *>(&original), 4);
    }

    /*
     * Name
     */

    #define NAME_OFFSET 0x55A8
    #define NAME_MAX 0x14

    std::string     Player::GetName(void) const
    {
        u8           buf[NAME_MAX + 1] = { 0 };

        // Convert game's name to utf8
        utf16_to_utf8(buf, reinterpret_cast<u16 *>(_offset + NAME_OFFSET), NAME_MAX);

        return (std::string(reinterpret_cast<char *>(buf)));
    }

    void    Player::SetName(std::string& name) const
    {
        u16           buf[NAME_MAX + 1] = { 0 };

        // If name is empty, abort
        if (name.empty())
            return;

        // Convert utf8 to utf16
        int res = utf8_to_utf16(buf, reinterpret_cast<const u8 *>(name.c_str()), NAME_MAX);

        // If conversion failed, abort
        if (res == -1)
            return;

        // Copy name to game
        Process::CopyMemory(reinterpret_cast<void *>(_offset + NAME_OFFSET), buf, NAME_MAX);
    }
}
