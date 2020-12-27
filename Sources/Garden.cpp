#include "cheats.hpp"

extern "C" void FixSaveFurn(void);
u32 g_FixSaveFurnAddr = 0;

static const char RTBP_AmountMSG[] = "You can't place more buildings of the ID 0x%02X";
static const char RTBP_ErrorMSG[] = "RTBP just tried to place/remove Building 0x%02X, which is invalid.\nPlease report this to the developers, along with:\n1)The building you selected on the list\n2)The building amount (Amount is: %d).";
static const char RTBP_EventMSG[] = "Only two event pwps can be placed at one time (to avoid issues with the game).\nPlease remove one of the existing event buildings to place a new one.";
static const char RTBP_0PWPMSG[] = "No buildings of this type can be found!";
static const char RTBP_0NUMMSG[] = "You have 0 buildings, how the hell are you removing one???";

namespace CTRPluginFramework
{
    void    ChangePlayerName(MenuEntry *entry)
    {
        Keyboard        keyboard("Player Name Changer:\n\nEnter the name you'd like to have:");
        std::string     input;

        keyboard.SetMaxLength(8);
        if (keyboard.Open(input) != -1)
        {
            // Ask for a second line name if the name is smaller than 8 characters
            if (Utils::GetSize(input) < 8) {
                if (MessageBox("Player Name Changer:\n\nDo you want your name to\nappear on the next line?", DialogType::DialogYesNo)())
                    input.insert(0, 1, '\n');
            }

            Player::GetInstance()->SetName(input);
        }
    }

    #define TOWN_NAME_OFFSET 0x0621BA
    #define TOWN_NAME_MAX    8

    void    ChangeTownName(MenuEntry *entry)
    {
        u16 newname[TOWN_NAME_MAX + 1] = {0};
        u16 oldname[TOWN_NAME_MAX + 1] = {0};

        Keyboard        keyboard("Town Name Changer:\n\nEnter the name you'd like to have:");
        std::string     input;

        keyboard.SetMaxLength(8);
        if (keyboard.Open(input) != -1)
        {
            // Ask for a second line name if the name is smaller than 8 characters
            if (Utils::GetSize(input) < 8) {
                if (MessageBox("Town Name Changer:\n\nDo you want the town name to\nappear on the next line?", DialogType::DialogYesNo)())
                    input.insert(0, 1, '\n');
            }

            Process::CopyMemory(oldname, reinterpret_cast<void *>(Game::Garden+TOWN_NAME_OFFSET), TOWN_NAME_MAX*2); //*2 as u16 characters

            // Convert utf8 to utf16

			int res = utf8_to_utf16(newname, reinterpret_cast<const u8*>(input.data()), TOWN_NAME_MAX);

			if (res == -1)
				return;

            u32 offset = Game::Garden; //Offset where Save starts in ram
            u32 size = 0x89B00; //Save Size
            const std::vector<u16> vec(std::begin(oldname), std::end(oldname));
            
            while (offset != 0) {
                offset = Utils::Search<u16>(offset, size, vec);
                if (offset == 0) return;
                size = 0x89B00 - (offset-Game::Garden); //reduce size each time
                Process::CopyMemory(reinterpret_cast<void *>(offset), newname, TOWN_NAME_MAX*2); //*2 as u16 characters
            }
        }
    }

//check if certain building was placed too often
    bool BuildingChecker(u8 buildingID, int maxamount) {		
        int Bslot = 0;
        int curramount = 0;
        while(true) { 			
            u32 Building = Game::Building + (0x4 * Bslot);
            if(buildingID == *(u8 *)Building) //If building was found
                curramount++;

            Bslot++; //goto next slot

    	//finished searching, if max amount wasn't reached return true
            if(56 < Bslot) 
                return 1;	

        //If max amount is smaller return false
            if(curramount >= maxamount) 
                return 0;	
        }
    }
	
