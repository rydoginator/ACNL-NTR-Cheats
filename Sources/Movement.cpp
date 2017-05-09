#include "cheats.hpp"

namespace CTRPluginFramework
{
    void    CoordinateModifier(MenuEntry *entry)
    {
        if (Controller::IsKeysDown(A + DPadDown))
            Player::GetInstance()->AddToCoordinates(0.f, 0.f, 0.1f);
        if (Controller::IsKeysDown(A + DPadUp))
            Player::GetInstance()->AddToCoordinates(0.f, 0.f, -0.1f);
        if (Controller::IsKeysDown(A + DPadLeft))
            Player::GetInstance()->AddToCoordinates(-1.f, 0.f, 0.f);
        if (Controller::IsKeysDown(A + DPadRight))
            Player::GetInstance()->AddToCoordinates(0.1f, 0.f, 0.f);
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

    void    WalkOverThings(MenuEntry *entry)
    {
        u32     offsets[] = { 0x6503FC, 0x650414, 0x650578, 0x6505F0, 0x6506A4, 0x6506BC, 0x6506C0, 0x6506ec };
        u32     original[] = { 0x0A000094, 0x0A000052, 0x0A000001, 0xDA000014, 0xED841A05, 0xED840A07, 0x0A000026, 0x0A000065 };
        u32     patch[] = { 0xEA000094, 0xEA000052, 0xEA000001, 0xEA000014, 0xE1A00000, 0xE1A00000, 0xEA000026, 0xEA000065 };
        
        if (Controller::IsKeysDown(L + DPadUp))
        {
            for (int i = 0; i < 8; i++)
            {
                Process::Patch(offsets[i], (u8 *)&patch[i], 4);
            }
        }

        if (Controller::IsKeysDown(L + DPadDown))
        {
            for (int i = 0; i < 8; i++)
            {
                Process::Patch(offsets[i], (u8 *)&original[i], 4);
            }
        }
    }

    void    SpeedHack(MenuEntry *entry)
    {
        u32     velocity;
        extern u32 g_velocity;

        if (Controller::IsKeysDown(B))
        {
            velocity = READU32(g_velocity);
            if (velocity >= 0x41A79DB3)
            {
                WRITEU32(g_velocity, 0x41A79DB3);
            }
            else if (velocity > 0)
            {
                ADDTOFLOAT(g_velocity, 0.1f);
            }
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