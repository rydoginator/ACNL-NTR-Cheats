#include "cheats.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework
{
	using StringIter = std::string::iterator;
	using StringConstIter = std::string::const_iterator;

	int		GetMatches(StringVector& output, std::string& input)
	{
		output.clear(); // clear the output
		StringVector items;
		char data[0x1001];
		File file("items.txt");
		std::string list;
		Keyboard keyboard;
		// Clone the input string but with forced lowcase
		std::string     lowcaseInput(input);
		for (char& c : lowcaseInput)
			c = std::tolower(c);
		if (file.Exists("items.txt"))
		{
			u64 size = file.GetSize();
			if (!file.IsOpen())
				return -1;
			file.Rewind();
			list.clear();
			if (list.capacity() < size)
				list.reserve(size);
			while (size)
			{
				memset(data, 0, 0x1001);
				s64 sizeToRead = size > 0x1000 ? 0x1000 : size;

				if (file.Read(data, sizeToRead) == File::OPResult::SUCCESS)
				{
					list += data;
					size -= sizeToRead;
				}
			}
			int offset = 0;
			int breaks = 0;
			// parse the items.txt into a string vector
			if (items.capacity() < size)
				items.reserve(size);
			
			while ((breaks = list.find('\n', offset)) != std::string::npos)
			{
				items.push_back(list.substr(offset, breaks - offset));
				offset = breaks + 1;
			}
			list.clear();
			//search for items in the list
			for (const std::string& item : items)
			{
				if (item.find(input) != std::string::npos)
					output.push_back(item);
			}
			return (output.size());
		}
		else
		{
			return -1;
		}
	}

	void InputChange(Keyboard& keyboard, InputChangeEvent& event)
	{
		std::string& input = keyboard.GetInput();

		// If the user removed a letter do nothing
		if (event.type == InputChangeEvent::CharacterRemoved)
		{
			// Set an error, to avoid that the user can return an incomplete name
			keyboard.SetError("Type a letter to search for a item.");
			return;
		}
		// If input's length is less than 3, ask for more letters
		if (input.size() < 3)
		{
			keyboard.SetError("Not enough letters to do the search.\nKeep typing.");
			return;
		}

		// Else do the search
		StringVector    matches;


		// Search for matches
		int count = GetMatches(matches, input);

		// If we don't have any matches, tell the user
		if (!count)
		{
			keyboard.SetError("Nothing matches your input.\nTry something else.");
			return;
		}

		// If we have only one matches, complete the input
		if (count == 1)
		{
			input = matches[0].substr(0,4);
			return;
		}
		// If we have more than 1, but less or equal than 10 matches, ask the user to choose which one
		if (count <= 10)
		{
			// Our new keyboard
			Keyboard    listKeyboard;

			// Populate the keyboard with the matches
			listKeyboard.Populate(matches);

			// User can't abort with B
			listKeyboard.CanAbort(false);
			// Nothing to display on the top screen
			listKeyboard.DisplayTopScreen = false;

			// Display the keyboard and get user choice
			int choice = listKeyboard.Open();

			// Complete the input
			input = matches[choice].substr(0,4); // get the item ID of the choice 
			return;
		}
		// We have too much results, the user must keep typing letters
		keyboard.SetError("Too many results: " + std::to_string(count) + "\nType more letters to narrow the results.");
	}
	/*
	Converts the substring 0-3 to a writable item id
	*/
	Item		GetItemFromString(std::string item)
	{
		Item id;
		if (item.empty())
			id.raw = 0xFFFF;
		else
		{
			const char* cstr = item.c_str();
			id.raw = std::strtoul(cstr, 0, 16);
		}
		return id;
	}
    void    Text2Item(MenuEntry *entry)
    {
        if (entry->Hotkeys[0].IsDown())
        {
            Item item = { 0 };

            // New keyboard, hint being:
            Keyboard keyboard("What item would you like?");

            // Add the function to check the input entered by the user
            keyboard.SetCompareCallback([](const void *input, std::string &error)
            {
                // Cast the input into the appropriate type (must match the type provided to Open)
                Item in = *static_cast<const Item *>(input);
                u32 chk;
                chk = in.ID - 0x2000;

                // Check the value
                if (chk >= 0x6000)
                {
                    error = "Invalid Item ID: Cannot be use with Text2Item!";
                    // Return that the value isn't valid
                    return (false);
                }

                // The value is valid
                return (true);
            });
            // If the function return -1, then the user canceled the keyboard, so do nothing 
            if (keyboard.Open(item.raw) != -1)
            {
                Player::GetInstance()->WriteInventorySlot(0, item.raw);
            }
        }
		if (entry->Hotkeys[1].IsDown())
		{
			std::string input;
			Keyboard keyboard("Which item would you like?");
			keyboard.OnInputChange(InputChange);
			if (keyboard.Open(input) != -1)
			{
				Item item = GetItemFromString(input);
				u32 check = item.ID - 0x2000;
				if (check >= 0x6000)
				{
					MessageBox("Cannot use item ID for Text To Item")();
				}
				else
				{
					Player::GetInstance()->WriteInventorySlot(0, item.raw);
				}
			}

		}
    }

    void    Duplication(MenuEntry   *entry)
    {
        static bool active = false;
        if (entry->Hotkeys[0].IsDown() && !active)
        {
            active = true; //We only need to try 1 attempt per hotkey press
            u32 item;

            if (Player::GetInstance()->ReadInventorySlot(0, item)) {
                int numOfEmptySlots;
                int* slots = Player::GetInstance()->GetAvaibleSlots(numOfEmptySlots);
                if(numOfEmptySlots > 0) {
                    Player::GetInstance()->WriteInventorySlot(slots[0], item);
                    Player::GetInstance()->WriteInventoryLock(slots[0], 0);
                    OSD::Notify(Utils::Format("Duplicated Item: 0x%04X into slot: %i", static_cast<u32>(0x22e2) + item & 0xFFFF, slots[0]));
                }  else {
                    OSD::Notify(Color::Red << "Found no empty slots to duplicate item into");
                }
            }

        } else if(!entry->Hotkeys[0].IsDown()) {
            active = false;
        }
    }

    void    DuplicationAll(void)
    {
        u32     *address = reinterpret_cast<u32 *>(Player::GetInstance()->GetInventoryAddress());
        u32     firstItem = *address;

        // If slot0 is empty, exit
        if (firstItem == 0x00007FFE)
            return;

        ++address;

        for (int i = 0; i < 15; i++, ++address)
        {
            // If current slot is empty
            if (*address == 0x00007FFE) {
                *address = firstItem;
                Player::GetInstance()->WriteInventoryLock(i + (i == 15 ? 0 : 1), 0);
            }
        }
    }

    void    ClearInv(void)
    {
        for (int i = 0; i < 16; i++) 
        {
            Player::GetInstance()->WriteInventorySlot(i, 0x7FFE);
            Player::GetInstance()->WriteInventoryLock(i, 0);
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
            OSD::Notify("Encyclopedia Filled!", Color::Green, Color::Black);
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
            OSD::Notify("Emoticons Filled!", Color::Green, Color::Black);
            entry->Disable();
        }
    }

    void    Songs(MenuEntry *entry)
    {
        for (int i = 0; i < 3; i++)
        {
            if (Player::GetInstance()->Write32(0x8F9C + (i * 4), 0xFFFFFFFF))
            {
                OSD::Notify("Song List Filled!", Color::Green, Color::Black);
                entry->Disable(); /// We disable the cheat once the cheat sucessfully writes to the player just in case they enable on title screen
            }
        }
    }

    void    FillCatalog(MenuEntry *entry)
    {
        u32     address = Player::GetInstance()->GetOffset() + 0x6C90;

        std::memset((void *)address, 0xFF, 106 * 4);
        entry->Disable();
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
        if (entry->Hotkeys[0].IsDown())
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
        static u64 seed = 0;
        if (seed == 0)
            seed = EncryptACNLMoney(999999999);
        Player::GetInstance()->Write64(0x6B8C, seed);
    }

    void    InfiniteBank(MenuEntry *entry)
    {
        u64 seed;
        static u32 money = 0;
        Player::GetInstance()->Read64(0x6B8C, seed);
        if (entry->WasJustActivated())
            money = DecryptACNLMoney(seed);
        if (DecryptACNLMoney(seed) > money)
            money = DecryptACNLMoney(seed);      // store new value if you increase your bells
        else if (DecryptACNLMoney(seed) < money) // if you lose some money then write the stored value back
            Player::GetInstance()->Write64(0x6B8C, EncryptACNLMoney(money));
    }

    void    MaxCoupons(MenuEntry *entry)
    {
        static u64 seed = 0;
        if (seed == 0)
            seed = EncryptACNLMoney(999999999);
        Player::GetInstance()->Write64(0x8D1C, EncryptACNLMoney(9999));
    }

    void    InfiniteCoupons(MenuEntry *entry)
    {
        u64 seed;
        static u32 coupons = 0;
        Player::GetInstance()->Read64(0x8D1C, seed);
        if (entry->WasJustActivated())
            coupons = DecryptACNLMoney(seed);
        if (DecryptACNLMoney(seed) > coupons)
            coupons = DecryptACNLMoney(seed);
        else if (DecryptACNLMoney(seed) < coupons)
            Player::GetInstance()->Write64(0x8D1C, EncryptACNLMoney(coupons));
    }

    void    MaxMedals(MenuEntry *entry)
    {
        static u64 seed = 0;
        if (seed == 0)
            seed = EncryptACNLMoney(9999);
        Player::GetInstance()->Write64(0x6b9c, seed);
    }

    void    InfiniteMedals(MenuEntry *entry)
    {
        u64 seed;
        static u32 medals = 0;
        Player::GetInstance()->Read64(0x6b9c, seed);
        if (entry->WasJustActivated())
            medals = DecryptACNLMoney(seed);
        if (DecryptACNLMoney(seed) > medals)
            medals = DecryptACNLMoney(seed);
        else if (DecryptACNLMoney(seed) < medals)
            Player::GetInstance()->Write64(0x6b9c, EncryptACNLMoney(medals));
    }

    void    MaxWallet(MenuEntry *entry)
    {
        static u64 seed = 0;
        if (seed == 0)
            seed = EncryptACNLMoney(99999);
        Player::GetInstance()->Write64(0x6F08, seed);
    }

    void    InfiniteWallet(MenuEntry *entry)
    {
        u64 seed;
        static u32 money = 0;
        Player::GetInstance()->Read64(0x6F08, seed);
        if (entry->WasJustActivated())
            money = DecryptACNLMoney(seed);
        if (DecryptACNLMoney(seed) > money)
            money = DecryptACNLMoney(seed);
        else if (DecryptACNLMoney(seed) < money)
            Player::GetInstance()->Write64(0x6F08, EncryptACNLMoney(money));
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
