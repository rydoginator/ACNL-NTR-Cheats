#include "Game.hpp"
#include "RAddress.hpp"
#include "Offsets.hpp"
#include "Values.hpp"

namespace CTRPluginFramework
{
    // Initialize properties
    void    Game::Initialize(void)
    {
        Garden = AutoRegion(USA_GARDEN, TO_EUR(USA_GARDEN), TO_JAP(USA_GARDEN))();
        TCPImage = Garden + 0x5758;
        Gravity = AutoRegion(USA_GRAVITY_OUT_ADDR, TO_EUR(USA_GRAVITY_OUT_ADDR), TO_JAP(USA_GRAVITY_OUT_ADDR))();
    }

    u32     Game::Garden = 0;
    u32     Game::TCPImage = 0;
    u32     Game::Gravity = 0;
    
}
