#ifndef CHEATS_H
#define CHEATS_H

#include "../Includes/plugin.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define     add_search_replace(find, replace)   g_find[g_i] = find; g_replace[g_i] = replace; g_i++
#define     reset_search()                      memset(g_find, 0, sizeof(g_find)); memset(g_replace, 0, sizeof(g_replace)); g_i = 0
#define     add_to_address(addr, value)         *(u32 *)addr += value
#define     sub_to_address(addr, value)         *(u32 *)addr -= value
#define     ADD64(addr, value)                  *(vs64 *)addr += value
#define     SUB64(addr, value)                  *(vs64 *)addr -= value
#define     ADDTOFLOAT(addr, add_value)         *(float *)addr += (float)add_value
#define     SUBTOFLOAT(addr, sub_value)         *(float *)addr -= (float)sub_value



/*
** USA Addresses
*/
#define     USA_LOCATION_ADDR                   0x33077504
#define     USA_INDOOR_POS_X_ADDR               0x330774fc
#define     USA_INDOOR_POS_Y_ADDR               0x33077500
#define     USA_INDOOR_POS_Z_ADDR               0x33077504
#define     USA_OUTDOOR_POS_X_ADDR              0x330773D0
#define     USA_OUTDOOR_POS_Y_ADDR              0x330773D4
#define     USA_OUTDOOR_POS_Z_ADDR              0x330773D8
#define     USA_TOWN_ITEMS_ADDR                 0x31F7A458
#define     USA_ISLAND_ITEMS_ADDR               0x31F96E58
#define     USA_PLAYER_ADDR                     0xAAE990 //0xAAD990, 0xAA6990
#define     USA_INV_ADDR                        0x31F2DBF0
#define     USA_VELOCITY_ADDR                   0x330773FC
#define     USA_GRASS_START_ADDR                0x31F80880
#define     USA_GRASS_END_ADDR                  0x31F8307F
#define     USA_NOOK_ADDR                       0x31F891E4
#define     USA_LEIF_ADDR                       0x31F8D674
#define     USA_TAN_ADDR                        0x31F27028
#define     USA_SEED_ADDR                       0x9B5268 //9AD248, 9B4268
#define     USA_EDIBLE_ADDR                     0x33077C86
#define     USA_ID_ADDR                         0x32CB0F60 
#define	    USA_SAVETIME_ADDR                   0x31F89120
#define     USA_REALTIME_ADDR                   0x95D508 //955500, 95c500
#define     USA_WORLD_X_ADDR                    0x33077838
#define     USA_WORLD_Y_ADDR                    0x3307783C
#define     USA_INPUT_TEXT_ADDR                 0x32CB0F60
#define     EUR_INPUT_TEXT_ADDR                 0x32C88BE0
#define     JAP_INPUT_TEXT_ADDR                 0x32CD39E0
#define		USA_VISITOR_OUTDOOR_X_ADDR			0x33079190
#define		USA_VISITOR_OUTDOOR_Z_ADDR			0x33079198
#define		USA_VISITOR_INDOOR_X_ADDR			0x330792bc
#define		USA_VISITOR_INDOOR_Z_ADDR			0x330792c4
#define		USA_MINUTES_ADDR					0x9515BA
#define		USA_HOURS_ADDR						0x9515BB
#define		USA_ONLINE0_INV_ADDR				0xAAB0e0
#define		USA_ONLINE1_INV_ADDR				0xA8C360
#define		USA_ONLINE2_INV_ADDR				0xA967E0
#define		USA_ONLINE3_INV_ADDR				0xAA0C60
#define		USA_ONLINE4_INV_ADDR				0xA8C360
#define		USA_ONLINE5_INV_ADDR				0xA967E0
#define		USA_ONLINE6_INV_ADDR				0xA9EC60
#define		USA_KEYBOARD_ADDR					0x32DC4A10
#define		USA_KEYBOARD_ISLAND_ADDR			0x32DD0FB8
#define		EUR_KEYBOAD_ISLAND_ADDR				0x32DCF994
#define		USA_INPUT_TEXT_ISLAND_ADDR			0x32CBD508
#define		USA_ABD_ADDR 						0x32DD1AC8 //this one stays in memory, so it is used to write to the inventory. nvm, it doesn't
#define		USA_ABD_REAL_ADDR					0x32DD1EF8 //this one is the real decimal offset,
#define		USA_ABD_OFFLINE_ADDR				0x32DC5520
#define		USA_WALKOVER_ADDR					0x33077533

#define		USA_CONDITIONAL_OUT_ADDR			0x33077524
#define		USA_CONDITIONAL_IN_ADDR				0x33077650
#define		USA_COLLISION_OUT_ADDR				0x33077534
#define		USA_COLLISION_IN_ADDR				0x33077663
#define		USA_QUICKFIRE_ADDR					0x33077537
#define		USA_GRAVITY_OUT_ADDR				0x33077537

#define		USA_KEYBOARD_POINTER				0x95F110
#define     USA_BANK_ADDR                       0x31F2DBAC
#define     USA_ONLINE0_BANK_ADDR               0xAAB09C
#define     USA_ONLINE1_BANK_ADDR               0xA8C31C
#define     USA_ONLINE2_BANK_ADDR               0xA9679C
#define     USA_ONLINE3_BANK_ADDR               0xAA0C1C
#define     USA_ONLINE4_BANK_ADDR               0xA8C31C
#define     USA_ONLINE5_BANK_ADDR               0xA9679C
#define     USA_ONLINE6_BANK_ADDR               0xA9EC1C

