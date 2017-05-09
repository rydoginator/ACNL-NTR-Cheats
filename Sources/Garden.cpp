#include "cheats.hpp"

namespace CTRPluginFramework
{
    void    SetNameTo(MenuEntry *entry)
    {
        if (!entry->IsActivated())
            return;

        Keyboard keyboard("Name Changer\n\nEnter the name you'd like to have:");

        std::string     input;

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

        entry->Disable();
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

    void    InjectTCP(MenuEntry *entry)
    {        
        if (!entry->IsActivated())
            return;

        File file;

        if (File::Open(file, "image.jpg", File::READ) == 0)
        {
            int res = file.Inject(Game::TCPImage, file.GetSize());
            file.Close();
            
            if (res == 0)
                MessageBox("Injection done")();
            else
                MessageBox("Injection failed")();
        }
        else
            MessageBox("Error\nCouldn't open image.jpg")();

        entry->Disable();
    }
}
