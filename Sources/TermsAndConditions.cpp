#include "CTRPluginFramework.hpp"
#include "Game.hpp"
#include <ctime>


namespace CTRPluginFramework
{
    enum Flags
    {
        SKIP_TC = 1,
        SKIP_SAVE = 2
    };

    void    StartMsg(void) //Startup message for plugin
    {
        u32     flags = 0;
        File    file("data.bin", File::RWC);

        file.Read((void *)&flags, sizeof(u32));

        if (!(flags & SKIP_TC))
        {
            static const std::string TC = "Terms & Conditions:\nThis software is provided free of charge.\nIf you have paid for this plugin,\nimmediately ask for a refund.\nThis software is provided 'as-is', without any express or implied warranty.\nIn no event will the authors be held\nliable for any damages arising from the\nuse of this software.\n\nDo you accept the Terms & Conditions?";

            if ((MessageBox(TC, DialogType::DialogYesNo)).SetClear(ClearScreen::Both)()) //If Yes is picked in T&C MessageBox
            {
                flags |= SKIP_TC;
            }
            else
            {
                MessageBox("You must accept the Terms & Conditions to use this plugin.").SetClear(ClearScreen::Both)();
                Process::ReturnToHomeMenu();
            }
        }

        if (!(flags & SKIP_SAVE))
        {
            static const std::string bkupmsg = "This plugin contains cheats that may break your save.\nWhile this is very unlikely to occur, it is still important to make a save backup.\n\nWould you like to backup your save file?";
            static const std::string bkupmsgskip = "Would you like to skip the Save Backup\nmessage in the future?";

            if ((MessageBox(bkupmsg, DialogType::DialogYesNo)).SetClear(ClearScreen::Both)())
            {
                std::string filename = "garden_plus";
                File    file;
                time_t rawtime;
                struct tm * timeinfo;
                char timestamp[80];

                // Get timestamp for filename
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                strftime(timestamp, 80, " [%F_%I-%M%p]", timeinfo); //String Format: Date (YYYY-MM-DD), Hour (12h format), minute, am/pm

                filename += timestamp;
                filename += ".dat";
                if (!File::Exists(filename))
                {
                    int mode = File::READ | File::WRITE | File::CREATE;
                    if (File::Open(file, filename, mode) == 0)
                    {
                        u32 res = file.Dump(Game::Garden, 0x89B00);

                        if (res != 0)
                            MessageBox(Utils::Format("Backup Save failed!\nError Code: %08X", res)).SetClear(ClearScreen::Both)();
                    }
                    else
                        MessageBox("Error: Couldn't create the backup!").SetClear(ClearScreen::Both)();
                }
                else
                    MessageBox("Save backup somehow already exists!")();
                file.Flush();
                file.Close();
            }

            if ((MessageBox(bkupmsgskip, DialogType::DialogYesNo)).SetClear(ClearScreen::Both)())
                flags |= SKIP_SAVE;
        }
        file.Rewind();
        file.Write((void *)&flags, sizeof(u32));
        file.Flush();
        file.Close();
    }
}
