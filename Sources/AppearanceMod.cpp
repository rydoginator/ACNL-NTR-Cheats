#include "cheats.hpp"
#include "Helpers/QuickMenu.hpp"

namespace CTRPluginFramework
{
    std::vector<QuickMenuItem*>    ChangeHairSubMenu(void)
    {
        static const StringVector list = 
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

        auto    changeHair = [](void *hairType) {Player::GetInstance()->WriteByte(0x4, (u32)hairType); };
        std::vector<QuickMenuItem*>     options;

        for (int i = 0; i < list.size(); i++)
            options.push_back(new QuickMenuEntry(list[i], changeHair, (void *)i));

        return (options);
    }
    
    std::vector<QuickMenuItem *>    ChangeFaceSubMenu(void) //Faces don't have seperate IDs for genders
    {
        static const StringVector list = 
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

        auto    changeFace = [](void *faceType) {Player::GetInstance()->WriteByte(0x6, (u32)faceType); };
        std::vector<QuickMenuItem*>     options;

        for (int i = 0; i < list.size(); i++)
            options.push_back(new QuickMenuEntry(list[i], changeFace, (void *)i));

        return (options);
    }
    
    std::vector<QuickMenuItem *>    ChangeHairColorSubMenu(void)
    {
        static const StringVector list = 
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

        auto    changeColor = [](void *colorType) {Player::GetInstance()->WriteByte(0x5, (u32)colorType); };
        std::vector<QuickMenuItem*>     options;

        for (int i = 0; i < list.size(); i++)
            options.push_back(new QuickMenuEntry(list[i], changeColor, (void *)i));

        return (options);
    }
    
    std::vector<QuickMenuItem *>    ChangeEyeColorSubMenu(void) 
    {
        static const StringVector list = 
        {
            "Black", //00
            "Orange", //01
            "Green", //02
            "Grey", //03
            "Blue", //04
            "Lighter Blue" //05
        };

        auto    changeColor = [](void *colorType) {Player::GetInstance()->WriteByte(0x7, (u32)colorType); };
        std::vector<QuickMenuItem*>     options;

        for (int i = 0; i < list.size(); i++)
            options.push_back(new QuickMenuEntry(list[i], changeColor, (void *)i));

        return (options);
    }

    std::vector<QuickMenuItem *>    ChangeTanSubMenu(void)
    {
        static const StringVector list = 
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

        auto    changeTan = [](void *tanType) {Player::GetInstance()->WriteByte(0x8, (u32)tanType); };
        std::vector<QuickMenuItem*>     options;

        for (int i = 0; i < list.size(); i++)
            options.push_back(new QuickMenuEntry(list[i], changeTan, (void *)i));

        return (options);
    }
    
    //Apparel
    void    ChangeTop(void)
    {
        u32 output;
        u16 underwet;
        // New keyboard, hint being:
        Keyboard  keyboard;
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
                    Player::GetInstance()->Write16(0x16, underwet); //Put top 'under' the wetsuit so it'll appear if user manually takes off wetsuit
            }
            
            Player::GetInstance()->Write16(0x12, output);
        }     
    }
    
    void    ChangeHat(void)
    {
        u32 output;
        Keyboard  keyboard;
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
            Player::GetInstance()->Write16(0xA, output);
    }
    
    void    ChangeAccessory(void)
    {
        u32 output;
        Keyboard  keyboard;
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
            Player::GetInstance()->Write16(0xE, output);
    }
    
    
    void    ChangePants(void)
    {
        u32 output;
        Keyboard  keyboard;
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
            Player::GetInstance()->Write16(0x1A, output);
    }
    
    void    ChangeSocks(void)
    {
        u32 output;
        Keyboard  keyboard;
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
            Player::GetInstance()->Write16(0x1E, output);
    }
    
    void    ChangeShoes(void)
    {
        u32 output;
        Keyboard  keyboard;
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
            Player::GetInstance()->Write16(0x1E, output);
    }

    void    AppearanceModifierMenu(void)
    {
        QuickMenu   &quickMenu = QuickMenu::GetInstance();
        auto        changeGender = [](void *gender) { Player::GetInstance()->WriteByte(0x55BA, (u32)gender); };

        quickMenu += new QuickMenuSubMenu("Appearance Modifier",
        {
            // Gender submenu
            new QuickMenuSubMenu("Gender",
            {
                new QuickMenuEntry("Male", changeGender, (void *)0),
                new QuickMenuEntry("Female", changeGender, (void *)1)
            }),
            
            new QuickMenuSubMenu("Hair", ChangeHairSubMenu()),
            new QuickMenuSubMenu("Hair Color", ChangeHairColorSubMenu()),
            new QuickMenuSubMenu("Face", ChangeFaceSubMenu()),
            new QuickMenuSubMenu("Eye Color", ChangeEyeColorSubMenu()),
            new QuickMenuSubMenu("Tan", ChangeTanSubMenu()),
            new QuickMenuSubMenu("Apparel",
            {
                new QuickMenuEntry("Hat", ChangeHat),
                new QuickMenuEntry("Accessory", ChangeAccessory),
                new QuickMenuEntry("Top/Dress/Wetsuit", ChangeTop),
                new QuickMenuEntry("Pants/Skirt", ChangePants),
                new QuickMenuEntry("Socks", ChangeSocks),
                new QuickMenuEntry("Shoes", ChangeShoes)
            })
        });
    }
}
