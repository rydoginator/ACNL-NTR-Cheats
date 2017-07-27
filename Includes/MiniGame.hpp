#ifndef MINIGAME_HPP
#define MINIGAME_HPP

#include "types.h"
#include <vector>

#include "Game.hpp"

namespace CTRPluginFramework
{
    class Korok
    {
    public:
        Korok(void);
        ~Korok(void);

        bool    CheckPosition(Position *position);

        u8      posX;
        u8      posY;
        bool    isFound;
    };

    class KorokMiniGame
    {
    public:
        KorokMiniGame(void);
        ~KorokMiniGame(void);

        // Return true if the game is finished
        bool    Update(void);

        static bool     InGame;
        int             LeftToFound;

    private:

        std::vector<Korok> _koroks;
    };
}

#endif