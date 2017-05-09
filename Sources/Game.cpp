#include "Game.hpp"
#include "RAddress.hpp"
#include "Offsets.hpp"
#include "Values.hpp"

namespace CTRPluginFramework
{
    // Initialize properties
    void    Game::Initialize(void)
    {
        ClubItem = reinterpret_cast<u32 *>(AutoRegion(USA_CLUB_ADDR, TO_EUR(USA_CLUB_ADDR), TO_JAP(USA_CLUB_ADDR))());
        Garden = AutoRegion(USA_GARDEN, TO_EUR(USA_GARDEN), TO_JAP(USA_GARDEN))();
        Gravity = AutoRegion(USA_GRAVITY_OUT_ADDR, TO_EUR(USA_GRAVITY_OUT_ADDR), TO_JAP(USA_GRAVITY_OUT_ADDR))();
        MainStreetPos = reinterpret_cast<Position *>(AutoRegion(USA_MAINSTREET_X, TO_EUR(USA_MAINSTREET_X), TO_JAP(USA_MAINSTREET_X))());
        Room = reinterpret_cast<u8 *>(AutoRegion(USA_ROOM_ID_ADDR, EUR_ROOM_ID_ADDR, JAP_ROOM_ID_ADDR)());
        TCPImage = Garden + 0x5758;
        TownItem = reinterpret_cast<u32 *>(AutoRegion(USA_TOWN_ITEMS_ADDR, TO_EUR(USA_TOWN_ITEMS_ADDR), TO_JAP(USA_TOWN_ITEMS_ADDR))());
        Velocity = AutoRegion(USA_VELOCITY_ADDR, TO_EUR(USA_VELOCITY_ADDR), TO_JAP(USA_VELOCITY_ADDR))();
        WorldPos = reinterpret_cast<Position *>(AutoRegion(USA_WORLD_X_ADDR, TO_EUR(USA_WORLD_X_ADDR), TO_JAP(USA_WORLD_X_ADDR))());
    }

    u32     Game::GetWorldOffset(void)
    {
        u8      room = *Room;
        Position *pos = room == 0x01 ? MainStreetPos : WorldPos;

        u32     x = pos->x;
        u32     y = pos->y;
        u32     reg0;
        u32     reg1;

        if (room == 0x01)
        {
            reg0 = x % 0x10;
            x /= 0x10;
            reg1 = y % 0x10;
            y /= 0x10;
            reg0 *= 0x4;
            reg1 *= 0x40;
            x *= 0x400;
            y *= 0x1400;
        }
        else
        {
            x -= 0x10;
            y -= 0x10;
            reg0 = x % 0x10;
            x /= 0x10;
            reg1 = y % 0x10;
            y /= 0x10;
            reg0 *= 0x4;
            reg1 *= 0x40;
            x *= 0x400;
            y *= 0x1400;
        }
        return (reg0 + reg1 + x + y);
    }

    u32     *Game::GetItem(void)
    {
        u32  *items;

        if (*Room == 0x0) items = TownItem;
        else if (*Room == 0x6F) items = ClubItem;
        else return (nullptr);
        
        return (items + GetWorldOffset());
    }

    u32         *Game::ClubItem = nullptr;
    u32         Game::Garden = 0;
    u32         Game::Gravity = 0;
    Position    *Game::MainStreetPos = nullptr;
    u32         Game::TCPImage = 0;
    u32         *Game::TownItem = nullptr;
    u32         Game::Velocity = 0;
    Position    *Game::WorldPos = nullptr;    
}
