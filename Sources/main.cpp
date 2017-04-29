#include "CTRPluginFramework.hpp"
#include "cheats.hpp"

#include <cstdio>
#include <string>
#include <vector>

#define FONT_A      "\uE000" // System Font A button
#define FONT_B      "\uE001" // System Font B button
#define FONT_X      "\uE002" // System Font X button
#define FONT_Y      "\uE003" // System Font Y button
#define FONT_L      "\uE052" // System Font L button
#define FONT_R      "\uE053" // System Font R button
#define FONT_ZL     "\uE054" // System Font ZL button
#define FONT_ZR     "\uE055" // System Font ZR button
#define FONT_DU     "\uE079" // System Font D-Pad Up button
#define FONT_DD     "\uE07A" // System Font D-Pad Down button
#define FONT_DL     "\uE07B" // System Font D-Pad Left button
#define FONT_DR     "\uE07C" // System Font D-Pad Right button
#define FONT_DUD    "\uE07D" // System Font D-Pad Up and Down button
#define FONT_DLR    "\uE07E" // System Font D-Pad Left and Right button
#define FONT_CP     "\uE049" // System Font Circle Pad button
#define FONT_T      "\uE058" // System Font Touch button

namespace CTRPluginFramework
{
    // This function is called on the plugin starts, before main
    void    PatchProcess(void)
    {
        u64 tid = Process::GetTitleID();
        //Process::ProtectRegion(0x00100000);

        // Pokemon Moon / Sun
        // Patch game to prevent deconnection from Stream / debugger
        if (tid == 0x0004000000175E00 
            || tid == 0x0004000000164800)
        {
            u32     patch  = 0xE3A01000;
            u32     original = 0;
            // Patch and get the original data
            Process::Patch(0x003DFFD0, (u8 *)&patch, 4); 
        }
    }


    int    main(void)
    {   
       PluginMenu      *m = new PluginMenu("Animal Crossing New Leaf Ver 4.0 Alpha");
       PluginMenu      &menu = *m;

       u64 tid = Process::GetTitleID();

       if (tid == 0x0004000000086300)
           assign_region(USA);
       else if (tid == 0x0004000000086400)
           assign_region(EUR);
       else if (tid == 0x0004000000086200)
           assign_region(JAP);

       MenuFolder *folder = new MenuFolder("Garden Codes");
       folder->Append(new MenuEntry("Set name to...", SetNameTo));
       folder->Append(new MenuEntry("Dump gardenram.bin", backup));
       folder->Append(new MenuEntry("Restore gardenram.bin", restore));
       folder->Append(new MenuEntry("Inject TCP Picture", InjectTCP));
       menu.Append(folder);

       folder = new MenuFolder("Movement Codes");

       folder->Append(new MenuEntry("Coordinates Modifier", coord, "Press \uE000 and D Pad in the direction that you want to move."));
       folder->Append(new MenuEntry("Teleport", teleport, "Press \uE001 and \uE079 to save your location, \uE001 and \uE07A to teleport back to the location. Use \uE052 or \uE053 to use multiple locations!"));
       folder->Append(new MenuEntry("Walk Over Things", walkOver, "Press \uE052 and \uE079 to enable walking through stuff, \uE052 and \uE07A to disable walking through stuff."));
       folder->Append(new MenuEntry("Speed Hack", speed));
       folder->Append(new MenuEntry("Walk Through Walls", pass_collisions, "Press \uE052 and \uE079 to enable walking through stuff, \uE052 and \uE07A to disable walking through stuff."));
       folder->Append(new MenuEntry("Moon Jump v4", moonJump, "Press \uE052 and \uE079 to go higher and \uE07A to go lower."));
       menu.Append(folder);

       folder = new MenuFolder("Inventory");
       folder->Append(new MenuEntry("Text to Item", text2item, "Press " FONT_X " and " FONT_DR " to open the keyboard to enter in the ID you want to recieve."));
       folder->Append(new MenuEntry("Duplicate", duplication, "Press " FONT_R " to duplicate the item that is slot 01 to slot 02."));
       folder->Append(new MenuEntry("Show names of buried items", showBuried));
       folder->Append(new MenuEntry("Pick up buried items", pickBuried));
       menu.Append(folder);

       folder = new MenuFolder("Enviroment");
       MenuFolder *ra = new MenuFolder("R + A Codes");

       ra->Append(new MenuEntry(1, "Remove All Items", deleteAll, "Press " FONT_R " and " FONT_A " to execute... Beware as there is no going back if you save."));
       ra->Append(new MenuEntry(1, "Remove All Weeds", weeder, "Press " FONT_R " and " FONT_A " to execute."));
       ra->Append(new MenuEntry(1, "Water All Flowers", quench, "Press " FONT_R " and " FONT_A "to execute."));
       folder->Append(ra);

       folder->Append(new MenuEntry("Real Time World Edit", worldEdit, "Press " FONT_R " and " FONT_DL " to open the keyboard to store the item. " FONT_R " and " FONT_DU " to store the item that you're standing on. And " FONT_R " + " FONT_DD " to write the item to the place that you're standing on."));
       
       menu.Append(folder);

       folder = new MenuFolder("Time Travel Codes");
       folder->Append(new MenuEntry("Time Travel", timeTravel, "Press either " FONT_R " or " FONT_B " and " FONT_DR " to travel forward or " FONT_DL " to retwind time or " FONT_B " and " FONT_DD " to set ingame time back to your 3DS's clock."));
       folder->Append(new MenuEntry("Time Machine", timeMachine, "Press " FONT_Y " and " FONT_DR " to start time traveling."));
       menu.Append(folder);

       folder = new MenuFolder("Misc.");
       folder->Append(new MenuEntry("Real Time Building Placer", customBuilding));
       folder->Append(new MenuEntry("Ghost Mode", ghostMode));
       folder->Append(new MenuEntry("Camera Mod", cameraMod));
       menu.Append(folder);

        // Add Text2Cheat to plugin's main loop
        menu.Callback(CheatsKeyboard);
        menu.Callback(PlayerUpdateCallback);
        Assign();

        // Launch menu and mainloop
        menu.Run();

        // Exit plugin
        return (0);
    }
}
