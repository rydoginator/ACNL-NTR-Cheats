#include "cheats.hpp"
#include "CTRPluginFramework/System/Rect.hpp"
#include "Helpers/MenuEntryHelpers.hpp"
#include "Helpers/QuickMenu.hpp"

namespace CTRPluginFramework
{

    void    SpeedSettings(MenuEntry *entry)
    {
        float *speed = GetArg<float>(entry);
        Keyboard keyboard("Which speed would you like to use?");
        keyboard.Open(*speed);
    }

    void    CoordinateModifier(MenuEntry *entry)
    {
        static Clock time;
        float speed = *GetArg<float>(entry, 1.f);
        Time delta = time.Restart();

        float value = 400.0f * delta.AsSeconds();

        if (entry->Hotkeys[0].IsDown()) // Up
            Player::GetInstance()->AddToCoordinates(0.f, 0.f, 0 - value * speed);
        if (entry->Hotkeys[1].IsDown()) // Down
            Player::GetInstance()->AddToCoordinates(0.f, 0.f, value * speed);
        if (entry->Hotkeys[2].IsDown()) // Left
            Player::GetInstance()->AddToCoordinates(0 - value * speed, 0.f, 0.f);
        if (entry->Hotkeys[3].IsDown()) // Right
            Player::GetInstance()->AddToCoordinates(value * speed, 0.f, 0.f);
    }

    void    TouchCoordinates(MenuEntry *entry)
    {
		static UIntRect     mapAreaTown(70, 50, 175, 155);
		static UIntRect		mapAreaMain(15, 40, 285, 140);
		static UIntRect		mapAreaIsland(70, 30, 170, 170);

        UIntVector  touchPos = Touch::GetPosition();
        Coordinates position = Player::GetInstance()->GetCoordinates();
		OSD::Run([](const Screen &screen)
		{
			Coordinates position = Player::GetInstance()->GetCoordinates();
			if (!screen.IsTop)
				return false;
			u8 room = *Game::Room;
			screen.Draw(Utils::Format("X: %f Y: %f", position.x, position.z), 10, 10);
			screen.Draw(Utils::Format("Room ID: %01X", room), 10, 20);
			return true;
		});

		if (*Game::MapBool == 1) // check if the map is visible
		{
			u8 roomID = *Game::Room;
			FloatVector  fPos(touchPos);
			if (roomID == 0 || roomID == 0x69) // if you're on the main map, use this math
			{
				if (mapAreaTown.Contains(touchPos))
				{
					position.x = (fPos.x - 77.f) * 14.94f + 526.f;
					position.z = (fPos.y - 50.f) * 15.21f + 526.f;
					Player::GetInstance()->SetCoordinates(position);
				}
			}
			else if (roomID == 1) // if on mainstreet
			{
				if (mapAreaMain.Contains(touchPos))
				{
					position.x = (fPos.x - 15.f) * 6.5f + 150.f;
					position.z = (fPos.y - 40.f) * 6.5f - 117.f;
					Player::GetInstance()->SetCoordinates(position);
				}
			}
			else if (roomID == 0x68) // island
			{
				if (mapAreaIsland.Contains(touchPos))
				{
					position.x = (fPos.x - 75.f) * 12.2f;
					position.z = (fPos.y - 30.f) * 12.2f;
					Player::GetInstance()->SetCoordinates(position);
				}
			}
		}
    }

