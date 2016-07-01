#include "cheats.h"

char	*builder_name = "itsRyan";

extern u32 tid_low;
extern u32 tid_high;

void	usa_menu(void)
{
	t_spoil spoiler;

	new_unselectable_entry("ACNL NTR Cheats Ver 2.1 Beta 3 USA");
	spoiler = new_spoiler("Enviroment Codes");
		new_spoiled_entry(spoiler, "Water all flowers", quench_usa);
		new_spoiled_entry(spoiler, "Seeder", seed_usa);
		new_spoiled_entry(spoiler, "Search and Replace (WIP)", search_usa);
		new_spoiled_entry(spoiler, "Grass", grass_usa);
		new_spoiled_entry(spoiler, "Desert", desert_usa);
		new_spoiled_entry(spoiler, "Remove all weeds", weeder_usa);
		new_spoiled_entry(spoiler, "Instant Tree", tree_usa);
	spoiler = new_spoiler("Inventory Codes");
		new_spoiled_entry(spoiler, "Text to Item", text2item_usa);
		new_spoiled_entry(spoiler, "Duplication", duplicate_usa);
	spoiler = new_spoiler("Movement Codes");
		new_spoiled_entry(spoiler, "Moon Jump", moonjump_usa);
		new_spoiled_entry(spoiler, "Teleport", teleport_usa);
		new_spoiled_entry(spoiler, "Coordinates Modifier", coord_usa);
}

void	eur_menu(void)
{
	t_spoil spoiler;

	new_unselectable_entry("ACNL NTR Cheats Ver 2.1 Beta 2 EUR");
	spoiler = new_spoiler("Enviroment Codes");
		new_spoiled_entry(spoiler, "Water all flowers", quench_eur);
		new_spoiled_entry(spoiler, "Seeder", seed_eur);
		new_spoiled_entry(spoiler, "Destroyer", search_eur);
		new_spoiled_entry(spoiler, "Grass", grass_eur);
		new_spoiled_entry(spoiler, "Desert", desert_eur);
		new_spoiled_entry(spoiler, "Remove all weeds", weeder_eur);
		new_spoiled_entry(spoiler, "Instant Tree", tree_eur);
	spoiler = new_spoiler("Inventory Codes");
		new_spoiled_entry(spoiler, "Text to Item", text2item_eur);
		new_spoiled_entry(spoiler, "Duplication", duplicate_eur);
	spoiler = new_spoiler("Movement Codes");
		new_spoiled_entry(spoiler, "Moon Jump", moonjump_eur);
		new_spoiled_entry(spoiler, "Teleport", teleport_eur);
		new_spoiled_entry(spoiler, "Coordinates Modifier", coord_eur);
}

/*
** USA: 00040000 00086300
** EUR: 00040000 00086400
*/
void	my_menus(void)
{
	if (tid_low == 0x86300)
		usa_menu();
	else if (tid_low == 0x86400)
		eur_menu();
	else
	{
		new_unselectable_entry("Unsupported ID");
		new_unselectable_entry("!!! Title id unrecognized !!!");
		new_unselectable_entry("!!! You need either       !!!");
		new_unselectable_entry("!!! 00040000 00086300     !!!");
		new_unselectable_entry("!!! or                    !!!");
		new_unselectable_entry("!!! 00040000 00086400     !!!");
	}

}