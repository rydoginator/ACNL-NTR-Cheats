#include "cheats.hpp"

namespace CTRPluginFramework
{
    void    BuildingPlacer(MenuEntry *entry)
    {
        u32 offset = 0;
        u8 input;
        u8 x = READU8(g_world_x);
        u8 y = READU8(g_main_y);
        if (Controller::IsKeysDown(R + DPadDown))
        {
            Keyboard keyboard("What building would you like to place?");

            //Exit if the user cancel the keyboard
            if (keyboard.Open(input) == -1)
                return;

            while (READU8(g_building_addr + offset) != 0xFC && offset < 0xE5)
            {
                offset += 0x4;
            }
            if (offset == 0xE5)
            {
                OSD::Notify("All building slots are filled!");
            }
            else
            {
                WRITEU8(g_building_addr + offset, input);
                WRITEU8(g_building_addr + offset + 0x2, x);
                WRITEU8(g_building_addr + offset + 0x3, y);
            }
        }
        if (Controller::IsKeysDown(R + DPadUp))
        {
            Keyboard keyboard("What building would you like to remove?");

            // Exit if the user cancel the keyboard
            if (keyboard.Open(input) == -1)
                return;

            while (READU8(g_building_addr + offset) != input && offset < 0xE5)
            {
                offset += 0x4;
            }
            if (offset == 0xE5)
            {
                OSD::Notify("Could not find your building");
            }
            else
            {
                WRITEU8(g_building_addr + offset, 0xFC);
                WRITEU8(g_building_addr + offset + 0x2, 0x00);
                WRITEU8(g_building_addr + offset + 0x3, 0x00);
            }
        }
    }

    void    GhostMode(MenuEntry *entry)
    {
        u32   patch = 0xE38110FF;
        u32   original = 0xE3811004;

        if (Controller::IsKeysDown(Y + DPadUp))
        {
            Process::Patch(0x00654594, (u8 *)&patch, 4);
        }
        if (Controller::IsKeysDown(Y + DPadDown))
        {
            Process::Patch(0x00654594, (u8 *)&original, 4);
        }
    }

    void    CameraMod(MenuEntry *entry)
    {
        u32 offset;
        static u32 pointer;
        static u32 x;
        static u32 z;
        static u32 storage;
        u32   patch = 0xEA000020;
        u32   original = 0x2A000020;

        if (Controller::IsKeyReleased(B))
        {
            Process::Patch(g_camera_asm, (u8 *)&original, 4);
        }
        if (READU32(g_camera_pointer) != 0)
        {
            if (!Controller::IsKeyDown(CPad))
            {
                if (READU32(g_coordinates_pointer) != 0)
                {
                    pointer = READU32(g_coordinates_pointer);
                    x = READU32(pointer + 0x24);
                    z = READU32(pointer + 0x2C);
                }
            }
            offset = READU32(g_camera_pointer);
            if (Controller::IsKeysDown(R + CPadDown))
            {
                offset += 0x12C;
                ADD16(offset, 0x2);
            }
            if (Controller::IsKeysDown(R + CPadUp))
            {
                offset += 0x12C;
                SUB16(offset, 0x2);
            }
            if (Controller::IsKeysDown(R + CPadRight))
            {
                offset += 0x12E;
                ADD16(offset, 0x2);
            }
            if (Controller::IsKeysDown(R + CPadLeft))
            {
                offset += 0x12E;
                SUB16(offset, 0x2);
            }
            if (Controller::IsKeysDown(R + CPadDown))
            {
                if (READU32(g_coordinates_pointer) != 0)
                {
                    pointer = READU32(g_coordinates_pointer);
                    WRITEU32(pointer + 0x24, x);
                    WRITEU32(pointer + 0x2C, z);
                }
            }
            if (Controller::IsKeysDown(R + X))
            {
                if (READU32(g_camstop_pointer) != 0)
                {
                    storage = READU32(g_camstop_pointer);
                    WRITEU32(g_camstop_pointer, 0x00000000);
                }
            }
            if (Controller::IsKeysDown(R + Y))
            {
                if (storage != 0)
                {
                    WRITEU32(g_camstop_pointer, storage);
                }
            }
        }
        if (Controller::IsKeysDown(B + DPadLeft))
        {
            Process::Patch(g_camera_asm, (u8 *)&patch, 4); //change the asm instruction to b, allows overwriting camera coordinates
            SUBTOFLOAT(g_camera_x, 0.1f);
        }
        if (Controller::IsKeysDown(B + DPadRight))
        {
            Process::Patch(g_camera_asm, (u8 *)&patch, 4);
            ADDTOFLOAT(g_camera_x, 0.1f);
        }
        if (Controller::IsKeysDown(B + DPadDown))
        {
            Process::Patch(g_camera_asm, (u8 *)&patch, 4);
            ADDTOFLOAT(g_camera_z, 0.1f);
        }
        if (Controller::IsKeysDown(B + DPadUp))
        {
            Process::Patch(g_camera_asm, (u8 *)&patch, 4);
            SUBTOFLOAT(g_camera_z, 0.1f);
        }
        if (Controller::IsKeysDown(B + R))
        {
            Process::Patch(g_camera_asm, (u8 *)&patch, 4);
            ADDTOFLOAT(g_camera_y, 0.1f);
        }
        if (Controller::IsKeysDown(B + L))
        {
            Process::Patch(g_camera_asm, (u8 *)&patch, 4);
            SUBTOFLOAT(g_camera_y, 0.1f);
        }
    }

    void    KeyboardExtender(MenuEntry *entry)
    {
        u32 offset = 0;

        Process::Read32(0x95F11C, offset);
        if (offset != 0)
        {
            Process::Write32(0xC + offset, 0x36);
            Process::Write32(0x12B + offset, 0x45);
            Process::Write8(0xAD7253, 0x01);
        }
    }
}