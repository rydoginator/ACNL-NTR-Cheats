#include "CTRPluginFramework.hpp"
#include "Game.hpp"
#include <ctime>


namespace CTRPluginFramework
{
    void    StartMsg(void) //Startup message for plugin
    {
        if (!File::Exists("T&C"))
        {
            static const std::string TC = "Terms & Conditions:\nThis software is provided free of charge.\nIf you have paid for this plugin,\nimmediately ask for a refund.\nThis software is provided 'as-is', without any express or implied warranty.\nIn no event will the authors be held\nliable for any damages arising from the\nuse of this software.\n\nDo you accept the Terms & Conditions?";

            static const std::string TCskip = "Would you like to skip the\nTerms & Conditions message\nin the future?\nPlease note that this means you\nunderstand and completely agree to\nthe Terms & Conditions.";

            if ((MessageBox(TC, DialogType::DialogYesNo))()) //If Yes is picked in T&C MessageBox
            {
                Sleep(Seconds(1.5f)); //Let the first MessageBox disappear to avoid a glitchy screen
                if ((MessageBox(TCskip, DialogType::DialogYesNo))())
                {
                    std::string filename = "T&C";
                    File    file;

                    if (File::Exists(filename))
                        file.Remove(filename);

                    int mode = File::READ | File::WRITE | File::CREATE;
                    if (File::Open(file, filename, mode) == 0)
                    {
                        u32 res = file.WriteLine(TC);
                        if (res != 0)
                            MessageBox(Utils::Format("Skip 'T&C' message failed!\nError Code: %08X", res))();
                    }
                    file.Close();
                }
            }
            else
            {
                MessageBox("You must accept the Terms & Conditions to use this plugin.")();
                abort();
            }
        }

        if (!File::Exists("skipsavemsg"))
        {
            static const std::string bkupmsg = "As 4.0+ is a rewrite of this plugin, some save breaking bugs may have been\nintroduced along the way.\n\nWould you like to backup your save file?";

            static const std::string bkupmsgskip = "Would you like to skip the Save Backup\nmessage in the future?";

            if ((MessageBox(bkupmsg, DialogType::DialogYesNo))())
            {
                std::string filename = "garden_plus";
                File    file;
                time_t rawtime;
                struct tm * timeinfo;
                char timestamp[80];

                //Get timestamp for filename
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
                            MessageBox(Utils::Format("Backup Save failed!\nError Code: %08X", res))();
                    }
                    else
                        MessageBox("Error: Couldn't create the backup!")();
                }
                else
                    MessageBox("Save backup somehow already exists!")();

                file.Close();
            }
            Sleep(Seconds(1.5f)); //Let the first MessageBox disappear to avoid a glitchy screen
            if ((MessageBox(bkupmsgskip, DialogType::DialogYesNo))())
            {
                std::string filename = "skipsavemsg";
                File    file;

                if (File::Exists(filename))
                    file.Remove(filename);

                int mode = File::READ | File::WRITE | File::CREATE;
                if (File::Open(file, filename, mode) == 0)
                {
                    u32 res = file.WriteLine(bkupmsg);
                    if (res != 0)
                        MessageBox(Utils::Format("Skip 'Backup Save' message failed!\nError Code: %08X", res))();
                }
                file.Close();
            }
        }
    }
}