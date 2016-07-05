#include "cheats.h"

#define		add_search_replace(find, replace)	g_find[g_i] = find; g_replace[g_i] = replace; g_i++
#define		reset_search()				memset(g_find, 0, sizeof(g_find)); memset(g_replace, 0, sizeof(g_find)); g_i = 0
extern u32	g_find[100];
extern u32	g_replace[100];
extern int	g_i;

void	find_and_replace_multiple(void *start_addr, u32 length)
{
	u32 find_value;
	u32 replace_value;
	int i;

	i = 0;
	while (length-- > 0)
	{
		for (i = 0; i < g_i; i++)
		{
			find_value = g_find[i];
			replace_value = g_replace[i];
			if (*(u16 *)start_addr == find_value)
			{
				*(u16 *)start_addr = replace_value;
				break;
			}
		}
		start_addr += 4;
	}
}
