#ifndef GAME_HPP
#define GAME_HPP

#include "types.h"

namespace CTRPluginFramework
{
    class Game
    {
    public:

        // Initialize properties
        static void    Initialize(void);

        // Properties

        static u32      Garden;         ///< Address of the garden
        static u32      Gravity;        ///< Address of gravity
        static u32      TCPImage;       ///< Address of the TCP picture
        static u32      Velocity;       ///< Address of velocity
        

    };
}

#endif