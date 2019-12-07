#include "Player.hpp"
#include "RAddress.hpp"
#include "Offsets.hpp"
#include "cheats.hpp"
#include "ctrulib/util/utf.h"
#include <cstring>

namespace   CTRPluginFramework
{
    Player      *Player::m_instance = nullptr;
    u32         Player::m_playerPointer = 0;

    // Constructor
    Player::Player(void)
    {
        // Set pointers
        m_currentSlot = reinterpret_cast<u8 *>(AutoRegion(USA_PLAYER_SLOT, EUR_PLAYER_SLOT, JAP_PLAYER_SLOT, USA_WA_PLAYER_SLOT, EUR_WA_PLAYER_SLOT, JAP_WA_PLAYER_SLOT)());
        m_PlayerInfoBase = AutoRegion(USA_PLAYERINFO_POINTER, EUR_PLAYERINFO_POINTER, JAP_PLAYERINFO_POINTER, USA_WA_PLAYERINFO_POINTER, EUR_WA_PLAYERINFO_POINTER, JAP_WA_PLAYERINFO_POINTER)();
        m_thought = reinterpret_cast<u16 *>(AutoRegion(USA_THOUGHT_ADDR, EUR_THOUGHT_ADDR, JAP_THOUGHT_ADDR, USA_WA_THOUGHT_ADDR, EUR_WA_THOUGHT_ADDR, JAP_WA_THOUGHT_ADDR)());

        // Read _offset
        Update(); ///< This will block the plugin until the user loaded his savegame

        if (m_instance != nullptr)
            delete m_instance;
        // Init _instance for GetInstance()
        m_instance = this;
    }

    // Return current Player's instance
    Player  *Player::GetInstance(void)
    {
        if (m_instance == nullptr)
            m_instance = new Player();

        return (m_instance);
    }

    // Return current player's offset
    u32     Player::GetOffset(void) const
    {
        return (m_offset);
    }

    // Return current player's info offset
    u32     Player::GetInfoOffset(void) const
    {
        return (*m_PlayerInfoPtr);
    }

    // Update Player's infos
    void    Player::Update(void)
    {
        u32 value;

		//while game didnt init the Player/rfPlayerPTR, redo this.
		do {
			m_playerPointer = FollowPointer(0x80ECC20, 0x670, 0x234, -1);
			Sleep(Milliseconds(1));
		} while (m_playerPointer == -1);

#ifdef DEBUG
		OSD::Notify(Utils::Format("0x%08X", m_playerPointer));
#endif

        // Don't exit this function until the offset is somewhat valid
        while (!Process::Read32(m_playerPointer, m_offset) || !Process::Read32(m_offset, value))
           Sleep(Milliseconds(1));

        //Update coordinates pointer
        u8 index = *m_currentSlot;
        m_PlayerInfoPtr = (u32 *)(m_PlayerInfoBase + (index*4));
        Process::Read8(*m_PlayerInfoPtr + 0x1A9, m_AnimationID);
    }

    /*
     * Read
     */

    bool    Player::ReadByte(u32 offset, u8 &value) const
    {
        return (Process::Read8(offset + m_offset, value));
    }
    
    bool    Player::Read16(u32 offset, u16 &value) const
    {
        return (Process::Read16(offset + m_offset, value));
    }

    bool    Player::Read32(u32 offset, u32 &value) const
    {
        return (Process::Read32(offset + m_offset, value));
    }

    bool    Player::Read64(u32 offset, u64 &value) const
    {
        return (Process::Read64(offset + m_offset, value));
    }


    /*
     * Write
     */

    bool    Player::WriteByte(u32 offset, u8 value) const
    {
        return (Process::Write8(offset + m_offset, value));
    }

    bool    Player::Write16(u32 offset, u16 value) const
    {
        return (Process::Write16(offset + m_offset, value));
    }
    
    bool    Player::Write32(u32 offset, u32 value) const
    {
        return (Process::Write32(offset + m_offset, value));
    }

    bool    Player::Write64(u32 offset, u64 value) const
    {
        return (Process::Write64(offset + m_offset, value));
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

    bool Player::WriteInventoryLock(int slot, u8 lock) const
    {
        return (WriteByte(0x6C10 + slot, lock));
    }

    //Get all the occurances of 0x7FFE inside someone's inventory and return which slots it's in (as an array) and how long the array is
    int     * Player::GetAvaibleSlots(int &length) const
    {
        u32 item[16];
        int slot = 0;
        static int slots[16];
        for (int i = 0; i < 16; i++)
        {
            ReadInventorySlot(i, item[i]);
        }
        for (int i = 0; i < 16; i++)
        {
            if (item[i] == 0x7FFE)
            {
                slots[slot] = i;
                slot++;
            }
        }
        length = slot;
        return (slots);
    }

    int     * Player::FindItems(int &length, u32 search) const
    {
        u32 item[16];
        int slot = 0;
        static int slots[16];
        for (int i = 0; i < 16; i ++)
        {
            ReadInventorySlot(i, item[i]);
        }
        for (int i = 0; i < 16; i++)
        {
            if (item[i] == search)
            {
                slots[slot] = i;
                slot++;
            }
        }
        length = slot;
        return (slots);
    }

    u32     Player::GetInventoryAddress(void) const
    {
        return (m_offset + 0x6BD0);
    }

    u8     Player::GetAnimationID(void) const
    {
        return m_AnimationID;
    }

    void     Player::SetAnimationID(u8 ID) const
    {
        if (*m_PlayerInfoPtr && ID <= 0xEA)
            Process::Write8(*m_PlayerInfoPtr + 0x1A9, ID);
    }

    void     Player::SetIdleAnimation(void) const
    {
        SetAnimationID(6);
    }

    /*
     * Coordinates
     */

    #define COORDINATES_OFFSET 0x14

    Coordinates Player::GetCoordinates(void) const
    {
        // If pointer isn't null
        if (*m_PlayerInfoPtr)
            return (*(reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET)));
        // Else return a zero filled struct
        Coordinates zero = { 0.f, 0.f, 0.f};
        return (zero);
    }

