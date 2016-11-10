#include "cheats.h"

char	*builder_name = "itsRyan";

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
	static const char * const seed_note = "Drop 100 bells, Type item ID,\n\nR+D Pad Down to Set,\n\nR+D Pad Up to Destroy,\n\nR+D Pad Left to Undo";
	static const char * const tree_note = "Press X for your tree to instantly grow!";
	static const char * const sar_note = "Type in XXXXYYYY where XXXX is search value and YYYY is repalce value. Send it in chat, and press L + D pad left to execute.";
	static const char * const ra_note =	"Enable one R+A cheat at a time,\n\nExecute one,\n\nThen go in and out of a house.";
	static const char * const warning_note = "!!! Warning !!!\n\nIn order to prevent a crash of the game," \
    "we strongly advise you to only open the menu either on the title screen or indoor.\n\nDon't ever open during a multiplayer session!";
	static const char * const real_note = "Type in the ID of the item ID you want, send it into chat and press R + D pad down to place the item directly where you're standing.";
	static const char * const des_note = "Press R + A to remove your grass!";
	static const char * const lush_note = "Press R + A to replenish all your grass!";
	static const char * const weed_note = "Press R + A to remove all weeds!";
	static const char * const flwr_note = "Press R + A to replenish all your flowers!";

void with_note_common(const char *name, const char *note, void (*cheatfunction)(void), int type)
{
	int 	index;

	if (type == 0)
		new_entry((char *)name, cheatfunction);
	else if (type == 1)
		new_radio_entry((char *)name, cheatfunction);
	else if (type == 2)
		new_spoiler((char *)name);
	else return;
	set_note(note, index);
}

inline void	new_entry_with_note(const char *name, const char *note, void (*cheatfunction)(void))
{
	with_note_common(name, note, cheatfunction, 0);
}

inline void	new_radio_entry_with_note(const char *name, const char *note, void (*cheatfunction)(void))
{
	with_note_common(name, note, cheatfunction, 1);
}

inline void	new_spoiler_with_note(const char *name, const char *note)
{
	with_note_common(name, note, NULL, 2);
}

void	usa_menu(void)
{
	new_unselectable_entry("ACNL NTR Cheats Ver 3.0.1 USA");
	new_entry_with_note("Warning ! Read the note !", warning_note, keep_it_off);
	new_spoiler_with_note("Environment Codes", enviro_note);
		new_spoiler("R + A Codes");
			new_radio_entry_with_note("Remove all weeds", weed_note, weeder_usa);
			new_radio_entry_with_note("Water all flowers", flwr_note, quench_usa);
			new_radio_entry_with_note("Grass", lush_note, grass_usa);
			new_radio_entry_with_note("Desert", des_note, desert_usa);
		exit_spoiler();
		new_entry_with_note("Real Time World Edit", real_note, real_usa);
		new_entry_with_note("Seeder", seed_note, seed_usa);
		new_entry_with_note("Search and Replace", sar_note, search_usa);
		new_entry_with_note("Instant Tree", tree_note, tree_usa);
	exit_spoiler();
	new_spoiler("Inventory Codes");
		new_entry_with_note("Text to Item", t2i_note, text2item_usa);
		new_entry_with_note("Duplication", dup_note, duplicate_usa);
		new_spoiler_with_note("Tan Modifier", tan_note);
			new_radio_entry("0", tan_usa);
			new_radio_entry("1", tan1_usa);
			new_radio_entry("2", tan2_usa);
			new_radio_entry("3", tan3_usa);
			new_radio_entry("4", tan4_usa);
			new_radio_entry("5", tan5_usa);
			new_radio_entry("6", tan6_usa);
			new_radio_entry("7", tan7_usa);
			new_radio_entry("8", tan8_usa);
			new_radio_entry("9", tan9_usa);
			new_radio_entry("10", tan10_usa);
			new_radio_entry("11", tan11_usa);
			new_radio_entry("12", tan12_usa);
			new_radio_entry("13", tan13_usa);
			new_radio_entry("14", tan14_usa);
			new_radio_entry("15", tan15_usa);
		exit_spoiler();
	exit_spoiler();
	new_spoiler_with_note("Movement Codes", trans_note);
		new_entry_with_note("Warping", warp_note, warping_usa);
		new_entry_with_note("Moon Jump", mj_note, moonjump_usa);
		new_entry_with_note("Coordinates Modifier", cm_note, coord_usa);
		new_entry_with_note("Speed Hack", speed_note, speed_usa);
		new_entry_with_note("Teleport", tele_note, teleport_usa);
	exit_spoiler();
	new_spoiler("Nookling Upgrades");
		new_radio_entry("T&T Mart", nook1_usa);
		new_radio_entry("Super T&T", nook2_usa);
		new_radio_entry("T.I.Y", nook3_usa);
		new_radio_entry("T&T Emporium", nook4_usa);
	exit_spoiler();
	new_spoiler_with_note("Time Travel Codes", time_note);
		//new_entry_with_note("Edible Items", edibleItems_usa);
		//new_entry_with_note("Seeder V2", seederV2_usa);
		new_entry_with_note("Time Travel", tt_note, timeTravel_usa);
		new_entry_with_note("Time Machine", tm_note, timeMachine_usa);
	exit_spoiler();
}

