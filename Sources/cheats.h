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
#define     ITEM_BYTES                          0x04
#define     RANGE_TOWN_ITEMS                    0x5000
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
#define	    USA_COLLISIONS_ADDR                 0x33077534
#define     USA_INPUT_TEXT_ADDR                 0x32CB0F60
#define     EUR_INPUT_TEXT_ADDR                 0x32C88BE0
#define     JAP_INPUT_TEXT_ADDR                 0x32CD39E0

enum
{
    USA = 0,
    EUR,
    JAP
};

/*
** Helpers
*/

void    find_and_replace_multiple(void *start_addr, u32 length);
void    keep_it_off(void);
void    retrieve_input_string(char *output, int size);
void    get_input_id(int *first, int *second);
bool    match(const char *str, const char *pattern);

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


#endif