    void    Player::SetCoordinates(Coordinates pos) const
    {
        // If pointer isn't null
        if (*m_PlayerInfoPtr)
            *(reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET)) = pos;
    }

    void    Player::SetCoordinates(float x, float y, float z) const
    {
        // If pointer is null
        if (!*m_PlayerInfoPtr)
            return;

        reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET)->x = x;
        reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET)->y = y;
        reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET)->z = z;
    }

    void    Player::SetCoordinatesX(float x) const
    {
        // If pointer is null
        if (!*m_PlayerInfoPtr)
            return;

        reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET)->x = x;
    }

    void    Player::SetCoordinatesY(float y) const
    {
        // If pointer is null
        if (!*m_PlayerInfoPtr)
            return;

        reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET)->y = y;
    }

    void    Player::SetCoordinatesZ(float z) const
    {
        // If pointer is null
        if (!*m_PlayerInfoPtr)
            return;

        reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET)->z = z;
    }

    void    Player::AddToCoordinates(float xDiff, float yDiff, float zDiff) const
    {
        // If pointer is null
        if (!*m_PlayerInfoPtr)
            return;

        Coordinates *coord = reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET);
        
        coord->x += xDiff;
        coord->y += yDiff;
        coord->z += zDiff;
    }

    void    Player::SetIntCoordinates(int x, int z) const
    {
        Coordinates *coord = reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET);

        coord->x = 32.f * x;
        coord->z = 32.f * z;
    }

    void    Player::SetFloatCoordinates(float x, float z) const
    {
        Coordinates *coord = reinterpret_cast<Coordinates *>(*m_PlayerInfoPtr + COORDINATES_OFFSET);

        coord->x = 32.f * x;
        coord->z = 32.f * z;
    }

    void    Player::SetRotation(u32 rotation) const
    {
        if (!*m_PlayerInfoPtr)
            return;
        Process::Write32(*m_PlayerInfoPtr + 0x2C, rotation);
    }

    u32    Player::GetRotation(void) const
    {
        if (!*m_PlayerInfoPtr)
            return -1;
        u32 rotation;
        Process::Read32(*m_PlayerInfoPtr + 0x2C, rotation);
        return (rotation);
    }

    /*
     * Thought
     */

    void    Player::ThinkTo(u16 item) const
    {
        u32     patch = 0xE1A00000;

        *m_thought = item;
        Process::Patch(0x002160BC, reinterpret_cast<u8 *>(&patch), 4); // nop the instruction that overwrites external thought bubbles
    }

    void    Player::UnThink(void) const
    {
        u32     original = 0xA000049;
        u32     value = 0;

        Process::Read32(0x002160BC, value);
        if (value == original)
            return;

        *m_thought = 0x7FFE;
        Process::Patch(0x002160BC, reinterpret_cast<u8 *>(&original), 4);
    }

    /*
     * Name
     */

    #define NAME_OFFSET 0x55A8
    #define NAME_MAX    16 ///< 8 Characters

    std::string     Player::GetName(void) const
    {
        u8           buf[NAME_MAX + 1] = { 0 };

        // Convert game's name to utf8
        utf16_to_utf8(buf, reinterpret_cast<u16 *>(m_offset + NAME_OFFSET), NAME_MAX);
        return (std::string(reinterpret_cast<char *>(buf)));
    }

    StringVector    Player::GetPatternNames(void) const
    {
        StringVector    names;
        u8              buf[NAME_MAX + 1] = { 0 };

        for (int i = 0; i < 10; i++)
        {
            memset(buf, 0, NAME_MAX);
            utf16_to_utf8(buf, reinterpret_cast<u16 *>(m_offset + 0x58 + (0x870 * i)), NAME_MAX);

            names.push_back(std::string(reinterpret_cast<char *>(buf)));
        }
        return (names);
    }

    void    Player::SetName(std::string& name) const
    {
        u16                 buf[NAME_MAX + 1] = { 0 };
        std::vector<int>    matchIndex;

        // If name is empty, abort
        if (name.empty())
            return;

        std::string     originalName = GetName();
        StringVector    names = GetPatternNames();

        for (int i = 0; i < 10; i++)
        {
            if (names[i].compare(originalName) == 0)
                matchIndex.push_back(i);
        }

        // Convert utf8 to utf16
        int res = utf8_to_utf16(buf, reinterpret_cast<const u8 *>(name.c_str()), NAME_MAX);

        // If conversion failed, abort
        if (res == -1)
            return;

        for (int i : matchIndex)
            Process::CopyMemory(reinterpret_cast<void *>(m_offset + 0x58 + 0x870 * i), buf, NAME_MAX);

        // Copy name to game
        Process::CopyMemory(reinterpret_cast<void *>(m_offset + NAME_OFFSET), buf, NAME_MAX);
    }
}