    void    BuildingModifier(MenuEntry *entry)
    {
        static const StringVector pwptype = {"Normal PWPs", "Event PWPs"};
        static const StringVector MainOptions = { "Place a Building", "Remove a Building", "Move a Building" };
        StringVector options;
        u32 off_building = Game::Building;
        u32 counter = 0;
        u32 maxcounter = 0;

        if (*Game::Room != 0) {
            MessageBox("RTBM Error!", "You need to be in the Town for this to work.")();
            return;
        }
        
        Keyboard keyboard("Building Modifier:\n\nChoose an option.");
        keyboard.Populate(MainOptions);
        int userChoice = keyboard.Open();

        if (userChoice == -1)
            return;

        /* Place Bulding */
        else if (userChoice == 0) //Place
        {
            for (const Building &pwp : buildingIDS)
                options.push_back(pwp.Name);

            keyboard.GetMessage() = "Building Placer:\n\nWhich building would you like to place?";
            keyboard.Populate(options);
            int index = keyboard.Open();

            if (index == -1)
                return;

            Building CurPWP = buildingIDS[index];

            if ((CurPWP.id >= 0x12 && CurPWP.id <= 0x4B) || CurPWP.id > 0xFC) //Invalid Buildings
            {
                MessageBox("Building Placer: Error!", Utils::Format(RTBP_ErrorMSG, CurPWP.id, counter))();
                return;
            }

            else if (CurPWP.IsEvent) { //Event Building
                if (*(Game::BuildingSlots+1) == 2) 
				{
                    MessageBox("Building Placer: Error!", RTBP_EventMSG)();
                    return;
                }

                counter = 56; //Event PWP are last two slots
                maxcounter = 58;
            }

            else 
			{ //Not Event Building
                counter = 0;
                maxcounter = 56;
            }
            //Checks if there are too many buildings of specific type	
            if (CurPWP.id == 0xDC) {
                if (!BuildingChecker(CurPWP.id, 8)) 
                {
                    MessageBox("Building Placer: Error!", Utils::Format(RTBP_AmountMSG, CurPWP.id))();
                    return;
                }  
	    }

            //Increment counter until we find a empty slot
            while (READU8(off_building + (counter * 4)) != 0xFC && counter < maxcounter) 
			{
                counter++;
            }

            if (counter == maxcounter)
                OSD::Notify(Color::Red << "Every Building Slot Is Filled!");

            else
            {
                Process::Write8(off_building + (counter * 4), CurPWP.id);
                Process::Write8(off_building + (counter * 4) + 2, static_cast<u8>(Game::WorldPos->x));
                Process::Write8(off_building + (counter * 4) + 3, static_cast<u8>(Game::WorldPos->y));
                OSD::Notify(Utils::Format("\"%s\" (0x%02X) Placed!", CurPWP.Name, CurPWP.id));
                OSD::Notify(Color::Green << "Reload the area to see effects.");
                if (CurPWP.IsEvent)
                    ADD8((Game::BuildingSlots+1), 1); //Increment Event Building Amount
                else
                    ADD8(Game::BuildingSlots, 1); ////Increment Normal Building Amount
				goto reload;
            }
            return;
        }

        /* Remove Building */
        else if (userChoice == 1) //Remove
        {
            std::vector<u8> buildings;
            std::vector<bool> IsEvent;
            int start = 0, end = 0;

            keyboard.GetMessage() = "Building Remover:\n\nWhich building type would you like to remove?";
            keyboard.Populate(pwptype);
            int pwptypechoice = keyboard.Open();

			if (pwptypechoice == 0)
			{ //Normal PWPs
				start = 0;
				end = 56;
			}
            else if (pwptypechoice == 1) //Event PWPs
			{ 
                start = 56;
                end = 58;
            }
            else  //Keyboard abort or some weird error
				return;

            for (int i = start; i < end; i++)
            {
                u8 BuildingID = 0xFC; //Set default to empty
                Process::Read8(off_building + (i*4), BuildingID);
                if (BuildingID != 0xFC) //check if a building is not empty
				{ 
                    buildings.push_back(BuildingID);
                }
            }

            if (buildings.size() == 0) //Possible case due to event pwps not always there
			{ 
                MessageBox("Building Remover: Error!", RTBP_0PWPMSG)();
                return;
            }
            
            for (int i = 0; i < buildings.size(); i++)
            {
                for (const Building& building : buildingIDS)
                {
                    if (building.id != buildings[i])
                        continue;

                    options.push_back(building.Name);
                    IsEvent.push_back(building.IsEvent);
                    break;
                }
            }

            keyboard.GetMessage() = "Building Remover:\n\nWhich building would you like to remove?";
            keyboard.Populate(options);
            int index = keyboard.Open();

            if (index > -1) //user didn't abort
            {
                u8 id = buildings[index];
                const char* name = options[index].c_str();

                while ((READU8(off_building + (start*4) + (counter*4)) != id) && counter < buildings.size() && counter+start < end)
                    counter++;
                Process::Write8(off_building + (start*4) + (counter * 4), 0xFC);
                Process::Write8(off_building + (start*4) + (counter * 4) + 2, 0);
                Process::Write8(off_building + (start*4) + (counter * 4) + 3, 0);

                if (IsEvent[index] && *(Game::BuildingSlots+1) > 0)
                    Process::Write8(reinterpret_cast<u32>(Game::BuildingSlots + 1), buildings.size()-1); //Decrement Event Building Amount
                else if (*Game::BuildingSlots > 0)
                    Process::Write8(reinterpret_cast<u32>(Game::BuildingSlots), buildings.size()-1); //Decrement Event Building Amount
				else
				{
					MessageBox("Building Remover: Error!", RTBP_0NUMMSG)();
					return;
				}
				OSD::Notify(Utils::Format("\"%s\" (0x%02X) Removed!", name, id));
				OSD::Notify(Color::Green << "Reload the area to see effects.");
				goto reload;

            }
            return;
        }

        /* Move Bulding */
        else if (userChoice == 2) //Move
        {
            std::vector<u8> buildings;
            int start = 0, end = 0;

            keyboard.GetMessage() = "Building Mover:\n\nWhich building type would you like to move?";
            keyboard.Populate(pwptype);
            int pwptypechoice = keyboard.Open();

            if (pwptypechoice == -1) //abort
                return;

            else if (pwptypechoice == 0) {
                start = 0;
                end = 56;
            }

            else if (pwptypechoice == 1) {
                start = 56;
                end = 58;
            }

            for (int i = start; i < end; i++)
            {
                u8 BuildingID = 0xFC; //Set default to empty
                Process::Read8(off_building + (i*4), BuildingID);
                if (BuildingID != 0xFC) { //check if a building is not empty
                    buildings.push_back(BuildingID);
                }
            }

            if (buildings.size() == 0) { //Possible case due to event pwps not always there
                MessageBox("Building Mover: Error!", RTBP_0PWPMSG)();
                return;
            }
            
            for (int i = 0; i < buildings.size(); i++)
            {
                for (const Building& building : buildingIDS)
                {
                    if (building.id != buildings[i])
                        continue;

                    options.push_back(building.Name);
                    break;
                }
            }

            keyboard.GetMessage() = "Building Mover:\n\nWhich building would you like to move?";
            keyboard.Populate(options);
            int index = keyboard.Open();

            if (index > -1) //user didn't abort
            {
                u8 id = buildings[index];
                const char* name = options[index].c_str();

                while (*(u8 *)(off_building + (start*4) + (counter * 4)) != id && counter < buildings.size() && counter+start < end)
                    counter++;

                Process::Write8(off_building + (start*4) + (counter * 4) + 2, static_cast<u8>(Game::WorldPos->x));
                Process::Write8(off_building + (start*4) + (counter * 4) + 3, static_cast<u8>(Game::WorldPos->y));

                OSD::Notify(Utils::Format("\"%s\" (0x%02X) Moved to Current Position!", name, id));
                OSD::Notify(Color::Green << "Reload the area to see effects.");
				goto reload;
            }
            return;
        }
	return;
	reload:
		if (MessageBox("Question", "Would you like to reload the area?", DialogType::DialogYesNo)())
		{
			Coordinates coord = Player::GetInstance()->GetCoordinates();
			int result = Game::TeleportRoom(*Game::Room, coord);
			switch (result)
			{
			case -1:
				OSD::Notify("You currently cannot warp!");
				break;
			case -2:
				OSD::Notify("You cannot warp at club tortimer!");
				break;
			case -3:
				OSD::Notify("You cannot warp from this area!");
				break;
			case -4:
				OSD::Notify("Please stand still while trying to teleport!");
				break;
			default:
				OSD::Notify("Reloading area...");
				break;
			}
		}
    }

