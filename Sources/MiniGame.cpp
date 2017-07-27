#include "MiniGame.hpp"
#include "Strings.hpp"
#include "CTRPluginFramework/Menu/MessageBox.hpp"
#include "Player.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework
{
    int     RandomNum(int start, int end);

    Korok::Korok(void) :
        posX(RandomNum(16, 95)), ///< Random posX
        posY(RandomNum(16, 79)), ///< Random posY
        isFound(false)             ///< Not found
    {
    }

    Korok::~Korok(void)
    {
    }

    bool    Korok::CheckPosition(Position *position)
    {
        if (!position || isFound)
            return (false);

        if (position->x == posX && position->y == posY)
            isFound = true;

        return isFound;
    }

    bool    KorokMiniGame::InGame = false;

    KorokMiniGame::KorokMiniGame(void)
    {
        // Generate 10 Koroks at random location
        for (int i = 0; i < 10; i++)
            _koroks.push_back(Korok());

        LeftToFound = 10;

        // Game started
        InGame = true;
    }

    KorokMiniGame::~KorokMiniGame(void)
    {
        InGame = false; ///< Reset game status
    }

    bool    KorokMiniGame::Update(void)
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

    void    MiniGame(void)
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
