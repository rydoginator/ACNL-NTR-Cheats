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

        if (!Controller::IsKeysDown(R + A) && entry != nullptr)
            return;

        FindReplacer<u16>  findReplacer(reinterpret_cast<u32>(Game::TownItem), 0x5000);

        for (int i = 0; i < 7; i++)
        {
            findReplacer.AddPair(weeds[i], 0x7FFE);
        }

        findReplacer();
    }

    void    SearchReplace(MenuEntry *entry)
    {
        static u32 search, replace;
        FindReplacer<u32> findReplacer(reinterpret_cast<u32>(Game::TownItem), 0x5000);
        Keyboard keyboard("What item would you like to search?");

        if (keyboard.Open(search) != -1)
        {
            Keyboard keyboard("What item would you like to replace it with?");
            if (keyboard.Open(replace) != -1)
            {
                findReplacer.AddPair(search, replace);
                findReplacer();
            }
        }
    }

    void    FillGrass(MenuEntry *entry)
    {
        static u32 offset = reinterpret_cast<u32> (Game::Grass);

        if(!Controller::IsKeysDown(R + A) && entry != nullptr)
            return;

        for (offset; offset < reinterpret_cast<u32>(Game::GrassEnd); offset += 4)
            Process::Write32(offset, 0xFFFFFFFF);
    }

    void    DestroyGrass(MenuEntry *entry)
    {
        static u32 offset = reinterpret_cast<u32> (Game::Grass);

        if (!Controller::IsKeysDown(R + A) && entry != nullptr)
            return;

        for (offset; offset < reinterpret_cast<u32>(Game::GrassEnd); offset += 4)
            Process::Write32(offset, 0x00000000);
    }

    void    WaterAllFlowers(MenuEntry *entry)
    {
        if (!Controller::IsKeysDown(R + A) && entry != nullptr)
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

    void    WorldEdit(MenuEntry *entry)
    {
        static u32 itemID;
        static bool valid = false; //boolean to declare whether you're using a valud value or not

        if (!Controller::IsKeyDown(R)) //return if not pressing R
            return;
        u32  *address = Game::GetItem(); //get the address of where your character is standing

        if (Controller::IsKeyDown(DPadLeft))
        {
            Keyboard    keyboard("What item would you like to use?");
            u32 item;
            if (keyboard.Open(itemID) != -1) //return if the user aborts (if != -1)
                valid = true;
            else
                valid = false; // if the user aborts, you don't want to be writing abritary values
        }

        if (Controller::IsKeyDown(DPadUp))
        {
            itemID = *address; //get the value of address
            valid = true;
        }

        if (Controller::IsKeyDown(DPadDown))
        {
            if (valid && address != nullptr)
                *address = itemID;
        }
    }
}
