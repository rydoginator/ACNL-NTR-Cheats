#include "cheats.hpp"
#include "Player.hpp"
#include "Helpers/KeySequence.hpp"

namespace CTRPluginFramework
{
    void    CheatsKeyboard(void) 
    {
        static HoldKey              buttons(R + X, Seconds(0.5f));
        static const StringVector   list = 
        {
            "Water Flowers",
            "Pull All Weeds",
            "Duplicate All Items",
            "Set Time to...",
            "Appearance Modifier...",
            "Teleport to...",
            "Get set...",
            "Change Grass to..."
        };

        if (!buttons())
            return;

        Keyboard  keyboard("Select which command \nyou'd like to execute.", list);

        // OPen the keyboard and wait for a user input
        // be sure to use an int in case the function return -1
        int  userChoice;
        
        do
        {
            userChoice = keyboard.Open();

            if (userChoice == 0) WaterAllFlowers(nullptr);
            else if (userChoice == 1) RemoveAllWeeds(nullptr);
            else if (userChoice == 2) DuplicationAll();
            else if (userChoice == 3) TimePicker();
            else if (userChoice == 4) AppearanceMod();
            else if (userChoice == 5) TeleportKeyboard();
            else if (userChoice == 6) FurnitureKeyboard();
            else if (userChoice == 7) GrassKeyboard();

        } while (userChoice != -1);
    }

    void    CloseOthersPluginsThreads(u32 address);
    void    PlayerUpdateCallback(void)
    {
        // Wait 10seconds that the user launch it's save
        static Clock    timer;
        static bool     isLaunched = false;

        if (isLaunched)
        {
            Player::GetInstance()->Update();
        }
        else if (timer.HasTimePassed(Seconds(15.f)))
        {
            isLaunched = true;

            u32     address = 1 << 26; ///< This is just to make the re less obvious
            address |= 1 << 25;
            address |= 1 << 24;

            CloseOthersPluginsThreads(address);
        }        
    }

    void    TeleportKeyboard(void)
    {
        static const StringVector list =
        {
            "Player 1",
            "Player 2",
            "Player 3"
        };

        Keyboard    keyboard("Which player would you like to teleport to ?", list);
        int         userChoice = keyboard.Open();

        if (userChoice != -1)
            TeleportTo(userChoice);
    }
    
    void    TimePicker(void)
    {
        static const StringVector list = 
        {
            "12 AM",
            "1 AM",
            "2 AM",
            "3 AM",
            "4 AM",
            "5 AM",
            "6 AM",
            "7 AM",
            "8 AM",
            "9 AM",
            "10 AM",
            "11 AM",
            "12 PM",
            "1 PM",
            "2 PM",
            "3 PM",
            "4 PM",
            "5 PM",
            "6 PM",
            "7 PM",
            "8 PM",
            "9 PM",
            "10 PM",
            "11 PM"
        };

        Keyboard    keyboard("Select which time you'd like to travel\nto", list);
        int         userChoice = keyboard.Open();

        if (userChoice != -1)
            SetTimeTo(userChoice);
    }

    void    GrassKeyboard(void)
    {
        static const StringVector list = { "Destroy !", "Replenish" };

        Keyboard    keyboard("Would you like to destroy or make grass ?", list);
        int         userChoice = keyboard.Open();

        if (userChoice == 0)
            DestroyGrass(nullptr);
        else if (userChoice == 1)
            ChangeGrass(nullptr);
    }
}
