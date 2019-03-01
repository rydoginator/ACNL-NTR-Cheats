#include "cheats.hpp"
#include "Helpers.hpp"
#include <cstring>

namespace CTRPluginFramework
{
    void    MainStreetKeyboard(MenuEntry *entry)
    {
        Keyboard  keyboard("Which building would you like to unlock / lock?");
        u32 nook = reinterpret_cast<u32>(Game::Nook);
        int offsets[] = {0x45C8, 0x8A58, 0x8B1E, 0x8B3E, 0x8B40, 0x8B50}; 
        std::vector<std::string> list =
        {
            "Kicks",
            "Museum Shop",
            "Club LOL",
            "Dream Suite",
            "Fortune Teller",
            "Shampoodle"
        };

        std::vector<std::string> state =
        {
            "Lock",
            "Unlock"
        };


        keyboard.Populate(list);
        int  shop = keyboard.Open();

        if (shop != -1)
        {
            keyboard.GetMessage() = "Unlock or Lock?";
            keyboard.Populate(state);

            int byte = keyboard.Open();
            if (byte != -1)
            {
                //If Kicks, Club LOL or Shampoodle & want to unlock
                if ((shop == 0 || shop == 2 || shop == 5) && byte == 1)
                {
                    byte = 2;
                }
                Process::Write8(nook + offsets[shop], byte);
            }
        }
    }

    int NooklingStoreSelector(void) {
        Keyboard keyboard("What Nooklings store would you like?");
        static const StringVector list =
        {
            "Nookling Cranny",
            "T&T Mart",
            "Super T&T",
            "T.I.Y",
            "T&T Emporium"
        };
        keyboard.Populate(list);

        return keyboard.Open();
    }

    void    NooklingKeyboard(MenuEntry *entry)
    {
        int userChoice = NooklingStoreSelector();

        if (userChoice != -1) //Not Abort
        {
            u32 nook = reinterpret_cast<u32>(Game::Nook);
            Process::Write16(nook, 0x0101 * userChoice);
            Process::Write8(nook + 0x4490, userChoice == 1 ? 2 : userChoice);
        }
    }

	void    CatalogToPockets(MenuEntry *entry)
	{
		int length = 0;
        u32 item = 0;
        static bool btn = false;

        if (entry->Hotkeys[0].IsDown() && !btn)
        {
            btn = true;
            if (*Game::Room < 0x38 || *Game::Room > 0x3D) {
                OSD::Notify("You aren't in a Nooklings Store!");
                return;
            }

            else if (*Game::Room == 0x38 || *Game::Room == 0x3D || *Game::Room == 0x3E) {//Nooks Cranny, Emporium F1+F2
                OSD::Notify("There is No Catalog In This Room!");
                return;
            }

            else if (*Game::BottomScreen != 0x7C && *Game::BottomScreen != 0x8A) { //Catalog UI, Catalog Confirm UI
                OSD::Notify("Open The Catalog Before Using This Cheat!");
                return;
            }

            int* slots = Player::GetInstance()->GetAvaibleSlots(length);
            
            if (length == 0) {
                OSD::Notify("No Free Inventory Slots Available!");
                return;
            }

			else if (length > 0)
			{
                Process::Read32(Game::CatalogItem, item);
                if (item != 0) { // Value is 0 before cursor is on an item
                Player::GetInstance()->WriteInventorySlot(slots[0], item);
                OSD::Notify(Utils::Format("Recieved Item 0x%04X", item&0xFFFF));
                }
            }
        }

        else if (!entry->Hotkeys[0].IsDown()) {
            btn = false;
        }
    }

    void ShopsAlwaysOpenKeyboard(MenuEntry *entry)
    {
        static const u32 patch = 0xE3A00000;
        static u32 address[9] = {Game::AlwaysOpen_Retail, Game::AlwaysOpen_Nookling, Game::AlwaysOpen_Garden, 
                                Game::AlwaysOpen_Ables, Game::AlwaysOpen_Sham, Game::AlwaysOpen_Kicks,
                                Game::AlwaysOpen_Nook, Game::AlwaysOpen_Katrina, Game::AlwaysOpen_Redd};
        bool alwaysopen = false;
        Keyboard keyboard("Which shop would you like to change to apply/remove Always Open to?");
        static const StringVector list = {
            "Retail",
            "Nooklings",
            "Garden Center",
            "Able Sisters",
            "Shampoodle",
            "Kicks",
            "Nooks",
            "Katrina",
            "Redd"
        };

        static const StringVector state = {
            "Remove Always Open",
            "Apply Always Open"
        };

        keyboard.Populate(list);
        int shop = keyboard.Open();

        if (shop != -1)
        {
            u32 offset = address[shop];

            keyboard.GetMessage() = "Apply or Remove?";
            keyboard.Populate(state);

            int byte = keyboard.Open();
            if (byte != -1) { //abort
                Process::Patch(offset, patch|(byte&1));
            }
        }
    }
}