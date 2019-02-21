#include "cheats.hpp"
#include "Helpers/QuickMenu.hpp"
#include "Hook.hpp"
#include "Helpers/newlibHeap.h"
#include "3ds.h"
#include <cstring>

extern "C" vu32* hidSharedMem;

namespace CTRPluginFramework
{
    // This function is called on the plugin starts, before main
    void    PatchProcess(FwkSettings &settings)
    {
        settings.ThreadPriority = 0x39;
        settings.AllowActionReplay = false;
    }

    extern Region               g_region;
    static const std::string    unsupportedVersion = "Your ACNL version isn't\nsupported!\nMake sure you have the\n1.5 update installed!";
    static const std::string    unsupportedGame = "Error\nGame not supported !\nVisit discord for support.";
    static const std::string    gameName = "Animal Crossing New Leaf";
    static const std::string    creator = "RyDog";
    static const std::string    developer = creator + " & Slattz";
    static const std::string    credits =
        "Plugin Version: " STRING_VERSION  "\n"
        "Creator: " + creator + "\n"
        "Developer: " + developer + "\n"
        "\n"
        "Special thanks to:\n"
        "Nanquitas\n"
        "Slattz\n"
        "WemI0\n"
        "Scotline\n"
        "and others :)";

    static bool    CheckRegion(void)
    {
        u64         tid = Process::GetTitleID();
        u16         ver = Process::GetVersion();

        // Get current game's region
        switch (tid)
        {
            case 0x0004000000086300:
                if (ver != 6192)
                    goto unsupported;
                g_region = USA;
                break;
            case 0x0004000000086400:
                if (ver != 6176)
                    goto unsupported;
                g_region = EUR;
                break;
            case 0x0004000000086200:
                if (ver != 6272)
                    goto unsupported;
                g_region = JAP;
                break;
            case 0x0004000000198d00:
                if (ver != 6160)
                    goto unsupported;
                g_region = w_JAP;
                break;
            case 0x0004000000198e00:
                if (ver != 5120)
                    goto unsupported;
                g_region = w_USA;
                break;
            case 0x0004000000198f00:
                if (ver != 6160)
                    goto unsupported;
                g_region = w_EUR;
                break;
            default:
                (MessageBox(unsupportedGame))();
                return (true);
        }

        return (false);

    unsupported:
        (MessageBox(unsupportedVersion))();
        return (true);
    }

    MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey)
    {
        if (entry != nullptr)
        {
            entry->Hotkeys += hotkey;
            entry->SetArg(new std::string(entry->Name()));
            entry->Name() += " " + hotkey.ToString();
            entry->Hotkeys.OnHotkeyChangeCallback([](MenuEntry *entry, int index)
            {
                std::string *name = reinterpret_cast<std::string *>(entry->GetArg());

                entry->Name() = *name + " " + entry->Hotkeys[0].ToString();
            });
        }

        return (entry);
    }

    MenuEntry *EntryWithHotkey(MenuEntry *entry, const std::vector<Hotkey> &hotkeys)
    {
        if (entry != nullptr)
        {
            for (const Hotkey &hotkey : hotkeys)
                entry->Hotkeys += hotkey;
        }

        return (entry);
    }

    void    InitQuickMenu(void);
    int     main(void)
    {
        Process::ProtectRegion((u32)hidSharedMem, MEMPERM_READ | MEMPERM_WRITE);
        PluginMenu  *m = new PluginMenu(gameName, MAJOR_VERSION, MINOR_VERSION, REVISION_VERSION, credits);
        PluginMenu  &menu = *m;
        menu.SynchronizeWithFrame(true);
        // T&C Message & Save Backup Message
        menu.OnFirstOpening = StartMsg;

        /*OSD::Run([](const Screen &screen)
        {
            if (!screen.IsTop) return false;
            screen.Draw(Utils::Format("Free: %08X", getMemFree()), 10, 10);
            return true;
        });*/

        if (CheckRegion())
            return (1); ///< Unsupported game/version

        // Initialize game's addresses based on region
        Game::Initialize();
        //Launch Updater
        httpcInit(0);
        if(launchUpdater())
        {
            httpcExit();
            ptmSysmInit();
            MessageBox("The update has been installed.\nYour 3DS will now be restarted.")();
            PTMSYSM_RebootAsync(0);
            ptmSysmExit();
            return 0;
        }
        httpcExit();

        // Initialize player
        Player::GetInstance();
        // Change QuickMenu's hotkey
        QuickMenu::GetInstance().ChangeHotkey(R + X);
        // Init QuickMenu
        InitQuickMenu();

        /*
        ** Garden
        ********************/

        menu += new MenuFolder("Save File Codes", std::vector<MenuEntry *>(
        {
            new MenuEntry("Set name to...", nullptr, SetNameTo),
            new MenuEntry("Save Dumper", nullptr, GardenDumper, "Select the keyboard icon to start dumping your save file."),
            new MenuEntry("Save Restore", nullptr, GardenRestore, "Select this icon to open file picker to restore from your previously dumped saves"),
            new MenuEntry("Change Town Fruit to...", nullptr, ChangeNativeFruit, "Special thanks to WemI0 and Scotline"),
            new MenuEntry("Change Town Grass to...", nullptr, ChangeGrass, "Special thanks to WemI0 and Scotline"),
            new MenuEntry("Real Time Building Modifier", nullptr, BuildingModifier, "Press on the keyboard option to bring up the building keyboard."),
        }));


        /*
        ** Movement
        ********************/

        menu += new MenuFolder("Movement Codes", std::vector<MenuEntry *>(
        {
            EntryWithHotkey(new MenuEntry("Coordinates Modifier", CoordinateModifier, SpeedSettings, "Press the hotkey to move to the corresponding direction."),
                { Hotkey(Key::A | Key::DPadUp, "Go up"), Hotkey(Key::A | Key::DPadDown, "Go down"), Hotkey(Key::A | Key::DPadLeft, "Go left") , Hotkey(Key::A | Key::DPadRight, "Go right")}),
            new MenuEntry("Touch Coordinates", TouchCoordinates, "Touch the map to teleport your character there."),
            EntryWithHotkey(new MenuEntry("Teleport", Teleporter, "Press the hotkey to save/restore your location. You can use a slot modifier hotkey together to change the slot that'll be used."),
                {Hotkey(Key::B | Key::DPadUp, "Save current location"), Hotkey(Key::B | Key::DPadDown, "Restore saved location"),
                 Hotkey(Key::L, "Use slot 2"), Hotkey(Key::R, "Use slot 3") }),
            EntryWithHotkey(new MenuEntry("Walk Over Things", WalkOverThings, "Press the hotkeys to enable/disable collisions."),
                {Hotkey(Key::L | Key::DPadUp, "Toggle Collisions")}),
            new MenuEntry("Speed Hack", SpeedHack, SpeedHackEditor, "Change how fast you want to go with the keyboard icon\nCredits to WemI0 for this cheat"),
            EntryWithHotkey(new MenuEntry("Moon Jump", MoonJump, SpeedSettings, "Press the hotkeys to move your character up/down.\nThis cheat also has a side effect of disabling gravity and causing various glitches."),
                {Hotkey(Key::L | Key::DPadUp, "Move up"), Hotkey(Key::L | Key::DPadDown, "Move down")}),
            new MenuEntry("Teleport to PWP...", nullptr, PWPTeleport, "Press on the keyboard to open up the menu to choose which PWP to teleport to")
        }));

        /*
        ** Main Street
        ********************/

        menu += new MenuFolder("Shop Codes", std::vector<MenuEntry *>(
        {
            new MenuEntry("Nookling Upgrades", nullptr, NooklingKeyboard, "Press the keyboard icon to change which upgrade the Nooklings have."),
            new MenuEntry("Main Street Shop Unlocker", nullptr, MainStreetKeyboard, "Press the keyboard icon to change what Main Street buildings are unlocked."),
            new MenuEntry("Shops Always Open", nullptr, ShopsAlwaysOpenKeyboard, "Press the keyboard icon to change which shops are always open."),
            EntryWithHotkey(new MenuEntry("Catalog to Pockets", CatalogToPockets, "Press the hotkey while in the catalog to send the item directly to your pockets!.\nOriginal cheat by Rydog, adapted by Slattz."),
                {Hotkey(Key::L, "Change Button Activator")})
        }));

        /*
        ** Time Travel
        ********************/

        menu += new MenuFolder("Time Travel Codes", std::vector<MenuEntry *>(
        {
            EntryWithHotkey(new MenuEntry("Time Travel", TimeTravel, TimeTravelSettings, "Press the hotkeys to travel through time.\nPress the keyboard icon to change the settings."),
            {
                Hotkey(Key::R | Key::DPadLeft, "Freely move time backwards"), Hotkey(Key::R | Key::DPadRight, "Freely move time forwards"),
                Hotkey(Key::B | Key::DPadLeft, "Rewind time by an hour"), Hotkey(Key::B | Key::DPadRight, "Go forward in time by an hour"),
                Hotkey(Key::R | Key::DPadUp, "Save current time") , Hotkey(Key::R | Key::DPadDown, "Restore saved time"),
                Hotkey(Key::B | Key::DPadDown, "Reset ingame time")
            }),
            new MenuEntry("Time Machine", nullptr, TimeMachine, "Press on the keyboard icon or enable the cheat to enter the time machine settings!")
        }));

        /*
        ** Inventory
        ********************/

        MenuFolder *inv = new MenuFolder("Inventory");
        {
            *inv += new MenuFolder("Money cheats", std::vector<MenuEntry *>(
                {
                    new MenuEntry(2, "Max/Infinite Bank", MaxMoneyBank, "Sets your bank to always have 999,999,999 bells."),
                    new MenuEntry(2, "Bells in Bank Don't Decrease", InfiniteBank, "Withdrawing any amount of bells does nothing.\nI wish my real bank did this..."),
                    new MenuEntry(3, "Max/Infinite Wallet", MaxWallet, "Sets your bank to always have 99,999 bells."),
                    new MenuEntry(3, "Bells in Wallet Don't Decrease", InfiniteWallet, "Spending any bells doesn't decrease your wallet.\nGo on a shopping spree!"),
                    new MenuEntry(4, "Coupons Don't Decrease", InfiniteCoupons),
                    new MenuEntry(4, "Infinite/Max Coupons", MaxCoupons),
                    new MenuEntry(5, "Medals Don't Decrease", InfiniteMedals),
                    new MenuEntry(5, "Infinite/Max Island Medals", MaxMedals),
                    new MenuEntry("Wallet editor (0)", WalletEditor, WalletEditorSetter, "Touch the keyboard icon on the bottom screen to change the desired value"),
                    new MenuEntry("Bank editor (0)", BankEditor, BankEditorSetter, "Touch the keyboard icon on the bottom screen to enter the desired amount of bells in your bank.")
                }));
            *inv += EntryWithHotkey(new MenuEntry("Text to Item", Text2Item, "Press the hotkeys to bring up the keyboard to enter the item ID."),
                {Hotkey(Key::X | Key::DPadRight, "Open the keyboard") });
            *inv += EntryWithHotkey(new MenuEntry("Duplicate", Duplication, "Press the hotkey to duplicate the item that is in slot 1 into the first available slot."),
                {Hotkey(Key::R, "Duplicate items") }),
            *inv += new MenuEntry("Pick up buried items", PickBuriedItems, "Press " FONT_Y " to pick up any buried items.\nWarning: this is a heavy cheat, so it might cause slowdown.");
            *inv += new MenuEntry("Inventory box extender", ExtendedInventoryBox, "This allows you to create 10 additionals boxes to store your items.\nOnce activated, open the quick menu in-game to see the option Inventory Box.");
            *inv += EntryWithHotkey(new MenuEntry("Fossil Inspector", GenerateFossils, "Press the hotkeys to process all fossils\nas if you talked to Blathers."),
                {Hotkey(Key::X | Key::A, "Inspect fossils") });
        }

        menu += inv;


        /*
        ** Environment
        ********************/

        MenuFolder *folder = new MenuFolder("Enviroment");
        {
            /* Subfolder of Enviroment
            ** These codes only execute when R+A is pressed, so I only want 1 enabled.
            ** I use the radio group parameter to prevent multiple from being enabled.
            *****************************************************************************/
            *folder += new MenuFolder("R + A Codes", std::vector<MenuEntry *>(
            {
                EntryWithHotkey(new MenuEntry(1, "Remove All Items", RemoveAllItems, "Press the hotkeys to execute... Beware as there is no going back if you save."),
                    { Hotkey(Key::R | Key::A, "Remove all items")}),
                EntryWithHotkey(new MenuEntry(1, "Remove All Weeds", RemoveAllWeeds, "Press the hotkeys to clear all weeds"),
                    { Hotkey(Key::R | Key::A, "Remove all weeds") }),
                EntryWithHotkey(new MenuEntry(1, "Water All Flowers", WaterAllFlowers, "Press the hotkeys to water all flowers"),
                    { Hotkey(Key::R | Key::A, "Water all flowers") }),
                EntryWithHotkey(new MenuEntry(1, "Fill Grass", FillGrass, "Press the hotkeys to fill your town with grass.\nPlease note that bald spots will respawn on the next day."),
                    { Hotkey(Key::R | Key::A, "Restore all grass") }),
                EntryWithHotkey(new MenuEntry(1, "Destroy Grass", DestroyGrass, "Press the hotkeys to destroy all the grass in your town to make a desert wasteland."),
                    {Hotkey(Key::R | Key::A, "Remove all grass")}),
            }));
			/* Subfolder of Enviroment
			** These codes control the fish functions
			*****************************************************************************/
            *folder += new MenuFolder("Fish Codes", std::vector<MenuEntry *>(
                {
                    new MenuEntry("Fish Cant Be Scared", FishCantBeScared, "Prevents fish from scaring when the player is running. Special thanks to Natfoth"),
                    new MenuEntry("Fish Bite Right Away", FishAlwaysBiteRightAway, "The fish will bite on the first bite every time. Special thanks to Natfoth"),
                    new MenuEntry("Fish Id Editor", FishIdEditor, FishIdEditorSetter, "Sets the Id of the fish that spawn. Fish will still only spawn in their correct areas. Only works for newly spawned fish. Special thanks to Natfoth"),
                }));
            *folder += EntryWithHotkey(new MenuEntry("Real Time World Edit", WorldEdit, "Press the corresponding hotkeys to use the cheat,"),
            { Hotkey(Key::R | Key::DPadLeft, "Open the keyboard"), Hotkey(Key::R | Key::DPadUp, "Store the item that you're standing on"),
                Hotkey(Key::R | Key::DPadDown, "Write the item to where your player is standing")}),
            *folder += new MenuEntry("Search and Replace", nullptr, SearchReplace, "Press the keyboard icon to enter in what you want to search and replace"),
            *folder += EntryWithHotkey(new MenuEntry("Flowers Are Unbreakable", UnbreakableFlowers, "Press the hotkey to enable/disable."),
                {Hotkey(Key::R | Key::DPadRight, "Change Button Activator")});
        }
        menu += folder;

        /*
        ** Unlock
        ********************/

        menu += new MenuFolder("Unlock Codes", std::vector<MenuEntry *>(
        {
            new MenuEntry("100% Mayor Permit", Permit, "Special thanks to Slattz"),
            new MenuEntry("Unlock All PWPs", PWPUnlock, "Special thanks to WemI0 and Scotline"),
            new MenuEntry("Fill Out Encyclopedia", Encyclopedia, "Special thanks to WemI0 and Scotline"),
            new MenuEntry("Fill Out Emoticons", Emoticons, "Special thanks to WemI0 and Scotline"),
            new MenuEntry("Fill Out K.K. Songs", Songs, "Special thanks to WemI0 and Scotline"),
            new MenuEntry("Fill out Catalog", FillCatalog, "Fill out the catalog in Nookling's shop.\nSpecial thanks to Slattz and WemI0")
        }));

        /*
        ** Misc.
        ********************/

        menu += new MenuFolder("Misc.", std::vector<MenuEntry *>(
        {
            EntryWithHotkey(new MenuEntry("Ghost Mode", GhostMode, "Press the hotkeys to make your character invisible/visible."),
                {
                    Hotkey(Key::Y | Key::DPadUp, "Toggle Invisibility")
                }),
            EntryWithHotkey(new MenuEntry("Camera Mod", CameraMod, "Press the hotkeys to move the camera around."),
                {
                    Hotkey(Key::R, "Rotate the camera (With Circle Pad)"), Hotkey(Key::R | Key::Y, "Detach the camera"), Hotkey(Key::R | Key::X, "Reattach the camera"), Hotkey(Key::R | Key::A, "Enable/Disable camera following behind player"),
                    Hotkey(Key::B | Key::DPadUp, "Pan the camera north"), Hotkey(Key::B | Key::DPadRight, "Pan the camera east"), Hotkey(Key::B | Key::DPadDown, "Pan the camera south"), Hotkey(Key::B | Key::DPadLeft, "Pan the camera west"),
                    Hotkey(Key::B | Key::L, "Pan the camera downwards"), Hotkey(Key::B | Key::R, "Pan the camera upwards")
                }),
            EntryWithHotkey(new MenuEntry("Country Spoofer", CountrySpoofer, "Spoofs your country, allowing you to go to another country's island.\nOriginal cheat by Levi & Nanquitas, adapted by Slattz."),
                {Hotkey(Key::B | Key::L, "Change Button Activator")}),
            new MenuEntry("Room Teleporter", nullptr, RoomPicker, "Teleports your character to any room that you wannt.\nCredits to Levi for this entire cheat!"),
            new MenuEntry("Custom Symbols Keyboard", CustomKB, "This turns all the symbols in the keyboard into Nintendo symbols.\nExample: \uE00F\uE004\uE000\uE00E\uE00E\uE04B"),
            new MenuEntry("Keyboard Extender", KeyboardExtender, "This extends the max characters that you can type into chat to 54 characters.\nSpecial thanks to Levi for this cheat"),
            new MenuEntry("Fast Game Speed", FastGameSpeed, "This makes things in the game speed up. This might make your game crash.\nCredits to Scotline and WemI0 for this cheat"),
            new MenuEntry("Item Form Changer", ItemFormChanger, ItemFormEditor, "This changes how your character holds tools"),
            new MenuEntry("Item Effect Changer", ItemEffectChanger, ItemEffectEditor, "This changes how your character uses items."),
            new MenuEntry("Special NPC Changer", AnimalChanger, AnimalChangerKeyboard, "This changes all the special NPC's like K.K. to what you choose."),
            EntryWithHotkey(new MenuEntry("Access Catalog & Storage Anywhere", StorageEverywhere, StorageEverywhereSettings, "Press the hotkeys and open the keyboard, emoticons, mailbox or force a bottom screen change to access the window of your choice" ),
            {
                Hotkey(Key::L, "Access drawers"), Hotkey(Key::R, "Access secret storage"), Hotkey(Key::L | Key::R, "Access catalog"), Hotkey(Key::Y, "Custom (use keyboard in cheat menu)")
            }),
            EntryWithHotkey(new MenuEntry("Faint", Faint, "Press the hotkeys to make your character pass out like they got bit by a scorpion!\nCredits to Kageshi"),
            {
                Hotkey(Key::R | Key::A, "Make your character faint")
            }),
            EntryWithHotkey(new MenuEntry("Ultimate Weed Pulling Hack", UltimateWeedPuller, "Press the hotkeys to start automatically plucking weeds in your town! \nPress the Hotkeys again to disable."),
            {
                Hotkey(Key::R, "Start/Stop plucking weeds")
            }),
            EntryWithHotkey(new MenuEntry("Ultimate Unburying Hack", UnBuryItems, "Press R to start unburying various buried items around your town!\nR again to disable."),
            {
                Hotkey(Key::R, "Start/Stop Unburying items")
            }),
            new MenuEntry("Corrupter", Corrupter, CorrupterSettings, "WARNING!\nThis corrupts random values in memory to cause funny side effects.\nUse at own risk!"),
            new MenuEntry("Pick Every Tour",  EnableAllTours, "Enabling this cheat lets you pick every tour from the tour list!\nCredits to Levi!"),
            EntryWithHotkey(new MenuEntry("Amiibo Spoofer", AmiiboSpoof, "Press hotkey to choose from the list of Villager Categories, (Default: " FONT_R ")\nCredits to Slattz and Scotline for the cheat."),
            {
                Hotkey(Key::R, "Open Villager Categories List")
            }),
            EntryWithHotkey(new MenuEntry("Emote ID changer", UseAnyEmote, "Press the hotkey to open a keyboard to patch the game's emotes.\n0xFF restores the game's original code.\nOriginal cheat by 0ICED0, adapted by Slattz."),
                {Hotkey(Key::R | Key::B, "Change Button Activator")}),
            EntryWithHotkey(new MenuEntry("Edit Every Pattern", EditAnyPattern, "Press the hotkey to enable/disable.\nCredits to Slattz for the cheat"),
                {Hotkey(Key::R | Key::DPadRight, "Change Button Activator")}),
            EntryWithHotkey(new MenuEntry("Weather Modifier", WeatherMod, "Press the hotkey to enable/disable.\nNOTE: Only you will see the changes."),
                {
                Hotkey(Key::Y | Key::DPadLeft, "Change Button Activator"),
                Hotkey(Key::Y | Key::DPadUp, "Change Increment Hotkey"),
                Hotkey(Key::Y | Key::DPadDown, "Change Decrement Hotkey")
                }),
            EntryWithHotkey(new MenuEntry("Confetti Mod", ConfettiMod, "Press the hotkey to enable/disable.\nNOTE: Only you will see the changes."),
                {
                Hotkey(Key::L | Key::DPadLeft, "Change Button Activator"),
                Hotkey(Key::L | Key::DPadUp, "Change Increment Hotkey"),
                Hotkey(Key::L | Key::DPadDown, "Change Decrement Hotkey")
                }),
            EntryWithHotkey(new MenuEntry("Cherry Blossom Mod", CherryBlossomMod, "Press the hotkey to enable/disable.\nNOTE: Only you will see the changes."),
                {
                Hotkey(Key::R | Key::DPadLeft, "Change Button Activator"),
                Hotkey(Key::R | Key::DPadUp, "Change Increment Hotkey"),
                Hotkey(Key::R | Key::DPadDown, "Change Decrement Hotkey")
                })
        }));

        /*
        ** Callbacks
        ********************/

        menu += []
        {
            Sleep(Milliseconds(1));
            QuickMenu::GetInstance()();
        };
        menu += PlayerUpdateCallback;
        menu += MiniGame;

        // Launch menu and mainloop
        menu.Run();

        // Exit plugin
        return (0);
    }
}
