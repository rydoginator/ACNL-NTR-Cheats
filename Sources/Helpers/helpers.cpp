#include "cheats.hpp"
#include "CTRPluginFramework/Utils/Utils.hpp"

#include <ctime>
#include <cstring>

namespace CTRPluginFramework
{
    //Credit to SciresM for this code! :)
    u32     DecryptACNLMoney(u64 money)
    {
        // Unpack 64-bit value into (u32, u16, u8, u8) values.
        u32 enc = (money & 0xFFFFFFFF);
        u16 adjust = ((money >> 32) & 0xFFFF);
        u8  shift_val = ((money >> 48) & 0xFF);
        u8  chk = ((money >> 56) & 0xFF);

        // Validate 8-bit checksum
        if ((((enc >> 0) + (enc >> 8) + (enc >> 16) + (enc >> 24) + 0xBA) & 0xFF) != chk) return 0;
        
        u8  left_shift = ((0x1C - shift_val) & 0xFF);
        u8  right_shift = 0x20 - left_shift;

        // Handle error case: Invalid shift value.
        if (left_shift >= 0x20)
        {
            return 0 + (enc << right_shift) - (adjust + 0x8F187432);
        }

        // This case should occur for all game-generated values.
        return (enc << left_shift) + (enc >> right_shift) - (adjust + 0x8F187432);
    }

    u64     EncryptACNLMoney(int dec)
    {
        // Make a new RNG
        u16 adjust = Utils::Random(0, 0x10000);
        u8  shift_val = Utils::Random(0, 0x1A);

        // Encipher value
        u32 enc = dec + adjust + 0x8F187432;
        enc = (enc >> (0x1C - shift_val)) + (enc << (shift_val + 4));

        // Calculate Checksum
        u8  chk = (((enc >> 0) + (enc >> 8) + (enc >> 16) + (enc >> 24) + 0xBA) & 0xFF);

        // Pack result
        return ((u64)enc << 0) | ((u64)adjust << 32) | ((u64)shift_val << 48) | ((u64)chk << 56);
    }
    
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
                        MessageBox(Format("Skip 'T&C' message failed!\nError Code: %08X", res))();
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
                strftime (timestamp, 80, " [%F_%I-%M%p]", timeinfo); //String Format: Date (YYYY-MM-DD), Hour (12h format), minute, am/pm
            
                filename += timestamp;
                filename += ".dat";
                if (!File::Exists(filename))
                {
                    int mode = File::READ | File::WRITE | File::CREATE;
                    if (File::Open(file, filename, mode) == 0)
                    {
                        u32 res = file.Dump(Game::Garden, 0x89B00);
                    
                        if (res != 0)
                        MessageBox(Format("Backup Save failed!\nError Code: %08X", res))();
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
                    MessageBox(Format("Skip 'Backup Save' message failed!\nError Code: %08X", res))();
                }
                file.Close();
            }
        }
    }

    u8       *memsearch(u8 *startPos, const void *pattern, u32 size, u32 patternSize)
    {
        const u8 *patternc = (const u8 *)pattern;
        u32 table[256];

        //Preprocessing
        for (u32 i = 0; i < 256; i++)
            table[i] = patternSize;
        for (u32 i = 0; i < patternSize - 1; i++)
            table[patternc[i]] = patternSize - i - 1;

        //Searching
        u32 j = 0;
        while (j <= size - patternSize)
        {
            u8 c = startPos[j + patternSize - 1];
            if (patternc[patternSize - 1] == c && memcmp(pattern, startPos + j, patternSize - 1) == 0)
                return startPos + j;
            j += table[c];
        }

        return nullptr;
    }
}
