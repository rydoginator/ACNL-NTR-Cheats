#include "cheats.hpp"
#include "ctrulib\services\cfgu.h"
#include "Helpers/Hook.hpp"
#include <cstring>

extern "C" void APT_Hook(void);
volatile u32    g_homeBtnWasPressed = 0;
volatile u32    g_aptHookReturnAddress = 0;

namespace CTRPluginFramework
{
    // This function is called on the plugin starts, before main
    void    PatchProcess(void)
    {
    }
    
    #define MAJOR_VERSION       4
    #define MINOR_VERSION       0
    #define REVISION_VERSION    0
    #define STRINGIFY(x)        #x
    #define TOSTRING(x)         STRINGIFY(x)
    #define STRING_VERSION      "[" TOSTRING(MAJOR_VERSION) "." TOSTRING(MINOR_VERSION) "." TOSTRING(REVISION_VERSION) " Beta 2" "]"
    static Hook                 g_aptHook;
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

    u8  *memsearch(u8 *startPos, const void *pattern, u32 size, u32 patternSize)
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

    void    InstallAPTHook(void)
    {
        static const u8     aptHomeButtonPattern[] =
        {
            0x00, 0xF0, 0x20, 0xE3, // NOP
            0xA1, 0x1A, 0x00, 0xEB, // BL   #0x6A8C
            0x00, 0x00, 0x50, 0xE3, // CMP  R0, #0
            0x00, 0xF0, 0x20, 0xE3, // NOP
            0x03, 0x00, 0x00, 0x1A, // BNE  #0x14
            0x00, 0x00, 0xDD, 0xE5, // LDRB R0, [SP]
            0x01, 0x00, 0x50, 0xE3, // CMP  R0, #1
            0x02, 0x00, 0xA0, 0x13, // MOVNE R0, #2
            0x9E, 0x1A, 0x00, 0xEB, // BL   #0x6A80
            0x04, 0x10, 0x94, 0xE5, // LDR  R1, [R4, #4]
            0x00, 0x00, 0x51, 0xE3, // CMP  R1, #0
            0x03, 0x00, 0x00, 0x0A  // BEQ  #0x14
        };

        u8 *targetAddr = memsearch((u8 *)0x00100000, aptHomeButtonPattern, Process::GetTextSize(), sizeof(aptHomeButtonPattern));

        if (targetAddr)
        {
            u32 address = (u32)targetAddr + 4;

            g_aptHookReturnAddress = address + 0x170;
            g_aptHook.Initialize(address, (u32)APT_Hook);
            g_aptHook.Enable();
        }
        else
            OSD::Notify("Error: APT Hook couldn't be made !");
    }
    
