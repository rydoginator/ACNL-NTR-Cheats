#ifndef GAME_HPP
#define GAME_HPP

#include "types.h"

namespace CTRPluginFramework
{
    struct Position
    {
        u32     x;
        u32     y;
    };

    class Game
    {
    public:

        // Initialize properties
        static void     Initialize(void);

        // Return current world offset
        static u32      GetWorldOffset(void);
        // Return item's address at current position.
        // nullptr is returned is Room is unknown
        static u32      *GetItem(void);

        // Properties

        static u32      *ClubItem;      ///< Address of the first item in club
        static u32      Garden;         ///< Address of the garden
        static u32      Gravity;        ///< Address of gravity
        static u32      *IslandItem;    ///< Address of the first item in the Island
        static Position *MainStreetPos; ///< Position of the player on MainStreet
        static u8       *Room;          ///< Address of the current room
        static u32      TCPImage;       ///< Address of the TCP picture
        static u32      *TownItem;      ///< Address of the first item in town
        static u32      Velocity;       ///< Address of velocity
        static Position *WorldPos;      ///< Position of the player in the world
        

    };
}

#endif