    void    GardenDumper(MenuEntry *entry)
    {
        File            file;
        Directory       dir("dumps", true);
        Keyboard        keyboard("GardenRam Dumper\n\nName the dump you'd like to create.");
        std::string     input;

        if (keyboard.Open(input) != -1)
        {
            // Add extension to the name if user didn't
            if (input.find(".dat") == std::string::npos)
                input += ".dat";

            // Let's create and open the file
            if (dir.OpenFile(file, input, File::RWC) == 0)
            {
                // Dump to the file
                if (file.Dump(Game::Garden, 0x89B00) == 0) // Success
                    (MessageBox("File dumped to:\n" + file.GetFullName()))();
                else // Failed
                    MessageBox("Error\nDump failed.")();
            }

            file.Flush();
            file.Close();
        }
    }

    void    GardenRestore(MenuEntry *entry)
    {
        File            file;
        Directory       dir("dumps");
        StringVector    list;

        if (dir.ListFiles(list, ".dat") == Directory::OPResult::NOT_OPEN)
        {
            MessageBox("Error\nCouldn't open dumps folder.")();
            return;
        }

        if (list.empty())
        {
            MessageBox("Error\nCouldn't find any dumps!")();
            return;
        }

        Keyboard    keyboard("Select which dump to restore.", list);
        int         userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            if (dir.OpenFile(file, list[userChoice], File::RWC) == 0)
            {
                if (file.Inject(Game::Garden, 0x89A80) == 0) {
                    MessageBox("Successfully restored your save !")();
                    g_FixSaveFurnAddr = Game::Internal_FurnFix;
                    u32 orig[1] = {0};
                    Process::Patch(g_FixSaveFurnAddr+0x41C, 0xE1A00000, orig); //Must be patched, otherwise game crashes
                    FixSaveFurn(); //Calls func to call Game's internal function to fix furniture
                    Process::Patch(g_FixSaveFurnAddr+0x41C, orig[0]); //Unpatch so game doesn't have a potential fit when it calls the func itself
                }
                else
                    MessageBox("Error\nError injecting dump!")();
            }
            else
                MessageBox("Error\nCouldn't open the dump!")();
        }
    }

    void    ChangeNativeFruit(MenuEntry *entry)
    {
        static const StringVector list =
        {
            "Apples",
            "Oranges",
            "Pears",
            "Peaches",
            "Cherries",
            "Coconuts",
            "Durians",
            "Lemons",
            "Lychee",
            "Mango",
            "Persimmon",
            "Bananas"
        };

        Keyboard    keyboard("What fruit would you like ?", list);
        int         userChoice = keyboard.Open();

        if (userChoice != -1)
            Process::Write8(Game::TownFruit, userChoice + 1);
    }

    void    PWPUnlock(MenuEntry *entry)
    {
        for (int i = 0; i < 3; i++)
        {
            Process::Write32(Game::PWP + (i * 4), 0xFFFFFFFF);
        }
        OSD::Notify("All PWPs Unlocked!", Color::Green, Color::Black);
        entry->Disable();
    }

    void    Permit(MenuEntry *entry)
    {
		u8 permitval = 0;
		Process::Read8(Game::Permit, permitval);
		Process::Write8(Game::Permit, (permitval & 1) | 0xC8);
		OSD::Notify("Development Permit is now 100%!", Color::Green, Color::Black);
		entry->Disable();

    }

	void	FillMuseum(MenuEntry* entry)
	{
		std::string name;
		StringVector names;
		u32 PlayerOffset;
		u8 cmp;

		Keyboard keyboard("Who is supposed to make the donation?");

		for (int i = 0; i < 4; i++) {
			PlayerOffset = 0xA0 + (i * 0xA480);
			Process::ReadString((Game::Garden + PlayerOffset + 0x55A8), name, 0x10, StringFormat::Utf16);
			if (!name.empty()) names.push_back(name); //if the read name is not empty, add it to the vector
			name.clear(); //just to be sure
		}
		if (!names.empty()) {
			keyboard.Populate(names);
			int player = keyboard.Open();
			if (player != -1) {
				for (int j = 0; j < 0x112; j++) {
					if (Process::Read8((Game::Garden + 0x06b300 + j), cmp) && cmp == 0x00) //check if there is an already existing donation
						Process::Write8((Game::Garden + 0x06b300 + j), 0x01 * (player + 1));
				}
				OSD::Notify("Filled Museum!", Color::Green, Color::Black);
			}
		}
	}

	void	SetOrdinance(MenuEntry* entry)  //Love Slattz <3
	{
		ordinance:
			Keyboard OrdinanceKboard("Ordinance Setter\n\nClick on an Ordinance to toggle it.\n\n" << Color::Gray << "(Press \uE001 to exit.)");
			bool EnabledOrds[4] = { 0,0,0,0 };
			u8 CurrentOrdinances = 0;
			StringVector Names = {
				"Early Bird",
				"Night Owl",
				"Bell Boom",
				"Keep Town Beautiful"
			};

			Process::Read8(Game::Garden + 0x0621cf, CurrentOrdinances);
			for (int i = 0; i < 4; i++) {
				EnabledOrds[i] = (((CurrentOrdinances & 0x1E) >> (i + 1)) & 1) == 1;
				if (EnabledOrds[i]) Names[i] += Color::DeepSkyBlue << " active";
			}

			OrdinanceKboard.Populate(Names);
			int input = OrdinanceKboard.Open();
			if (input < 0 || input > 3) return;

			Process::Write8(Game::Garden + 0x0621cf, CurrentOrdinances ^ (2 << input));
			goto ordinance;
	}



    void    MaxTreeSize(MenuEntry *entry)
    {
        Process::Write8(Game::TownTree, 0x7);
        Process::Write32(Game::TownTree + 0x1632A, 0x10000000);
        Process::Write16(Game::TownTree + 0x163B8, 0x686);
    }

    void    ChangeGrass(MenuEntry *entry)
    {
        static const StringVector list =
        {
            "Triangle",
            "Circle",
            "Square"
        };

        Keyboard    keyboard("What grass type would you like ?", list);
        int         userChoice = keyboard.Open();

        if (userChoice != -1)
            Process::Write8(Game::TownGrass, userChoice);
    }
}
