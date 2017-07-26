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

    class Korok
    {
    public:
        Korok() :
            posX(RandomNum(16, 95)), ///< Random posX
            posY(RandomNum(16, 79)), ///< Random posY
            isFound(false)             ///< Not found
        {
        }

        ~Korok(){}
        
        bool    CheckPosition(Position *position)
        {
            if (!position || isFound)
                return (false);

            if (position->x == posX && position->y == posY)
                isFound = true;

            return isFound;
        }

        u8      posX;
        u8      posY;
        bool    isFound;
    };

    class KorokMiniGame
    {
    public:

        KorokMiniGame()
        {
            // Generate 10 Koroks at random location
            for (int i = 0; i < 10; i++)
                _koroks.push_back(Korok());

            LeftToFound = 10;

            // Game started
            InGame = true;
        };

        ~KorokMiniGame()
        {
            InGame = false; ///< Reset game status
        }

        // Return true if the game is finished
        bool    Update(void)
        {
            if (LeftToFound)
            {
                // Check that we're outdoor
                if (*Game::Room == 0)
                {
                    // Fetch position
                    Position    *position = Game::WorldPos;

                    // Check our position with the position of the Koroks
                    for (Korok &korok : _koroks)
                    {
                        if (korok.CheckPosition(position))
                        {
                            LeftToFound--;
                            MessageBox(Format("Yahaha! You found me!\nThere are %d korok seed(s) left!", LeftToFound))();
                        }
                    }
                }
                return (false);
            }

            InGame = false;
            return (true);
        }

        static bool     InGame;
        int             LeftToFound;

    private:

        std::vector<Korok> _koroks;        
    };

    bool    KorokMiniGame::InGame = false;

	void	MiniGame(void)
	{
        static KorokMiniGame *game = nullptr;
        static KeySequence keySequence({ Key::DPadUp, Key::DPadUp, Key::DPadDown, Key::DPadDown, Key::DPadLeft, Key::DPadRight, Key::DPadLeft, Key::DPadRight, Key::B, Key::A });

        if (keySequence())
        {
            // If a game is already running
            if (KorokMiniGame::InGame)
            {
                static const char *warning = "A game is already running.\nKorok(s) left: %d\n\nDo you want to exit the game ?";

                if ((MessageBox(Format(warning, game->LeftToFound), DialogType::DialogYesNo))())
                {
                    // User want to exit
                    delete game;
                    game = nullptr;
                }
            }   
            // Else we create a new game
            else
            {
                game = new KorokMiniGame();
                MessageBox("Yahaha! Help find me find the rest of the Korok's!")();

                //Change the player appearence to botw link
                Player::GetInstance()->Write16(0xA, 0x28EB);
                Player::GetInstance()->Write16(0x16, 0x266D);
                Player::GetInstance()->Write16(0x1A, 0x26FF);
                Player::GetInstance()->Write16(0x22, 0x27A5);
            }
        }

        if (game != nullptr)
        {
            bool isGameFinished = game->Update();

            if (isGameFinished)
            {
                // Clean game resources
                delete game;
                game = nullptr;
                MessageBox("Congratulation for finding all Koroks !!\nWe hope you enjoyed the easter egg !\n Don't tell anyone, and enjoy 4.0 :)")();
            }
        }
		
	}
}