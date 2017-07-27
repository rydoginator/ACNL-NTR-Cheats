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

    using KorokVector = std::vector<Korok>;

    class KorokMiniGame
    {
    public:
        KorokMiniGame(void);
        ~KorokMiniGame(void);

        // Return true if the game is finished
        bool    Update(void);

        static KorokMiniGame *GetInstance(void);
        KorokVector &GetKoroks(void);

        static bool     InGame;
        
        int             LeftToFound;

    private:
        static bool     _OSDAlreadyCreated;
        static KorokMiniGame *_instance;

        std::vector<Korok> _koroks;
    };
}

#endif