#include "cheats.hpp"

namespace CTRPluginFramework
{
    void    CheatsKeyboard(void)
    {
        if (Controller::IsKeysDown(R + X))
        {
            Keyboard  keyboard("Select which command you'd like to execute.");

            // Creating my entry list
            std::vector<std::string> list = 
            {
                "Cheat 1",
                "Cheat 2",
                "Cheat 3",
                "Cheat 4",
                "Cheat 5",
                "Cheat 6",
                "Cheat 7",
                "Cheat 8"
            };

            // Populate the keyboard with the entries
            keyboard.Populate(list);

            // OPen the keyboard and wait for a user input
            // be sure to use an int in case the function return -1
            int  userChoice = keyboard.Open();

            // If userChoice == -1, the user aborted the keybord or an error occurred
            if (userChoice != -1)
            {
                OSD::Notify("You've selected: [" + list[userChoice] + "]");
            }
        }
    }
}