void	eur_menu(void)
{
	new_unselectable_entry("ACNL NTR Cheats Ver 3.0.1 EUR");
	new_entry_with_note("Warning ! Read the note !", warning_note, keep_it_off);
	new_spoiler_with_note("Environment Codes", enviro_note);
		new_spoiler("R + A Codes");
			new_radio_entry_with_note("Remove all weeds", weed_note, weeder_eur);
			new_radio_entry_with_note("Water all flowers", flwr_note, quench_eur);
			new_radio_entry_with_note("Grass", lush_note, grass_eur);
			new_radio_entry_with_note("Desert", des_note, desert_eur);
		exit_spoiler();
		new_entry_with_note("Real Time World Edit", real_note, real_eur);
		new_entry_with_note("Seeder", seed_note, seed_eur);
		new_entry_with_note("Search and Replace", sar_note, search_eur);
		new_entry_with_note("Instant Tree", tree_note, tree_eur);
	exit_spoiler();
	new_spoiler("Inventory Codes");
		new_entry_with_note("Text to Item", t2i_note, text2item_eur);
		new_entry_with_note("Duplication", dup_note, duplicate_eur);
		new_spoiler_with_note("Tan Modifier", tan_note);
			new_radio_entry("0", tan_eur);
			new_radio_entry("1", tan1_eur);
			new_radio_entry("2", tan2_eur);
			new_radio_entry("3", tan3_eur);
			new_radio_entry("4", tan4_eur);
			new_radio_entry("5", tan5_eur);
			new_radio_entry("6", tan6_eur);
			new_radio_entry("7", tan7_eur);
			new_radio_entry("8", tan8_eur);
			new_radio_entry("9", tan9_eur);
			new_radio_entry("10", tan10_eur);
			new_radio_entry("11", tan11_eur);
			new_radio_entry("12", tan12_eur);
			new_radio_entry("13", tan13_eur);
			new_radio_entry("14", tan14_eur);
			new_radio_entry("15", tan15_eur);
		exit_spoiler();
	exit_spoiler();
	new_spoiler_with_note("Movement Codes", trans_note);
		new_entry_with_note("Warping", warp_note, warping_eur);
		new_entry_with_note("Moon Jump", mj_note, moonjump_eur);
		new_entry_with_note("Coordinates Modifier", cm_note, coord_eur);
		new_entry_with_note("Speed Hack", speed_note, speed_eur);
		new_entry_with_note("Teleport", tele_note, teleport_eur);
	exit_spoiler();
	new_spoiler("Nookling Upgrades");
		new_radio_entry("T&T Mart", nook1_eur);
		new_radio_entry("Super T&T", nook2_eur);
		new_radio_entry("T.I.Y", nook3_eur);
		new_radio_entry("T&T Emporium", nook4_eur);
	exit_spoiler();
	new_spoiler_with_note("Time Travel Codes", time_note);
		//new_entry_with_note("Edible Items", edibleItems_eur);
		//new_entry_with_note("Seeder V2", seederV2_eur);
		new_entry_with_note("Time Travel", tt_note, timeTravel_eur);
		new_entry_with_note("Time Machine", tm_note, timeMachine_eur);
	exit_spoiler();
}