#define     USA_MEOW_ADDR                       0x31F2FD3C
#define     USA_ONLINE0_MEOW_ADDR               0xAAD22C
#define     USA_ONLINE1_MEOW_ADDR               0xA8E4AC
#define     USA_ONLINE2_MEOW_ADDR               0xA9892C
#define     USA_ONLINE3_MEOW_ADDR               0xAA2DAC
#define     USA_ONLINE4_MEOW_ADDR               0xA8E4AC
#define     USA_ONLINE5_MEOW_ADDR               0xA9892C
#define     USA_ONLINE6_MEOW_ADDR               0xAA0DAC

#define     USA_WALLET_ADDR                     0x31F2DF28
#define     USA_ONLINE0_WALLET_ADDR             0xAAB418
#define     USA_ONLINE1_WALLET_ADDR             0xA8C698
#define     USA_ONLINE2_WALLET_ADDR             0xA96B18
#define     USA_ONLINE3_WALLET_ADDR             0xAA0F98
#define     USA_ONLINE4_WALLET_ADDR             0xA8C698
#define     USA_ONLINE5_WALLET_ADDR             0xA96B18
#define     USA_ONLINE6_WALLET_ADDR             0xA9EF98

#define		USA_CONFIRM_BOOL_ADDR				0x32DC6555
#define		USA_NOOKLING1_PRICE_ADDR			0x330B9278
#define		USA_NOOKLING2_PRICE_ADDR			0x330BBA98

#define		USA_ROOM_ID_ADDR					0x94F4C5
#define		EUR_ROOM_ID_ADDR					0x94E4C5
#define		JAP_ROOM_ID_ADDR					0x9484C5

#define		USA_NPC_ADDR 						0x204ACE
#define		EUR_NPC_ADDR						0x204AEE
#define		JAP_NPC_ADDR						0x204A0E

#define		USA_ISABELLE_ADDR					0x330B667E
#define		USA_KAPPN_ADDR						0x330B77FE

#define		USA_BADGE_ADDR						0x31F2C6BC
#define		USA_TURNIP_ADDR						0x31F91D60

#define		USA_MAINSTREET_ITEMS				0x305ACF38
#define		USA_MAINSTREET_X					0x33077838
#define		USA_MAINSTREET_Y					0x3307783C


/*
** Values
*/

#define		EUR_DIFFERENCE						0x28380
#define		JAP_DIFFERENCE						0x22A80

#define     ITEM_BYTES                          0x04
#define     RANGE_TOWN_ITEMS                    0x5000

#define     bell999M1        					0xA0127E55
#define     bell999M2        					0x3F07C41E
#define     bell1M1           					0xC59D1E4F
#define     bell1M2    					        0x890D2C5C
#define     bell99k1          					0x71E341DE
#define     bell99k2          					0x2D191422
#define		bell990_1							0x848F1963
#define		bell990_2							0x4914EB74
#define     bell0k1            					0x4A53C78C
#define     bell0k2            					0xAA0B2075
#define		bellBound1							0xDE41E371
#define		bellBound2							0x2D191422
#define		bellNeg1							0x789C71D3
#define		bellNeg2							0x12077362


enum
{
    USA = 0,
    EUR,
    JAP
};

enum
{
	KEYBOARDINPUT,
	ISLANDFINDER
};

/*
** Helpers
*/

/*
** helpers.c
*/
void    svcSleepThread(s64 ns);
void    disable_entry(int identifier);
void    update_status(int state, int identifier);
void    new_entry_note(char *str, const char * const note, void (*function)(void));
void    new_entry_index(char *str, void (*function)(void), int identifier);
void    new_entry_index_note(char *str, const char * const note, void (*function)(void), int identifier);
void    new_toggle_entry(char *str, void (*function)(void), int identifier);
void    new_toggle_entry_note(char *str, char *note, void (*function)(void), int identifier);
void    find_and_replace_multiple(void *start_addr, u32 length);
void    keep_it_off(void);
void    retrieve_input_string(char *output, int size);
void    get_input_id(int *first, int *second);
void	keyboardInput(void);
bool    match(const char *str, const char *pattern);
//void	islandFinder(void);

void    assign_region(u32 region);
void    text_to_cheats(void);
void    coord(void);
void    seeder(void);
void    search(void);
void    text2item(void);
void    moonjump(void);
void    teleport(void);
void    warping(void);
void    weeder(void);
void    quench(void);
void    tree(void);
void    duplicate(void);
void    grass(void);
void    desert(void);
void    speed(void);
void    nook1(void);
void    nook2(void);
void    nook3(void);
void    nook4(void);
void    update_tan_entry(void);
void    increase_tan_level(void);
void    decrease_tan_level(void);
void    walkThru(void);
void    edibleItems(void);
void    timeMachine(void);
void    timeTravel(void);
void    real(void);
void	collisions(void);
void	midnight(void);
void	morning(void);
void	noon(void);
void	stalking_1(void);
void	gorgeous_set(void);
void	clear_inv(void);
void	dynamicMod(void);
void	walkOver(void);
void	bank_999m(void);
void	bank_1m(void);
void	bank_0m(void);
void    wallet_99k(void);
void   wallet_0k(void);
void    wallet_out(void);
void    wallet_neg(void);
void	canBuy(void);
void	nookFree(void);
void	changeNook(void);
void	changeBrewster(void);
void 	changeOwl(void);
void    badge_gold(void);
void    badge_silver(void);
void    badge_bronze(void);
void    badge_none(void);
void	turnip_990(void);
void	antiGravity(void);


#endif