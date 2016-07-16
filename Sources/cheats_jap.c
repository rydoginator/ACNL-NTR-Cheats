#include "cheats.h"

extern u32			g_find[100];
extern u32			g_replace[100];
extern int			g_i;

void    coord_jap(void)//JAP
{
    static int           loc = 0;

    if (is_pressed(BUTTON_A))
    {
        loc = READU32(0x173B8CC4); //JP
    }
    if (loc == -1) //FFFFFFFF=outdoors
    {
        if (is_pressed(BUTTON_A + BUTTON_DD))
            add_to_address((void *)0x173B8B98, 0x00001800); //JP
        if (is_pressed(BUTTON_A + BUTTON_DU))
            sub_to_address((void *)0x173B8B98, 0x00001800); //JP
        if (is_pressed(BUTTON_A + BUTTON_DL))
            sub_to_address((void *)0x173B8B90, 0x00001000); //JP
        if (is_pressed(BUTTON_A + BUTTON_DR))
            add_to_address((void *)0x173B8B90, 0x00001000); //JP
    }
    else //if it's anything but FFFFFFFF then you're indoors
    {
        if (is_pressed(BUTTON_A + BUTTON_DD))
            add_to_address((void *)0x173B8CC4, 0x00008000); //JP
        if (is_pressed(BUTTON_A + BUTTON_DU))
            sub_to_address((void *)0x173B8CC4, 0x00008000); //JP
        if (is_pressed(BUTTON_A + BUTTON_DL))
            sub_to_address((void *)0x173B8CBC, 0x00008000); //JP
        if (is_pressed(BUTTON_A + BUTTON_DR))
            add_to_address((void *)0x173B8CBC, 0x00008000); //JP
    }
}

