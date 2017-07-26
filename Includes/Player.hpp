#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
    struct PACKED Coordinates
    {
        float   x;
        float   y;
        float   z;
    };

    class Player
    {
    public:

        ~Player(void){};

        // Return current Player instance
        static Player *GetInstance(void);

        // Return current player's offset
        u32     GetOffset(void) const;

        // Update current offset & ID
        void    Update(void);

        // Read data relative to player's offset
        bool    ReadByte(u32 offset, u8 &value) const;
        bool    Read16(u32 offset, u16 &value) const;
        bool    Read32(u32 offset, u32 &value) const;
        bool    Read64(u32 offset, u64 &value) const;

        // Write data relative to player's offset        
        bool    WriteByte(u32 offset, u8 value) const;
        bool    Write16(u32 offset, u16 value) const;
        bool    Write32(u32 offset, u32 value) const;
        bool    Write64(u32 offset, u64 value) const;

        // Inventory
        bool    ReadInventorySlot(int slot, u32 &item) const;
        bool    WriteInventorySlot(int slot, u32 item) const;
        int     * FindItems(int &length, u32 search) const;
        int     * GetAvaibleSlots(int &length) const;
        u32     GetInventoryAddress(void) const;


        // Coordinates

        // Return current coordinates
        Coordinates     GetCoordinates(void) const;
        // Set coordinates
        void    SetCoordinates(Coordinates pos) const;
        void    SetCoordinates(float x, float y, float z) const;
        void    SetCoordinatesX(float x) const;
        void    SetCoordinatesY(float y) const;
        void    SetCoordinatesZ(float z) const;
        // Change coordinates
        void    AddToCoordinates(float xDiff, float yDiff, float zDiff) const;

        // Thought
        void    ThinkTo(u16 item) const;  ///< Put item in a thought bubble.
        void    UnThink(void) const;      ///< Revert patch done by ThinkTo
        
        // Name
        // Return the player's name as a string with utf8 encoding
        std::string     GetName(void) const;
        // Set the player's name. name must be a string with utf8 encoding
        void            SetName(std::string &name) const;

    private:
        Player(void);

        u32             _offset;

        u32             _coordinatePointerBase;
        u32             *_coordinatePointer;
        u8              *_coordinateIndex;
        u16             *_thought;

        static Player   *_instance;
        static u32      _playerPointer;
    };
}

#endif