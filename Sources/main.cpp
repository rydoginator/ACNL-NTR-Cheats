#include "CTRPluginFramework.hpp"
#include "cheats.hpp"

namespace CTRPluginFramework
{
    // This function is called on the plugin starts, before main
    void PatchProcess(void)
    {
    }

    int main(void)
    {
        PluginMenu* m = new PluginMenu("Animal Crossing New Leaf Ver 4.0 Alpha");
        PluginMenu& menu = *m;

        u64 tid = Process::GetTitleID();

        // Assign globals according to the current game's region
        if (tid == 0x0004000000086300)
            assign_region(USA);
        else if (tid == 0x0004000000086400)
            assign_region(EUR);
        else if (tid == 0x0004000000086200)
            assign_region(JAP);
        else
        {
            // Game not recognised
            MessageBox  msgBox("Error\nGame not supported !\nVisit discord for support.");

            msgBox();
            return (0);
        }

        /*
        ** Garden
        ********************/

        MenuFolder* folder = new MenuFolder("Garden Codes");

        folder->Append(new MenuEntry("Set name to...", SetNameTo));
        folder->Append(new MenuEntry("Garden Dumper", nullptr, GardenDumper));
        folder->Append(new MenuEntry("Garden Restore", nullptr, GardenRestore));
        folder->Append(new MenuEntry("Inject TCP Picture", InjectTCP));

        menu.Append(folder);

        /*
        ** Movement
        ********************/

        folder = new MenuFolder("Movement Codes");

        folder->Append(new MenuEntry("Coordinates Modifier", CoordinateModifier, "Press \uE000 and D Pad in the direction that you want to move."));
        folder->Append(new MenuEntry("Teleport", Teleporter, "Press \uE001 and \uE079 to save your location, \uE001 and \uE07A to teleport back to the location. Use \uE052 or \uE053 to use multiple locations!"));
        folder->Append(new MenuEntry("Walk Over Things", WalkOverThings, "Press \uE052 and \uE079 to enable walking through stuff, \uE052 and \uE07A to disable walking through stuff."));
        folder->Append(new MenuEntry("Speed Hack", SpeedHack));
        folder->Append(new MenuEntry("Moon Jump v4", MoonJump, "Press \uE052 and \uE079 to go higher and \uE07A to go lower."));
        
        menu.Append(folder);

        /*
        ** Inventory
        ********************/

        folder = new MenuFolder("Inventory");

        folder->Append(new MenuEntry("Text to Item", Text2Item, "Press " FONT_X " and " FONT_DR " to open the keyboard to enter in the ID you want to recieve."));
        folder->Append(new MenuEntry("Duplicate", Duplication, "Press " FONT_R " to duplicate the item that is slot 01 to slot 02."));
        folder->Append(new MenuEntry("Show names of buried items", ShowBuriedItems));
        folder->Append(new MenuEntry("Pick up buried items", PickBuriedItems));
        folder->Append(new MenuEntry("Show bells", ShowBells));
        folder->Append(new MenuEntry("Set bells", nullptr, SetBells));

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

        /*
        ** Misc.
        ********************/

        folder = new MenuFolder("Misc.");

        folder->Append(new MenuEntry("Real Time Building Placer", BuildingPlacer));
        folder->Append(new MenuEntry("Ghost Mode", GhostMode));
        folder->Append(new MenuEntry("Camera Mod", CameraMod));
        folder->Append(new MenuEntry("Keyboard Extender", KeyboardExtender, "This extends the max characters that you can type into chat to 54 characters. Now you can type short stories into chat :)"));
        
        menu.Append(folder);

        /*
        ** Callbacks
        ********************/

        // Add Text2Cheat to plugin's main loop
        menu.Callback(SleepThread);
        menu.Callback(CheatsKeyboard);
        menu.Callback(PlayerUpdateCallback);
        Assign();

        // Launch menu and mainloop
        menu.Run();

        // Exit plugin
        return (0);
    }
}
