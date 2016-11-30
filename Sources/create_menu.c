#include "cheats.h"

char    *builder_name = "itsRyan";

    static const char * const t2i_note = "Type item ID and send it into chat,\n\nPress X+D Pad Right,\n\nTo write item to slot 1!";
    static const char * const dup_note = "Press R to duplicate the slot 1 item to slot 2!";
    static const char * const tan_note = "Go into a different room to see changes.";
    static const char * const trans_note = "Do not execute during loading screens!";
    static const char * const cm_note = "Press A+D Pad in any direction to move around at turbo speed!";
    static const char * const mj_note = "Press and hold L to moon jump!";
    static const char * const tele_note = "B+D Pad Up to save,\n\nB+D Pad Down to teleport,\n\nPress L/R to store multiple.";
    static const char * const speed_note = "Press and hold B to start running at turbo fast speed!";
    static const char * const warp_note = "Touch the map to warp anywhere!";
    static const char * const time_note = "Do not use online!";
    static const char * const tt_note = "Fast forward: B+D Pad Right;\n\nRewind: B+D Pad Left,\n\nB+D Pad Down to revert ingame time to system time.\n\nPress L+D Pad Right/Left to watch time rewind/fastforward.";
    static const char * const tm_note = "Type YYMMDDHHmm,\n\nPress Y+D Pad Right to fast forward to that,\n\nOr press Y+D Pad Left to rewind that amount.";
    static const char * const enviro_note = "After executing one of these codes,\n\nUpdate the status to verify the object!";
    static const char * const seed_note = "Hold R and A as you're dropping an item to change the item ID.";
    static const char * const tree_note = "Press X for your tree to instantly grow!";
    static const char * const sar_note = "Type in XXXXYYYY where XXXX is search value and YYYY is repalce value. Send it in chat, and press L + D pad left to execute.";
    static const char * const ra_note = "Enable one R+A cheat at a time,\n\nExecute one,\n\nThen go in and out of a house.";
    static const char * const warning_note = "!!! Warning !!!\n\nIn order to prevent a crash of the game," \
    "we strongly advise you to only open the menu either on the title screen or indoor.\n\nDon't ever open during a multiplayer session!";
    static const char * const real_note = "Type in the ID of the item ID you want, send it into chat and press R + D pad down to place the item directly where you're standing.";
    static const char * const des_note = "Press R + A to remove your grass!";
    static const char * const lush_note = "Press R + A to replenish all your grass!";
    static const char * const weed_note = "Press R + A to remove all weeds!";
    static const char * const flwr_note = "Press R + A to replenish all your flowers!";
    static const char * const cl_note = "Only works outdoors! Press R + D Pad up to enable, Press R + D Pad down to disable.";
    static const char * const eat_note = "Type item ID into chat, send it and press L while eating an item to change the item to the item ID you typed in.";

void with_note_common(const char *name, const char *note, void (*cheatfunction)(void), int type)
{
    int     index;

    if (type == 0)
        index = new_entry((char *)name, cheatfunction);
    else if (type == 1)
        index = new_radio_entry((char *)name, cheatfunction);
    else if (type == 2)
        index = new_spoiler((char *)name);
    else return;
    set_note(note, index);
}

inline void new_entry_with_note(const char *name, const char *note, void (*cheatfunction)(void))
{
    with_note_common(name, note, cheatfunction, 0);
}

inline void new_radio_entry_with_note(const char *name, const char *note, void (*cheatfunction)(void))
{
    with_note_common(name, note, cheatfunction, 1);
}

inline void new_spoiler_with_note(const char *name, const char *note)
{
    with_note_common(name, note, NULL, 2);
}

char    tan_level_buffer[40] = "First init";
int     g_increase_menu_index = 0;
int     g_decrease_menu_index = 0;

