#include "cheats.hpp"
#include "Player.hpp"
#include "Helpers\KeySequence.hpp"

namespace CTRPluginFramework
{
    void    CheatsKeyboard(void) 
    {
        bool g_command;
        static HoldKey  buttons(R + X, Seconds(0.5f));

        if (!buttons())
        	return;

        g_command = true;
        Keyboard  keyboard("Select which command \nyou'd like to execute.");

        // Creating my entry list
        std::vector<std::string> list = 
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

        // Populate the keyboard with the entries
        keyboard.Populate(list);

        // OPen the keyboard and wait for a user input
        // be sure to use an int in case the function return -1
        int  userChoice = keyboard.Open();

            // If userChoice == -1, the user aborted the keybord or an error occurred
        switch(userChoice)
        {
            case 0:
                WaterAllFlowers(nullptr);
                g_command = false;
                break;
            case 1:
                RemoveAllWeeds(nullptr);
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
            case 5:
                TeleportKeyboard();
            case 6:
             	FurnitureKeyboard();
               	break;
			case 7:
				GrassKeyboard();
				break;
            default:
                break;
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

    void    TeleportKeyboard(void)
    {
        Keyboard keyboard("Which player would you like to teleport to?");
        std::vector<std::string> list =
        {
            "Player 1",
            "Player 2",
            "Player 3"
        };
        keyboard.Populate(list);

        int userChoice = keyboard.Open();
        if (userChoice != -1)
        {
            TeleportTo(userChoice);
        }
    }

    void    SleepThread(void)
    {
        // Put the thread as sleep for 0.1 seconds. Prevents overloading the thread
        svcSleepThread(10000);
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
        keyboard.Populate(list);

        int  userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            SetTimeTo(userChoice);
        }
    }

	void	GrassKeyboard(void)
	{
		Keyboard keyboard("Would you like to destroy or make grass?");
		std::vector<std::string> list =
		{
			"Destroy!",
			"Replenish"
		};
		int userChoice = keyboard.Open();

		if (userChoice == 0)
			DestroyGrass(nullptr);
		else if (userChoice == 1)
			ChangeGrass(nullptr);
	}

	void	Secret(void)
	{
		static KeySequence keySequence({ Key::DPadUp, Key::DPadUp, Key::DPadDown, Key::DPadDown, Key::DPadLeft, Key::DPadRight, Key::DPadLeft, Key::DPadRight, Key::B, Key::A });

		if (keySequence())
		{
			YaHa();
		}
	}

	void	YaHa(void)
	{
		static u8 x[10];
		static u8 y[10];
		static u8 completed[10];
		static int koroks = 10;

		//Change the player appearence to botw link
		Player::GetInstance()->Write16(0xA, 0x28EB);
		Player::GetInstance()->Write16(0x16, 0x266D);
		Player::GetInstance()->Write16(0x1A, 0x26FF);
		Player::GetInstance()->Write16(0x22, 0x27A5);

		MessageBox("Yahaha! Help find me find the rest of the Korok's!")();

		//generate randum numbers for the korok seeds
		for (int i = 0; i < 10; i++)
		{
			x[i] = RandomNum(16, 95);
			y[i] = RandomNum(16, 79);
		}
		char buffer[0x100];
		for (int i = 0; i < 10; i++)
		{
			sprintf(buffer, "pos[%i] (%i , %i)", i, x[i], y[i]);
			OSD::Notify(buffer);
		}
		goto KorokLoop;
		KorokLoop:
			u8      xPos = static_cast<u8>(Game::WorldPos->x);
			u8      yPos = static_cast<u8>(Game::WorldPos->y);
			static u32 offset = reinterpret_cast<u32>(Game::Room);
			static u8		room;
			Process::Read8(offset, room);
			if (room == 00 ) //check to see if you're outdoors, and on the main land
			{
				for (int i = 0; i < 10; i++)
				{
					if (xPos == x[i] && yPos == y[i] && i != completed[i])
					{
						koroks--;
						sprintf(buffer, "Yahaha! You found me!\nThere are %i korok seed(s) left!", koroks);
						MessageBox(buffer)();
						completed[i] = i; //add the current index to list so that it doesn't index it again

						goto KorokLoop;
					}
				}
				goto KorokLoop;
			}
			else
			{
				goto exit;
			}
		exit:
			MessageBox msgBox("Please go outside to search for Koroks. Would you prefer to quit instead?", DialogType::DialogYesNo);
			if (msgBox())
			{
				static Clock timer;
				if (timer.HasTimePassed(Seconds(2.5f)))
					goto KorokLoop;
				else
					return;
			}

		MessageBox("You found the easter egg! Don't tell anyone, and enjoy 4.0 :)")();
	}
}