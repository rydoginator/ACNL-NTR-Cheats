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
        static UIntRect     mapArea(70, 50, 175, 155);

        UIntVector  touchPos = Touch::GetPosition();
        Coordinates position = Player::GetInstance()->GetCoordinates();

        if (mapArea.Contains(touchPos))
        {
            if (*Game::MapBool == 1)
            {
                switch (*Game::Room)
                { //todo:add more room ids
                    case 0:
                        goto MainLand;
                        break;
                    case 0x69:
                        goto MainLand;
                        break;
                    default:
                        break;

                }//todo: find data for island and main street
                return;
            MainLand:
                FloatVector  fPos(touchPos);

                position.x = (fPos.x - 77.f) * 14.94f + 526.f;
                position.z = (fPos.y - 50.f) * 15.21f + 526.f;
                Player::GetInstance()->SetCoordinates(position);
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
        u32     coordinatePointer = AutoRegion(USA_CAMSTOP_POINTER, EUR_CAMSTOP_POINTER, JAP_CAMSTOP_POINTER)();
        u8      coordinateIndex;
        u32     pointers[4];
        float   x, y, z;

        Process::Read8(AutoRegion(USA_COORDINATES_BYTE, EUR_COORDINATES_BYTE, JAP_COORDINATES_BYTE)(), coordinateIndex);
        for (int i = 0; i < 4; i++)
        {
            Process::Read32(coordinatePointer + i *4, pointers[i]);
        }

        if ((u8)coordinateIndex == 0 || person >= (u8)coordinateIndex)
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
        for (int i = 0; i < buildings.size(); i++)
        {
            for (int j = 0; j < buildingIDS.size(); j++)
            {
                if (buildingIDS[j].id == buildings[i])
                    entryNames.push_back(buildingIDS[j].Name);
            }
        }
        keyboard.Populate(entryNames);
        int index = keyboard.Open();

        Player::GetInstance()->SetIntCoordinates(x[index], y[index] + 3);
    }

    void    WalkOverThings(MenuEntry *entry)
    {
        u32     offsets[] = { 0x6503FC, 0x650414, 0x650578, 0x6505F0, 0x6506A4, 0x6506BC, 0x6506C0, 0x6506ec };
        u32     original[] = { 0x0A000094, 0x0A000052, 0x0A000001, 0xDA000014, 0xED841A05, 0xED840A07, 0x0A000026, 0x0A000065 };
        u32     patch[] = { 0xEA000094, 0xEA000052, 0xEA000001, 0xEA000014, 0xE1A00000, 0xE1A00000, 0xEA000026, 0xEA000065 };
        
        if (entry->Hotkeys[0].IsDown())
        {
            for (int i = 0; i < 8; i++)
            {
                Process::Patch(offsets[i] + (u32)Game::CodeDifference, (u8 *)&patch[i], 4);
            }
        }

        if (entry->Hotkeys[1].IsDown())
        {
            for (int i = 0; i < 8; i++)
            {
                Process::Patch(offsets[i] + (u32)Game::CodeDifference, (u8 *)&original[i], 4);
            }
        }
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
            else if (velocity > 0)
                Process::WriteFloat(Game::Velocity, velocity + 0.1f);
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
}