    static  Coordinates     g_savedPos[3] = { 0 };
    void    Teleporter(MenuEntry *entry)
    {
        auto   savePosition = [](void *slot) { g_savedPos[(u32)slot] = Player::GetInstance()->GetCoordinates(); };
        auto   loadPosition = [](void *slot) { Player::GetInstance()->SetCoordinates(g_savedPos[(u32)slot]); };

        static QuickMenuSubMenu *teleporterSubMenu = new QuickMenuSubMenu("Teleporter",
        {
            new QuickMenuEntry("Save position #1", savePosition, (void *)0),
            new QuickMenuEntry("Load position #1", loadPosition, (void *)0),
            new QuickMenuEntry("Save position #2", savePosition, (void *)1),
            new QuickMenuEntry("Load position #2", loadPosition, (void *)1),
            new QuickMenuEntry("Save position #3", savePosition, (void *)2),
            new QuickMenuEntry("Load position #3", loadPosition, (void *)2),
        });

        // If entry was just activated, add the Teleporter submenu to the QuickMenu
        if (entry->WasJustActivated())
            QuickMenu::GetInstance() += teleporterSubMenu;

        // But if we disabled the entry, then remove the Teleporter submenu from QuickMenu
        if (!entry->IsActivated())
        {
            QuickMenu::GetInstance() -= teleporterSubMenu;
            return;
        }

        int           slot = 0;

        if (entry->Hotkeys[2].IsDown())
            slot = 2;
        else if (entry->Hotkeys[3].IsDown())
            slot = 1;

        if (entry->Hotkeys[0].IsDown())
            g_savedPos[slot] = Player::GetInstance()->GetCoordinates();
        else if (entry->Hotkeys[1].IsDown())
            Player::GetInstance()->SetCoordinates(g_savedPos[slot]);
    }

    void    TeleportTo(int person)
    {
        u32     PlayerInfoPtr = AutoRegion(USA_PLAYERINFO_POINTER, EUR_PLAYERINFO_POINTER, JAP_PLAYERINFO_POINTER, USA_WA_PLAYERINFO_POINTER, EUR_WA_PLAYERINFO_POINTER, JAP_WA_PLAYERINFO_POINTER)();
        u32     off_PlayerSlot = AutoRegion(USA_PLAYER_SLOT, EUR_PLAYER_SLOT, JAP_PLAYER_SLOT, USA_WA_PLAYER_SLOT, EUR_WA_PLAYER_SLOT, JAP_WA_PLAYER_SLOT)();
        u8      currentSlot;
        u32     pointers[4];
        float   x, y, z;

        Process::Read8(off_PlayerSlot, currentSlot);
        for (int i = 0; i < 4; i++)
        {
            Process::Read32(PlayerInfoPtr + i*4, pointers[i]);
        }

        if ((u8)currentSlot == 0 || person >= (u8)currentSlot)
        {
            Process::ReadFloat(pointers[person + 1] + 0x14, x);
            Process::ReadFloat(pointers[person + 1] + 0x18, y);
            Process::ReadFloat(pointers[person + 1] + 0x1C, z);
            Player::GetInstance()->SetCoordinates(x, y, z);
        }
        else
        {
            Process::ReadFloat(pointers[person] + 0x14, x);
            Process::ReadFloat(pointers[person] + 0x18, y);
            Process::ReadFloat(pointers[person] + 0x1C, z);
            Player::GetInstance()->SetCoordinates(x, y, z);
        }

    }

    void    PWPTeleport(MenuEntry *entry)
    {
        std::vector<u8> buildings;
        std::vector<u8> x;
        std::vector<u8> y;
        u32 offset = Game::Building;
        Keyboard keyboard("Which building would you like to teleport to?");
        StringVector entryNames;

        for (int i = 0; i < 20; i++)
        {
            if (*(u8 *)(offset) != 0xFC)
            {
  
                buildings.push_back(READU8(offset));
                x.push_back(READU8(offset + 2));
                y.push_back(READU8(offset + 3));
            }
            offset += 4;
        }
        for (int i = 0; i < buildings.size(); ++i)
        {
            for (const Building& building : buildingIDS)
            {
                if (building.id != buildings[i])
                    continue;

                entryNames.push_back(building.Name);
                break;
            }
        }
        keyboard.Populate(entryNames);
        int index = keyboard.Open();

        Player::GetInstance()->SetIntCoordinates(x[index], y[index] + 3);
    }

