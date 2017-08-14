#ifndef MINIGAME_HPP
#define MINIGAME_HPP

#include "types.h"
#include "Game.hpp"
#include "CTRPluginFramework/System/Rect.hpp"

#include <vector>


namespace CTRPluginFramework
{
    #define DEBUG_MINIGAME 0 ///< Change 0-1 to display the debugs infos

    class Korok
    {
    public:
        Korok(void);
        ~Korok(void);

        bool    CheckPosition(Position *position);

        u8          posX;
        u8          posY;
        bool        isFound;
        UIntRect    hitbox;
    };

    using KorokVector = std::vector<Korok>;

    class KorokMiniGame
    {
    public:
        static KorokMiniGame *GetInstance(void);

        KorokMiniGame(void);
        ~KorokMiniGame(void);

        // Return true if the game is finished
        bool            Update(void);        
        KorokVector     &GetKoroks(void);

        static bool     InGame;        
        int             LeftToFound;

    private:
#if DEBUG_MINIGAME
        static bool             _OSDAlreadyCreated;
#endif
        static KorokMiniGame    *_instance;

        std::vector<Korok>      _koroks;
    };
}

#endif