#include "cheats.hpp"
#include "Player.hpp"

namespace CTRPluginFramework
{
    void    CheatsKeyboard(void) 
    {
        bool g_command;
        if (Controller::IsKeysDown(R + X))
        {
            g_command = true;
            Keyboard  keyboard("Select which command \nyou'd like to execute.");

            // Creating my entry list
            std::vector<std::string> list = 
            {
                "Water Flowers",
                "Pull All Weeds",
                "Duplicate All Items",
                "Set Time to...",
                "Appearance Modifier..."
            };

            // Populate the keyboard with the entries
            keyboard.Populate(list);

            // OPen the keyboard and wait for a user input
            // be sure to use an int in case the function return -1
            int  userChoice = keyboard.Open();

            // If userChoice == -1, the user aborted the keybord or an error occurred
            switch(userChoice)
            {
                case 0:
                    quench(nullptr);
                    g_command = false;
                    break;
                case 1:
                    weeder(nullptr);
                    g_command = false;
                    break;
                case 2:
                    duplicationAll();
                    break;
                case 3:
                    timePicker();
                    break;
                case 4:
                    appearanceMod();
                    break;
                default:
                    break;
            }
        }
    }

   void    PlayerUpdateCallback(void)
    {
        // Wait 10seconds that the user launch it's save
        static Clock    timer;
        static bool     isLaunched = false;

        // Check only twice per minutes
        if (isLaunched && timer.HasTimePassed(Seconds(0.5f)))
        {
            Player  *Player = Player::GetInstance();

            if (Player != nullptr)
                Player->Update();

            timer.Restart();
        }
        else if (timer.HasTimePassed(Seconds(10.f)))
        {
            isLaunched = true;
            timer.Restart();
        }        
    }

    void    SleepThread(void)
    {
        // Put the thread as sleep for 0.001 seconds. Prevents overloading the thread
        svcSleepThread(1000000);
    }
    
    void    timePicker(void)
    {
        Keyboard  keyboard("Select which time you'd like to travel\nto");
        std::vector<std::string> list = 
        {
            "12 AM",
            "1 AM",
            "2 AM",
            "3 AM",
            "4 AM",
            "12 PM",
        };
        keyboard.Populate(list);

        int  userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            switch(userChoice)
            {
                case 0:
                    setTimeTo(0);
                    break;
                case 1:
                    setTimeTo(1);
                    break;
                case 2:
                    setTimeTo(2);
                    break;
                case 3:
                    setTimeTo(3);
                    break;
                case 5:
                    setTimeTo(12);
                    break;
                default:
                    break;
            }
        }
    }
}