    void    WalkOverThings(MenuEntry *entry)
    {
        static bool btn = false;
        static bool active = false;
        static const u32 offsets[] = { 0x6503FC, 0x6506A4, 0x6506BC, 0x6506C0, 0x6506EC };
        static const u32 original[] = { 0x0A000094, 0xED841A05, 0xED840A07, 0x0A000026, 0x0A000065 };
        static const u32 patch[] = { 0xEA000094, 0xE1A00000, 0xE1A00000, 0xEA000026, 0xEA000065 };
        
        if (entry->Hotkeys[0].IsDown() && !btn)
        {
            if (!active)
            {
                for (int i = 0; i < 5; i++) {
                    Process::Patch(offsets[i] + (u32)Game::CodeDifference, patch[i]);
                }
                OSD::Notify("Walk Over Things: " << Color::Green << "Enabled!");
                active = true;
                btn = true;
            }

            else if (active)
            {
                for (int i = 0; i < 5; i++) {
                    Process::Patch(offsets[i] + (u32)Game::CodeDifference, original[i]);
                }
                OSD::Notify("Walk Over Things: " << Color::Red << "Disabled!");
                active = false;
                btn = true;
            }
        }

        else if (!entry->Hotkeys[0].IsDown())
            btn = false;
    }

    void    SpeedHack(MenuEntry *entry)
    {
        if (Controller::IsKeyDown(B) || Controller::IsKeyDown(L) || Controller::IsKeyDown(R))
        {
            float       velocity;
            float       speed = *GetArg<float>(entry, 5.238f);

            if (!Process::ReadFloat(Game::Velocity, velocity)) //#TODO: check if we're on a loading screen or no
                return;

            if (velocity >= speed)
                Process::WriteFloat(Game::Velocity, speed);
            else if (velocity > 0.0f)
                Process::WriteFloat(Game::Velocity, velocity + 0.5f);
        }
    }

    void    SpeedHackEditor(MenuEntry *entry)
    {
        Keyboard keyboard("Which speed would you like to use?");
        static std::vector<std::string> list =
        {
            "Regular",
            "Fast",
            "Faster",
            "Sanic",
            "Sonic Boom!",
            "Warp Speed WARNING!"
        };
        keyboard.Populate(list);
        keyboard.CanAbort(false);

        int     userChoice = keyboard.Open();
        float   *speed = GetArg<float>(entry);

        *speed = 5.238f * (userChoice + 1);
    }

    void    MoonJump(MenuEntry *entry)
    {
        static Clock time;

        Time delta = time.Restart();

        float value = 200.0f * delta.AsSeconds();
        float speed = *GetArg<float>(entry, 1.f);

        if (entry->Hotkeys[0].IsDown())
        {
                Process::Write16(Game::Gravity, 0xFFFF);
                Player::GetInstance()->AddToCoordinates(0.f, value * speed, 0.f);
        }
        if (entry->Hotkeys[1].IsDown())
        {
            Player::GetInstance()->AddToCoordinates(0.f, 0 - value * speed, 0.f);
        }
    }

    void RoomPicker(MenuEntry *entry)
    {
		if (entry->Hotkeys[0].IsDown())
		{
			StringVector options;
			for (const IDs& option : rooms)
				options.push_back(option.Name);
			Keyboard keyboard("Which room would you like to warp to?\n\nNote:\nSome rooms may crash under certain\ncircumstances, which are out of\nour control and due to your save.\nIf your character appears fully black and\nyou can't move, use the faint cheat.");
			keyboard.Populate(options);
			int index = keyboard.Open();
			if (index == -1)
				return;
			int result = Game::TeleportRoom(rooms[index].id);
			switch (result)
			{
				case -1:
					OSD::Notify("You currently cannot warp!");
					break;
				case -2:
					OSD::Notify("You cannot warp at club tortimer!");
					break;
				case -3:
					OSD::Notify("You cannot warp from this area!");
					break;
				case -4:
					OSD::Notify("Please stand still while trying to teleport!");
					break;
				default:
					OSD::Notify(Utils::Format("Teleporting to... %s", rooms[index].Name));
					break;
			}
        }
    }
}
