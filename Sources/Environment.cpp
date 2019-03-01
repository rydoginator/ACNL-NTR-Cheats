#include "cheats.hpp"
#include "FindReplacer.hpp"
#include "Helpers/MenuEntryHelpers.hpp"

namespace CTRPluginFramework
{
    void    RemoveAllItems(MenuEntry *entry)
    {
        if (entry->Hotkeys[0].IsDown())
        {
            u32     *item = Game::TownItem;

            for (int i = 0; i < 0x1400; i++)
            {
                *item++ =  0x00007FFE;
            }
            OSD::Notify(Color::Green << "Removed All Items!");
        }
    }

    void    RemoveAllWeeds(MenuEntry *entry)
    {
        static u16 weeds[] = { 0x007C, 0x007D, 0x007E, 0x007F, 0x00CB, 0x00CC, 0x00CD, 0x00F8 };

        if (entry == nullptr)
            goto weed;
        if (entry->Hotkeys[0].IsDown())
            goto weed;
        return;

        weed:
        FindReplacer<u16>  findReplacer(reinterpret_cast<u32>(Game::TownItem), 0x5000);

        for (int i = 0; i < 7; i++)
        {
            findReplacer.AddPair(weeds[i], 0x7FFE);
        }

        findReplacer();
        OSD::Notify(Color::Green << "Removed All Weeds!");
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
                OSD::Notify(Utils::Format("0x%04X replaced with 0x%04X", search, replace));
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

        OSD::Notify(Color::Green << "Grass Filled!" << Color::White << "(reload the area)");
    }

    void    DestroyGrass(MenuEntry *entry)
    {
        static u32 offset = reinterpret_cast<u32> (Game::Grass);

        if (!Controller::IsKeysDown(R + A) && entry != nullptr)
            return;

        for (offset; offset < reinterpret_cast<u32>(Game::GrassEnd); offset += 4)
            Process::Write32(offset, 0x00000000);

        OSD::Notify(Color::Green << "Grass Removed!" << Color::White << "(reload the area)");
    }

    void    WaterAllFlowers(MenuEntry *entry)
    {
        if (entry == nullptr)
            goto water;
        //since hotkeys aren't available when the arg is nullptr, check if the arg is nullptr first
        if (entry->Hotkeys[0].IsDown())
            goto water;
        return;

        water:

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
        OSD::Notify(Color::Green << "Flowers Watered!" << Color::White << "(reload the area)");
    }

    void    WorldEdit(MenuEntry *entry)
    {
        static u32 itemID;
        static bool valid = false; //boolean to declare whether you're using a valid value or not

        if (entry->Hotkeys[0].IsDown()) //Open keyboard
        {
            Keyboard    keyboard("What item would you like to use?");
            u32 item;
            if (keyboard.Open(itemID) != -1) //return if the user aborts (if != -1)
                valid = true;
            else
                valid = false; // if the user aborts, you don't want to be writing abritary values
        }

        if (entry->Hotkeys[1].IsDown()) //Store item below feet
        {
            u32  *address = Game::GetItem(); //get the address of where your character is standing
            itemID = *address; //get the value of address
            valid = true;
        }

        if (entry->Hotkeys[2].IsDown()) //Write item
        {
            u32  *address = Game::GetItem(); //get the address of where your character is standing
            if (valid && address != nullptr)
            {
                *address = itemID;
                OSD::Notify(Utils::Format("0x%04X set on ground", itemID));
            }
        }
    }

    static bool FishIdRefresh = false;
    void    FishIdEditorSetter(MenuEntry *entry)
    {
        u32         *value = GetArg<u32>(entry);
        Keyboard    keyboard("Fish Id Editor\n\nEnter the desired fish to find. New spawned fish only.");

        keyboard.IsHexadecimal(true);
        keyboard.SetCompareCallback([](const void *in, std::string &error)
        {
            u32 input = *static_cast<const u32 *>(in);

            if (input >= 0x22E2 && input <= 0x232C) {
                FishIdRefresh = true;
                return (true);
            }

            error = "The value must be between 0x22E2 - 0x232C";
            return (false);
        });
        if (keyboard.Open(*value) != -1)
        {
            std::string &name = entry->Name();
            int pos = name.find("(");

            if (pos != std::string::npos)
            {
                name.erase(pos);
                name += Utils::Format("(%d)", *value);
            }
        }
    }

	void    FishIdEditor(MenuEntry *entry)
	{
        static bool active = false;
        u32     offset = Game::FishSetId;
        u32     original = 0xE1A0A000;
        u32     patch = 0xE3A0A000;

        if ((entry->WasJustActivated() && !active) || FishIdRefresh)
        {
            u32 fishId = *GetArg<u32>(entry);
            if (fishId < 0x22E2) {
                fishId = 0x22E2; // Failsafe as to not break the fish functions
            }
            else if (fishId > 0x232C) {
                fishId = 0x232C; // Failsafe as to not break the fish functions
            }


            patch += fishId - 0x22E2 + 1; //We can just add our value straight to the patch bytes as long as its <= 75. We need to subtract the min from it to get the index instead
            Process::Patch(offset, patch);
            OSD::Notify(Utils::Format("All Fish Set To: 0x%04X", fishId & 0xFFFF));


            active = true;
            FishIdRefresh = false;
        }
        else if (!entry->IsActivated() && active)
        {
            Process::Patch(offset, original);
            OSD::Notify("Fish Restored To Normal Id's: " << Color::Red << "Disabled!");
            active = false;
        }
	}

	void    FishCantBeScared(MenuEntry *entry)
	{
		static bool active = false;
		u32     offset = Game::FishCantScare;
		u32     original = 0xE3500000;
		u32     patch = 0xE3500001;

		if (entry->WasJustActivated() && !active)
		{
			Process::Patch(offset, patch);
			OSD::Notify("Fish Cannot be scared: " << Color::Green << "Enabled!");
			active = true;
		}
		else if (!entry->IsActivated() && active)
		{
			Process::Patch(offset, original);
			OSD::Notify("Fish Cannot be scared: " << Color::Red << "Disabled!");
			active = false;
		}

	}

	void    FishAlwaysBiteRightAway(MenuEntry *entry)
	{
		static bool active = false;
		u32     offset = Game::FishBiteRightAway;
		u32     original = 0xE0800100;
		u32     patch = 0xE3A0005A;

		if (entry->WasJustActivated() && !active)
		{
			Process::Patch(offset, patch);
			OSD::Notify("Fish Bite Right Away: " << Color::Green << "Enabled!");
			active = true;
		}
		else if (!entry->IsActivated() && active)
		{
			Process::Patch(offset, original);
			OSD::Notify("Fish Bite Right Away: " << Color::Red << "Disabled!");
			active = false;
		}
	}
}
