#include "MiniGame.hpp"
#include "Strings.hpp"
#include "CTRPluginFramework/Menu/MessageBox.hpp"
#include "Player.hpp"
#include "Helpers.hpp"
#include "NTR.hpp"

namespace CTRPluginFramework
{
    int     RandomNum(int start, int end);

    Korok::Korok(void) :
        posX(RandomNum(16, 95)), ///< Random posX
        posY(RandomNum(16, 79)), ///< Random posY
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

    bool    KorokMiniGame::InGame = false;
    bool    KorokMiniGame::_OSDAlreadyCreated = false;
    KorokMiniGame   *KorokMiniGame::_instance = nullptr;
    std::string g_DebugLine;
    bool        g_osdLock = false; ///< Hacky way

    int     OSDMiniGameCallback(u32 isBottom, u32 addr, u32 addrB, u32 stride, u32 format);
    
    KorokMiniGame::KorokMiniGame(void)
    {
        // Generate 10 Koroks at random location
        for (int i = 0; i < 10; i++)
            _koroks.push_back(Korok());

        LeftToFound = 10;

        // Game started
        InGame = true;
        _instance = this;

        // Check that the osd is already added
        if (!_OSDAlreadyCreated)
        {
            NTR::NewCallback((NTR::OverlayCallback)OSDMiniGameCallback);
            _OSDAlreadyCreated = true;
        }
    }

    KorokMiniGame::~KorokMiniGame(void)
    {
        InGame = false; ///< Reset game status
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
                UIntVector  touchPos = Touch::GetPosition();
                bool        osd = false;

                // Check our position with the position of the Koroks
                for (Korok &korok : _koroks)
                {
                    if (!osd && !korok.isFound)
                    {
                        osd = true;
                        g_osdLock = true;
                        g_DebugLine = Format("Player[%d, %d] Korok[%d, %d] Touch[%d, %d]", position->x, position->y, korok.posX, korok.posY, touchPos.x, touchPos.y);
                        g_osdLock = false;
                    }
                    if (korok.CheckPosition(position))
                    {
                        LeftToFound--;
                        g_osdLock = true;
                        MessageBox(Format("Yahaha! You found me!\nThere are %d korok seed(s) left!", LeftToFound))();
                        g_osdLock = false;
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
            g_osdLock = true;
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

            g_osdLock = false;
        }

        if (game != nullptr)
        {
            bool isGameFinished = game->Update();

            if (isGameFinished)
            {
                // Clean game resources
                delete game;
                game = nullptr;
                g_osdLock = true;
                MessageBox("Congratulation for finding all Koroks !!\nWe hope you enjoyed the easter egg !\n Don't tell anyone, and enjoy 4.0 :)")();
                g_osdLock = false;
            }
        }
    }

    static void    DrawRect(u32 posX, u32 posY)
    {        
        u16     color = 0xF800; ///< Red

        for (int i = 0; i < 2; i++)
        {
            u16     *framebuf = (u16 *)NTR::GetLeftFramebuffer(posX + i, posY);

            for (int j = 0; j < 2; j++)
            {
                *framebuf++ = color;
            }
        }
    }

    int     OSDMiniGameCallback(u32 isBottom, u32 addr, u32 addrB, u32 stride, u32 format)
    {
        static u32 lastAddress = 0;

        if (addr == lastAddress || !isBottom || g_osdLock || !KorokMiniGame::InGame)
            return (1);

        lastAddress = addr;

        KorokMiniGame *kMiniGame = KorokMiniGame::GetInstance();

        if (kMiniGame != nullptr)
        {
            KorokVector &koroks = kMiniGame->GetKoroks();

            for (Korok &korok : koroks)
            {
                if (!korok.isFound)
                {
                    DrawRect(korok.posX * 2 + 48, korok.posY * 2.14f + 16);
                }
            }
            Draw::String(0, 0, Color::Blank, Color::Black, (u8 *)g_DebugLine.c_str());
            return (0);
        }

        return (1);
    }
}
