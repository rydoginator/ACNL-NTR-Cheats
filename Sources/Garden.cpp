#include "cheats.hpp"

namespace CTRPluginFramework
{

    void    NameChanger_OnInputChange(Keyboard &keyboard, InputChangeEvent &event)
    {
        std::string &input = keyboard.GetInput();

        if (event.type == InputChangeEvent::CharacterAdded
            && GetSize(input) >= 9)
        {
            RemoveLastChar(input);
        }
    }

    void    SetNameTo(MenuEntry *entry)
    {
        Keyboard keyboard("Name Changer\n\nEnter the name you'd like to have:");

        std::string     input;

        keyboard.OnInputChange(NameChanger_OnInputChange);
        if (keyboard.Open(input) != -1)
        {
            // Ask for a second line name
            MessageBox msgBox("Do you want your name to\nappear below the bubble?", DialogType::DialogYesNo);

            if (msgBox())
            {
                std::string secondLine = "\n";

                secondLine += input;
                input = secondLine;
            }

            Player::GetInstance()->SetName(input);
        }
    }


    void    BuildingPlacer(MenuEntry *entry)
    {
        u32     offset = 0;
        u8      input;

        if (Controller::IsKeysDown(R + DPadDown))
        {
            Keyboard keyboard("What building would you like to place?");
            
            //Exit if the user cancel the keyboard
            if (keyboard.Open(input) == -1)
                return;
            
            u8      x = static_cast<u8>(Game::WorldPos->x);
            u8      y = static_cast<u8>(Game::MainStreetPos->y);
            u32     slots = reinterpret_cast<u32>(Game::BuildingSlots); //address of byte that represents how many buildings are taken up
            u32     building = reinterpret_cast<u32>(Game::Building);

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

            u32  building = reinterpret_cast<u32>(Game::Building);
            u32      slots = reinterpret_cast<u32>(Game::BuildingSlots);

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
        Keyboard        keyboard("GardenRam Dumper\n\nName the dump you'd like to create.");
        std::string     input;
        File            file;
        Directory       dir;

        if (keyboard.Open(input) != -1)
        {
            // Add extension to the name if user didn't
            if (input.find(".bin") == std::string::npos)
                input += ".bin";

            // Open dumps folder, create it if it doesn't exist
            if (Directory::Open(dir, "dumps", true) == 0)
            {
                // Folder successfully opened

                // Let's create and open the file
                if (dir.OpenFile(file, input, true) == 0)
                {
                    // Successfully opened the file 

                    // Dump to the file
                    if (file.Dump(Game::Garden, 0x89A80) == 0)
                    {
                        // Success

                        std::string     path;
                        std::string     message;

                        // Assemble full path
                        path = dir.GetPath();
                        path += input;

                        // Assemble message for MessageBox
                        message = "File dumped to:\n";
                        message += path;

                        // Create MessageBox and open it
                        (MessageBox(message))();
                    }
                    else
                    {
                        //  Failed
                        MessageBox("Error\nDump failed.")();
                    }
                }
            }
            else
            {
                // Failed to open the folder, notify the user
                MessageBox("Error\nCouldn't open dumps folder.")();
            }

            // Close file and directory
            file.Close();
            dir.Close();
        }
    }

    void    GardenRestore(MenuEntry *entry)
    {
        File            file;
        Directory       dir;
        std::vector<std::string> list;

        if (Directory::Open(dir, "dumps", true) == 0)
        {
            dir.ListFiles(list, ".bin");

            if (!list.empty())
            {
                Keyboard keyboard("Select which dump to restore.");

                keyboard.Populate(list);

                int userChoice = keyboard.Open();

                if (userChoice != -1)
                {
                    if (dir.OpenFile(file, list[userChoice], false) == 0)
                    {
                        if (file.Inject(Game::Garden, 0x89A80) == 0)
                        {
                            MessageBox("Successfully restored your\nsave!")();
                        }
                        else
                        {
                            MessageBox("Error\nError injecting dump!")();
                        }
                    }
                    else
                    {
                        MessageBox("Error\nCouldn't open the dump!")();
                    }
                }
            }
            else
            {
                MessageBox("Error\nCouldn't find any dumps!")();
            }
        }
        else
        {
            // Failed to open the folder, notify the user
            MessageBox("Error\nCouldn't open dumps folder.")();
        }
        file.Close();
        dir.Close();
    }

    void    ChangeNativeFruit(MenuEntry *entry)
    {
        static u32 offset = reinterpret_cast<u32> (Game::TownFruit);
        Keyboard keyboard("What fruit would you like?");
        std::vector<std::string> list = 
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

        keyboard.Populate(list);

        u8 userChoice = keyboard.Open();

        if (userChoice != -1)
            Process::Write8(offset, userChoice + 1);
    }

    void    PWPUnlock(MenuEntry *entry)
    {
        static u32 offset = reinterpret_cast<u32> (Game::PWP);
        for (int i = 0; i < 3; i++)
        {
            Process::Write32(offset + (i * 4), 0xFFFFFFFF);
        } 
    }

    void    Permit(MenuEntry *entry)
    {
        static u32 offset = reinterpret_cast<u32> (Game::Permit);
        Process::Write32(offset, 0xD7DFC900);
    }

    void    MaxTreeSize(MenuEntry *entry)
    {
        static u32 offset = reinterpret_cast<u32> (Game::TownTree);
        Process::Write8(offset, 0x7);
        Process::Write32(offset + 0x1632A, 0x10000000);
        Process::Write16(offset + 0x163B8, 0x686);
    }

    void    ChangeGrass(MenuEntry *entry)
    {
        static u32 offset = reinterpret_cast<u32> (Game::TownGrass);
        Keyboard keyboard("What grass type would you like?");
        std::vector<std::string> list = 
        {
            "Triangle",
            "Circle",
            "Square"
        };

        keyboard.Populate(list);

        u8 userChoice = keyboard.Open();

        if (userChoice != -1)
            Process::Write8(offset, userChoice);
    }
}
