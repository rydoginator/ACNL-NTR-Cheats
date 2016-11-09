#include "cheats.h"

char	*builder_name = "itsRyan";

	static const char * const t2i = "Type item ID and send it into chat,\n\nPress X+D Pad Right,\n\nTo write item to slot 1!";
	static const char * const dup = "Press R to duplicate the slot 1 item to slot 2!";
	static const char * const tan = "Go into a different room to see changes.";
	static const char * const trans = "Do not execute during loading screens!";
	static const char * const cm = "Press A+D Pad in any direction to move around at turbo speed!";
	static const char * const mj = "Press and hold L to moon jump!";
	static const char * const tele = "B+D Pad Up to save,\n\nB+D Pad Down to teleport,\n\nPress L/R to store multiple.";
	static const char * const speed = "Press and hold B to start running at turbo fast speed!";
	static const char * const warp = "Touch the map to warp anywhere!";
	static const char * const time = "Do not use online!";
	static const char * const tt = "Fast forward: B+D Pad Right;\n\nRewind: B+D Pad Left,\n\nB+D Pad Down to revert ingame time to system time.\n\nPress L+D Pad Right/Left to watch time rewind/fastforward.";
	static const char * const tm = "Type YYMMDDHHmm,\n\nPress Y+D Pad Right to fast forward to that,\n\nOr press Y+D Pad Left to rewind that amount.";
	static const char * const enviro = "After executing one of these codes,\n\nUpdate the status to verify the object!";
	static const char * const seed = "Drop 100 bells, Type item ID,\n\nR+D Pad Down to Set,\n\nR+D Pad Up to Destroy,\n\nR+D Pad Left to Undo";
	static const char * const tree = "Press X for your tree to instantly grow!";
	static const char * const sar = "Type in XXXXYYYY where XXXX is search value and YYYY is repalce value. Send it in chat, and press L + D pad left to execute.";
	static const char * const ra =	"Enable one R+A cheat at a time,\n\nExecute one,\n\nThen go in and out of a house.";
	static const char * const warning = "!!! Warning !!!\n\nIn order to prevent a crash of the game," \
    "we strongly advise you to only open the menu either on the title screen or indoor.\n\nDon't ever open during a multiplayer session!";
	static const char * const real = "Type in the ID of the item ID you want, send it into chat and press R + D pad down to place the item directly where you're standing.";
	static const char * const des = "Press R + A to remove your grass!";
	static const char * const lush = "Press R + A to replenish all your grass!";
	static const char * const weed = "Press R + A to remove all weeds!";
	static const char * const flwr = "Press R + A to replenish all your flowers!";

void	usa_menu(void)
{
	int index;
	new_unselectable_entry("ACNL NTR Cheats Ver 3.0.1 USA");
	index = new_entry("Warning!", keep_it_off);
		set_note(warning, index);
	index = new_spoiler("Environment Codes");
		set_note(enviro, index);
		new_spoiler("R + A Codes");
			index = new_radio_entry("Remove all weeds", weeder_usa);
				set_note(weed, index);
			index = new_radio_entry("Water all flowers", quench_usa);
				set_note(flwr, index);
			index = new_radio_entry("Grass", grass_usa);
				set_note(lush, index);
			index = new_radio_entry("Desert", desert_usa);
				set_note(des, index);
		exit_spoiler();
		index = new_entry("Real Time World Edit", real_usa);
			set_note(real, index);
		index = new_entry("Seeder", seed_usa);
			set_note(seed, index);
		index = new_entry("Search and Replace", search_usa);
			set_note(sar, index);
		index = new_entry("Instant Tree", tree_usa);
			set_note(tree, index);
	exit_spoiler();
	new_spoiler("Inventory Codes");
		index = new_entry("Text to Item", text2item_usa);
			set_note(t2i, index);
		index = new_entry("Duplication", duplicate_usa);
			set_note(dup, index);
		index = new_spoiler("Tan Modifier");
			set_note(tan, index);
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
	index = new_spoiler("Movement Codes");
		set_note(trans, index);
		index = new_entry("Warping", warping_usa);
			set_note(warp, index);
		index = new_entry("Moon Jump", moonjump_usa);
			set_note(mj, index);
		index = new_entry("Coordinates Modifier", coord_usa);
			set_note(cm, index);
		index = new_entry("Speed Hack", speed_usa);
			set_note(speed, index);
		index = new_entry("Teleport", teleport_usa);
			set_note(tele, index);
	exit_spoiler();
	new_spoiler("Nookling Upgrades");
		new_radio_entry("T&T Mart", nook1_usa);
		new_radio_entry("Super T&T", nook2_usa);
		new_radio_entry("T.I.Y", nook3_usa);
		new_radio_entry("T&T Emporium", nook4_usa);
	exit_spoiler();
	index = new_spoiler("Time Travel Codes");
		set_note(time, index);
		//new_entry("Edible Items", edibleItems_usa);
		//new_entry("Seeder V2", seederV2_usa);
		index = new_entry("Time Travel", timeTravel_usa);
			set_note(tt, index);
		index = new_entry("Time Machine", timeMachine_usa);
			set_note(tm, index);
	exit_spoiler();
}

