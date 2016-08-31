#include "cheats.h"

char	*builder_name = "itsRyan";

void	usa_menu(void)
{
	new_unselectable_entry("ACNL NTR Cheats Ver 3.0 Beta 1");
	new_spoiler("Environment Codes");
		new_entry("Water all flowers", quench_usa);
		new_entry("Seeder", seed_usa);
		new_entry("Search and Replace", search_usa);
		new_entry("Grass", grass_usa);
		new_entry("Desert", desert_usa);
		new_entry("Remove all weeds", weeder_usa);
		new_entry("Instant Tree", tree_usa);
	exit_spoiler();
	new_spoiler("Player 1 Codes");
		new_entry("Text to Item", text2item_usa);
		new_entry("Duplication", duplicate_usa);
		new_entry("Max Tan", tan_usa);
	exit_spoiler();
	new_spoiler("Player 2 Codes");
		new_entry("Text to Item", text2item2_usa);
		new_entry("Duplication", duplicate2_usa);
		new_entry("Max Tan", tan2_usa);
	exit_spoiler();
	new_spoiler("Player 3 Codes");
		new_entry("Text to Item", text2item3_usa);
		new_entry("Duplication", duplicate3_usa);
		new_entry("Max Tan", tan3_usa);
	exit_spoiler();
	new_spoiler("Player 4 Codes");
		new_entry("Text to Item", text2item4_usa);
		new_entry("Duplication", duplicate4_usa);
		new_entry("Max Tan", tan4_usa);
	exit_spoiler();
	new_spoiler("Movement Codes");
		new_entry("Warping", warping_usa);
		new_entry("Moon Jump", moonjump_usa);
		new_entry("Coordinates Modifier", coord_usa);
		new_entry("Speed Hack", speed_usa);
		new_entry("Teleport", teleport_usa);
	exit_spoiler();
	new_spoiler("Nookling Upgrades");
		new_radio_entry("T&T Mart", nook1_usa);
		new_radio_entry("Super T&T", nook2_usa);
		new_radio_entry("T.I.Y", nook3_usa);
		new_radio_entry("T&T Emporium", nook4_usa);
	exit_spoiler();
	new_spoiler("Beta Codes");
		new_entry("Walk Thru Walls", walkThru_usa);
		new_entry("Edible Items", edibleItems_usa);
		new_entry("Seeder V2", seederV2_usa);
		new_entry("Time Travel", timeTravel_usa);
		new_entry("Time Machine", timeMachine_usa);
	exit_spoiler();
}

void	eur_menu(void)
{
	u32 index;

	new_unselectable_entry("ACNL NTR Cheats Ver 3.0 Alpha");
	index = new_spoiler("Environment Codes");
	set_note("Example note", index);
		new_entry("Water all flowers", quench_eur);
		new_entry("Seeder", seed_eur);
		new_entry("Search and Replace", search_eur);
		new_radio_entry("Grass", grass_eur);
		new_radio_entry("Desert", desert_eur);
		new_entry("Remove all weeds", weeder_eur);
		new_entry("Instant Tree", tree_eur);
	exit_spoiler();
	new_spoiler("Player 1 Codes");
		new_entry("Text to Item", text2item_eur);
		new_entry("Duplication", duplicate_eur);
		new_entry("Max Tan", tan_eur);
	exit_spoiler();
	new_spoiler("Player 2 Codes");
		new_entry("Text to Item", text2item2_eur);
		new_entry("Duplication", duplicate2_eur);
		new_entry("Max Tan", tan2_eur);
	exit_spoiler();
	new_spoiler("Player 3 Codes");
		new_entry("Text to Item", text2item3_eur);
		new_entry("Duplication", duplicate3_eur);
		new_entry("Max Tan", tan3_eur);
	exit_spoiler();
	new_spoiler("Player 4 Codes");
		new_entry("Text to Item", text2item4_eur);
		new_entry("Duplication", duplicate4_eur);
		new_entry("Max Tan", tan4_eur);
	exit_spoiler();
	new_spoiler("Movement Codes");
		new_entry("Warping", warping_eur);
		new_entry("Moon Jump", moonjump_eur);
		new_entry("Coordinates Modifier", coord_eur);
		new_entry("Speed Hack", speed_eur);
		new_entry("Teleport", teleport_eur);
	exit_spoiler();
	new_spoiler("Nookling Upgrades");
		new_radio_entry("T&T Mart", nook1_eur);
		new_radio_entry("Super T&T", nook2_eur);
		new_radio_entry("T.I.Y", nook3_eur);
		new_radio_entry("T&T Emporium", nook4_eur);
	exit_spoiler();
}

void	jap_menu(void)
{
	new_unselectable_entry("ACNL NTR Cheats Ver 3.0 Alpha");
	new_spoiler("Environment Codes");
		new_entry("Water all flowers", quench_jap);
		new_entry("Seeder", seed_jap);
		new_entry("Search and Replace", search_jap);
		new_entry("Grass", grass_jap);
		new_entry("Desert", desert_jap);
		new_entry("Remove all weeds", weeder_jap);
		new_entry("Instant Tree", tree_jap);
	exit_spoiler();
	new_spoiler("Player 1 Codes");
		new_entry("Text to Item", text2item_jap);
		new_entry("Duplication", duplicate_jap);
		new_entry("Max Tan", tan_usa);
	exit_spoiler();
	new_spoiler("Player 2 Codes");
		new_entry("Text to Item", text2item2_jap);
		new_entry("Duplication", duplicate2_jap);
		new_entry("Max Tan", tan2_jap);
	exit_spoiler();
	new_spoiler("Player 3 Codes");
		new_entry("Text to Item", text2item3_jap);
		new_entry("Duplication", duplicate3_jap);
		new_entry("Max Tan", tan3_jap);
	exit_spoiler();
	new_spoiler("Player 4 Codes");
		new_entry("Text to Item", text2item4_jap);
		new_entry("Duplication", duplicate4_jap);
		new_entry("Max Tan", tan4_jap);
	exit_spoiler();
	exit_spoiler();
	new_spoiler("Movement Codes");
		new_entry("Warping", warping_jap);
		new_entry("Moon Jump", moonjump_jap);
		new_entry("Coordinates Modifier", coord_jap);
		new_entry("Speed Hack", speed_jap);
		new_entry("Teleport", teleport_jap);
	exit_spoiler();
	new_spoiler("Nookling Upgrades");
		new_radio_entry("T&T Mart", nook1_jap);
		new_radio_entry("Super T&T", nook2_jap);
		new_radio_entry("T.I.Y", nook3_jap);
		new_radio_entry("T&T Emporium", nook4_jap);
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
		new_unselectable_entry("!!! You need either       !!!");
		new_unselectable_entry("!!! 00040000 00086200     !!!");
		new_unselectable_entry("!!! or                    !!!");
		new_unselectable_entry("!!! 00040000 00086300     !!!");
		new_unselectable_entry("!!! or                    !!!");
		new_unselectable_entry("!!! 00040000 00086400     !!!");
	}

}