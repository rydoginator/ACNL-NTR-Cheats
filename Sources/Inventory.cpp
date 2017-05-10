#include "cheats.hpp"

namespace CTRPluginFramework
{
    bool    CheckItemInput(const void *input, std::string &error)
    {
        // Cast the input into the appropriate type (must match the type provided to Open)
        u32  in = *static_cast<const u32 *>(input);

        // Check the value
        if (in < 0x1000 || in > 0xFFFF)
        {
            error = "The value must be between 1000 - FFFF";
            // Return that the value isn't valid
            return (false);
        }

        // The value is valid
        return (true);
    }

    void    Text2Item(MenuEntry *entry)
    {
        if (Controller::IsKeysDown(X + DPadRight))
        {
            u32 output;
            // New keyboard, hint being:
            Keyboard keyboard("What item would you like ?");

            // Add the function to check the input entered by the user
            keyboard.SetCompareCallback(CheckItemInput);

            // If the function return -1, then the user canceled the keyboard, so do nothing 
            if (keyboard.Open(output) != -1)
            {
                Player::GetInstance()->WriteInventorySlot(0, output);
            }
        }
    }

    void    Duplication(MenuEntry *entry)
    {        
        if (Controller::IsKeyDown(R))
        {
            u32 item;

            if (Player::GetInstance()->ReadInventorySlot(0, item))
                Player::GetInstance()->WriteInventorySlot(1, item);
        }
    }

    void    ShowBuriedItems(MenuEntry *entry)
    {
        u32     *item = Game::GetItem();

        if (item != nullptr)
        {
            // Check to see if you're on a buried spot
            if (*item >> 16 == 0x8000) 
                Player::GetInstance()->ThinkTo(*item & 0xFFFF);
            else
                Player::GetInstance()->UnThink();
        }
    }

    void    PickBuriedItems(MenuEntry *entry)
    {
        if (!Controller::IsKeysDown(Y))
            return;

        u32     *item = Game::GetItem();

        if (item != nullptr)
        {
            // Check to see if you're on a buried spot
            if (*item >> 16 == 0x8000)
                *item &= 0xFFFF;
        }
    }

    void    ShowBells(MenuEntry *entry)
    {
        u64 money;
        u32 result;
        char buffer[0x100];

        Player::GetInstance()->Read64(0x6f08, money);
        result = DecryptACNLMoney(money);

        sprintf(buffer, "Bells %i", result);
        OSD::WriteLine(1, buffer, 0, 0);
    }

    void    SetBells(MenuEntry *entry)
    {
        u64     money;
        u32     output;

        Keyboard keyboard("How much money would you like?");

        keyboard.IsHexadecimal(false);

        // If the function return -1, then the user canceled the keyboard, so do nothing 
        if (keyboard.Open(output) != -1)
        {
            money = EncryptACNLMoney(output);

            Player::GetInstance()->Write64(0x6f08, money);
        }
    }
}