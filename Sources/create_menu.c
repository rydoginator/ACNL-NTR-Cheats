#include "cheats.h"

char	*builder_name = "itsRyan";

void	usa_menu(void)
{
	new_unselectable_entry("ACNL NTR Cheats Ver 3.0 USA");
	new_spoiler("Environment Codes");
		new_spoiler("R + A Codes");
			new_radio_entry("Remove all weeds", weeder_usa);
			new_radio_entry("Water all flowers", quench_usa);
			new_radio_entry("Grass", grass_usa);
			new_radio_entry("Desert", desert_usa);
		exit_spoiler();
		new_entry("Real Time World Edit", real);
		new_entry("Seeder", seed_usa);
		new_entry("Search and Replace", search_usa);
		new_entry("Instant Tree", tree_usa);
	exit_spoiler();
	new_spoiler("Inventory Codes");
		new_entry("Text to Item", text2item_usa);
		new_entry("Duplication", duplicate_usa);
		//new_entry("Max Tan", tan_usa);
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
		//new_entry("Edible Items", edibleItems_usa);
		//new_entry("Seeder V2", seederV2_usa);
		new_entry("Time Travel", timeTravel_usa);
		new_entry("Time Machine", timeMachine_usa);
	exit_spoiler();
}

void	eur_menu(void)
{
	u32 index;

	new_unselectable_entry("ACNL NTR Cheats 3.0 EUR");
	new_spoiler("Environment Codes");
		new_spoiler("R + A Codes");
			new_radio_entry("Remove all weeds", weeder_eur);
			new_radio_entry("Water all flowers", quench_eur);
			new_radio_entry("Grass", grass_eur);
			new_radio_entry("Desert", desert_eur);
		exit_spoiler();
		new_entry("Real Time World Edit", real_eur);
		new_entry("Seeder", seed_eur);
		new_entry("Search and Replace", search_eur);
		new_entry("Instant Tree", tree_eur);
	exit_spoiler();
	new_spoiler("Inventory Codes");
		new_entry("Text to Item", text2item_eur);
		new_entry("Duplication", duplicate_eur);
		//new_entry("Max Tan", tan_usa);
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
	new_spoiler("Beta Codes");
		//new_entry("Walk Thru Walls", walkThru_eur);
		//new_entry("Edible Items", edibleItems_eur);
		//new_entry("Seeder V2", seederV2_eur);
		new_entry("Time Travel", timeTravel_eur);
		new_entry("Time Machine", timeMachine_eur);
	exit_spoiler();
}

void	jap_menu(void)
{
	new_unselectable_entry("Your version is not supported yet.");
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
