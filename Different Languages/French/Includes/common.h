#ifndef COMMON_H
#define COMMON_H
#include "plugin.h"
#include "hid.h"

extern u32 		IoBasePad;
extern vu32 	*pad_base;

static inline int is_pressed(u32 keys)
{
	if (pad_base != NULL)
	{
		if (((hidKeysDown() & keys) == keys))
			return (1);
	}
	else
		if (((((*(vu32*)(IoBasePad) ^ 0xFFF) & 0xFFF) & keys) == keys))
			return (1);
	return (0);
}

static inline int any_is_pressed(u32 keys)
{
	if (pad_base != NULL)
	{
		if (((hidKeysDown() & keys)))
			return (1);
	}
	else
		if (((((*(vu32*)(IoBasePad) ^ 0xFFF) & 0xFFF) & keys)))
			return (1);
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
		if (!(any_is_pressed(keys)))
			return;
}

static inline void wait_all_released(void)
{
	while (1)
		if (((*(vu32*)(IoBasePad) ^ 0xFFF) & 0xFFF) == 0)
			return;
}

static inline int upper_left_touched(void)
{
	if (is_pressed(KEY_TOUCH))
		if (hidTouchPos().px < 160 && hidTouchPos().py < 120)
			return (1);
	return (0);
}

static inline int upper_right_touched(void)
{
	if (is_pressed(KEY_TOUCH))
		if (hidTouchPos().px >= 160 && hidTouchPos().py < 120)
			return (1);
	return (0);
}

static inline int lower_left_touched(void)
{
	if (is_pressed(KEY_TOUCH))
		if (hidTouchPos().px < 160 && hidTouchPos().py >= 120)
			return (1);
	return (0);
}

static inline int lower_right_touched(void)
{
	if (is_pressed(KEY_TOUCH))
		if (hidTouchPos().px >= 160 && hidTouchPos().py >= 120)
			return (1);
	return (0);
}
#endif