void	eur_menu(void)
{
	int index;
	new_unselectable_entry("ACNL NTR Cheats Ver 3.0.1 EUR");
	index = new_entry("Warning!", keep_it_off);
		set_note(warning, index);
	index = new_spoiler("Environment Codes");
		set_note(enviro, index);
		new_spoiler("R + A Codes");
			index = new_radio_entry("Remove all weeds", weeder_eur);
				set_note(weed, index);
			index = new_radio_entry("Water all flowers", quench_eur);
				set_note(flwr, index);
			index = new_radio_entry("Grass", grass_eur);
				set_note(lush, index);
			index = new_radio_entry("Desert", desert_eur);
				set_note(des, index);
		exit_spoiler();
		index = new_entry("Real Time World Edit", real_eur);
			set_note(real, index);
		index = new_entry("Seeder", seed_eur);
			set_note(seed, index);
		index = new_entry("Search and Replace", search_eur);
			set_note(sar, index);
		index = new_entry("Instant Tree", tree_eur);
			set_note(tree, index);
	exit_spoiler();
	new_spoiler("Inventory Codes");
		index = new_entry("Text to Item", text2item_eur);
			set_note(t2i, index);
		index = new_entry("Duplication", duplicate_eur);
			set_note(dup, index);
		index = new_spoiler("Tan Modifier");
			set_note(tan, index);
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
	index = new_spoiler("Movement Codes");
		set_note(trans, index);
		index = new_entry("Warping", warping_eur);
			set_note(warp, index);
		index = new_entry("Moon Jump", moonjump_eur);
			set_note(mj, index);
		index = new_entry("Coordinates Modifier", coord_eur);
			set_note(cm, index);
		index = new_entry("Speed Hack", speed_eur);
			set_note(speed, index);
		index = new_entry("Teleport", teleport_eur);
			set_note(tele, index);
	exit_spoiler();
	new_spoiler("Nookling Upgrades");
		new_radio_entry("T&T Mart", nook1_eur);
		new_radio_entry("Super T&T", nook2_eur);
		new_radio_entry("T.I.Y", nook3_eur);
		new_radio_entry("T&T Emporium", nook4_eur);
	exit_spoiler();
	index = new_spoiler("Time Travel Codes");
		set_note(time, index);
		//new_entry("Edible Items", edibleItems_eur);
		//new_entry("Seeder V2", seederV2_eur);
		index = new_entry("Time Travel", timeTravel_eur);
			set_note(tt, index);
		index = new_entry("Time Machine", timeMachine_eur);
			set_note(tm, index);
	exit_spoiler();
}

void	jap_menu(void)
{
	int index;
	new_unselectable_entry("ACNL NTR Cheats Ver 3.0.1 JAP");
	index = new_entry("Warning!", keep_it_off);
		set_note(warning, index);
	index = new_spoiler("Environment Codes");
		set_note(enviro, index);
		new_spoiler("R + A Codes");
			index = new_radio_entry("Remove all weeds", weeder_jap);
				set_note(weed, index);
			index = new_radio_entry("Water all flowers", quench_jap);
				set_note(flwr, index);
			index = new_radio_entry("Grass", grass_jap);
				set_note(lush, index);
			index = new_radio_entry("Desert", desert_jap);
				set_note(des, index);
		exit_spoiler();
		index = new_entry("Real Time World Edit", real_jap);
			set_note(real, index);
		index = new_entry("Seeder", seed_jap);
			set_note(seed, index);
		index = new_entry("Search and Replace", search_jap);
			set_note(sar, index);
		index = new_entry("Instant Tree", tree_jap);
			set_note(tree, index);
	exit_spoiler();
	new_spoiler("Inventory Codes");
		index = new_entry("Text to Item", text2item_jap);
			set_note(t2i, index);
		index = new_entry("Duplication", duplicate_jap);
			set_note(dup, index);
		index = new_spoiler("Tan Modifier");
			set_note(tan, index);
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
	index = new_spoiler("Movement Codes");
		set_note(trans, index);
		index = new_entry("Warping", warping_jap);
			set_note(warp, index);
		index = new_entry("Moon Jump", moonjump_jap);
			set_note(mj, index);
		index = new_entry("Coordinates Modifier", coord_jap);
			set_note(cm, index);
		index = new_entry("Speed Hack", speed_jap);
			set_note(speed, index);
		index = new_entry("Teleport", teleport_jap);
			set_note(tele, index);
	exit_spoiler();
	new_spoiler("Nookling Upgrades");
		new_radio_entry("T&T Mart", nook1_jap);
		new_radio_entry("Super T&T", nook2_jap);
		new_radio_entry("T.I.Y", nook3_jap);
		new_radio_entry("T&T Emporium", nook4_jap);
	exit_spoiler();
	index = new_spoiler("Time Travel Codes");
		set_note(time, index);
		//new_entry("Edible Items", edibleItems_jap);
		//new_entry("Seeder V2", seederV2_jap);
		index = new_entry("Time Travel", timeTravel_jap);
			set_note(tt, index);
		index = new_entry("Time Machine", timeMachine_jap);
			set_note(tm, index);
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
