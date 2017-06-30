#include "Game.hpp"
#include "RAddress.hpp"
#include "Offsets.hpp"
#include "Values.hpp"

namespace CTRPluginFramework
{
    // Initialize properties
    void    Game::Initialize(void)
    {
        Building = reinterpret_cast<u32 *>(AutoRegion(USA_BUILDING_ADDR, TO_EUR(USA_BUILDING_ADDR), TO_JAP(USA_BUILDING_ADDR))());
        ClubItem = reinterpret_cast<u32 *>(AutoRegion(USA_CLUB_ADDR, TO_EUR(USA_CLUB_ADDR), TO_JAP(USA_CLUB_ADDR))());
        Garden = AutoRegion(USA_GARDEN, TO_EUR(USA_GARDEN), TO_JAP(USA_GARDEN))();
        Gravity = AutoRegion(USA_GRAVITY_OUT_ADDR, TO_EUR(USA_GRAVITY_OUT_ADDR), TO_JAP(USA_GRAVITY_OUT_ADDR))();
        IslandItem = reinterpret_cast<u32 *>(AutoRegion(USA_ISLAND_ITEMS_ADDR, TO_EUR(USA_ISLAND_ITEMS_ADDR), TO_JAP(USA_ISLAND_ITEMS_ADDR))());
        MainStreetItem = reinterpret_cast<u32 *>(AutoRegion(USA_MAINSTREET_ITEMS, TO_EUR(USA_MAINSTREET_ITEMS), TO_JAP(USA_MAINSTREET_ITEMS))());
        MainStreetPos = reinterpret_cast<Position *>(AutoRegion(USA_MAINSTREET_X, TO_EUR(USA_MAINSTREET_X), TO_JAP(USA_MAINSTREET_X))());
        Room = reinterpret_cast<u8 *>(AutoRegion(USA_ROOM_ID_ADDR, EUR_ROOM_ID_ADDR, JAP_ROOM_ID_ADDR)());
        BuildingSlots = reinterpret_cast <u32 *>(AutoRegion(USA_BUILDING_BYTE, TO_EUR(USA_BUILDING_BYTE), TO_JAP(USA_BUILDING_BYTE))());
        TCPImage = Garden + 0x5758;
        TimeReal = reinterpret_cast<u64 *>(AutoRegion(USA_REALTIME_ADDR, EUR_REALTIME_ADDR, JAP_REALTIME_ADDR)());
        TimeSave = reinterpret_cast<u64 *>(AutoRegion(USA_SAVETIME_ADDR, TO_EUR(USA_SAVETIME_ADDR), TO_JAP(USA_SAVETIME_ADDR))());
        TownItem = reinterpret_cast<u32 *>(AutoRegion(USA_TOWN_ITEMS_ADDR, TO_EUR(USA_TOWN_ITEMS_ADDR), TO_JAP(USA_TOWN_ITEMS_ADDR))());
        Velocity = AutoRegion(USA_VELOCITY_ADDR, TO_EUR(USA_VELOCITY_ADDR), TO_JAP(USA_VELOCITY_ADDR))();
        Hour = reinterpret_cast<u8 *>(AutoRegion(USA_HOURS_ADDR, EUR_HOURS_ADDR, JAP_HOURS_ADDR)());
        CodeDifference = reinterpret_cast<u32 *>(AutoRegion(USA_CODE_DIFFERENCE, EUR_CODE_DIFFERENCE, JAP_CODE_DIFFERENCE)());
        Minute = reinterpret_cast<u8 *>(AutoRegion(USA_MINUTES_ADDR, EUR_MINUTES_ADDR, JAP_MINUTES_ADDR)());
        WorldPos = reinterpret_cast<Position *>(AutoRegion(USA_WORLD_X_ADDR, TO_EUR(USA_WORLD_X_ADDR), TO_JAP(USA_WORLD_X_ADDR))());
        Nook = reinterpret_cast<u32 *>(AutoRegion(USA_NOOK_ADDR, TO_EUR(USA_NOOK_ADDR), TO_JAP(USA_NOOK_ADDR))());
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
        u32   items;

        if (*Room == 0x0) items = reinterpret_cast<u32>(TownItem);
        else if (*Room == 0x01) items = reinterpret_cast<u32>(MainStreetItem);
        else if (*Room == 0x68) items = reinterpret_cast<u32>(IslandItem);
        else if (*Room == 0x6F) items = reinterpret_cast<u32>(ClubItem);
        else return (nullptr);
        
        return (reinterpret_cast<u32 *>(items + GetWorldOffset()));
    }
    

    u32         *Game::Building = nullptr;
    u32         *Game::ClubItem = nullptr;
    u32         Game::Garden = 0;
    u32         Game::Gravity = 0;
    u32         *Game::IslandItem = nullptr;
    u32         *Game::MainStreetItem = nullptr;
    Position    *Game::MainStreetPos = nullptr;
    u8          *Game::Room = nullptr;
    u32         Game::TCPImage = 0;
    u64         *Game::TimeReal = nullptr;
    u64         *Game::TimeSave = nullptr;
    u32         *Game::TownItem = nullptr;
    u32         Game::Velocity = 0;
    u8          *Game::Hour = nullptr;
    u8          *Game::Minute = nullptr;
    u32         *Game::BuildingSlots = nullptr;
    Position    *Game::WorldPos = nullptr;
    u32         *Game::CodeDifference = nullptr;
    u32         *Game::Nook = nullptr;  
}
