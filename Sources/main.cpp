#include "cheats.hpp"

namespace CTRPluginFramework
{
    // This function is called on the plugin starts, before main
    void    PatchProcess(void)
    {
    }
    
    #define MAJOR_VERSION       4
    #define MINOR_VERSION       0
    #define REVISION_VERSION    25
    #define STRINGIFY(x)        #x
    #define TOSTRING(x)         STRINGIFY(x)
    #define STRING_VERSION      "[" TOSTRING(MAJOR_VERSION) "." TOSTRING(MINOR_VERSION) "." TOSTRING(REVISION_VERSION) "]"
    
    extern Region               g_region;
    static const std::string    unsupportedVersion = "Your ACNL version isn't\nsupported!\nMake sure you have the\n1.5 update installed!";
    static const std::string    unsupportedGame = "Error\nGame not supported !\nVisit discord for support.";
    static const std::string    gameName = "Animal Crossing New Leaf";
    static const std::string    developer = "RyDog";
    static const std::string    credits =
        "Plugin Version: " STRING_VERSION  "\n"
        "Creator: " + developer + "\n"
        "\n"
        "Special thanks to:\n"
        "Nanquitas\n"
        "Slattz\n"
        "Mega Mew\n"
        "Scotline\n"
        "and others :)";    

    
    int     main(void)
    {
        PluginMenu  *m = new PluginMenu(gameName, MAJOR_VERSION, MINOR_VERSION, REVISION_VERSION, credits);
        PluginMenu  &menu = *m;
        u64         tid = Process::GetTitleID();
        u16         ver = Process::GetVersion();

        // Get current game's region
        if (tid == 0x0004000000086300)
        {
            if (ver != 6192)
                return (MessageBox(unsupportedVersion)());
            g_region = USA;
        }           
        else if (tid == 0x0004000000086400)
        {
            if (ver != 6176)
                return (MessageBox(unsupportedVersion)());
            g_region = EUR;
        }
            
        else if (tid == 0x0004000000086200)
        {
            if (ver != 6272)
                return (MessageBox(unsupportedVersion)());
            g_region = JAP;
        }           
        else
            return (MessageBox(unsupportedGame)());

        // Initialize game's addresses based on region
        Game::Initialize();
        // Initialize player
        Player::GetInstance();

        /*
        ** Garden
        ********************/

        MenuFolder* folder = new MenuFolder("Save File Codes");

        folder->Append(new MenuEntry("Set name to...", nullptr, SetNameTo));
        folder->Append(new MenuEntry("Save Dumper", nullptr, GardenDumper));
        folder->Append(new MenuEntry("Save Restore", nullptr, GardenRestore));
        folder->Append(new MenuEntry("Inject TCP Picture", InjectTCP));
        folder->Append(new MenuEntry("Change Town Fruit to...", nullptr, ChangeNativeFruit, "Special thanks to Mega Mew and Scotline"));
        folder->Append(new MenuEntry("Change Town Grass to...", nullptr, ChangeGrass, "Special thanks to Mega Mew and Scotline"));
        folder->Append(new MenuEntry("Real Time Building Placer", BuildingPlacer));

        menu.Append(folder);

        /*
        ** Movement
        ********************/

        folder = new MenuFolder("Movement Codes");

        folder->Append(new MenuEntry("Coordinates Modifier", CoordinateModifier, "Press \uE000 and D Pad in the direction that you want to move."));
        folder->Append(new MenuEntry("Touch Coordinates", TouchCoordinates, "Touch the map to teleport your character there."));
        folder->Append(new MenuEntry("Teleport", Teleporter, "Press \uE001 and \uE079 to save your location, \uE001 and \uE07A to teleport back to the location. Use \uE052 or \uE053 to use multiple locations!"));
        folder->Append(new MenuEntry("Walk Over Things", WalkOverThings, "Press \uE052 and \uE079 to enable walking through stuff, \uE052 and \uE07A to disable walking through stuff."));
        folder->Append(new MenuEntry("Speed Hack", SpeedHack, SpeedHackEditor, "Credits to Mega Mew for this cheat"));
        folder->Append(new MenuEntry("Moon Jump", MoonJump, "Press \uE052 and \uE079 to go higher and \uE07A to go lower."));
        
        menu.Append(folder);

        folder = new MenuFolder("Main Street Codes");

        folder->Append(new MenuEntry("Nookling Upgrades", nullptr, NooklingKeyboard));
        folder->Append(new MenuEntry("Fill out Catalog", FillCatalog));
        folder->Append(new MenuEntry("Fill out Main Street", FillMainStreet, "Unlocks all the Main Street buildings except Leif + Nooklings"));
        menu.Append(folder);

        /*
        ** Inventory
        ********************/

        folder = new MenuFolder("Inventory");

        folder->Append(new MenuEntry("Text to Item", Text2Item, "Press " FONT_X " and " FONT_DR " to open the keyboard to enter in the ID you want to recieve."));
        folder->Append(new MenuEntry("Duplicate", Duplication, "Press " FONT_R " to duplicate the item that is slot 01 to slot 02."));
        folder->Append(new MenuEntry("Show names of buried items", ShowBuriedItems));
        folder->Append(new MenuEntry("Pick up buried items", PickBuriedItems));
        folder->Append(new MenuEntry("Set bells", nullptr, SetBells));
        folder->Append(new MenuEntry("Inventory box extender", ExtendedInventoryBox, "This allows you to create 10 additionals boxes to store your items.\nHold Start 1 second to choose which one to open."));
        folder->Append(new MenuEntry("Fossil Inspector", GenerateFossils, "Press " FONT_X " and " FONT_A " to process all fossils\nas if you talked to Blathers"));

        menu.Append(folder);

        /*
        ** Environment
        ********************/

        folder = new MenuFolder("Enviroment");

        /* Subfolder of Enviroment
        ** These codes only execute when R+A is pressed, so I only want 1 enabled. 
        ** I use the radio group parameter to prevent multiple from being enabled.
        *****************************************************************************/
        MenuFolder  *ra = new MenuFolder("R + A Codes");

        ra->Append(new MenuEntry(1, "Remove All Items", RemoveAllItems, "Press " FONT_R " and " FONT_A " to execute... Beware as there is no going back if you save."));
        ra->Append(new MenuEntry(1, "Remove All Weeds", RemoveAllWeeds, "Press " FONT_R " and " FONT_A " to execute."));
        ra->Append(new MenuEntry(1, "Water All Flowers", WaterAllFlowers, "Press " FONT_R " and " FONT_A "to execute."));
        ra->Append(new MenuEntry(1, "Fill Grass", FillGrass, "Press " FONT_R " and " FONT_A " to fill your town with grass.\nPlease note that bald spots will respawn on the next day."));
        ra->Append(new MenuEntry(1, "Destroy Grass", DestroyGrass, "Press " FONT_R " and " FONT_A " to destroy all the grass in your town to make a desert wasteland."));
        
        folder->Append(ra);
        folder->Append(new MenuEntry("Real Time World Edit", WorldEdit, "Press " FONT_R " and " FONT_DL " to open the keyboard to store the item. " FONT_R " and " FONT_DU " to store the item that you're standing on. And " FONT_R " + " FONT_DD " to write the item to the place that you're standing on."));

        menu.Append(folder);

        /*
        ** Time Travel
        ********************/

        folder = new MenuFolder("Time Travel Codes");

        folder->Append(new MenuEntry("Time Travel", TimeTravel, "Press either " FONT_R " or " FONT_B " and " FONT_DR " to travel forward or " FONT_DL " to retwind time or " FONT_B " and " FONT_DD " to set ingame time back to your 3DS's clock."));
        folder->Append(new MenuEntry("Time Machine", TimeMachine, "Press " FONT_Y " and " FONT_DR " to start time traveling."));
        
        menu.Append(folder);

        folder = new MenuFolder("Unlock Codes");

        folder->Append(new MenuEntry("100% Mayor permit", Permit, "Special thanks to Slattz"));
        folder->Append(new MenuEntry("Unlock all PWPs", PWPUnlock, "Special thanks to Mega Mew and Scotline"));
        folder->Append(new MenuEntry("Fill out encyclopedia", Encyclopedia, "Special thanks to Mega Mew and Scotline"));
        folder->Append(new MenuEntry("Fill out emoticons", Emoticons, "Special thanks to Mega Mew and Scotline"));
        folder->Append(new MenuEntry("Fill out K.K. Songs", Songs, "Special thanks to Mega Mew and Scotline"));

        menu.Append(folder);

        /*
        ** Misc.
        ********************/

        folder = new MenuFolder("Misc.");

        folder->Append(new MenuEntry("Ghost Mode", GhostMode));
        folder->Append(new MenuEntry("Camera Mod", CameraMod));
        folder->Append(new MenuEntry("Custom Symbols Keyboard", CustomKB, "This turns all the symbols in the keyboard into Nintendo symbols.\nExample: \uE00F\uE004\uE000\uE00E\uE00E\uE04B"));
        folder->Append(new MenuEntry("Keyboard Extender", KeyboardExtender, "This extends the max characters that you can type into chat to 54 characters. Now you can type short stories into chat :)"));
        folder->Append(new MenuEntry("Fast Game Speed", FastGameSpeed, "This makes things in the game speed up. This might make your game crash.\nCredits to Scotline and Mega Mew for this cheat"));
        folder->Append(new MenuEntry("Item Form Changer", ItemFormChanger, ItemFormEditor, "This changes how your character holds tools"));
        folder->Append(new MenuEntry("Item Effect Changer", ItemEffectChanger, ItemEffectEditor, "This changes how your character uses items."));
        folder->Append(new MenuEntry("Special NPC Changer", AnimalChanger, AnimalChangerKeyboard, "This changes all the special NPC's like K.K. to what you choose."));
        folder->Append(new MenuEntry("Access Catalog & Storage Anywhere", StorageEverywhere, "Press L or R to access your storage, and press L+R to access the catalog while switching emoticon tabs\nSpecial thanks Mega Mew and Scotline for this cheat :)"));
        folder->Append(new MenuEntry("Faint", Faint, "Press R + A to make your character pass out like he got bit by a scorpion!"));
        
        menu.Append(folder);

        /*
        ** Callbacks
        ********************/

        // Add Text2Cheat to plugin's main loop
        menu.Callback([] { Sleep(Milliseconds(1)); });
        menu.Callback(CheatsKeyboard);
        menu.Callback(PlayerUpdateCallback);
        menu.Callback(MiniGame);

        // Launch menu and mainloop
        menu.Run();

        // Exit plugin
        return (0);
    }
}
