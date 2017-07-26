#include "cheats.hpp"

namespace CTRPluginFramework
{
    void    FillMainStreet(MenuEntry *entry)
    {
        u32 nook = reinterpret_cast<u32>(Game::Nook);  
        Process::Write8(nook + 0x45C8, 0x2); //Kicks
        Process::Write8(nook + 0x8A58, 0x1); //Museum Shop
        Process::Write8(nook + 0x8B1E, 0x2); //Club LOL
        Process::Write8(nook + 0x8B3E, 0x1); //Dream Suite
        Process::Write8(nook + 0x8B40, 0x1); //Fortune Teller
        Process::Write8(nook + 0x8B50, 0x2); //Shampoodle
    }

    void    FillCatalog(MenuEntry *entry)
    {
        for (int i = 0; i < 0x90; i++)
        {
            Player::GetInstance()->Write32(0x6C90 + (i * 4), 0xFFFFFFFF);
        }
    }

    void    NooklingKeyboard(MenuEntry *entry)
    {
        Keyboard  keyboard("Would you like to travel\nbackwards or forwards?");
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
}