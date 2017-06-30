#include "cheats.hpp"
#include "CTRPluginFramework/System/Rect.hpp"

namespace CTRPluginFramework
{
    void    CoordinateModifier(MenuEntry *entry)
    {
        if (Controller::IsKeysDown(A + DPadDown))
            Player::GetInstance()->AddToCoordinates(0.f, 0.f, 0.1f);
        if (Controller::IsKeysDown(A + DPadUp))
            Player::GetInstance()->AddToCoordinates(0.f, 0.f, -0.1f);
        if (Controller::IsKeysDown(A + DPadLeft))
            Player::GetInstance()->AddToCoordinates(-0.1f, 0.f, 0.f);
        if (Controller::IsKeysDown(A + DPadRight))
            Player::GetInstance()->AddToCoordinates(0.1f, 0.f, 0.f);
    }

    void    TouchCoordinates(MenuEntry *entry)
    {
        static UIntRect     mapArea(70, 50, 175, 155);

        UIntVector  touchPos = Touch::GetPosition();
        Coordinates position = Player::GetInstance()->GetCoordinates();

        if (mapArea.Contains(touchPos))
        {
            FloatVector  fPos(touchPos);

            position.x = (fPos.x - 77.f) * 14.94f + 526.f;
            position.z = (fPos.y - 50.f) * 15.21f + 526.f;
            Player::GetInstance()->SetCoordinates(position);
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
        // Init - Set velocity if it's 0
        if (!entry->GetArg())
        {
            entry->SetArg(new float);
            float *arg = static_cast<float *>(entry->GetArg());
            *arg = 0.1f;
        }

        if (Controller::IsKeysDown(B))
        {
            u32     velocity = READU32(Game::Velocity);
            float   speed = *static_cast<float *>(entry->GetArg());
 
            if (velocity >= 0x41A79DB3)
            {
                WRITEU32(Game::Velocity, 0x41A79DB3);
            }
            else if (velocity > 0)
            {
                ADDTOFLOAT(Game::Velocity, speed);
            }
        }
    }

    bool    CheckSpeedInput(const void *in, std::string &error)
    {
        float  input = *reinterpret_cast<const float *>(in);

        // If input >= 1.f => ERROR
        if (input >= 1.f)
        {
            error = "Error !\n\nThe speed can't be superior to 0.9";
            return (false);
        }

        // If input <= 0.f => ERROR
        if (input <= 0.f)
        {
            error = "Error !\n\nThe speed must be superior to 0 and can't be negative";
            return (false);
        }

        // Else we're good
        return (true);
    }

    void    SpeedHackEditor(MenuEntry *entry)
    {
        // Init - Set velocity if it's 0
        if (!entry->GetArg())
        {
            entry->SetArg(new float);
            float *arg = static_cast<float *>(entry->GetArg());
            *arg = 0.1f;
        }

        Keyboard kb("Speed Hack Editor\n\nEnter the speed you want to use:");

        float   *initialSpeed = static_cast<float *>(entry->GetArg());
        float   newSpeed;

        kb.SetCompareCallback(CheckSpeedInput);

        if (kb.Open(newSpeed, *initialSpeed) != -1)
        {
            *initialSpeed = newSpeed;
        }
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
