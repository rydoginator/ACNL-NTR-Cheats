#include "cheats.hpp"
#include "CTRPluginFramework/System/Rect.hpp"
#include "Helpers/MenuEntryHelpers.hpp"

namespace CTRPluginFramework
{
    void    CoordinateModifier(MenuEntry *entry)
    {
        static Clock time;

        Time delta = time.Restart();

        float value = 400.0f * delta.AsSeconds();
        float NegValue = -400.0f * delta.AsSeconds();

        if (Controller::IsKeysDown(A + DPadDown))
            Player::GetInstance()->AddToCoordinates(0.f, 0.f, value);
        if (Controller::IsKeysDown(A + DPadUp))
            Player::GetInstance()->AddToCoordinates(0.f, 0.f, NegValue);
        if (Controller::IsKeysDown(A + DPadLeft))
            Player::GetInstance()->AddToCoordinates(NegValue, 0.f, 0.f);
        if (Controller::IsKeysDown(A + DPadRight))
            Player::GetInstance()->AddToCoordinates(value, 0.f, 0.f);
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

    void    Teleporter(MenuEntry *entry)
    {
        static Coordinates  savedPos[3] = { 0 };

        int           slot = 0;

        if (Controller::IsKeysDown(L))
            slot = 2;
        else if (Controller::IsKeysDown(R))
            slot = 1;

        if (Controller::IsKeysDown(B + DPadUp))
        {
            savedPos[slot] = Player::GetInstance()->GetCoordinates();
        }
        else if (Controller::IsKeysDown(B + DPadDown))
        {
            Player::GetInstance()->SetCoordinates(savedPos[slot]);
        }
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

    void    WalkOverThings(MenuEntry *entry)
    {
        u32     offsets[] = { 0x6503FC, 0x650414, 0x650578, 0x6505F0, 0x6506A4, 0x6506BC, 0x6506C0, 0x6506ec };
        u32     original[] = { 0x0A000094, 0x0A000052, 0x0A000001, 0xDA000014, 0xED841A05, 0xED840A07, 0x0A000026, 0x0A000065 };
        u32     patch[] = { 0xEA000094, 0xEA000052, 0xEA000001, 0xEA000014, 0xE1A00000, 0xE1A00000, 0xEA000026, 0xEA000065 };
        
        if (Controller::IsKeysDown(L + DPadUp))
        {
            for (int i = 0; i < 8; i++)
            {
                Process::Patch(offsets[i] + (u32)Game::CodeDifference, (u8 *)&patch[i], 4);
            }
        }

        if (Controller::IsKeysDown(L + DPadDown))
        {
            for (int i = 0; i < 8; i++)
            {
                Process::Patch(offsets[i] + (u32)Game::CodeDifference, (u8 *)&original[i], 4);
            }
        }
    }

    void    SpeedHack(MenuEntry *entry)
    {
        if (Controller::IsKeysDown(B))
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
        if (Controller::IsKeysDown(L + DPadUp))
        {
                Process::Write16(Game::Gravity, 0xFFFF);
                Player::GetInstance()->AddToCoordinates(0.f, 0.05f, 0.f);
        }
        if (Controller::IsKeysDown(L + DPadDown))
        {
            Player::GetInstance()->AddToCoordinates(0.f, -0.05f, 0.f);
        }
    }
}
