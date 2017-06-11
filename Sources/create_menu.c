#include "cheats.h"

#define ENTRY_COUNT 300

typedef struct s_menu
{
    int         count;
    int         status;
    u32         f[ENTRY_COUNT];
    u32         s[ENTRY_COUNT];
    int         a[ENTRY_COUNT];
    const char  *t[ENTRY_COUNT];
    const char  *n[ENTRY_COUNT];
    void        (*fp[ENTRY_COUNT])();
}             t_menu;


typedef void    (*FuncPointer)(void);
extern t_menu menu;



void    new_super_unselectable_entry(char *str, FuncPointer function)
{
    int index;

    index = menu.count;
    if (index >= 300)
        return;
    new_unselectable_entry(str);
    menu.f[index] |= BIT(0) | BIT(1);
    menu.fp[index] = function;
}

char    *builder_name = "RyDog and Paul";

    static const char * const t2i_note = "Type item ID and send it into chat,\n\nPress X+D Pad Right,\n\nTo write item to slot 1!";
    static const char * const dup_note = "Press R to duplicate the slot 1 item to slot 2!";
    static const char * const tan_note = "Go into a different room to see changes.";
    static const char * const trans_note = "Do not execute during loading screens!";
    static const char * const cm_note = "Press A+D Pad in any direction to move around at turbo speed!";
    static const char * const mj_note = "Press and hold L + D Pad Up to fly higher, Press L + D Pad down to go lower.";
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
    static const char * const cl_note = "Only works outdoors! Press L + D Pad up to enable, Press L + D Pad down to disable.";
    static const char * const eat_note = "Type item ID into chat, send it and press L to store it, and press R + A while eating an item to change that item into what you typed into the chat/keyboard.";
    static const char * const dynamic_note = "When inside a ADB, press Y + D pad right to write the decimal to slot 1.";
    static const char * const gr_note = "Rapid fire with tools, anti gravity and more. Enable with L + D Pad up, disable with L + D Pad down.";
    static const char * const cam_note = "R + Circle pad = rotation \n\n R + A stop player from moving or Y lock camera, X unlock camera (needed) \n\n B + D pad move camera, L/R up and down";
    static const char * const turn_note = "Set the turnip price to 990 bells for the current week.";	
    static const char * const badge_note = "Change all badges to selected type.";
    static const char * const med_note = "Change your Medal Amount to the selected value.";
    static const char * const meow_note = "Change your Meow Coupon Amount to the selected value.";
	static const char * const medun_note = "  WARNING!! Unstable!!\nMedals may become negative\nwhen Adding!! To fix: Decrease to a positive\nnumber & buy anything!\nTo Use: Press Up to increase medals by amount selected,Press Down to decrease by selected value.";
    static const char * const clear_note = "Press R + A to completely clear your town of everything. There is no going back, so don't save if you don't like it.";
    static const char * const pwp_note = "Unlock all PWPs. Only works when using Player 1. Don't save if you don't like it.";
	static const char * const invi_note = "Press R + A to seed Illegal Items. USE INDOORS ONLY!";
	static const char * const inf_drop_note = "Enable with R + DPad UP, Disable with R + DPad DOWN.";
	//static const char * const coming_soon_note = "Not implemented yet! Coming Soon!";
	//static const char * const careful_note = "Be careful with this Cheat!";
	//static const char * const size_mod_note = "Use R + B to use the Cheat.";
	//static const char * const hands_note = "Use R + A to loop through useable Items";
	//static const char * const illegal_note = "This Cheat is not available in the Public Version of the Plugin!";
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
    new_toggle_entry("Use keyboard on island", keyboardInput, KEYBOARDINPUT);
    new_spoiler("Custom Codes - EUR");
		new_entry_with_note("Infinite Drop", inf_drop_note, inf_drop);
		new_entry_with_note("Illegal Items", invi_note, InvalidItms);
		new_spoiler("Size Modifiers");
			new_radio_entry("Invisible", size_invisible);
			new_radio_entry("Tiny", size_tiny);
			new_radio_entry("Normal", size_normal);
			new_radio_entry("x2", size_x2);
			new_radio_entry("x3", size_x3);
			new_radio_entry("x4", size_x4);
			new_radio_entry("x8", size_x8);
		exit_spoiler();
		new_spoiler("Shadow Size Modifier");
			new_radio_entry("Invisible", ss_invisible);
			new_radio_entry("Normal", ss_normal);
			new_radio_entry("x2", ss_x2);
			new_radio_entry("x3", ss_x3);
			new_radio_entry("x4", ss_x4);
			new_radio_entry("x8", ss_x8);
		exit_spoiler();
		new_spoiler("Map Mod");
			new_radio_entry("ON", mp_ts_on);
			new_radio_entry("OFF", mp_ts_off);
		exit_spoiler();
		new_spoiler("Player Mod");
			new_radio_entry("ON", fall_on);
			new_radio_entry("OFF", fall_off);
		exit_spoiler();
		new_spoiler("Size Fucker");
			new_radio_entry("ON", size_fuck_on);
			new_radio_entry("OFF", size_fuck_off);
		exit_spoiler();
		new_spoiler("Building Size");
			new_radio_entry("Invisible", buildings_invisible);
			new_radio_entry("Tiny", buildings_tiny);
			new_radio_entry("Normal", buildings_normal);
			new_radio_entry("x2", buildings_x2);
			new_radio_entry("x3", buildings_x3);
			new_radio_entry("x4", buildings_x4);
			new_radio_entry("x8", buildings_x8);
		exit_spoiler();
		new_spoiler("Shiny Flowers");
			new_radio_entry("ON", shiny_flowers);
			new_radio_entry("OFF", shiny_flowers_off);
		exit_spoiler();
		new_spoiler("Wider Models");
			new_radio_entry("ON", models_wider);
			new_radio_entry("OFF", models_wider_off);
		exit_spoiler();
		new_spoiler("Head Mod");
			new_radio_entry("ON", head_mod);
			new_radio_entry("OFF", head_mod_off);
		exit_spoiler();
    exit_spoiler();
    new_spoiler("Inventory Codes");
        new_entry_with_note("Text to Item", t2i_note, text2item);
        new_entry_with_note("Duplication", dup_note, duplicate);
        new_entry_with_note("Dynamic Slot 1 Modifier", dynamic_note, dynamicMod);
    exit_spoiler();
    new_spoiler("Special NPC Mod");
        new_radio_entry("Owl", changeOwl);
        new_radio_entry("Brewster", changeBrewster);
        new_radio_entry("Nook", changeNook);
        new_radio_entry("Joan", changeJoan);
        new_radio_entry("Katrina", changeKatrina);
        new_radio_entry("Acorn Tortimer", changeAcorn);
        new_radio_entry("Redd", changeRedd);
        new_radio_entry("K.K. Slider", changeKK);
        new_radio_entry("Wisp", changeWisp);
        new_radio_entry("Kapp'n", changeKappa);
        new_radio_entry("Resetti", changeResetti);
        new_radio_entry("Rover", changeRover);
        new_radio_entry("Harvey", changeHarvey);
    exit_spoiler();
    new_spoiler("Money Codes");
        new_spoiler("Bank Values");
            new_radio_entry("Bank Breaker", bank_999m);
            new_radio_entry("Be a millionare!", bank_1m);
            new_radio_entry("Go broke", bank_0m);
        exit_spoiler();
        new_spoiler("Wallet Values");
            new_radio_entry("Wallet Breaker", wallet_out);
            new_radio_entry("Infinite Bells", wallet_99k);
            new_radio_entry("Go broke", wallet_0k);
            new_radio_entry("Negative Bells", wallet_neg);
        exit_spoiler();
        new_spoiler("Medal Modifiers");
            new_entry_with_note("---Stable Modifier---", med_note, keep_it_off);
            new_radio_entry("50K Medals", medal_50k);
            new_radio_entry("10K Medals", medal_10k);
            new_radio_entry("1K Medals", medal_1k);
            new_radio_entry("0 Medals", medal_0);
            new_entry_with_note("---Unstable Modifier---", medun_note, keep_it_off);
            new_radio_entry("Medal Mod 1", medals_1s);
            new_radio_entry("Medal Mod 10", medals_10s);
            new_radio_entry("Medal Mod 100", medals_100s);
            new_radio_entry("Medal Mod 1000", medals_1000s);
        exit_spoiler(); 
        new_spoiler_with_note("Meow Coupon Codes", meow_note);
            new_radio_entry("Infinite Meow Coupons", meow_99k);
            new_radio_entry("No Coupons Left", meow_0k);
            new_radio_entry("Negative Coupons", meow_neg);
        exit_spoiler();
    exit_spoiler();
    new_spoiler_with_note("Movement Codes", trans_note);
        new_entry_with_note("Anti Gravity and more", gr_note, antiGravity);
        new_entry_with_note("Walk Through Walls", cl_note, collisions);
        new_entry_with_note("Walk Over Objects", cl_note, walkOver);
        new_entry_with_note("Warping", warp_note, warping);
        new_entry_with_note("Moon Jump", mj_note, moonjump);
        new_entry_with_note("Coordinates Modifier", cm_note, coord);
        new_entry_with_note("Speed Hack", speed_note, speed);
        new_entry_with_note("Teleport", tele_note, teleport);
    exit_spoiler();
    new_spoiler_with_note("Environment Codes", enviro_note);
        new_spoiler("R + A Codes");
            new_radio_entry_with_note("Clear your town of all items", clear_note, deleteAll);
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
    new_spoiler("Appearance Codes");
        new_spoiler_with_note("Tan Modifier", tan_note);
            new_unselectable_entry(tan_level_buffer);
            g_increase_menu_index = new_entry("Increase Tan", increase_tan_level);
            g_decrease_menu_index = new_entry("Decrease Tan", decrease_tan_level);
        exit_spoiler();
    exit_spoiler();
    new_spoiler("Nookling Upgrades");
        new_radio_entry("T&T Mart", nook1);
        new_radio_entry("Super T&T", nook2);
        new_radio_entry("T.I.Y", nook3);
        new_radio_entry("T&T Emporium", nook4);
    exit_spoiler();
    new_spoiler_with_note("Badge Codes", badge_note);
        new_radio_entry("All Gold", badge_gold);
        new_radio_entry("All Silver", badge_silver);
        new_radio_entry("All Bronze", badge_bronze);
        new_radio_entry("No Badges", badge_none);
    exit_spoiler();
    new_spoiler_with_note("Time Travel Codes", time_note);
        new_entry_with_note("Time Travel", tt_note, timeTravel);
        new_entry_with_note("Time Machine", tm_note, timeMachine);
    exit_spoiler();
    new_spoiler("Misc. Codes");
        new_entry_with_note("Camera Mod", cam_note, cameraMod);
        new_entry_with_note("Edible Items", eat_note,  edibleItems);
		new_entry_with_note("Unlock All PWPS", pwp_note, PWP_all);
        new_entry("Purchase 'Not for sale' Items From Catalog", canBuy);
        new_entry("Nookling Items are Free", nookFree);
        new_entry_with_note("Turnip Price is 990", turn_note, turnip_990);
    exit_spoiler();


}

