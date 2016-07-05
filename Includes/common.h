#ifndef COMMON_H
#define COMMON_H
#include "plugin.h"

extern u32 IoBasePad;

static inline int is_pressed(u32 keys)
{
	//u32 i = 0x13000;

	//while (--i > 0 && ((((*(vu32*)(IoBasePad) ^ 0xFFF) & 0xFFF) & keys) == keys));
	//if (i == 0)
	if ((((*(vu32*)(IoBasePad) ^ 0xFFF) & 0xFFF) & keys) == keys)
		return(1);
	return (0);
}

static inline int any_is_pressed(u32 keys)
{
	//u32 i = 0x13000;

	//while (--i > 0 && ((*(vu32*)(IoBasePad) ^ 0xFFF) & 0xFFF) & keys);
	//if (i == 0)
	if (((*(vu32*)(IoBasePad) ^ 0xFFF) & 0xFFF) & keys)
		return(1);
	return (0);
}

static inline int wait_keys(u32 keys)
{
	while (!(any_is_pressed(keys)))
		continue;
}

static inline void wait_keys_released(u32 keys)
{
	while (1)
		if (!(is_pressed(keys)))
			return;
}

static inline void wait_all_released(void)
{
	while (1)
		if (((*(vu32*)(IoBasePad) ^ 0xFFF) & 0xFFF) == 0)
			return;
}

#endif
