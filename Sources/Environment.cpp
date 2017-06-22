#include "cheats.hpp"
#include "FindReplacer.hpp"

namespace CTRPluginFramework
{
    void    RemoveAllItems(MenuEntry *entry)
    {
        if (Controller::IsKeysDown(R + A))
        {
            u32     *item = Game::TownItem;

            for (int i = 0; i < 0x1400; i++)
            {
                *item++ =  0x00007FFE;
            }
        }
    }

    void    RemoveAllWeeds(MenuEntry *entry)
    {
        static u16 weeds[] = { 0x007C, 0x007D, 0x007E, 0x007F, 0x00CB, 0x00CC, 0x00CD, 0x00F8 };

        if (!Controller::IsKeysDown(R + A) && !g_command)
            return;

        FindReplacer<u16>  findReplacer(reinterpret_cast<u32>(Game::TownItem), 0x5000);

        for (int i = 0; i < 7; i++)
        {
            findReplacer.AddPair(weeds[i], 0x7FFE);
        }

        findReplacer();
    }

    void    WaterAllFlowers(MenuEntry *entry)
    {
        if (!Controller::IsKeysDown(R + A) && !g_command)
            return;

        u32     address = reinterpret_cast<u32>(Game::TownItem);
        u32     end = address + RANGE_TOWN_ITEMS;
        u32     item;

        // Parse all items in Town
        for (; address < end; address += ITEM_BYTES)
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
        static u32  itemID;
        static int  valid = -1;
        char buffer[0x100];       

        // Enter the item to place
        if (Controller::IsKeyPressed(R))
        {
            u32 *i = Game::GetItem();
            itemID = *i;
            sprintf(buffer, "Offset: %08X \nValue: %08X", Game::GetItem(), itemID);
            OSD::Notify(buffer);
        }
        if (Controller::IsKeysDown(R + DPadLeft))
        {
            Keyboard    keyboard("What item would you like to use?");

            u32     output;
            int     result = keyboard.Open(output);

            // if result == -1, output is undefined so do nothing
            if (result != -1)
            {
                itemID = output;
                valid = 0;
            }
            else
                valid = -1;
        }

        // Write the saved item where you're standing on
        if (Controller::IsKeysDown(R + DPadDown))
        {
            u32  *pointer = Game::GetItem();

            if (valid == 0 && pointer != nullptr)
                *pointer = itemID;
        }

        // Save the item you're standing on
        if (Controller::IsKeysDown(R + DPadUp))
        {
            u32 *i = Game::GetItem();

            if (i != nullptr)
            {
                itemID = *i;
                valid = 0;
            }                
        }
    }
}
