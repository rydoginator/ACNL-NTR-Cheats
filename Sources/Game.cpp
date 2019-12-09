#include "Game.hpp"
#include "RAddress.hpp"
#include "Offsets.hpp"
#include "Values.hpp"
#include "cheats.hpp"

namespace CTRPluginFramework
{
    // Initialize properties
    void    Game::Initialize(void)
    {
        ClubItem = reinterpret_cast<u32 *>(AutoRegion(USA_CLUB_ADDR, TO_EUR(USA_CLUB_ADDR), TO_JAP(USA_CLUB_ADDR), TO_WA_USA(USA_CLUB_ADDR), TO_WA_EUR(USA_CLUB_ADDR), TO_WA_JAP(USA_CLUB_ADDR))());
		Garden = FollowPointer(0x300005A8, 0x48, 0, 0, 0, 0x24, 0x10, 0, -1);
		Building = Garden + 0x4BE88;
		TimeReal = reinterpret_cast<u64*>(FollowPointer(0x300005A8, 0x14, 0x3c, 0x10, 0x148, -1) + 0x50C);
		IslandItem = reinterpret_cast<u32*>(Garden + ISLAND_ITEMS_ADDR);
		BuildingSlots = reinterpret_cast<u8*>(Garden + BUILDING_BYTE);
		TimeSave = reinterpret_cast<u64*>(Garden + SAVETIME_ADDR);
		TownItem = reinterpret_cast<u32*>(Garden + TOWN_ITEMS_ADDR);
		Nook = reinterpret_cast<u32*>(Garden + NOOK_ADDR);
		TownFruit = Garden + TOWN_FRUIT;
		TownGrass = Garden + GRASS_TYPE;
		Permit = Garden + PERMIT_ADDRESS;
		TownTree = Garden + TREE_SIZE;
		PWP = Garden + PWP_ADDRESS;
		Grass = reinterpret_cast<u32*>(GRASS_START_ADDR);
		GrassEnd = reinterpret_cast<u32*>(GRASS_END_ADDR);
        Gravity = AutoRegion(USA_GRAVITY_OUT_ADDR, TO_EUR(USA_GRAVITY_OUT_ADDR), TO_JAP(USA_GRAVITY_OUT_ADDR), TO_WA_USA(USA_GRAVITY_OUT_ADDR), TO_WA_EUR(USA_GRAVITY_OUT_ADDR), TO_WA_JAP(USA_GRAVITY_OUT_ADDR))();
        MainStreetItem = reinterpret_cast<u32 *>(AutoRegion(USA_MAINSTREET_ITEMS, TO_EUR(USA_MAINSTREET_ITEMS), TO_JAP(USA_MAINSTREET_ITEMS), TO_WA_USA(ISLAND_ITEMS_ADDR), TO_WA_EUR(ISLAND_ITEMS_ADDR), TO_WA_EUR(ISLAND_ITEMS_ADDR))()); //
        MainStreetPos = reinterpret_cast<Position *>(FollowPointer(0xFFFF190, 0x4BDC, -1) + 0x1B8);
		Room = reinterpret_cast<u8 *>(FollowPointer(0x809E5CC, -0x164, -1) - 0x4CBA);
		TCPImage = Garden + 0x5758;
		WalkOverThingsOffset = (FollowPointer(0x11C2B0, -0x4FF7, 0xFDC, -1) - 0x44D0);
        Velocity = AutoRegion(USA_VELOCITY_ADDR, TO_EUR(USA_VELOCITY_ADDR), TO_JAP(USA_VELOCITY_ADDR), TO_WA_USA(USA_VELOCITY_ADDR), TO_WA_EUR(USA_VELOCITY_ADDR), TO_WA_JAP(USA_VELOCITY_ADDR))();
        Hour = reinterpret_cast<u8 *>(FollowPointer(0x809F550, 0x1848, -1) + 0x463);
        CodeDifference = reinterpret_cast<u32 *>(AutoRegion(USA_CODE_DIFFERENCE, EUR_CODE_DIFFERENCE, JAP_CODE_DIFFERENCE, USA_WA_CODE_DIFFERENCE, EUR_WA_CODE_DIFFERENCE, JAP_WA_CODE_DIFFERENCE)());
        Minute = reinterpret_cast<u8 *>(FollowPointer(0x809F550, 0x1848, -1) + 0x462);
		WorldPos = reinterpret_cast<Position*>(FollowPointer(0xFFFF190, 0x4BDC, -1) + 0x1B8);
		GameSpeed = reinterpret_cast<u32 *>(FollowPointer(0x809E5CC, -0x274C, -1) + 0x2C88);
        ItemForm = AutoRegion(USA_ITEM_FORM, TO_EUR(USA_ITEM_FORM), TO_JAP(USA_ITEM_FORM), TO_WA_USA(USA_ITEM_FORM), TO_WA_EUR(USA_ITEM_FORM), TO_WA_JAP(USA_ITEM_FORM))();
		Location = reinterpret_cast<u32 *>(FollowPointer(0xFFFFEDC, -0x2F88, -1) + 0x1C);
        Keyboard = (FollowPointer(0x809E1B8, 0x1700, -1) + 0xF50);
        WispSpoof = reinterpret_cast<u32>(FollowPointer(0x80E8F88, 0x17C, -1));
        DIESpoof = reinterpret_cast<u32>(AutoRegion(USA_AMIIBO_DIE, TO_EUR(USA_AMIIBO_DIE), TO_JAP(USA_AMIIBO_DIE), TO_WA_USA(USA_AMIIBO_DIE), TO_WA_EUR(USA_AMIIBO_DIE), TO_WA_JAP(USA_AMIIBO_DIE))());
        StaticNPC = reinterpret_cast<u32 >(FollowPointer(0x809E5CC, -0x2A0C, -1) + 0x8C2);
        DynamicNPC = reinterpret_cast<u32 >(AutoRegion(USA_ISABELLE_ADDR, TO_EUR(USA_ISABELLE_ADDR), TO_JAP(USA_ISABELLE_ADDR), TO_WA_USA(USA_ISABELLE_ADDR), TO_WA_EUR(USA_ISABELLE_ADDR), TO_WA_JAP(USA_ISABELLE_ADDR))());
        BottomScreen = reinterpret_cast<u8 *>(AutoRegion(USA_BOTTOM_ADDR, EUR_BOTTOM_ADDR, JAP_BOTTOM_ADDR, USA_WA_BOTTOM_ADDR, EUR_WA_BOTTOM_ADDR, JAP_WA_BOTTOM_ADDR)());
        Consciousness = reinterpret_cast<u16 *>(AutoRegion(USA_FAINT_ADDR, TO_EUR(USA_FAINT_ADDR), TO_JAP(USA_FAINT_ADDR), TO_WA_USA(USA_FAINT_ADDR), TO_WA_EUR(USA_FAINT_ADDR), TO_WA_JAP(USA_FAINT_ADDR))());
        KeyboardText = reinterpret_cast<u32 *>(FollowPointer(0x809F550, 0x20C, -1) + 0x2120);
        EnterBool = reinterpret_cast<u8 *>(FollowPointer(0x809E1B8, 0x1700, -1) + 0xB73);
        Visibility = reinterpret_cast<u32>(AutoRegion(USA_VISIBILITY_ADDR, EUR_VISIBILITY_ADDR, JAP_VISIBILITY_ADDR, USA_WA_VISIBILITY_ADDR, EUR_WA_VISIBILITY_ADDR, JAP_WA_VISIBILITY_ADDR)());
        CatalogItem = reinterpret_cast<u32>(FollowPointer(0x809E5CC,-0x3C10, -1) + 0x1C);
        MapBool = reinterpret_cast<u8 *>(FollowPointer(0x809E1E8, 0x2CC, -1) - 0x11C);
        Tours = reinterpret_cast<u32 *>(AutoRegion(USA_TOURS, EUR_TOURS, JAP_TOURS, USA_WA_TOURS, EUR_WA_TOURS, JAP_WA_TOURS)());
        EmoteASM = reinterpret_cast<u32 >(FollowPointer(0x809E5CC, -0x2544, -1) + 0x7444);
        PatternEdit = reinterpret_cast<u32 >(FollowPointer(0x809E5CC, -0x229C, -1) - 0x1B70);
        NoBreakFlowers = reinterpret_cast<u32 >(FollowPointer(0x809E5CC, -0x23FC, -1) - 0x3640);
		CountryASM = reinterpret_cast<u32 >(FollowPointer(0x83D014C, -1) + 0x4FCC);
		Weather = reinterpret_cast<u32 >(FollowPointer(0x809E5CC, -0x3264, -1) - 0x9EC);
        Confetti = reinterpret_cast<u32 >(FollowPointer(0x809E5CC, -0x142C, -1) - 0x1FA0);
		CherryBlossom = reinterpret_cast<u32 >(FollowPointer(0x809E5CC, -0x21CC, -1) - 0x16B8);
		AlwaysOpen_Retail = reinterpret_cast<u32 >(FollowPointer(0x809E5CC, -0x9DC, -1) - 0x435);
        AlwaysOpen_Nookling = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0x1934, -1) - 0x1F0);
        AlwaysOpen_Garden = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0x39FC, -1) - 0x29F4);
        AlwaysOpen_Ables = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0x193C, -1) + 0x44C);
        AlwaysOpen_Sham = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0x2CCC, -1) + 0xFCC);
        AlwaysOpen_Kicks = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0x1F74, -1) - 0x1AEC);
        AlwaysOpen_Nook = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0x210C, -1) - 0x4F0);
        AlwaysOpen_Katrina = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0x86C, -1) - 0x14);
        AlwaysOpen_Redd = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0x14E4, -1) - 0x14);
		Internal_FurnFix = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0x329C, -1) - 0x254C);
        FishCantScare = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0xF44, -1) + 0x20CC);
        FishBiteRightAway = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0xF44, -1) + 0x1DFC);
        FishSetId = reinterpret_cast<u32>(FollowPointer(0x809E5CC, -0x10AC, -1) - 0xAC8);
        GameMode = reinterpret_cast<u32 *>(FollowPointer(0x809E5CC, +0x1354, -1) + 0x9FC);
        InstantText = reinterpret_cast<u32>(FollowPointer(0x80EF34C, -0x1930, -1) - 0x4608);
		EchoTheMusic = reinterpret_cast<u32>(FollowPointer(0x80EF34C, -0x23F0, -1) - 0x3CFC);
    }

    u32     Game::GetWorldOffset(void)
    {
        u8      room = *Room;
        Position *pos = room == 0x01 ? MainStreetPos : WorldPos;

        u32     x = pos->x;
        u32     y = pos->y;
        u32     reg0;
        u32     reg1;

#ifdef DEBUG
        OSD::Notify(Utils::Format("X: %i Y: %i", x, y));
#endif // DEBUG

        
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

    u8     Game::GetMode(void)
    {
        u8 mode = 0;
        Process::Read8(*GameMode + 0x1329D, mode);
        return mode;
    }

	int		Game::TeleportRoom(u8 id, Coordinates coords)
	{
		static const u32 offset = (FollowPointer(0x100760, -1) + 0x293); //AutoRegion(0x9513D3, 0x9503CF, 0x94A3CF, 0x9503C3, 0x9503CF, 0x9493CF)();
		static const u32 offset2 = (FollowPointer(0x80EF34C, 0x4EC, -1) - 0x19F0); //AutoRegion(0xAC2990, 0xAC1990, 0xABB990, 0xAC1990, 0xAC1990, 0xABA990)();
		static const u32 InfoOffsetCheck = AutoRegion(0x330773BC, TO_EUR(0x330773BC), TO_JAP(0x330773BC), TO_WA_USA(0x330773BC), TO_WA_EUR(0x330773BC), TO_WA_JAP(0x330773BC))();
		u32 InfoOffset = Player::GetInstance()->GetInfoOffset();
		u8 AnimID = Player::GetInstance()->GetAnimationID();
		u8 banner = 0;
		if (InfoOffset != InfoOffsetCheck && InfoOffset != InfoOffsetCheck + 0x12C)
		{
			return -1;
		}
		if (GetMode() == 2) // if on club tortimer
		{
			return -2;
		}
		if ((*Game::Room >= 0x5F && *Game::Room <= 0x62) || (*Game::Room >= 0x69 && *Game::Room <= 0x9E)) //Check if on tour, in HHA, saving, formatting, or loading or prologue
		{
			return -3;
		}
		if (AnimID == 6 || AnimID == 0xD || AnimID == 0x1F || AnimID == 0x20) //check if idle (also idle when swimming)
		{
			Process::Write8(offset, 0x01);
			Process::Write16(offset + 1, 0x0001);
			*(Game::Room + 1) = id; //Set the 'next' id and not actual ID, hence the +1
			//Process::Write16(offset2, 0x0001);
			//Sleep(Seconds(2));
			Process::Write8(offset2 + 0x14, AnimID);
			*(reinterpret_cast<Coordinates*>(offset2)) = coords; // copy coordinates
			return 1;
		}
		else
		{
			return -4;
		}
	}

	int		Game::TeleportRoom(u8 id)
	{
		static const u32 offset = (FollowPointer(0x100760, -1) + 0x293); //AutoRegion(0x9513D3, 0x9503CF, 0x94A3CF, 0x9503C3, 0x9503CF, 0x9493CF)();
		static const u32 offset2 = (FollowPointer(0x80EF34C, 0x4EC, -1) -0x19F0); //AutoRegion(0xAC2990, 0xAC1990, 0xABB990, 0xAC1990, 0xAC1990, 0xABA990)();
		static const u32 InfoOffsetCheck = AutoRegion(0x330773BC, TO_EUR(0x330773BC), TO_JAP(0x330773BC), TO_WA_USA(0x330773BC), TO_WA_EUR(0x330773BC), TO_WA_JAP(0x330773BC))();
		u32 InfoOffset = Player::GetInstance()->GetInfoOffset();
		u8 AnimID = Player::GetInstance()->GetAnimationID();
		u8 banner = 0;
		static Clock clock;
		if (InfoOffset != InfoOffsetCheck && InfoOffset != InfoOffsetCheck + 0x12C)
		{
			return -1;
		}
		if (GetMode() == 2) // if on club tortimer
		{
			return -2;
		}
		if ((*Game::Room >= 0x5F && *Game::Room <= 0x62) || (*Game::Room >= 0x69 && *Game::Room <= 0x9E)) //Check if on tour, in HHA, saving, formatting, or loading or prologue
		{
			return -3;
		}
		if (AnimID == 6 || AnimID == 0xD || AnimID == 0x1F || AnimID == 0x20) //check if idle (also idle when swimming)
		{
			clock.Restart();
			Process::Write8(offset, 0x01);
			Process::Write16(offset + 1, 0x0001);
			*(Game::Room + 1) = id; //Set the 'next' id and not actual ID, hence the +1
			Process::Write16(offset2, 0x0001);
			return 1;
		}
		else
		{
			return -4;
		}
	}

    u32         Game::Building = 0;
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
	u32			Game::WalkOverThingsOffset = 0;
    u32         Game::Velocity = 0;
    u8          *Game::Hour = nullptr;
    u8          *Game::Minute = nullptr;
    u8         *Game::BuildingSlots = nullptr;
    Position    *Game::WorldPos = nullptr;
    u32         *Game::CodeDifference = nullptr;
    u32         *Game::Nook = nullptr;
    u32         Game::TownFruit = 0;
    u32         Game::TownGrass = 0;
    u32         Game::TownTree = 0;
    u32         Game::Permit = 0;
    u32         Game::PWP = 0;
    u32         *Game::Grass = nullptr;
    u32         *Game::GrassEnd = nullptr;
    u32         Game::FishCantScare = 0;
    u32         Game::FishBiteRightAway = 0;
    u32         Game::FishSetId = 0;
    u32         *Game::GameSpeed = nullptr;
    u32         Game::ItemForm = 0;
    u32         *Game::Location = nullptr;
    u32         Game::Keyboard = 0;
    u32         Game::WispSpoof = 0;
    u32         Game::DIESpoof = 0;
    u32         Game::StaticNPC = 0;
    u32         Game::DynamicNPC = 0;
    u8          *Game::BottomScreen = nullptr;
    u16         *Game::Consciousness = nullptr;
    u32         *Game::KeyboardText = nullptr;
    u8          *Game::EnterBool = nullptr;
    u32         Game::Visibility = 0;
    u32         Game::CatalogItem = 0;
    u8          *Game::MapBool = nullptr;
    u32         *Game::Tours = nullptr;
    u32         Game::EmoteASM = 0;
    u32         Game::PatternEdit = 0;
    u32         Game::NoBreakFlowers = 0;
    u32         Game::CountryASM = 0;
    u32         Game::Weather = 0;
    u32         Game::Confetti = 0;
    u32         Game::CherryBlossom = 0;
    u32         Game::AlwaysOpen_Retail = 0;
    u32         Game::AlwaysOpen_Nookling = 0;
    u32         Game::AlwaysOpen_Garden = 0;
    u32         Game::AlwaysOpen_Ables = 0;
    u32         Game::AlwaysOpen_Sham = 0;
    u32         Game::AlwaysOpen_Kicks = 0;
    u32         Game::AlwaysOpen_Nook = 0;
    u32         Game::AlwaysOpen_Katrina = 0;
    u32         Game::AlwaysOpen_Redd = 0;
    u32         Game::Internal_FurnFix = 0;
    u32         *Game::GameMode = nullptr;
    u32         Game::InstantText = 0;
    u32         Game::EchoTheMusic = 0;
}
