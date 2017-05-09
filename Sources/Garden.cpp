#include "cheats.hpp"
#include "ctrulib/util/utf.h"

namespace CTRPluginFramework
{
    void    SetNameTo(MenuEntry *entry)
    {
        if (!entry->IsActivated())
            return;
        Keyboard keyboard("Name Changer\n\nEnter the name you'd like to have:");

        std::string     input;
        u16             output[0x100] = { 0 };

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

            // Convert input to game's format
            int res = utf8_to_utf16(output, reinterpret_cast<const u8*>(input.c_str()), 0x100);

            if (res > 0)
            {
                Player::GetInstance()->CopyMemory(0x55a8, output);
                entry->Disable();
            }
        }
        else
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
                    extern u32 g_garden;
                    if (file.Dump(g_garden, 0x89A80) == 0)
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
                        MessageBox      msgBox(message);

                        msgBox();
                    }
                    else
                    {
                        //  Failed

                        MessageBox msgBox("Error\nDump failed.");

                        msgBox();
                    }
                }
            }
            else
            {
                // Failed to open the folder, notify the user
                MessageBox msgBox("Error\nCouldn't open dumps folder.");

                msgBox();
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
                    if (dir.OpenFile(file, list[userChoice], File::READ) == 0)
                    {
                        extern u32 g_garden;
                        if (file.Inject(g_garden, 0x89A80) == 0)
                        {
                            MessageBox      msgBox("Successfully restored your\nsave!");

                            msgBox();
                        }
                        else
                        {
                            MessageBox msgBox("Error\nError injecting dump!");
                        }
                    }
                    else
                    {
                        MessageBox msgBox("Error\nCouldn't open the dump!");

                        msgBox();
                    }
                }
            }
            else
            {
                MessageBox msgBox("Error\nCouldn't find any dumps!");
                msgBox();
            }
        }
        else
        {
            // Failed to open the folder, notify the user
            MessageBox msgBox("Error\nCouldn't open dumps folder.");

            msgBox();
        }
        file.Close();
        dir.Close();
    }

    void    InjectTCP(MenuEntry *entry)
    {
        extern u32 g_garden;
        File file;
        if (!entry->IsActivated())
            return;
        int ret = File::Open(file, "image.jpg", File::READ);
        if (ret == 0)
        {
            int res = file.Inject(g_garden + 0x5758, file.GetSize());
            file.Close();
            entry->Disable();
        }
    }
}
