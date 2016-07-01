#ifndef CHEATS_H
#define CHEATS_H

#include "../Includes/plugin.h"

#define		add_search_replace(find, replace) g_find[g_i] = find; g_replace[g_i] = replace; g_i++
#define		reset_search()                    memset(g_find, 0, sizeof(g_find)); memset(g_replace, 0, sizeof(g_replace)); g_i = 0

/*
** Helpers
*/

void	find_and_replace_multiple(void *start_addr, u32 length);
void	add_to_address(void *address, u32 value_to_add);
void	sub_to_address(void *address, u32 value_to_sub);

/*
** USA
*/

void    coord_usa(void);
void    seed_usa(void);
void    search_usa(void);
void    text2item_usa(void);
void    moonjump_usa(void);
void    teleport_usa(void);
void	weeder_usa(void);
void	quench_usa(void);
void	tree_usa(void);
void	duplicate_usa(void);
void	grass_usa(void);
void	desert_usa(void);

/*
** EUR
*/

void    coord_eur(void);
void    seed_eur(void);
void    search_eur(void);
void    text2item_eur(void);
void    moonjump_eur(void);
void    teleport_eur(void);
void	weeder_eur(void);
void	quench_eur(void);
void	tree_eur(void);
void	duplicate_eur(void);
void	grass_eur(void);
void	desert_eur(void);

#endif
