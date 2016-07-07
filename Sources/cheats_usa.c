#include "cheats.h"

u32			g_find[100];
u32			g_replace[100];
int			g_i = 0;

void    coord_usa(void)
{
	static int	loc = 0;

	if (is_pressed(BUTTON_A))
	{
		loc = READU32(0x17321644);
	}
	if (loc == -1) //FFFFFFFF=outdoors
	{
		if (is_pressed(BUTTON_A + BUTTON_DD))
			add_to_address((void *)0x17321518, 0x00001800);
		if (is_pressed(BUTTON_A + BUTTON_DU))
			sub_to_address((void *)0x17321518, 0x00001800);
		if (is_pressed(BUTTON_A + BUTTON_DL))
			sub_to_address((void *)0x17321510, 0x00001000);
		if (is_pressed(BUTTON_A + BUTTON_DR))
			add_to_address((void *)0x17321510, 0x00001000);
	}
	else //if it's anything but FFFFFFFF then you're indoors
	{
		if (is_pressed(BUTTON_A + BUTTON_DD))
			add_to_address((void *)0x17321644, 0x00008000);
		if (is_pressed(BUTTON_A + BUTTON_DU))
			sub_to_address((void *)0x17321644, 0x00008000);
		if (is_pressed(BUTTON_A + BUTTON_DL))
			sub_to_address((void *)0x1732163c, 0x00008000);
		if (is_pressed(BUTTON_A + BUTTON_DR))
			add_to_address((void *)0x1732163c, 0x00008000);
	}
}
void    search_usa(void)
{
	static u16	result;
	u16		*id;
	char		id_str[5];
	int		i;

	if (is_pressed(BUTTON_L + BUTTON_DU))
	{
		id = (u16 *)0x16F4C160;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU8(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		if (result != 0)
		{
		reset_search();
		add_search_replace(result, 0x9999);
		find_and_replace_multiple((void *)0x16005958, 0x5000);
		find_and_replace_multiple((void *)0x16022328, 0x1000);
		}
	}
	if (is_pressed(BUTTON_L + BUTTON_DD))
	{
		id = (u16 *)0x16F4C160;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU8(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(0x9999, result);
		find_and_replace_multiple((void *)0x16005958, 0x5000);
		find_and_replace_multiple((void *)0x16022328, 0x1000);
	}
}

void    seed_usa(void)
{
	u16		result;
	u16		replace;
	u16		*id;
	char		id_str[5];
	int		i;

	if (is_pressed(BUTTON_R + BUTTON_DD))
	{
		id = (u16 *)0x16F4C160;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU8(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(0x20A7, result);
		find_and_replace_multiple((void *)0x16005958, 0x5000);
		find_and_replace_multiple((void *)0x16022328, 0x1000);
	}
	if (is_pressed(BUTTON_R + BUTTON_DU))
	{
		id = (u16 *)0x16F4C160;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU8(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(result, 0x7FFE);
		find_and_replace_multiple((void *)0x16005958, 0x5000);
		find_and_replace_multiple((void *)0x16022328, 0x1000);
	}
	if (is_pressed(BUTTON_R + BUTTON_DL))
	{
		id = (u16 *)0x16F4C160;
		for (i = 0; i < 4; i++)
			id_str[i] = (char)READU8(id + i);
		result = (u16)strtoul(id_str, NULL, 16);
		reset_search();
		add_search_replace(result, 0x20A7);
		find_and_replace_multiple((void *)0x16005958, 0x5000);
		find_and_replace_multiple((void *)0x16022328, 0x1000);
	}
}


void    text2item_usa(void)
{
	u16		*id = (u16 *)0x16F4C160;
	char		id_str[5] = { 0 };
	int		i;
	u16		result;

	if (!is_pressed(BUTTON_X + BUTTON_DR))
		return;
	for (i = 0; i < 4; i++)
		id_str[i] = (char)READU16(id + i);
	result = (u16)strtoul(id_str, NULL, 16);
	WRITEU16(0x15FBEAD0, result);
	wait_all_released();
}


void    moonjump_usa(void)
{
	u32		key = getKey();
	static int		loc = 0;
	if (is_pressed(BUTTON_L))
	{
		loc = READU32(0x17321644);
		if (loc == -1)
		{
			WRITEU32(0x17321514, 0x43E00000);
		}
		else
		{
			WRITEU32(0x17321640, 0x44000000);
		}
	}
}

void    teleport_usa(void)
{
	static u32    indoor_X[3] = { 0 };
	static u32    indoor_Y[3] = { 0 };
	static u32    outdoor_X[3] = { 0 };
	static u32    outdoor_Y[3] = { 0 };
	static int    loc = 0;

	if (is_pressed(BUTTON_B)) //Pointer to define whether player is indoors or not
	{
		loc = READU32(0x17321644);
	}
	if (is_pressed(BUTTON_B + BUTTON_DU))
	{
		if (loc == -1) 
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then save in slot3
			{
				outdoor_X[2] = READU32(0x17321510);
				outdoor_Y[2] = READU32(0x17321518);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then save in slot2
			{
				outdoor_X[1] = READU32(0x17321510);
				outdoor_Y[1] = READU32(0x17321518);
			}
			else //If noting is pressed then save in slot0
			{
				outdoor_X[0] = READU32(0x17321510);
				outdoor_Y[0] = READU32(0x17321518);
			}
		}
		else
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then save in slot3
			{
				indoor_X[2] = READU32(0x1732163c);
				indoor_Y[2] = READU32(0x17321644);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then save in slot2
			{
				indoor_X[1] = READU32(0x1732163c);
				indoor_Y[1] = READU32(0x17321644);
			}
			else //If noting is pressed then save in slot0
			{
				indoor_X[0] = READU32(0x1732163c);
				indoor_Y[0] = READU32(0x17321644);
			}
		}
	}
	if (is_pressed(BUTTON_B + BUTTON_DD))
	{
		if (loc == -1)
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then restore slot3
			{
				WRITEU32(0x17321510, outdoor_X[2]);
				WRITEU32(0x17321518, outdoor_Y[2]);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then restore slot2
			{
				WRITEU32(0x17321510, outdoor_X[1]);
				WRITEU32(0x17321518, outdoor_Y[1]);
			}
			else //If noting is pressed then restore slot0
			{
				WRITEU32(0x17321510, outdoor_X[0]);
				WRITEU32(0x17321518, outdoor_Y[0]);
			}
		}
		else
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then restore slot3
			{
				WRITEU32(0x1732163c, indoor_X[2]);
				WRITEU32(0x17321644, indoor_Y[2]);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then restore slot2
			{
				WRITEU32(0x1732163c, indoor_X[1]);
				WRITEU32(0x17321644, indoor_Y[1]);
			}
			else //If noting is pressed then restore slot0
			{
				WRITEU32(0x1732163c, indoor_X[0]);
				WRITEU32(0x17321644, indoor_Y[0]);
			}
		}
	}
}

void	speed_usa(void)
{
	u32			  key = getKey();
	u32			  velocity;
	if (key == BUTTON_B)
	{
		velocity = READU32(0x1732153C);
		if (velocity >= 0x41A79DB3)
		{
			WRITEU32(0x1732153C, 0x41A79DB3);
		}
		else if (velocity > 0)
		{
		add_to_address((void*)0x1732153C, 0x00100000);
		}
	}
}

void	weeder_usa(void)
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
		find_and_replace_multiple((void *)0x16005958, 0x5000);
		wait_all_released();
	}
}

void	quench_usa(void)
{
	if (is_pressed(BUTTON_R + BUTTON_A))
	{
		reset_search();
		add_search_replace(0x0000009F, 0x4000009F);
		add_search_replace(0x000000A0, 0x400000A0);
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
		find_and_replace_multiple((void *)0x16005958, 0x5000);
		wait_all_released();
	}
}

void	tree_usa(void)
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
		find_and_replace_multiple((void *)0x16005958, 0x5000);
		find_and_replace_multiple((void *)0x16022328, 0x1000);
	}
}

