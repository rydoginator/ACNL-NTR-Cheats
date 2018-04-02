#include "cheats.hpp"
#include <cstring>

namespace CTRPluginFramework
{
    void    FillCatalog(MenuEntry *entry)
    {
        u32     address = Player::GetInstance()->GetOffset() + 0x6C90;

        std::memset((void *)address, 0xFF, 106 * 4);
    }

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

    void    NooklingKeyboard(MenuEntry *entry)
    {
        Keyboard  keyboard("What Nooklings store would you like?");
        std::vector<std::string> list =
        {
            "Nookling Cranny",
            "T&T Mart",
            "Super T&T",
            "T.I.Y",
            "T&T Emporium"
        };
        keyboard.Populate(list);

        int  userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            SetNook(userChoice);
        }
    }

    void    SetNook(int value)
    {
        u32 nook = reinterpret_cast<u32>(Game::Nook);  
        Process::Write16(nook, 0x0101 * value);
        Process::Write8(nook+ 0x4490, value == 1 ? 2 : value);
    }

    void    CatalogToPockets(MenuEntry *entry)
    {
        int length;
        if (!Controller::IsKeyDown(L))
            return;
        if (Controller::IsKeyPressed(A))
        {
            if (*Game::CatalogItem != 0 && *Game::BottomScreen == 0x7C)
            {
                u16 item = *Game::CatalogItem;
                int *slots = Player::GetInstance()->GetAvaibleSlots(length);
                if (length != 0)
                    Player::GetInstance()->WriteInventorySlot(slots[0], item);
            }
        }
    }
}