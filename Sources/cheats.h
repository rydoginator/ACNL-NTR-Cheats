#ifndef CHEATS_H
#define CHEATS_H

#include "../Includes/plugin.h"
#include <string.h>
#include <stdlib.h>

#define   add_search_replace(find, replace) g_find[g_i] = find; g_replace[g_i] = replace; g_i++
#define   reset_search()                    memset(g_find, 0, sizeof(g_find)); memset(g_replace, 0, sizeof(g_replace)); g_i = 0
#define   add_to_address(addr, value)       *(u32 *)addr += value
#define   sub_to_address(addr, value)       *(u32 *)addr -= value
#define OFFSET_TOWN_ITEMS 0x16005958
#define OFFSET_TOWN_ITEMS_EUR 0x16005c58
#define OFFSET_TOWN_ITEMS_JAP 0x1609D158
#define ITEM_BYTES 0x04
#define RANGE_TOWN_ITEMS 0x5000

#ifndef WRITES64
#   define WRITES64(addr, data)     *(vs64*)(addr) = data
#endif

#define	ADD64(addr, value)		*(vs64*)addr += value
#define SUB64(addr, value)		*(vs64*)addr -= value

#ifndef ADDTOFLOAT
#define ADDTOFLOAT(addr, add_value) *(float *)addr += (float)add_value
#define SUBTOFLOAT(addr, sub_value) *(float *)addr -= (float)sub_value
#endif

/*
** Helpers
*/

void	find_and_replace_multiple(void *start_addr, u32 length);
void  disableCheat(int index);

/*
** USA
*/

void    coord_usa(void);
void    seed_usa(void);
void    search_usa(void);
void    text2item_usa(void);
void    moonjump_usa(void);
void    teleport_usa(void);
void	warping_usa(void);
void	weeder_usa(void);
void	quench_usa(void);
void	tree_usa(void);
void	duplicate_usa(void);
void	grass_usa(void);
void	desert_usa(void);
void	speed_usa(void);
void	nook1_usa(void);
void	nook2_usa(void);
void	nook3_usa(void);
void	nook4_usa(void);
void	tan_usa(void);
void	text2item2_usa(void);
void	text2item3_usa(void);
void	text2item4_usa(void);
void	duplicate2_usa(void);
void	duplicate3_usa(void);
void	duplicate4_usa(void);
void	tan2_usa(void);
void	tan3_usa(void);
void	tan4_usa(void);
void	walkThru_usa(void);
void	edibleItems_usa(void);
void	seederV2_usa(void);
void	timeMachine_usa(void);
void	timeTravel_usa(void);

/*
** JAP
*/

void    coord_jap(void);
void    seed_jap(void);
void    search_jap(void);
void    text2item_jap(void);
void    moonjump_jap(void);
void    teleport_jap(void);
void	warping_jap(void);
void	weeder_jap(void);
void	quench_jap(void);
void	tree_jap(void);
void	duplicate_jap(void);
void	grass_jap(void);
void	desert_jap(void);
void	speed_jap(void);
void	nook1_jap(void);
void	nook2_jap(void);
void	nook3_jap(void);
void	nook4_jap(void);
void	tan_jap(void);
void	text2item2_jap(void);
void	text2item3_jap(void);
void	text2item4_jap(void);
void	duplicate2_jap(void);
void	duplicate3_jap(void);
void	duplicate4_jap(void);
void	tan2_jap(void);
void	tan3_jap(void);
void	tan4_jap(void);


/*
** EUR
*/

void    coord_eur(void);
void    seed_eur(void);
void    search_eur(void);
void    text2item_eur(void);
void    moonjump_eur(void);
void    teleport_eur(void);
void	warping_eur(void);
void	weeder_eur(void);
void	quench_eur(void);
void	tree_eur(void);
void	duplicate_eur(void);
void	grass_eur(void);
void	desert_eur(void);
void	speed_eur(void);
void	nook1_eur(void);
void	nook2_eur(void);
void	nook3_eur(void);
void	nook4_eur(void);
void	tan_eur(void);
void	text2item2_eur(void);
void	text2item3_eur(void);
void	text2item4_eur(void);
void	duplicate2_eur(void);
void	duplicate3_eur(void);
void	duplicate4_eur(void);
void	tan2_eur(void);
void	tan3_eur(void);
void	tan4_eur(void);
void	walkThru_eur(void);
void	edibleItems_eur(void);
void	seederV2_eur(void);
void	timeMachine_eur(void);
void	timeTravel_eur(void);


#endif