void	duplicate_usa(void)
{
	u32		dupe = 0;
	
	if (is_pressed(BUTTON_R))
	{
		dupe = READU32(0x15FBEAD0);
		WRITEU32(0x15FBEAD4, dupe);
	}
}

void	grass_usa(void)
{
	disableCheat(8);
	if (is_pressed(BUTTON_R + BUTTON_A))
	{
		int i;

		for (i = 0x1600BD80; i < 0x1600E57F; i++)
			*(u32 *)i = 0xFFFFFFFF;
		wait_all_released();
	}
}

void	desert_usa(void)
{
	disableCheat(8);
	if (is_pressed(BUTTON_R + BUTTON_A))
	{
		int i;

		for (i = 0x1600BD80; i < 0x1600E57F; i++)
			*(u32 *)i = 0x00000000;
		wait_all_released();
	}
}

//Nook Upgrades

void	nook1_usa(void)
{
    disableCheat(21);
	disableCheat(22);
	disableCheat(23);
	WRITEU16(0x160146E0, 0x0101);

}

void	nook2_usa(void)
{
    disableCheat(20);
	disableCheat(22);
	disableCheat(23);
	WRITEU16(0x160146E0, 0x0202);
}

void	nook3_usa(void)
{
	disableCheat(20);
	disableCheat(21);
	disableCheat(23);
	WRITEU16(0x160146E0, 0x0303);
}

void	nook4_usa(void)
{
    disableCheat(20);
	disableCheat(21);
	disableCheat(22);
	WRITEU16(0x160146E0, 0x0404);
}

void	tan_usa(void)
{
	WRITEU8(0x15FB7F28, 0xF);
}
