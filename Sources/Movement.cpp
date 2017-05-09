#include "cheats.hpp"

namespace CTRPluginFramework
{
    void    CoordinateModifier(MenuEntry *entry)
    {
        static u32 offset;
        extern u32 g_coordinates_pointer;
        offset = READU32(g_coordinates_pointer);
        if (offset != 0)
        {
            offset += 0x24;
            if (Controller::IsKeysDown(A + DPadDown))
                ADDTOFLOAT(offset + 8, 0.1f);
            if (Controller::IsKeysDown(A + DPadUp))
                SUBTOFLOAT(offset + 8, 0.1f);
            if (Controller::IsKeysDown(A + DPadLeft))
                SUBTOFLOAT(offset, 0.1f);
            if (Controller::IsKeysDown(A + DPadRight))
                ADDTOFLOAT(offset, 0.1f);
        }
    }

    void    Teleporter(MenuEntry *entry)
    {
        static u32 offset;
        static u32    X[3] = { 0 };
        static u32    Y[3] = { 0 };
        int           loc;
        int           slot;
        extern u32 g_coordinates_pointer;

        if (Controller::IsKeysDown(L))
        {
            slot = 2;
        }
        else if (Controller::IsKeysDown(R))
        {
            slot = 1;
        }
        else
        {
            slot = 0;
        }

        offset = READU32(g_coordinates_pointer);
        if (offset != 0)
        {
            offset += 0x24;
            if (Controller::IsKeysDown(B + DPadUp))
            {
                X[slot] = READU32(offset);
                Y[slot] = READU32(offset + 8);
            }
            else if (Controller::IsKeysDown(B + DPadDown))
            {
                WRITEU32(offset, X[slot]);
                WRITEU32(offset + 8, Y[slot]);
            }
        }
    }

    void    WalkOverThings(MenuEntry *entry)
    {
        u32 offsets[] = { 0x6503FC, 0x650414, 0x650578, 0x6505F0, 0x6506A4, 0x6506BC, 0x6506C0, 0x6506ec };
        u32 original[] = { 0x0A000094, 0x0A000052, 0x0A000001, 0xDA000014, 0xED841A05, 0xED840A07, 0x0A000026, 0x0A000065 };
        u32 patch[] = { 0xEA000094, 0xEA000052, 0xEA000001, 0xEA000014, 0xE1A00000, 0xE1A00000, 0xEA000026, 0xEA000065 };
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
        char buffer[0x100];
        u32     velocity;
        float   acceleration;
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
        u32     offset;
        extern u32 g_coordinates_pointer;
        extern u32 g_out_grav;

        offset = READU32(g_coordinates_pointer);
        if (Controller::IsKeysDown(L + DPadUp))
        {
            if (offset != 0)
            {
                offset += 0x24;
                WRITEU16(g_out_grav, 0xFFFF);
                ADDTOFLOAT(offset + 4, 0.05f);
            }
        }
        if (Controller::IsKeysDown(L + DPadDown))
        {
            if (offset != 0)
            {
                offset += 0x24;
                SUBTOFLOAT(offset + 4, 0.05f);
            }
        }
    }
}