void	jap_menu(void)
{
	new_unselectable_entry("ACNL NTR Cheats Ver 3.0.1 JAP");
	new_entry_with_note("Warning ! Read the note !", warning_note, keep_it_off);
	new_spoiler_with_note("Environment Codes", enviro_note);
		new_spoiler("R + A Codes");
			new_radio_entry_with_note("Remove all weeds", weed_note, weeder_jap);
			new_radio_entry_with_note("Water all flowers", flwr_note, quench_jap);
			new_radio_entry_with_note("Grass", lush_note, grass_jap);
			new_radio_entry_with_note("Desert", des_note, desert_jap);
		exit_spoiler();
		new_entry_with_note("Real Time World Edit", real_note, real_jap);
		new_entry_with_note("Seeder", seed_note, seed_jap);
		new_entry_with_note("Search and Replace", sar_note, search_jap);
		new_entry_with_note("Instant Tree", tree_note, tree_jap);
	exit_spoiler();
	new_spoiler("Inventory Codes");
		new_entry_with_note("Text to Item", t2i_note, text2item_jap);
		new_entry_with_note("Duplication", dup_note, duplicate_jap);
		new_spoiler_with_note("Tan Modifier", tan_note);
			new_radio_entry("0", tan_jap);
			new_radio_entry("1", tan1_jap);
			new_radio_entry("2", tan2_jap);
			new_radio_entry("3", tan3_jap);
			new_radio_entry("4", tan4_jap);
			new_radio_entry("5", tan5_jap);
			new_radio_entry("6", tan6_jap);
			new_radio_entry("7", tan7_jap);
			new_radio_entry("8", tan8_jap);
			new_radio_entry("9", tan9_jap);
			new_radio_entry("10", tan10_jap);
			new_radio_entry("11", tan11_jap);
			new_radio_entry("12", tan12_jap);
			new_radio_entry("13", tan13_jap);
			new_radio_entry("14", tan14_jap);
			new_radio_entry("15", tan15_jap);
		exit_spoiler();
	exit_spoiler();
	new_spoiler_with_note("Movement Codes", trans_note);
		new_entry_with_note("Warping", warp_note, warping_jap);
		new_entry_with_note("Moon Jump", mj_note, moonjump_jap);
		new_entry_with_note("Coordinates Modifier", cm_note, coord_jap);
		new_entry_with_note("Speed Hack", speed_note, speed_jap);
		new_entry_with_note("Teleport", tele_note, teleport_jap);
	exit_spoiler();
	new_spoiler("Nookling Upgrades");
		new_radio_entry("T&T Mart", nook1_jap);
		new_radio_entry("Super T&T", nook2_jap);
		new_radio_entry("T.I.Y", nook3_jap);
		new_radio_entry("T&T Emporium", nook4_jap);
	exit_spoiler();
	new_spoiler_with_note("Time Travel Codes", time_note);
		//new_entry_with_note("Edible Items", edibleItems_jap);
		//new_entry_with_note("Seeder V2", seederV2_jap);
		new_entry_with_note("Time Travel", tt_note, timeTravel_jap);
		new_entry_with_note("Time Machine", tm_note, timeMachine_jap);
	exit_spoiler();
}

/*
** USA: 00040000 00086300
** EUR: 00040000 00086400
** JAP: 00040000 00086200
*/
void	my_menus(void)
{
	u32	tid;
	
	set_hid_address(0x10002000); //This is in order to unlock the advanced HID capabilities such as Touchscreen and the stick (No N3DS hid for the moment)
	tid = get_tid_low();
	if (tid == 0x86300)
		usa_menu();
	else if (tid == 0x86400)
		eur_menu();
	else if (tid == 0x86200)
		jap_menu();
	else
	{
		new_unselectable_entry("Unsupported ID");
		new_unselectable_entry("!!! Title id unrecognized !!!");
		new_unselectable_entry("!!! You need      !!!");
		//new_unselectable_entry("!!! 00040000 00086200     !!!");
		//new_unselectable_entry("!!! or                    !!!");
		new_unselectable_entry("!!! 00040000 00086300     !!!");
		//new_unselectable_entry("!!! or                    !!!");
		//new_unselectable_entry("!!! 00040000 00086400     !!!");
	}

}
