#include "cheats.hpp"

namespace CTRPluginFramework
{
    //Appearance
    void    ChangeGender(void)
    {
        Keyboard  keyboard("Which gender would you like?");
        static std::vector<std::string> list = 
        {
            "Male", //there are only two genders, folks
            "Female"
        };
        keyboard.Populate(list);

        int userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            Player::GetInstance()->WriteByte(0x55BA, userChoice);
            AppearanceMod();
        }
        else
        {
            OSD::Notify("You must load your save to use this cheat!");
        }
    }

    void    ChangeHair(void)
    {
        Keyboard  keyboard("Which hairstyle would you like?");
        static std::vector<std::string> list = 
        {
            "Male 01", 
            "Male 02",
            "Male 03", 
            "Male 04",
            "Male 05", 
            "Male 06",
            "Male 07", 
            "Male 08", 
            "Male 09",
            "Male 10", 
            "Male 11",
            "Male 12", 
            "Male 13",
            "Male 14", 
            "Male 15", 
            "Male 16",
            "Messy Hair", 
            "Female 01", 
            "Female 02",
            "Female 03", 
            "Female 04",
            "Female 05", 
            "Female 06",
            "Female 07", 
            "Female 08", 
            "Female 09",
            "Female 10", 
            "Female 11",
            "Female 12", 
            "Female 13",
            "Female 14", 
            "Female 15", 
            "Female 16"
        };

        keyboard.Populate(list);

        u8 userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            Player::GetInstance()->WriteByte(0x4, userChoice);
            AppearanceMod();
        }       
    }
    
    void    ChangeFace(void) //Faces don't have seperate IDs for genders
    {
        Keyboard  keyboard("Which face would you like?");
        static std::vector<std::string> list = 
        {
            "Face 01", 
            "Face 02",
            "Face 03", 
            "Face 04",
            "Face 05", 
            "Face 06",
            "Face 07", 
            "Face 08", 
            "Face 09",
            "Face 10", 
            "Face 11"
        };

        keyboard.Populate(list);

        u8 userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            Player::GetInstance()->WriteByte(0x6, userChoice);
            AppearanceMod();
        }       
    }
    
    void    ChangeHairCol(void)
    {
        Keyboard  keyboard("Which hair colour would you like?");
        static std::vector<std::string> list = 
        {
            "Dark brown",
            "Light brown",
            "Orange", 
            "Light blue",
            "Gold", 
            "Light green",
            "Pink", 
            "White", 
            "Black",
            "Auburn", 
            "Red",
            "Dark blue", 
            "Blonde",
            "Dark green", 
            "Light purple", 
            "Ash brown"
        };

        keyboard.Populate(list);

        u8 userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            Player::GetInstance()->WriteByte(0x5, userChoice);
            AppearanceMod();
        }       
    }
    
    void    ChangeEyeCol(void) 
    {
        Keyboard  keyboard("Which eye colour would you like?");
        static std::vector<std::string> list = 
        {
            "Black", //00
            "Orange", //01
            "Green", //02
            "Grey", //03
            "Blue", //04
            "Lighter Blue" //05
        };

        keyboard.Populate(list);

        u8 userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            Player::GetInstance()->WriteByte(0x7, userChoice);
            AppearanceMod();
        }       
    }

    void    ChangeTan(void)
    {
        Keyboard  keyboard("Which tan level would you like?");
        static std::vector<std::string> list = 
        {
            "Level 01 (Pale)", 
            "Level 02",
            "Level 03", 
            "Level 04",
            "Level 05", 
            "Level 06",
            "Level 07", 
            "Level 08", 
            "Level 09",
            "Level 10", 
            "Level 11",
            "Level 12", 
            "Level 13", 
            "Level 14",
            "Level 15 (Dark)"
        };

        keyboard.Populate(list);

        u8 userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            Player::GetInstance()->WriteByte(0x8, userChoice);
            AppearanceMod();
        }       
    }
    
    //Apparel
    void    ChangeTop(void)
    {
        u32 output;
        u16 underwet;
        // New keyboard, hint being:
        Keyboard  keyboard("Which top would you like ?");
        // Add the function to check the input entered by the user
        keyboard.SetCompareCallback([](const void *input, std::string &error)
            {
                // Cast the input into the appropriate type (must match the type provided to Open)
                u32 in = *static_cast<const u32 *>(input);

                // Check the value
                if (in < 0x2495 || in > 0x26F5)
                {
                    error = "The value must be between " + Hex((u16)0x2495) + " - "  + Hex((u16)0x26F5);
                    // Return that the value isn't valid
                    return (false);
                }

                // The value is valid
                return (true);
            });

        // If the function return -1, then the user canceled the keyboard, so do nothing 
        if (keyboard.Open(output) != -1)
        {
            if (output >= 0x26ED && output <= 0x26F5) //Check if ID is a Wetsuit
            {
                Player::GetInstance()->Read16(0x12, underwet); //Get current top
                if (underwet < 0x26ED) //If the current top isn't a wetsuit
                {
                Player::GetInstance()->Write16(0x16, underwet); //Put top 'under' the wetsuit so it'll appear if user manually takes off wetsuit
                }
            }
            
            Player::GetInstance()->Write16(0x12, output);
            ApparelMod();
        }     
    }
    
    void    ChangeHat(void)
    {
        u32 output;
        Keyboard  keyboard("Which hat would you like ?");
        keyboard.SetCompareCallback([](const void *input, std::string &error)
            {
                u32 in = *static_cast<const u32 *>(input);

                if (in < 0x280B || in > 0x28F3)
                {
                    error = "The value must be between " + Hex((u16)0x280B) + " - "  + Hex((u16)0x28F3);
                    return (false);
                }
                return (true);
            });

        if (keyboard.Open(output) != -1)
        {
            Player::GetInstance()->Write16(0xA, output);
            ApparelMod();
        }     
    }
    
    void    ChangeAccessory(void)
    {
        u32 output;
        Keyboard  keyboard("Which accessory would you like ?");
        keyboard.SetCompareCallback([](const void *input, std::string &error)
            {
                u32 in = *static_cast<const u32 *>(input);

                if (in < 0x28F5 || in > 0x295B)
                {
                    error = "The value must be between " + Hex((u16)0x28F5) + " - "  + Hex((u16)0x295B);
                    return (false);
                }
                return (true);
            });

        if (keyboard.Open(output) != -1)
        {
            Player::GetInstance()->Write16(0xE, output);
            ApparelMod();
        }     
    }
    
    
    void    ChangePants(void)
    {
        u32 output;
        Keyboard  keyboard("Which pants would you like ?");
        keyboard.SetCompareCallback([](const void *input, std::string &error)
            {
                u32 in = *static_cast<const u32 *>(input);

                if (in < 0x26F8 || in > 0x2776)
                {
                    error = "The value must be between " + Hex((u16)0x26F8) + " - "  + Hex((u16)0x2776);
                    return (false);
                }
                return (true);
            });

        if (keyboard.Open(output) != -1)
        {
            Player::GetInstance()->Write16(0x1A, output);
            ApparelMod();
        }     
    }
    
    void    ChangeSocks(void)
    {
        u32 output;
        Keyboard  keyboard("Which socks would you like ?");
        keyboard.SetCompareCallback([](const void *input, std::string &error)
            {
                u32 in = *static_cast<const u32 *>(input);

                if (in < 0x2777 || in > 0x279E)
                {
                    error = "The value must be between " + Hex((u16)0x2777) + " - "  + Hex((u16)0x279E);
                    return (false);
                }
                return (true);
            });

        if (keyboard.Open(output) != -1)
        {
            Player::GetInstance()->Write16(0x1E, output);
            ApparelMod();
        }     
    }
    
    void    ChangeShoes(void)
    {
        u32 output;
        Keyboard  keyboard("Which shoes would you like ?");
        keyboard.SetCompareCallback([](const void *input, std::string &error)
            {
                u32 in = *static_cast<const u32 *>(input);

                if (in < 0x279F || in > 0x27E5)
                {
                    error = "The value must be between " + Hex((u16)0x279F) + " - "  + Hex((u16)0x27E5);
                    return (false);
                }
                return (true);
            });

        if (keyboard.Open(output) != -1)
        {
            Player::GetInstance()->Write16(0x1E, output);
            ApparelMod();
        }  
    }
    
    //ApparelMod Function
    void    ApparelMod(void)
    {
        Keyboard  keyboard("Choose what to edit");
        static std::vector<std::string> list = 
        {
            "Hat",
            "Accessory",
            "Top/Dress/Wetsuit",
            "Pants/Skirt",
            "Socks",
            "Shoes",
            "Return to appearance menu..."
        };
        keyboard.Populate(list);
        int userChoice = keyboard.Open();

        switch (userChoice)
        {
            case 0:
                ChangeHat();
                break;
            case 1:
                ChangeAccessory();
                break;
            case 2:
                ChangeTop();
                break;
            case 3:
                ChangePants();
                break;
            case 4:
                ChangeSocks();
                break;
            case 5:
                ChangeShoes();
                break;
            case 6:
                AppearanceMod();
                break;
            default:
                break;
        }

    }
    
    //Main appearance mod function
        void    AppearanceMod(void)
    {
        Keyboard  keyboard("Choose what to edit");
        static std::vector<std::string> list = 
        {
            "Gender",
            "Hair",
            "Hair Colour",
            "Face",
            "Eye Colour",
            "Tan",
            "Apparel"
        };

        keyboard.Populate(list);
        int userChoice = keyboard.Open();

        switch (userChoice)
        {
            case 0:
                ChangeGender();
                break;
            case 1:
                ChangeHair();
                break;
            case 2:
                ChangeHairCol();
                break;
            case 3:
                ChangeFace();
                break;
            case 4:
                ChangeEyeCol();
                break;
            case 5:
                ChangeTan();
                break;
            case 6:
                ApparelMod();
                break;
            default:
                break;
        }
    }
}