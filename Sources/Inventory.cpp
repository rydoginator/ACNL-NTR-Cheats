#include "cheats.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework
{
    void    Text2Item(MenuEntry *entry)
    {
        if (Controller::IsKeysDown(X + DPadRight))
        {
            u32 output;

            // New keyboard, hint being:
            Keyboard keyboard("What item would you like ?");

            // Add the function to check the input entered by the user
            keyboard.SetCompareCallback([](const void *input, std::string &error)
            {
                // Cast the input into the appropriate type (must match the type provided to Open)
                u32 in = *static_cast<const u32 *>(input);

                // Check the value
                if ((in << 8) < 0x200000 || (in << 8) > 0x600000)
                {
                    error = "Invalid Item ID!";
                    // Return that the value isn't valid
                    return (false);
                }

                // The value is valid
                return (true);
            });

            // If the function return -1, then the user canceled the keyboard, so do nothing 
            if (keyboard.Open(output) != -1)
            {
                Player::GetInstance()->WriteInventorySlot(0, output);
            }
        }
    }

    void    Duplication(MenuEntry   *entry)
    {
        if (Controller::IsKeyDown(R))
        {
            u32 item;

            if (Player::GetInstance()->ReadInventorySlot(0, item))
                Player::GetInstance()->WriteInventorySlot(1, item);
        }
    }

    void    DuplicationAll(void)
    {
        u32     *address = reinterpret_cast<u32 *>(Player::GetInstance()->GetInventoryAddress());
        u32     firstItem = *address;

        // If slot0 is empty, exit
        if (firstItem == 0x00007FFE)
            return;

        address++;

        for (int i = 0; i < 14; i++, address++)
        {
            // If current slot is empty
            if (*address == 0x00007FFE)
                *address = firstItem;
        }
    }

    void    ShowBuriedItems(MenuEntry *entry)
    {
        u32* item = Game::GetItem();

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

        u32* item = Game::GetItem();

        if (item != nullptr)
        {
            // Check to see if you're on a buried spot
            if (*item >> 16 == 0x8000)
                *item &= 0xFFFF;
        }
    }

    void    Encyclopedia(MenuEntry *entry)
    {
        u32 offset = Player::GetInstance()->GetOffset();
        static u8 buffer[] = { 0xcc,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xd0,0x9a};
        
        if (offset != 0)
        {
            Process::CopyMemory(reinterpret_cast<void *>(offset + 0x6c70), buffer, sizeof(buffer));
            entry->Disable();
        }
    }

    void    Emoticons(MenuEntry *entry)
    {
        u32 offset = Player::GetInstance()->GetOffset();
        static u8 buffer[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x20, 0x21, 0x24, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2E
        };
        if (offset != 0)
        {
            Process::CopyMemory(reinterpret_cast<void *>(offset + 0x89d0), buffer, sizeof(buffer));
            entry->Disable();
        }
    }

    void    Songs(MenuEntry *entry)
    {
        for (int i = 0; i < 3; i++)
        {
            if (Player::GetInstance()->Write32(0x8F9C + (i * 4), 0xFFFFFFFF))
                entry->Disable(); /// We disable the cheat once the cheat sucessfully writes to the player just in case they enable on title screen
        }
    }

    void    HaveMaxBells(MenuEntry *entry)
    {
        u64 money = EncryptACNLMoney(99999);
        Player::GetInstance()->Write64(0x6F08, money);
    }

    // Inventory has 16 slots
    // File struct:
    // 0 - 3: current opened box
    // 4 - end: box item's
    #define BOX_SIZE 64
    #define FILE_SIZE 4 + BOX_SIZE * 10

    struct InventoryBox
    {
        InventoryBox()
        {
            currentBox = 0;
            lastBox = 0;

            // If file don't exist, create it and init it
            if (!File::Exists("InventoryBoxs.bin"))
            {
                // Open with create flag
                if (File::Open(file, "InventoryBoxs.bin", File::RWC | File::SYNC) == 0)
                {
                    u8  buffer[FILE_SIZE] = { 0 };
                    // Fill the size with 0 bytes
                    file.Write(buffer, FILE_SIZE);
                }
            }
            // Else open it and get current box's index
            else
            {
                if (File::Open(file, "InventoryBoxs.bin") == 0)
                {
                    u32  index = 0;

                    file.Read(&index, 4);
                    currentBox = index;
                }
            }
        }
        ~InventoryBox()
        {
            file.Flush();
        }
        int     currentBox;
        int     lastBox;
        File    file;
    };

    static  InventoryBox        g_inventoryBox;
    static  QuickMenuSubMenu    *g_inventorySubMenu = nullptr;

    void    OpenBox(void *arg)
    {
        File    &file = g_inventoryBox.file;
        int     id = (int)arg - 1;
        u32     inventory = Player::GetInstance()->GetInventoryAddress();
        char    buffer[0x100] = {0};

        // Save current box
        {
            // Go to current box's offset in file
            file.Seek(4 + (g_inventoryBox.currentBox * BOX_SIZE), File::SET);

            // Now save current items
            file.Write(reinterpret_cast<void *>(inventory), BOX_SIZE);
        }

        // Open new box
        {
            // If id == 0, load last box
            if (id == -1)
                id = g_inventoryBox.lastBox;
            // Go to wanted box's offset in file
            file.Seek(4 + (id * BOX_SIZE), File::SET);

            // Read items from file and write them in ram
            file.Read(buffer, BOX_SIZE);
            Process::CopyMemory(reinterpret_cast<void *>(inventory), buffer, BOX_SIZE);
        }

        // Update lastBox
        g_inventoryBox.lastBox = g_inventoryBox.currentBox;

        // Update current box
        g_inventoryBox.currentBox = id;
        file.Seek(0, File::SET);
        file.Write(static_cast<void *>(&id), 4);

        // Update Last entry in QuickMenu
        g_inventorySubMenu->items[0]->name = Utils::Format("Last: %d", id + 1);

        // A little notification is always nice :)
        OSD::Notify(Utils::Format("Opened box: %d", id + 1), Color::LimeGreen);
    }

    void    ExtendedInventoryBox(MenuEntry *entry)
    {
        // If entry is disabled
        if (!entry->IsActivated())
        {
            g_inventoryBox.file.Close();
            // Remove Inventory Box from QuickMenu
            QuickMenu::GetInstance() -= g_inventorySubMenu;
            return;
        }

        // If just enabled the entry
        if (entry->WasJustActivated())
        {
            g_inventoryBox.file.Close();
            g_inventoryBox = InventoryBox();
            // Check that InventoryBox is correctly initialized
            if (!g_inventoryBox.file.IsOpen())
            {
                OSD::Notify("Inventory Box: An error occurred", Color::Red);
                entry->Disable();
                return;
            }

            // Create the submenu if it's not done yet
            if (g_inventorySubMenu == nullptr)
            {
                g_inventorySubMenu = new QuickMenuSubMenu("Inventory Box");
                (*g_inventorySubMenu) += new QuickMenuEntry("Last: 1", OpenBox, (void *)0);
                for (int i = 1; i < 11; i++)
                    (*g_inventorySubMenu) += new QuickMenuEntry(Utils::Format("Box %d", i), OpenBox, (void *)i);
            }

            // Add Inventory Box in QuickMenu
            QuickMenu::GetInstance() += g_inventorySubMenu;
        }
    }

    void    GenerateFossils(MenuEntry *entry)
    {
        int length;
        if (Controller::IsKeysDown(X + A))
        {
            int *slots = Player::GetInstance()->FindItems(length, 0x202A);
            for (int i = 0; i < length; i++)
            {
                u16 fossil = Utils::Random(0, 66); ///< Generate a new fossil for each iteration
                Player::GetInstance()->WriteInventorySlot(slots[i], 0x3130 + fossil);
            }
        }
    }

    void    MaxMoneyBank(MenuEntry *entry)
    {
        Player::GetInstance()->Write64(0x6B6C, EncryptACNLMoney(999999999));
    }

    void    InfiniteCoupons(MenuEntry *entry)
    {
        Player::GetInstance()->Write64(0x8D1C, EncryptACNLMoney(9999));
    }

    void    InfiniteMedals(MenuEntry *entry)
    {
        Player::GetInstance()->Write64(0x6b9c, EncryptACNLMoney(9999));
    }

    void    InfiniteWallet(MenuEntry * entry)
    {
        Player::GetInstance()->Write64(0x6F08, EncryptACNLMoney(99999));
    }

    void    WalletEditorSetter(MenuEntry *entry)
    {
        u32         *value = GetArg<u32>(entry);
        Keyboard    keyboard("Wallet Editor\n\nEnter the desired amount of bells");

        keyboard.IsHexadecimal(false);
        keyboard.SetCompareCallback([](const void *in, std::string &error)
        {
            u32 input = *static_cast<const u32 *>(in);

            if (input >= 0 && input <= 99999) return (true);

            error = "The value must be between 0 - 99999";
            return (false);
        });

        if (keyboard.Open(*value) != -1)
        {
            std::string &name = entry->Name();
            int pos = name.find("(");

            if (pos != std::string::npos)
            {
                name.erase(pos);
                name += Utils::Format("(%d)", *value);
            }
        }
    }

    void    WalletEditor(MenuEntry *entry)
    {
        if (entry->IsActivated())
        {
            u64 money = EncryptACNLMoney(*GetArg<u32>(entry));

            Player::GetInstance()->Write64(0x6F08, money);
        }

        entry->Disable();
    }

    void    BankEditorSetter(MenuEntry *entry)
    {
        u32         *value = GetArg<u32>(entry);
        Keyboard    keyboard("Bank Editor\n\nEnter the desired amount of bells");

        keyboard.IsHexadecimal(false);
        keyboard.SetCompareCallback([](const void *in, std::string &error)
        {
            u32 input = *static_cast<const u32 *>(in);

            if (input >= 0 && input <= 999999999) return (true);

            error = "The value must be between 0 - 999999999";
            return (false);
        });
        if (keyboard.Open(*value) != -1)
        {
            std::string &name = entry->Name();
            int pos = name.find("(");

            if (pos != std::string::npos)
            {
                name.erase(pos);
                name += Utils::Format("(%d)", *value);
            }
        }
    }

    void    BankEditor(MenuEntry *entry)
    {
        if (entry->IsActivated())
        {
            u64 money = EncryptACNLMoney(*GetArg<u32>(entry));

            Player::GetInstance()->Write64(0x6B8C, money);
        }

        entry->Disable();
    }
}
