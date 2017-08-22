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

            if (event.type == InputChangeEvent::CharacterAdded && Utils::GetSize(input) >= 9)
                Utils::RemoveLastChar(input);
        });
        if (keyboard.Open(input) != -1)
        {
            // Ask for a second line name
            if ((MessageBox("Do you want your name to\nappear below the bubble ?", DialogType::DialogYesNo))())
                input.insert(0, 1, '\n');

            Player::GetInstance()->SetName(input);
        }
    }

    void    BuildingPlacer(MenuEntry *entry)
    {
        u32     offset = 0;
        u8      input;

        if (Controller::IsKeysDown(R + DPadDown))
        {
            Keyboard keyboard("What building would you like to place ?");
            
            //Exit if the user cancel the keyboard
            if (keyboard.Open(input) == -1)
                return;
            
            u8      x = static_cast<u8>(Game::WorldPos->x);
            u8      y = static_cast<u8>(Game::MainStreetPos->y);
            u32     slots = Game::BuildingSlots; //address of byte that represents how many buildings are taken up
            u32     building = Game::Building;

            while (READU8(building + offset) != 0xFC && offset < 0xE5)
            {
                offset += 0x4;
            }
            if (offset >= 0xE5)
            {
                OSD::Notify("All building slots are filled!");
            }
            else
            {
                WRITEU8(building + offset, input);
                WRITEU8(building + offset + 0x2, x);
                WRITEU8(building + offset + 0x3, y);
                ADD8(slots, 1);
            }
        }

        if (Controller::IsKeysDown(R + DPadUp))
        {
            Keyboard keyboard("What building would you like to remove?");

            // Exit if the user cancel the keyboard
            if (keyboard.Open(input) == -1)
                return;

            u32     building = Game::Building;
            u32     slots = reinterpret_cast<u32>(Game::BuildingSlots);

            while (READU8(building + offset) != input && offset < 0xE5)
            {
                offset += 0x4;
            }
            if (offset == 0xE5)
            {
                OSD::Notify("Could not find your building");
            }
            else
            {
                WRITEU8(building + offset, 0xFC);
                WRITEU8(building + offset + 0x2, 0x00);
                WRITEU8(building + offset + 0x3, 0x00);
                SUB8(slots, 1);
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
            if (input.find(".bin") == std::string::npos)
                input += ".bin";

            // Let's create and open the file
            if (dir.OpenFile(file, input, File::RWC) == 0)
            {
                // Dump to the file
                if (file.Dump(Game::Garden, 0x89A80) == 0) // Success
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

        if (dir.ListFiles(list, ".bin") == Directory::OPResult::NOT_OPEN)
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
    }

    void    Permit(MenuEntry *entry)
    {
        Process::Write32(Game::Permit, 0xD7DFC900);
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
