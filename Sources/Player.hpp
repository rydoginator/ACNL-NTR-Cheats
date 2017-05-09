#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
    struct Coordinates
    {
        float   x;
        float   y;
        float   z;
    };

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
        u32             _offset;

        Coordinates     **_coordinatePointer;
        u16             *_thought;

        static Player   *_instance;
        static u32      _playerPointer;
    };
}

#endif