/*
** USA: 00040000 00086300
** EUR: 00040000 00086400
** JAP: 00040000 00086200
*/

void    while_plugin_is_alive(void)
{
    text_to_cheats();
}

void    my_menus(void)
{
    u32 tid;
    
    set_hid_address(0x10002000); //This is in order to unlock the advanced HID capabilities such as Touchscreen and the stick (No N3DS hid for the moment)
    tid = get_tid_low();
    if (tid == 0x86300)
    {
        assign_region(USA);
        new_super_unselectable_entry("ACNL NTR Cheats Ver 3.2.1P USA", while_plugin_is_alive);
    }
    else if (tid == 0x86400)
    {
        assign_region(EUR);
        new_super_unselectable_entry("ACNL NTR Cheats Ver 3.2.1P EUR", while_plugin_is_alive); 
    }
    else if (tid == 0x86200)
    {
        assign_region(JAP);
        new_super_unselectable_entry("ACNL NTR Cheats Ver 3.2.1P JAP", while_plugin_is_alive); 
    }
    else
   {	
        new_unselectable_entry("You're Using An Unsupported TitleID!");			
        new_unselectable_entry("This plugin does not support");
		new_unselectable_entry("The Welcome Amiibo Cart!");
		new_unselectable_entry("The plugin only supports the");
		new_unselectable_entry("Following TitleIDs:");
		new_unselectable_entry("0004000000086200 (JAP, v1.5)");
		new_unselectable_entry("0004000000086300 (USA, v1.5)");
		new_unselectable_entry("0004000000086400 (EUR, v1.5)");
        new_unselectable_entry("Please download the original");
        new_unselectable_entry("ACNL from freeShop / CiaAngel");
		new_unselectable_entry("And install the v1.5 update!");
		
        return;
    }
    smenu();
}
