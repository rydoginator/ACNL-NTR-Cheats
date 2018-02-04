#include "cheats.hpp"
#include "CTRPluginFramework/Utils/Utils.hpp"

namespace CTRPluginFramework
{
    void    SetNameTo(MenuEntry *entry)
    {
        Keyboard        keyboard("Name Changer\n\nEnter the name you'd like to have:");
        std::string     input;

        keyboard.OnInputChange([](Keyboard &keyboard, InputChangeEvent &event)
        {
            std::string &input = keyboard.GetInput();

            if (event.type == InputChangeEvent::CharacterAdded && Utils::GetSize(input) >= 6)
                Utils::RemoveLastChar(input);
        });
        if (keyboard.Open(input) != -1)
        {
            // Ask for a second line name if the name is smaller than 6 characters
            if (Utils::GetSize(input) < 6 
                && (MessageBox("Do you want your name to\nappear below the bubble ?", DialogType::DialogYesNo))())
                input.insert(0, 1, '\n');

            Player::GetInstance()->SetName(input);
        }
    }

    void    BuildingPlacer(MenuEntry *entry)
    {
        Keyboard keyboard("Building placer\nChoose an option.");
        StringVector options = { "Place a building", "Remove a building" };
        keyboard.Populate(options);
        int userChoice = keyboard.Open();
        u32 building = Game::Building;
        u32 counter = 0;

        options.clear(); //clear options in order to store the building ids in it.
        if (userChoice == 0)
        {
            for (const Buildings &option : buildingIDS)
                options.push_back(option.Name);
            Keyboard _keyboard("Which building would you like to place?");
            _keyboard.Populate(options);
            int index = _keyboard.Open();
            u8 id = buildingIDS[index].id;
            while (*(u8 *)(building + (counter * 4)) != 0xFC && counter < 31)
                counter++;
            if (counter == 30)
                OSD::Notify("All building slots are filled!");
            else
            {
                Process::Write8(building + (counter * 4), id);
                Process::Write8(building + (counter * 4) + 2, static_cast<u8>(Game::WorldPos->x));
                Process::Write8(building + (counter * 4) + 3, static_cast<u8>(Game::WorldPos->y));
                *Game::BuildingSlots++;
                
            }
            return;
        }
        else if (userChoice == 1)
        {
            std::vector<u8> buildings;
            std::vector<u8> x, y;
            
            for (int i = 0; i < 30; i++)
            {
                if (READU8(building + (i * 4)) != 0xFC) //check if a building is not empty
                {
                    buildings.push_back(READU8(building + (i * 4)));
                    x.push_back(READU8(building + (i * 4) + 2));
                    y.push_back(READU8(building + (i * 4) + 3));
                }
            }
            
            for (int i = 0; i < buildings.size(); i++)
            {
                for (int j = 0; j < buildingIDS.size(); j++)
                {
                    if (buildingIDS[j].id == buildings[i])
                        options.push_back(buildingIDS[j].Name);
                }
            }
            Keyboard _keyboard("Which building would you like to destroy?");
            _keyboard.Populate(options);
            int index = _keyboard.Open();

            if (index != -1)
            {
                u8 id = buildings[index];
                while (*(u8 *)(building + (counter * 4)) != id && counter < buildings.size())
                    counter++;
                Process::Write8(building + (counter * 4), 0xFC);
                Process::Write8(building + (counter * 4) + 2, 0);
                Process::Write8(building + (counter * 4) + 3, 0);
                *Game::BuildingSlots--;
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
                if (file.Inject(Game::Garden, 0x89A80) == 0)
                    MessageBox("Successfully restored your save !")();
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
        Process::Write32(Game::Permit, 0xD7DFC900);
        OSD::Notify("Permit now 100%!", Color::Green, Color::Black);
        entry->Disable();
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
