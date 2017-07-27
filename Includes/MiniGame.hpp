#ifndef MINIGAME_HPP
#define MINIGAME_HPP

#include "types.h"
#include "Game.hpp"
#include "CTRPluginFramework/System/Rect.hpp"

#include <vector>


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
        UIntRect hitbox;
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