static inline void  smenu(void)
{
    update_tan_entry();
    new_entry_with_note("Warning ! Read the notes !", warning_note, keep_it_off);
    new_entry("Text to cheat", text_to_cheats);
    new_spoiler_with_note("Environment Codes", enviro_note);
        new_spoiler("R + A Codes");
            new_radio_entry_with_note("Remove all weeds", weed_note, weeder);
            new_radio_entry_with_note("Water all flowers", flwr_note, quench);
            new_radio_entry_with_note("Grass", lush_note, grass);
            new_radio_entry_with_note("Desert", des_note, desert);
        exit_spoiler();
        new_entry_with_note("Real Time World Edit", real_note, real);
        new_entry_with_note("Seeder", seed_note, seeder);
        new_entry_with_note("Search and Replace", sar_note, search);
        new_entry_with_note("Instant Tree", tree_note, tree);
    exit_spoiler();
    new_spoiler("Inventory Codes");
        new_entry_with_note("Text to Item", t2i_note, text2item);
        new_entry_with_note("Duplication", dup_note, duplicate);
    exit_spoiler();
    new_spoiler("Apparence Codes");
        new_spoiler_with_note("Tan Modifier", tan_note);
            new_unselectable_entry(tan_level_buffer);
            g_increase_menu_index = new_entry("Increase Tan", increase_tan_level);
            g_decrease_menu_index = new_entry("Decrease Tan", decrease_tan_level);
        exit_spoiler();
    exit_spoiler();
    new_spoiler_with_note("Movement Codes", trans_note);
        new_entry_with_note("Walk Through Walls", cl_note, collisions);
        new_entry_with_note("Warping", warp_note, warping);
        new_entry_with_note("Moon Jump", mj_note, moonjump);
        new_entry_with_note("Coordinates Modifier", cm_note, coord);
        new_entry_with_note("Speed Hack", speed_note, speed);
        new_entry_with_note("Teleport", tele_note, teleport);
    exit_spoiler();
    new_spoiler("Nookling Upgrades");
        new_radio_entry("T&T Mart", nook1);
        new_radio_entry("Super T&T", nook2);
        new_radio_entry("T.I.Y", nook3);
        new_radio_entry("T&T Emporium", nook4);
    exit_spoiler();
    new_spoiler_with_note("Time Travel Codes", time_note);
        new_entry_with_note("Time Travel", tt_note, timeTravel);
        new_entry_with_note("Time Machine", tm_note, timeMachine);
    exit_spoiler();
    new_spoiler("Misc. Codes");
        new_entry_with_note("Edible Items", eat_note,  edibleItems);
    exit_spoiler();

}

/*
** USA: 00040000 00086300
** EUR: 00040000 00086400
** JAP: 00040000 00086200
*/

void    my_menus(void)
{
    u32 tid;
    
    set_hid_address(0x10002000); //This is in order to unlock the advanced HID capabilities such as Touchscreen and the stick (No N3DS hid for the moment)
    tid = get_tid_low();
    if (tid == 0x86300)
    {
        assign_region(USA);
        new_unselectable_entry("ACNL NTR Cheats Ver 3.1 Hourly USA");
    }
    else if (tid == 0x86400)
    {
        assign_region(EUR);
        new_unselectable_entry("ACNL NTR Cheats Ver 3.1 Hourly EUR"); 
    }
    else if (tid == 0x86200)
    {
        assign_region(JAP);
        new_unselectable_entry("ACNL NTR Cheats Ver 3.1 Hourly JAP"); 
    }
    else
    {
        new_unselectable_entry("Unsupported ID");
        new_unselectable_entry("!!! Title id unrecognized !!!");
        new_unselectable_entry("!!! You need              !!!");
        new_unselectable_entry("!!! 00040000 00086200     !!!");
        new_unselectable_entry("!!! or                    !!!");
        new_unselectable_entry("!!! 00040000 00086300     !!!");
        new_unselectable_entry("!!! or                    !!!");
        new_unselectable_entry("!!! 00040000 00086400     !!!");
        return;
    }
    smenu();
}
