#include "cheats.hpp"

namespace CTRPluginFramework
{
    void    RemoveAllItems(MenuEntry *entry)
    {
        extern u32 g_town_items;
        if (Controller::IsKeysDown(R + A))
        {
            for (int i = 0; i < 0x1400; i++)
            {
                WRITEU32(g_town_items + (i * 4), 0x00007FFE);
            }
        }
    }

    void    RemoveAllWeeds(MenuEntry *entry)
    {
        extern u32 g_town_items;
        u16 weeds[] = { 0x007C, 0x007D, 0x007E, 0x007F, 0x00CB, 0x00CC, 0x00CD, 0x00F8 };

        if (!Controller::IsKeysPressed(R + A) && g_command)
            return;
        for (int i = 0; i < 7; i++)
        {
            reset_search();
            add_search_replace(weeds[i], 0x7FFE);
            find_and_replace_multiple(g_town_items, 0x5000);
        }
    }

    void    WaterAllFlowers(MenuEntry *entry)
    {
        extern u32 g_town_items;
        u32     address;
        u32     item;

        if (!Controller::IsKeysPressed(R + A) && g_command)
            return;
        // Parse all items in Town
        for (address = g_town_items; address < g_town_items + RANGE_TOWN_ITEMS; address += ITEM_BYTES)
        {
            item = READU16(address);
            // Deal with wilted flower
            if (item >= 0xCE && item <= 0xF7)
            {
                item -= 0x2F;
            }
            // If item is a flower add water flag
            if (item >= 0x9F && item <= 0xC8)
            {
                item |= 0x40000000;
                WRITEU32(address, item);
            }
        }
    }

    void     WorldEdit(MenuEntry *entry)
    {
        extern u32 g_town_items;
        extern u32 g_main_items;
        extern u32 g_island_items;
        extern u8 g_room;
        extern u32 g_world_x;
        extern u32 g_world_y;
        extern u32 g_main_x;
        extern u32 g_main_y;
        static u32 item;
        static int valid = -1;
        char buffer[0x100];

        u32 output;

        if (Controller::IsKeysDown(R + DPadLeft))
        {
            Keyboard keyboard("What item would you like to use?");
            keyboard.IsHexadecimal(true);

            int result = keyboard.Open(output);

            // if result == -1, output is undefined so do nothing
            if (result != -1)
            {
                item = output;
                valid = 0;
            }
            else
                valid = -1;
        }
        if (Controller::IsKeysDown(R + DPadDown))
        {
            if (READU8(g_room) == 0x01)
                writeLocation(g_main_items, item);
            else if (READU8(g_room) == 0x00)
                writeLocation(g_town_items, item);
            else if (READU8(g_room) == 0x68)
                writeLocation(g_island_items, item);
        }
        if (Controller::IsKeysDown(R + DPadUp))
        {
            if (READU8(g_room) == 0x01)
            {
                item = getItem(g_main_items);
                sprintf(buffer, "%08X -> %08X", g_main_items, getItem(g_main_items));
                OSD::Notify(buffer);
            }
            else if (READU8(g_room) == 0x00)
            {
                item = getItem(g_town_items);
            }
            else if (READU8(g_room) == 0x68)
            {
                item = getItem(g_island_items);
            }
        }
        if (Controller::IsKeyPressed(R))
        {
            u8    room = READU8(g_room);
            u32   x = room == 0x01 ? READU32(g_main_x) : READU32(g_world_x);
            u32   y = room == 0x01 ? READU32(g_main_y) : READU32(g_world_y);
            u32   offset = computeOffset(x, y);
            u32   item;
            if (room == 0x01)
            {
                item = getItem(g_main_items);
                sprintf(buffer, "%08X -> %08X", offset + g_main_items, item);
                OSD::Notify(buffer);
            }
            else if (room == 0x00)
            {
                item = getItem(g_town_items);
                sprintf(buffer, "%08X -> %08X", offset + g_town_items, item);
                OSD::Notify(buffer);
            }
            else if (room == 0x68)
            {
                item = getItem(g_island_items);
                sprintf(buffer, "%08X -> %08X", offset + g_island_items, item);
                OSD::Notify(buffer);
            }

        }
    }
}