#include "cheats.hpp"

namespace CTRPluginFramework
{
    void    Text2Item(MenuEntry *entry)
    {
        if (Controller::IsKeysDown(X + DPadRight))
        {
            u32 output;
            // New keyboard, hint being:
            Keyboard keyboard("What item would you like ?");

            // Add the function to check the input entered by the user
            keyboard.SetCompareCallback(CheckItemInput);

            // If the function return -1, then the user canceled the keyboard, so do nothing 
            if (keyboard.Open(output) != -1)
            {
                Player::GetInstance()->WriteSlot(0, output);
            }
        }
    }

    void    Duplication(MenuEntry *entry)
    {
        u32 item;
        if (Controller::IsKeyDown(R))
        {
            Player::GetInstance()->ReadSlot(0, item);
            Player::GetInstance()->WriteSlot(1, item);
        }
    }

    void    ShowBuriedItems(MenuEntry *entry)
    {
        extern u32 g_room;
        extern u32 g_main_x;
        extern u32 g_main_y;
        extern u32 g_world_x;
        extern u32 g_world_y;
        extern u32 g_town_items;
        extern u32 g_club_items;
        extern u32 g_thought;

        u8    room = READU8(g_room);
        u32   x = room == 0x01 ? READU32(g_main_x) : READU32(g_world_x);
        u32   y = room == 0x01 ? READU32(g_main_y) : READU32(g_world_y);
        u32   offset = computeOffset(x, y);
        u32   patch = 0xE1A00000;
        u32   original = 0xA000049;
        u16   item;

        if (room == 0x00)
        {
            if (READU16(g_town_items + offset + 0x2) == 0x8000) //check to see if you're on a buried spot
            {
                item = getItem(g_town_items);
                WRITEU16(g_thought, item);
                Process::Patch(0x002160BC, (u8 *)&patch, 4); //nop the instruction that overwrites external thought bubbles
            }
            else
            {
                if (READU32(0x002160BC) != original)
                {
                    Process::Patch(0x002160BC, (u8 *)&original, 4);
                    WRITEU16(g_thought, 0x7FFE);
                }
            }
        }
        else if (room == 0x6F)
        {
            if (READU16(g_club_items + offset + 0x2) == 0x8000) //check to see if you're on a buried spot
            {
                item = getItem(g_club_items);
                WRITEU16(g_thought, item);
                Process::Patch(0x002160BC, (u8 *)&patch, 4); //nop the instruction that overwrites external thought bubbles
            }
            else
            {
                if (READU32(0x002160BC) != original)
                {
                    Process::Patch(0x002160BC, (u8 *)&original, 4);
                    WRITEU16(g_thought, 0x7FFE);
                }
            }
        }
    }

    void    PickBuriedItems(MenuEntry *entry)
    {
        extern u32 g_room;
        extern u32 g_main_x;
        extern u32 g_main_y;
        extern u32 g_world_x;
        extern u32 g_world_y;
        extern u32 g_town_items;
        extern u32 g_club_items;

        u8    room = READU8(g_room);
        u32   x = room == 0x01 ? READU32(g_main_x) : READU32(g_world_x);
        u32   y = room == 0x01 ? READU32(g_main_y) : READU32(g_world_y);
        u32   offset = computeOffset(x, y);
        u16   item;


        if (room == 0x00)
        {
            if (READU16(g_town_items + offset + 0x2) == 0x8000)
            {
                if (Controller::IsKeysDown(Y))
                {
                    WRITEU16(g_town_items + offset + 0x2, 0x0000);
                }
            }
        }
        else if (room == 0x6F)
        {
            if (READU16(g_club_items + offset + 0x2) == 0x8000)
            {
                if (Controller::IsKeysDown(Y))
                {
                    WRITEU16(g_club_items + offset + 0x2, 0x0000);
                }
            }
        }
    }

    void    ShowBells(MenuEntry *entry)
    {
        u64 money;
        u32 result;
        char buffer[0x100];

        Player::GetInstance()->Read64(0x6f08, money);
        result = DecryptACNLMoney(money);

        sprintf(buffer, "Bells %i", result);
        OSD::WriteLine(1, buffer, 0, 0);
    }

    void    SetBells(MenuEntry *entry)
    {
        u64     money;
        u32     output;

        Keyboard keyboard("How much money would you like?");

        keyboard.IsHexadecimal(false);

        // If the function return -1, then the user canceled the keyboard, so do nothing 
        if (keyboard.Open(output) != -1)
        {
            money = EncryptACNLMoney(output);

            Player::GetInstance()->Write64(0x6f08, money);
        }
    }
}