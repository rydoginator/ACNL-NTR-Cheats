#include "cheats.hpp"
#include "AmiiboSpoof.hpp"
#include "Helpers/OSDMenu.hpp"

namespace CTRPluginFramework
{
    void    WispSpoofer(u16 Amiibo_ID)
    {
        static Clock time;
        static const u32 offset = GetWispOffset();

        if (offset == 0)
        {
            OSD::Notify(Color::Red << "A problem occured with the Wisp pointer!");
            return;
        }

        time.Restart(); //Restart timer so it'll work again
        while (!time.HasTimePassed(Seconds(10.f))) //Write to offsets until timer stops - 7.f is fine on n3ds but not on o3ds
        {
            Process::Write16(offset+0x219, Amiibo_ID); //Amiibo ID
            Process::Write8(offset+0x204, 0x13); //Tell game an amiibo is being scanned
        }

        Process::Write16(offset+0x219, 0x0000); //Finished: null the amiibo ID
        Process::Write8(offset+0x204, 0x12); //Finished: Tell game an amiibo has been/can be scanned
    }

    void    DIESpoofer(const char* Model)
    {
        /* Basically defunct, needs to be revisited, if ever */

        //u8     DIEUIOpen;
        static const u32 offset = reinterpret_cast<u32>(Game::DIESpoof);
/*        Process::Read8(offset - 0x25289D0, DIEUIOpen); //Check DIE Minigame UI bool state (open / unopen)
        
        if (DIEUIOpen)
        {*/
            Process::Write16(offset, 0x0101); //Tell game an amiibo is being scanned
            Process::CopyMemory((void *)(offset + 0x10), (void *)Model, 5); //Villager Model Name
            Process::CopyMemory((void *)(offset + 0x16), (void *)Model, 5); //Villager Model Name
            //Process::Write16(offset, 0x0601); //Tell game amiibo has been scanned
        //}
    }
    
    using StringVector = std::vector<std::string>;
    void    VillagersKeyboard(u8 mode)
    {
        int             choice;
        OSDMenu &menu = OSDMenu::GetInstance();
        StringVector    species;
        StringVector    villagers;

        menu.Clear();
        menu.SetTitle("Select the type of villager you want to spoof.");
        // Populate with specie
        for (const Species &specie : g_species)
            species.push_back(specie.Name);

        // Set the entries
        for (u32 i = 0; i < species.size(); ++i)
            menu += species;

        menu.Open(); //Ask user which category they want to load

        // Wait until the menu is closed
        while (menu.IsBusy())
            menu.Update();

        choice = menu.GetSelectionIndex();
        menu.Close();
        if (choice == -1)
        {
            OSD::Notify("Amiibo Spoofer cannot continue!");
            return;
        }
        const Species &selected = g_species[choice]; //Populate with villagers corresponding to user choice

        menu.Clear();
        menu.SetTitle("Which villager do you want to spoof?");
        for (u32 i = selected.Start; i <= selected.End; i++)
            villagers.push_back(g_villagers[i].Name);

        // Set the entries
        for (u32 i = 0; i < villagers.size(); ++i)
            menu += villagers;

        menu.Open(); //Ask user which villager they want to choose

        // Wait until the menu is closed
        while (menu.IsBusy())
            menu.Update();

        const Villagers &villagerSelected = g_villagers[choice + selected.Start]; //Do something with villager selected
        menu.Close();

        if (mode == MODE_WISP)
            WispSpoofer(villagerSelected.AMIIBO_ID);

        else if (mode == MODE_DIE)
            //DIESpoofer(villagerSelected.Filename);
            OSD::Notify("D.I.E. Minigame currently not supported.");

        else if (mode == MODE_PL)
            //PLSpoofer(villagerSelected.Filename);
            OSD::Notify("P.L. Minigame currently not supported.");

        else if (mode == MODE_AMC)
            //AMCSpoofer(villagerSelected.AMIIBO_ID);
            OSD::Notify("Amiibo Camera currently not supported.");

        else return;
    }

    u32    GetWispOffset(void)
    {
        static const u32 offset = reinterpret_cast<u32>(Game::WispSpoof);
        /* To port Wisp offset: Binary search in IDA: 10 40 2D E9 00 00 90 E5 83 FF FF EB */
        u32 pointer = 0;

        Process::Read32(offset, pointer);
        if (pointer != 0)
        {
            Process::Read32(pointer+0x18, pointer);
            if (pointer != 0)
            {
                Process::Read32(pointer+0x1C, pointer);

                if (pointer != 0)
                    return pointer;
            }
        }

        return 0;
    }

    void   AmiiboSpoof(MenuEntry *entry)
    {
        static bool btn = false;
        static const std::string CLKAmiiboicn = Color::Red << "Click the amiibo icon before trying to use the Amiibo Spoofer.";
        AmiiboChecks Wisp;
        //AmiiboChecks DIE;
        //AmiiboChecks PL;
        //AmiiboChecks AMC;

        Wisp.Offset = GetWispOffset();
        Process::Read8(Wisp.Offset + 0x215, Wisp.UIOpen); //Get Lamp UI state (open / unopen)
        Process::Read8(Wisp.Offset + 0x216, Wisp.CanScanAmiibo); //Get Wisp Amiibo Scanability State
        //Process::Read8(off_DIEUI - 0x25289D0, DIE_UIOpen); //Get DIE Minigame UI state (open / unopen)
        
        if (entry->Hotkeys[0].IsDown() && !btn)
        {
            btn = true;

            if (*Game::Room >= 3 && *Game::Room <= 0x1A) //Check Houses
            {
                if (Wisp.UIOpen && Wisp.Offset != 0)
                {
                    if (Wisp.CanScanAmiibo)
                        VillagersKeyboard(MODE_WISP);

                    else
                        OSD::Notify(Color::Red << "Be on the scan screen before trying to spoof an Amiibo."); 
                }

                else
                    OSD::Notify(Color::Red << "Open Wisp's Lamp to use the Amiibo Spoofer.");
            }
            
            else if (*Game::Room == 0x9D) //Check Desert Island Escape
            {
                //if (DIE_UIOpen)
                    //VillagersKeyboard(MODE_DIE);
                    OSD::Notify(Color::Red << "D.I.E. Minigame currently not supported.");

                //else
                //    OSD::Notify(CLKAmiiboicn); 
            }

            else if (*Game::Room == 0x9E) //Check Puzzle League Minigame
            {
                //if (PL_UIOpen)
                    OSD::Notify(Color::Red << "P.L. Minigame currently not supported.");
                    //VillagersKeyboard(MODE_PL);

                //else
                //    OSD::Notify(CLKAmiiboicn); 
            }

            else if (*Game::Room == 0xA4) //Check Amiibo Camera
            {
                //if (AMC_UIOpen)
                    //VillagersKeyboard(MODE_AMC);
                    OSD::Notify(Color::Red << "Am. Camera currently not supported.");

                //else
                //    OSD::Notify(CLKAmiiboicn); 
            }

            else
                OSD::Notify(Color::Red << "Amiibo Spoofer can't be used in this location!"); 
        }

        else if (!entry->Hotkeys[0].IsDown())
            btn = false;
    }
}