void    search_jap(void) //JAP
{
	static u16	result;
	u16		*id;
	char		id_str[5];
	int		i;

	if (is_pressed(BUTTON_L + BUTTON_DU))
	{
		id = (u16 *)0x16FE3C60;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU8(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(result, 0x9999);
		find_and_replace_multiple((void *)0x1609D158, 0x5000);
		find_and_replace_multiple((void *)0x160B9B28, 0x1000);
	}
	if (is_pressed(BUTTON_L + BUTTON_DD))
	{
		id = (u16 *)0x16FE3C60;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU8(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(0x9999, result);
		find_and_replace_multiple((void *)0x1609D158, 0x5000);
		find_and_replace_multiple((void *)0x160B9B28, 0x1000);
	}
}

void    seed_jap(void) //JAP
{
	u16        result;

	if (is_pressed(BUTTON_R + BUTTON_DD))
	{
		u16        *id = (u16 *)0x16FE3C60;
		char    id_str[5] = { 0 };
		int        i;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU16(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(0x20A7, result);
		find_and_replace_multiple((void *)0x1609D158, 0x5000);
		find_and_replace_multiple((void *)0x160B9B28, 0x1000);
		wait_all_released();
	}
	if (is_pressed(BUTTON_R + BUTTON_DU))
	{
		u16        *id = (u16 *)0x16FE3C60;
		char    id_str[5] = { 0 };
		int        i;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU16(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(result, 0x7FFE);
		find_and_replace_multiple((void *)0x1609D158, 0x5000);
		find_and_replace_multiple((void *)0x160B9B28, 0x1000);
		wait_all_released();
	}
	if (is_pressed(BUTTON_R + BUTTON_DL))
	{
		u16        *id = (u16 *)0x16FE3C60;
		char    id_str[5] = { 0 };
		int        i;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU16(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(result, 0x20A7);
		find_and_replace_multiple((void *)0x1609D158, 0x5000);
		find_and_replace_multiple((void *)0x160B9B28, 0x1000);
		wait_all_released();
	}
}

void    text2item_jap(void)//jap
{
	u16        *id = (u16 *)0x16FE3C60;
	char    id_str[5] = { 0 };
	int        i;
	u16        result;

	if (!is_pressed(BUTTON_X + BUTTON_DR))
		return;
	for (i = 0; i < 4; i++)
		id_str[i] = (char)READU16(id + i);
	result = (u16)strtoul(id_str, NULL, 16);
	WRITEU16(0x160562D0, result);
	wait_all_released();
}

void    moonjump_jap(void)//JAP
{
	static int           loc = 0;

	if (is_pressed(BUTTON_L))
	{
		loc = READU32(0x173B8CC4);
		if (loc == -1)
		{
			WRITEU32(0x173B8B94, 0x43E00000);
		}
		else
		{
			WRITEU32(0x173B8CC0, 0x44000000);
		}
	}
}

void    teleport_jap(void) //JAP
{
	static u32    indoor_X[3] = { 0 };
	static u32    indoor_Y[3] = { 0 };
	static u32    outdoor_X[3] = { 0 };
	static u32    outdoor_Y[3] = { 0 };
	static int    loc = 0;

	if (is_pressed(BUTTON_B)) //Pointer to define whether player is indoors or not
	{
		loc = READU32(0x173B8CC4);
	}
	if (is_pressed(BUTTON_B + BUTTON_DU))
	{
		if (loc == -1)
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then save in slot3
			{
				outdoor_X[2] = READU32(0x173B8B90);
				outdoor_Y[2] = READU32(0x173B8B98);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then save in slot2
			{
				outdoor_X[1] = READU32(0x173B8B90);
				outdoor_Y[1] = READU32(0x173B8B98);
			}
			else //If noting is pressed then save in slot0
			{
				outdoor_X[0] = READU32(0x173B8B90);
				outdoor_Y[0] = READU32(0x173B8B98);
			}
		}
		else
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then save in slot3
			{
				indoor_X[2] = READU32(0x173B8CBC);
				indoor_Y[2] = READU32(0x173B8CC4);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then save in slot2
			{
				indoor_X[1] = READU32(0x173B8CBC);
				indoor_Y[1] = READU32(0x173B8CC4);
			}
			else //If noting is pressed then save in slot0
			{
				indoor_X[0] = READU32(0x173B8CBC);
				indoor_Y[0] = READU32(0x173B8CC4);
			}
		}
	}
	if (is_pressed(BUTTON_B + BUTTON_DD))
	{
		loc = READU32(0x17321644);
		if (loc == -1)
		{

			if (is_pressed(BUTTON_L)) //If L is pressed then restore slot3
			{
				WRITEU32(0x173B8B90, outdoor_X[2]);
				WRITEU32(0x173B8B98, outdoor_Y[2]);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then restore slot2
			{
				WRITEU32(0x173B8B90, outdoor_X[1]);
				WRITEU32(0x173B8B98, outdoor_Y[1]);
			}
			else //If noting is pressed then restore slot0
			{
				WRITEU32(0x173B8B90, outdoor_X[0]);
				WRITEU32(0x173B8B98, outdoor_Y[0]);
			}
		}
		else
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then restore slot3
			{
				WRITEU32(0x173B8CBC, indoor_X[2]);
				WRITEU32(0x173B8CC4, indoor_Y[2]);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then restore slot2
			{
				WRITEU32(0x173B8CBC, indoor_X[1]);
				WRITEU32(0x173B8CC4, indoor_Y[1]);
			}
			else //If noting is pressed then restore slot0
			{
				WRITEU32(0x173B8CBC, indoor_X[0]);
				WRITEU32(0x173B8CC4, indoor_Y[0]);
			}
		}
	}
}

void	warping_jap(void)
{
	if (upper_left_touched())
	{
		WRITEU32(0x173B8B98, 0x4427405E);
		WRITEU32(0x173B8B94, 0x42E00000);
		WRITEU32(0x173B8B90, 0x44253715);
		wait_keys_released(KEY_TOUCH);
	}
	if (upper_right_touched())
	{
		WRITEU32(0x173B8B98, 0x442C4000);
		WRITEU32(0x173B8B94, 0x42E00000);
		WRITEU32(0x173B8B90, 0x45239943);
		wait_keys_released(KEY_TOUCH);
	}
	if (lower_left_touched())
	{
		WRITEU32(0x173B8B98, 0x450A7F48);
		WRITEU32(0x173B8B94, 0x42E00000);
		WRITEU32(0x173B8B90, 0x4442761E);
		wait_keys_released(KEY_TOUCH);
	}
	if (lower_right_touched())
	{
		WRITEU32(0x173B8B98, 0x45071000);
		WRITEU32(0x173B8B94, 0x42E00000);
		WRITEU32(0x173B8B90, 0x451E028E);
		wait_keys_released(KEY_TOUCH);
	}
}

void	speed_jap(void) //JAP
{
	u32			  velocity;

	if (is_pressed(BUTTON_B))
	{
		velocity = READU32(0x173B8BBC);
		if (velocity >= 0x41A79DB3)
		{
			WRITEU32(0x173B8BBC, 0x41A79DB3);
		}
		else if (velocity > 0)
		{
			add_to_address((void*)0x173B8BBC, 0x00100000);
		}
	}
}

void	weeder_jap(void)
{
	if (is_pressed(BUTTON_R + BUTTON_A))
	{
		reset_search();
		add_search_replace(0x0000007C, 0x00007FFE);
		add_search_replace(0x0000007D, 0x00007FFE);
		add_search_replace(0x0000007E, 0x00007FFE);
		add_search_replace(0x0000007F, 0x00007FFE);
		add_search_replace(0x000000CB, 0x00007FFE);
		add_search_replace(0x000000CC, 0x00007FFE);
		add_search_replace(0x000000CD, 0x00007FFE);
		add_search_replace(0x000000F8, 0x00007FFE);
			find_and_replace_multiple((void *)0x1609D158, 0x5000);
		wait_all_released();
	}
}

void	quench_jap(void)
{
	if (is_pressed(BUTTON_R + BUTTON_A))
	{
	reset_search();
	add_search_replace(0x0000009F, 0x4000009F);
	add_search_replace(0x000C00A0, 0x400000A0);
	add_search_replace(0x000000A1, 0x400000A1);
	add_search_replace(0x000000A2, 0x400000A2);
	add_search_replace(0x000000A3, 0x400000A3);
	add_search_replace(0x000000A4, 0x400000A4);
	add_search_replace(0x000000A5, 0x400000A5);
	add_search_replace(0x000000A6, 0x400000A6);
	add_search_replace(0x000000A7, 0x400000A7);
	add_search_replace(0x000000A8, 0x400000A8);
	add_search_replace(0x000000A9, 0x400000A9);
	add_search_replace(0x000000AA, 0x400000AA);
	add_search_replace(0x000000AB, 0x400000AB);
	add_search_replace(0x000000AC, 0x400000AC);
	add_search_replace(0x000000AD, 0x400000AD);
	add_search_replace(0x000000AE, 0x400000AE);
	add_search_replace(0x000000AF, 0x400000AF);
	add_search_replace(0x000000B0, 0x400000B0);
	add_search_replace(0x000000B1, 0x400000B1);
	add_search_replace(0x000000B2, 0x400000B2);
	add_search_replace(0x000000B3, 0x400000B3);
	add_search_replace(0x000000B4, 0x400000B4);
	add_search_replace(0x000000B5, 0x400000B5);
	add_search_replace(0x000000B6, 0x400000B6);
	add_search_replace(0x000000B7, 0x400000B7);
	add_search_replace(0x000000B8, 0x400000B8);
	add_search_replace(0x000000B9, 0x400000B9);
	add_search_replace(0x000000BB, 0x400000BB);
	add_search_replace(0x000000BC, 0x400000BC);
	add_search_replace(0x000000BD, 0x400000BD);
	add_search_replace(0x000000BE, 0x400000BE);
	add_search_replace(0x000000BF, 0x400000BF);
	add_search_replace(0x000000C0, 0x400000C0);
	add_search_replace(0x000000C1, 0x400000C1);
	add_search_replace(0x000000C2, 0x400000C2);
	add_search_replace(0x000000C3, 0x400000C3);
	add_search_replace(0x000000C4, 0x400000C4);
	add_search_replace(0x000000C5, 0x400000C5);
	add_search_replace(0x000000C6, 0x400000C6);
	add_search_replace(0x000000C7, 0x400000C7);
	add_search_replace(0x000000C8, 0x400000C8);
	add_search_replace(0x000000CE, 0x4000009F); //Red Tulips
	add_search_replace(0x000000CF, 0x400000A0);
	add_search_replace(0x000000D0, 0x400000A1);
	add_search_replace(0x000000D1, 0x400000A2);
	add_search_replace(0x000000D2, 0x400000A3);
	add_search_replace(0x000000D3, 0x400000A4);
	add_search_replace(0x000000D4, 0x400000A5);
	add_search_replace(0x000000D5, 0x400000A6);
	add_search_replace(0x000000D6, 0x400000A7);
	add_search_replace(0x000000D7, 0x400000A8);
	add_search_replace(0x000000D8, 0x400000A9);
	add_search_replace(0x000000D9, 0x400000AA);
	add_search_replace(0x000000DA, 0x400000AB);
	add_search_replace(0x000000DB, 0x400000AC);
	add_search_replace(0x000000DC, 0x400000AD);
	add_search_replace(0x000000DD, 0x400000AE);
	add_search_replace(0x000000DE, 0x400000AF);
	add_search_replace(0x000000DF, 0x400000B0);
	add_search_replace(0x000000E0, 0x400000B1);
	add_search_replace(0x000000E1, 0x400000B2);
	add_search_replace(0x000000E2, 0x400000B3);
	add_search_replace(0x000000E3, 0x400000B4);
	add_search_replace(0x000000E4, 0x400000B5);
	add_search_replace(0x000000E5, 0x400000B6);
	add_search_replace(0x000000E6, 0x400000B7);
	add_search_replace(0x000000E7, 0x400000B8);
	add_search_replace(0x000000E8, 0x400000B9);
	add_search_replace(0x000000E9, 0x400000BA);
	add_search_replace(0x000000EA, 0x400000BB);
	add_search_replace(0x000000EB, 0x400000BC);
	add_search_replace(0x000000EC, 0x400000BD);
	add_search_replace(0x000000ED, 0x400000BE);
	add_search_replace(0x000000EE, 0x400000BF);
	add_search_replace(0x000000EF, 0x400000C0);
	add_search_replace(0x000000F0, 0x400000C1);
	add_search_replace(0x000000F1, 0x400000C2);
	add_search_replace(0x000000F2, 0x400000C3);
	add_search_replace(0x000000F3, 0x400000C4);
	add_search_replace(0x000000F4, 0x400000C5);
	add_search_replace(0x000000F5, 0x400000C6);
	add_search_replace(0x000000F6, 0x400000C7);
	add_search_replace(0x000000F7, 0x400000C8);
		find_and_replace_multiple((void *)0x1609D158, 0x5000);
	}
}

void	tree_jap(void)
{
	if (is_pressed(BUTTON_X))
	{
		reset_search();
		add_search_replace(0x003A, 0x003E);
		add_search_replace(0x003F, 0x0043);
		add_search_replace(0x0044, 0x0048);
		add_search_replace(0x0049, 0x004D);
		add_search_replace(0x004E, 0x0052);
		add_search_replace(0x0022, 0x0026);
		add_search_replace(0x0027, 0x002B);
		add_search_replace(0x002C, 0x0030);
		add_search_replace(0x0031, 0x0035);
		add_search_replace(0x0036, 0x0039);
		add_search_replace(0x0053, 0x0057);
		add_search_replace(0x0058, 0x005C);
		add_search_replace(0x005D, 0x0061);
		add_search_replace(0x0062, 0x0066);
		add_search_replace(0x0067, 0x006B);
		add_search_replace(0x006C, 0x0043);
		find_and_replace_multiple((void *)0x1609D158, 0x5000);
		find_and_replace_multiple((void *)0x160B9B28, 0x1000);

	}
}

void	duplicate_jap(void)//JAP
{
	u32			dupe = 0;
	u32			dupe0 = 0;
	u32			dupe1 = 0;
	u32			dupe2 = 0;
	
	if (is_pressed(BUTTON_R))
	{
		dupe = READU32(0x160562D0);
		dupe0 = READU32(0xAEEC28); //online pointer0
		dupe1 = READU32(0xAF8B38); //online pointer1
		dupe2 = READU32(0xB02A48); //online pointer2
		WRITEU32(0x160562D4, dupe);
		WRITEU32(0xAEEC2C, dupe0);
		WRITEU32(0xAF8B3C, dupe1);
		WRITEU32(0xB02A4C, dupe2);	
	}
}

void	grass_jap(void)
{
	disableCheat(8);
	if (is_pressed(BUTTON_R + BUTTON_A))
	{
		int i;

		for (i = 0x160A3580; i < 0x160a5d7c; i++)
			*(u32 *)i = 0xFFFFFFFF;
		wait_all_released();
	}
}

void	desert_jap(void)
{
	disableCheat(7);
	if (is_pressed(BUTTON_R + BUTTON_A))
	{
		int i;
	
		for (i = 0x160A3580; i < 0x160a5d7c; i++)
			*(u32 *)i = 0x00000000;
		wait_all_released();
	}
}

//Nook Upgrades

void	nook1_jap(void)
{
	WRITEU16(0x160ABEE0, 0x0101);
}

void	nook2_jap(void)
{	
	WRITEU16(0x160ABEE0, 0x0202);
}

void	nook3_jap(void)
{
	WRITEU16(0x160ABEE0, 0x0303);
}

void	nook4_jap(void)
{
	WRITEU16(0x160ABEE0, 0x0404);
}

void	tan_jap(void)
{
	WRITEU8(0x1604F728, 0xF);
}