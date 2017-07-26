#include "cheats.hpp"

namespace CTRPluginFramework
{
    bool    CheckItemInput(const void *input, std::string &error)
    {
        // Cast the input into the appropriate type (must match the type provided to Open)
        u32 in = *static_cast<const u32 *>(input);

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

    void    Duplication(MenuEntry   *entry)
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


    void    SetBells(MenuEntry *entry)
    {
        u64 money;
        u32 output;

        Keyboard keyboard("How much money would you like?");

        keyboard.IsHexadecimal(false);

        // If the function return -1, then the user canceled the keyboard, so do nothing 
        if (keyboard.Open(output) != -1)
        {
            money = EncryptACNLMoney(output);

            Player::GetInstance()->Write64(0x6f08, money);
        }
    }

    void    Encyclopedia(MenuEntry *entry)
    {
        static u32 offset = Player::GetInstance()->GetOffset();
        static  u8 buffer[] = { 0xFF, 0xFF, 0x47, 0xFF, 0xFF, 0xFF, 0x7F, 0x97, 0xE3, 0x38, 0x81, 0xA3, 0x01, 0x00, 0x00, 0x00, 0x00, 0xE6, 0x7F, 0xEF, 0x7F, 0xF2, 0xFF, 0xFF, 0xDA, 0xCF, 0xCF, 0x15, 0xC7, 0x3E, 0x6B, 0xB6, 0x6B, 0x6F, 0xFC, 0xFF, 0x9F, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD3, 0xF6, 0x42, 0x63, 0x73, 0xAB, 0xD5, 0x06, 0xCC, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x02, 0xFE, 0xFF, 0xFF, 0x17, 0xEF, 0xFA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x9A, 0x9C, 0x93, 0xF6, 0x73, 0x00, 0x00, 0x00, 0xD2};
        if (offset != 0)
        {
            Process::CopyMemory(reinterpret_cast<void *>(offset + 0x6c20), buffer, 0x70);
            entry->Disable();
        }
    }

    void    Emoticons(MenuEntry *entry)
    {
        static u32 offset = Player::GetInstance()->GetOffset();
        static u8 buffer[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x20, 0x21, 0x24, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2E, 0x00, 0x00, 0x00, 0xD2};
        if (offset != 0)
        {
            Process::CopyMemory(reinterpret_cast<void *>(offset + 0x89d0), buffer, 0x20);
            entry->Disable();
        }
    }

    void    Songs(MenuEntry *entry)
    {
        static bool execution = false; //we want to add a check to see if it's executing so that we can disable the cheat once its done to prevent slow down
        for (int i = 0; i < 3; i++)
        {
            if (Player::GetInstance()->Write32(0x8F9C + (i * 4), 0xFFFFFFFF));
                execution = true;
        }
        if (execution)
            entry->Disable(); //we only want to disable the cheat once the cheat sucessfully writes to the player just in case they enable on title screen
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

    struct InventoryBox
    {
        int     currentBox;
        int     lastBox;
        File    file;
    };

    void    OpenBox(MenuEntry *entry, int id)
    {
        InventoryBox    *box = static_cast<InventoryBox *>(entry->GetArg());
        File            &file = box->file;

        // If file is not open, something's wrong
        if (!file.IsOpen())
        {
            OSD::Notify("An error occured !", Color::Red);
            OSD::Notify("Try to re-enable the cheat.");
            entry->Disable();
            return;
        }

        u32     inventory = Player::GetInstance()->GetInventoryAddress();
        char    buffer[0x100] = {0};

        // Save current box
        {
            // Go to current box's offset in file
            file.Seek(4 + (box->currentBox * BOX_SIZE), File::SET);

            // Now save current items
            file.Write(reinterpret_cast<void *>(inventory), BOX_SIZE);
        }

        // Open new box
        {
            // Go to wanted box's offset in file
            file.Seek(4 + (id * BOX_SIZE), File::SET);

            // Read items from file and write them in ram

            file.Read(buffer, BOX_SIZE);
            Process::CopyMemory(reinterpret_cast<void *>(inventory), buffer, BOX_SIZE);
        }

        // Update lastBox
        box->lastBox = box->currentBox;

        // Update current box
        box->currentBox = id;
        file.Seek(0, File::SET);
        file.Write(static_cast<void *>(&id), 4);

        // A little notification is always nice :)
        sprintf(buffer, "Opened box %d", id + 1);
        OSD::Notify(buffer, Color::LimeGreen);
    }

    void    ExtendedInventoryBox(MenuEntry *entry)
    {
        // If entry is disabled, properly release InventoryBox
        if (!entry->IsActivated())
        {
            InventoryBox    *box = static_cast<InventoryBox *>(entry->GetArg());

            if (box != nullptr)
            {
                box->file.Close();
                delete box;
                entry->SetArg(nullptr);
            }
            return;
        }

        // If just enabled the entry, create InventoryBox and open the file
        if (entry->WasJustActivated())
        {
            InventoryBox    *box = new InventoryBox;

            box->currentBox = 0;
            box->lastBox = 0;
            entry->SetArg(box);

            // If file don't exist, create it and init it
            if (!File::Exists("InventoryBoxs.bin"))
            {
                File    &file = box->file;

                // Open with create flag
                int flags = File::READ | File::WRITE | File::CREATE | File::SYNC;
                if (File::Open(file, "InventoryBoxs.bin", flags) == 0)
                {
                    int size = 4 + (BOX_SIZE * 10);
                    u8  buffer[4 + (BOX_SIZE * 10)] = { 0 };

                    file.Write(buffer, size);
                }
                else
                {
                    OSD::Notify("InventoryBox: An error occurred.", Color::Red);
                    entry->Disable();
                    return;
                }
            }
            // Else open it and get current box's index
            else
            {
                File    &file = box->file;

                if (File::Open(file, "InventoryBoxs.bin") == 0)
                {
                    u32  index = 0;

                    file.Read(&index, 4);
                    box->currentBox = index;
                }
                else
                {
                    OSD::Notify("InventoryBox: An error occurred.", Color::Red);
                    entry->Disable();
                    return;
                }
            }
        }

        static HoldKey  start(Key::Start, Seconds(1.f));

        if (!start())
            return;

        using StringVector = std::vector<std::string>;

        char            buffer[0x100] = { 0 };
        InventoryBox    *box = static_cast<InventoryBox *>(entry->GetArg());
        StringVector    boxList;
        std::string     keyboardHint = "Inventory Box\n\nWhich box do you want to open ?\n";

        sprintf(buffer, "Currently opened: [Box %d]", box->currentBox + 1);
        keyboardHint += buffer;

        Keyboard        keyboard(keyboardHint);
        
        // Init my list
        sprintf(buffer, "Last: %d", box->lastBox + 1);
        boxList.push_back(buffer);
        
        for (int i = 1; i < 11; i++)
        {
            sprintf(buffer, "Box %d", i);
            boxList.push_back(buffer);
        }

        // Init my keyboard with my list
        keyboard.Populate(boxList);

        // Show keyboard and get the box id

        int  id = keyboard.Open();

        // User did B, abort
        if (id == -1)
            return;

        // If user decided to open the last opened box
        if (id == 0)
            OpenBox(entry, box->lastBox);
        else
            OpenBox(entry, id - 1);
    }

    void    GenerateFossils(MenuEntry *entry)
    {
        int length;
        if (Controller::IsKeysDown(X + A))
        {
            int *slots = Player::GetInstance()->FindItems(length, 0x202A);
            for (int i = 0; i < length; i++)
            {
                u16 fossil = rand() % 0x57; //generate a new fossil for each iteration
                Player::GetInstance()->WriteInventorySlot(slots[i], 0x3130 + fossil);
            }
        }
    }
}
