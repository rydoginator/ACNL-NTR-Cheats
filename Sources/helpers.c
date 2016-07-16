#include "cheats.h"

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