    int     main(void)
    {
        // Install APT Hook to block home button
        InstallAPTHook();

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
        StartMsg(); //T&C Message & Save Backup Message

        /*
        ** Garden
        ********************/

        MenuFolder* folder = new MenuFolder("Save File Codes");

        folder->Append(new MenuEntry("Set name to...", nullptr, SetNameTo));
        folder->Append(new MenuEntry("Save Dumper", nullptr, GardenDumper, "Select the keyboard icon to start dumping your save file."));
        folder->Append(new MenuEntry("Save Restore", nullptr, GardenRestore, "Select this icon to open file picker to restore from your previously dumped saves"));
        folder->Append(new MenuEntry("Change Town Fruit to...", nullptr, ChangeNativeFruit, "Special thanks to Mega Mew and Scotline"));
        folder->Append(new MenuEntry("Change Town Grass to...", nullptr, ChangeGrass, "Special thanks to Mega Mew and Scotline"));
        folder->Append(new MenuEntry("Real Time Building Placer", BuildingPlacer, "Press R + D Pad down to place a building by ID directly where you are standing\nPress R + D pad up to place a building where you are standing."));

        menu.Append(folder);

        /*
        ** Movement
        ********************/

        folder = new MenuFolder("Movement Codes");

        folder->Append(new MenuEntry("Coordinates Modifier", CoordinateModifier, "Press \uE000 and D Pad in the direction that you want to move."));
        folder->Append(new MenuEntry("Touch Coordinates", TouchCoordinates, "Touch the map to teleport your character there."));
        folder->Append(new MenuEntry("Teleport", Teleporter, "Press \uE001 and \uE079 to save your location, \uE001 and \uE07A to teleport back to the location. Use \uE052 or \uE053 to use multiple locations!"));
        folder->Append(new MenuEntry("Walk Over Things", WalkOverThings, "Press \uE052 and \uE079 to enable walking through stuff, \uE052 and \uE07A to disable walking through stuff."));
        folder->Append(new MenuEntry("Speed Hack", SpeedHack, SpeedHackEditor, "Change how fast you want to go with the keyboard icon\nCredits to Mega Mew for this cheat"));
        folder->Append(new MenuEntry("Moon Jump", MoonJump, "Press \uE052 and \uE079 to go higher and \uE07A to go lower."));
        
        menu.Append(folder);

        folder = new MenuFolder("Main Street Codes");

        folder->Append(new MenuEntry("Nookling Upgrades", nullptr, NooklingKeyboard, "Press the keyboard icon to change which upgrade the Nooklings have"));
        folder->Append(new MenuEntry("Fill out Catalog", FillCatalog, "Fill out the catalog in Nookling's shop"));
        folder->Append(new MenuEntry("Fill out Main Street", FillMainStreet, "Unlocks all the Main Street buildings except Leif + Nooklings"));
        folder->Append(new MenuEntry("Catalog to Pockets", CatalogToPockets, "Press " FONT_L " and " FONT_A " while in the catalog to send the item directly to your pockets!"));
        menu.Append(folder);

        /*
        ** Inventory
        ********************/

        folder = new MenuFolder("Inventory");

        folder->Append(new MenuEntry("Text to Item", Text2Item, "Press " FONT_X " and " FONT_DR " to open the keyboard to enter in the ID you want to recieve."));
        folder->Append(new MenuEntry("Duplicate", Duplication, "Press " FONT_R " to duplicate the item that is slot 01 to slot 02."));
        folder->Append(new MenuEntry("Show names of buried items", ShowBuriedItems, "This allows you to view what is buried underground in the little thought bubble above your head\nWarning: this is a heavy cheat, so it might cause slowdown."));
        folder->Append(new MenuEntry("Pick up buried items", PickBuriedItems, "Press " FONT_Y " to pick up any buried items.\nWarning: this is a heavy cheat, so it might cause slowdown."));
        folder->Append(new MenuEntry("Inventory box extender", ExtendedInventoryBox, "This allows you to create 10 additionals boxes to store your items.\nHold Start 1 second to choose which one to open."));
        folder->Append(new MenuEntry("Fossil Inspector", GenerateFossils, "Press " FONT_X " and " FONT_A " to process all fossils\nas if you talked to Blathers"));
        folder->Append(new MenuEntry("Max Bank", MaxMoneyBank));
        folder->Append(new MenuEntry("Infinite Wallet", InfiniteWallet));
        folder->Append(new MenuEntry("Infinite/Max Coupons", InfiniteCoupons));
        folder->Append(new MenuEntry("Infinite/Max Island Medals", InfiniteMedals));
        folder->Append(new MenuEntry("Wallet editor (0)", WalletEditor, WalletEditorSetter, "Touch the keyboard icon on the bottom screen to change the desired value"));
        folder->Append(new MenuEntry("Bank editor...", nullptr, SetBells, "Press the keyboard icon on the bottom screen to enter in the desired amount of bells to your bank.")); //todo: add entry name changer and value checker

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
        folder->Append(new MenuEntry("Search and Replace", nullptr, SearchReplace, "Press the keyboard icon to enter in what you want to search and replace"));
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

        folder->Append(new MenuEntry("Ghost Mode", GhostMode, "Press Y + D pad up to enable, Y + D pad down to disable"));
        folder->Append(new MenuEntry("Camera Mod", CameraMod, "R + Circle pad = rotation \n\n R + A stop player from moving or Y lock camera, X unlock camera(needed) \n\n B + D pad move camera, L / R up and down"));
        folder->Append(new MenuEntry("Custom Symbols Keyboard", CustomKB, "This turns all the symbols in the keyboard into Nintendo symbols.\nExample: \uE00F\uE004\uE000\uE00E\uE00E\uE04B"));
        folder->Append(new MenuEntry("Keyboard Extender", KeyboardExtender, "This extends the max characters that you can type into chat to 54 characters.\nSpecial thanks to Wii8461 for this cheat"));
        folder->Append(new MenuEntry("Fast Game Speed", FastGameSpeed, "This makes things in the game speed up. This might make your game crash.\nCredits to Scotline and Mega Mew for this cheat"));
        folder->Append(new MenuEntry("Item Form Changer", ItemFormChanger, ItemFormEditor, "This changes how your character holds tools"));
        folder->Append(new MenuEntry("Item Effect Changer", ItemEffectChanger, ItemEffectEditor, "This changes how your character uses items."));
        folder->Append(new MenuEntry("Special NPC Changer", AnimalChanger, AnimalChangerKeyboard, "This changes all the special NPC's like K.K. to what you choose."));
        folder->Append(new MenuEntry("Access Catalog & Storage Anywhere", StorageEverywhere, "Press L or R to access your storage, and press L+R to access the catalog while switching emoticon tabs\nSpecial thanks Mega Mew and Scotline for this cheat :)"));
        folder->Append(new MenuEntry("Faint", Faint, "Press R + A to make your character pass out like he got bit by a scorpion!\nCredits to Hikaru"));
        
        menu.Append(folder);

        /*
        ** Callbacks
        ********************/

        // Add Text2Cheat to plugin's main loop
        menu.Callback([]
        {
            Sleep(Milliseconds(1));
            if (g_homeBtnWasPressed)
            {
                g_homeBtnWasPressed = 0;
                OSD::Notify("The homebutton is disabled because of memory issue", Color::Red, Color::Blank);
            }
        });
        menu.Callback(CheatsKeyboard);
        menu.Callback(PlayerUpdateCallback);
        menu.Callback(MiniGame);

        // Launch menu and mainloop
        menu.Run();

        // Exit plugin
        return (0);
    }
}
