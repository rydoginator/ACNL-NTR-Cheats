#include "MiniGame.hpp"
#include "Strings.hpp"
#include "CTRPluginFramework/Graphics/OSD.hpp"
#include "CTRPluginFramework/Menu/MessageBox.hpp"
#include "CTRPluginFramework/Utils/Utils.hpp"
#include "Player.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework
{
    Korok::Korok(void) :
        posX(Utils::Random(16, 95)), ///< Random posX
        posY(Utils::Random(16, 79)), ///< Random posY
        isFound(false),             ///< Not found
        hitbox(posX - 5, posY - 5, 10, 10)
    {
    }

    Korok::~Korok(void)
    {
    }

    bool    Korok::CheckPosition(Position *position)
    {
        if (!position || isFound)
            return (false);

        if (hitbox.Contains(position->x, position->y))
            isFound = true;

        return isFound;
    }

    bool            KorokMiniGame::InGame = false;
    KorokMiniGame   *KorokMiniGame::_instance = nullptr;
#if DEBUG_MINIGAME
    bool            KorokMiniGame::_OSDAlreadyAdded = false;
    std::string     g_DebugLine;

    static bool     OSDMiniGameCallback(const Screen &screen);
#endif
 
    KorokMiniGame::KorokMiniGame(void)
    {
        // Generate 10 Koroks at random location
        for (int i = 0; i < 10; i++)
            _koroks.push_back(Korok());

        LeftToFound = 10;

        // Game started
        InGame = true;
        _instance = this;

#if DEBUG_MINIGAME
        // Check that the osd is already added
        if (!_OSDAlreadyAdded)
        {
            OSD::Run(OSDMiniGameCallback);
            _OSDAlreadyAdded = true;
        }
#endif
    }

    KorokMiniGame::~KorokMiniGame(void)
    {
        InGame = false; ///< Reset game status
#if DEBUG_MINIGAME
        OSD::Stop(OSDMiniGameCallback);
#endif
        _instance = nullptr;
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
#if DEBUG_MINIGAME
                UIntVector  touchPos = Touch::GetPosition();
                bool        osd = false;
#endif

                // Check our position with the position of the Koroks
                for (Korok &korok : _koroks)
                {
#if DEBUG_MINIGAME
                    if (!osd && !korok.isFound)
                    {
                        osd = true;
                        g_DebugLine = Format("Player[%d, %d] Korok[%d, %d] Touch[%d, %d]", position->x, position->y, korok.posX, korok.posY, touchPos.x, touchPos.y);
                    }
#endif
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

    KorokMiniGame *KorokMiniGame::GetInstance(void)
    {
        return (_instance);
    }

    KorokVector  &KorokMiniGame::GetKoroks(void)
    {
        return (_koroks);
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

#if DEBUG_MINIGAME
    
    static void    DrawRect(const Screen &screen, u32 posX, u32 posY)
    {        
        u16     color = 0xF800; ///< Red

        for (int i = 0; i < 2; i++)
        {
            u16     *framebuf = reinterpret_cast<u16 *>(screen.GetFramebuffer(posX + i, posY));

            for (int j = 0; j < 2; j++)
            {
                *framebuf++ = color;
            }
        }
    }

    static bool     OSDMiniGameCallback(const Screen &screen)
    {
        KorokMiniGame *kMiniGame = KorokMiniGame::GetInstance();

        if (kMiniGame == nullptr || screen.IsTop)
            return (false);

        KorokVector &koroks = kMiniGame->GetKoroks();

        for (Korok &korok : koroks)
        {
            if (!korok.isFound)
            {
                DrawRect(screen, korok.posX * 2 + 48, korok.posY * 2.14f + 16);
            }
        }
        screen.Draw(g_DebugLine, 0, 0, Color::Blank, Color::Black);
        return (true);
    }
#endif
}
