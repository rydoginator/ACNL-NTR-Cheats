#include "cheats.h"

u32			g_find[100];
u32			g_replace[100];
int			g_i = 0;

void    coord_usa(void)
{
	static int	loc = 0;

	if (is_pressed(BUTTON_A))
	{
		loc = READU32(0x33077504);
	}
	if (loc == -1) //FFFFFFFF=outdoors
	{
		if (is_pressed(BUTTON_A + BUTTON_DD))
			ADDTOFLOAT(0x330773D8, 1.0);
		if (is_pressed(BUTTON_A + BUTTON_DU))
			SUBTOFLOAT(0x330773D8, 1.0);
		if (is_pressed(BUTTON_A + BUTTON_DL))
			SUBTOFLOAT(0x330773D0, 1.0);
		if (is_pressed(BUTTON_A + BUTTON_DR))
			ADDTOFLOAT(0x330773D0, 1.0);
	}
	else //if it's anything but FFFFFFFF then you're indoors
	{
		if (is_pressed(BUTTON_A + BUTTON_DD))
			ADDTOFLOAT(0x33077504, 1.0);
		if (is_pressed(BUTTON_A + BUTTON_DU))
			SUBTOFLOAT(0x33077504, 1.0);
		if (is_pressed(BUTTON_A + BUTTON_DL))
			SUBTOFLOAT(0x330774fc, 1.0);
		if (is_pressed(BUTTON_A + BUTTON_DR))
			ADDTOFLOAT(0x330774fc, 1.0);
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
	WRITEU16(0xAF8C28, result);
	WRITEU16(0xB0CA48, result);
	WRITEU16(0xB02B38, result);
	WRITEU16(0xB16958, result);
	WRITEU16(0xB15958, result);
	wait_all_released();
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
		loc = READU32(0x33077504);
	}
	if (is_pressed(BUTTON_B + BUTTON_DU))
	{
		if (loc == -1) 
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then save in slot3
			{
				outdoor_X[2] = READU32(0x330773D0);
				outdoor_Y[2] = READU32(0x330773D8);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then save in slot2
			{
				outdoor_X[1] = READU32(0x330773D0);
				outdoor_Y[1] = READU32(0x330773D8);
			}
			else //If noting is pressed then save in slot0
			{
				outdoor_X[0] = READU32(0x330773D0);
				outdoor_Y[0] = READU32(0x330773D8);
			}
		}
		else
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then save in slot3
			{
				indoor_X[2] = READU32(0x330774fc);
				indoor_Y[2] = READU32(0x33077504);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then save in slot2
			{
				indoor_X[1] = READU32(0x330774fc);
				indoor_Y[1] = READU32(0x33077504);
			}
			else //If noting is pressed then save in slot0
			{
				indoor_X[0] = READU32(0x330774fc);
				indoor_Y[0] = READU32(0x33077504);
			}
		}
	}
	if (is_pressed(BUTTON_B + BUTTON_DD))
	{
		if (loc == -1)
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then restore slot3
			{
				WRITEU32(0x330773D0, outdoor_X[2]);
				WRITEU32(0x330773D8, outdoor_Y[2]);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then restore slot2
			{
				WRITEU32(0x330773D0, outdoor_X[1]);
				WRITEU32(0x330773D8, outdoor_Y[1]);
			}
			else //If noting is pressed then restore slot0
			{
				WRITEU32(0x330773D0, outdoor_X[0]);
				WRITEU32(0x330773D8, outdoor_Y[0]);
			}
		}
		else
		{
			if (is_pressed(BUTTON_L)) //If L is pressed then restore slot3
			{
				WRITEU32(0x330774fc, indoor_X[2]);
				WRITEU32(0x33077504, indoor_Y[2]);
			}
			else if (is_pressed(BUTTON_R)) //If R is pressed then restore slot2
			{
				WRITEU32(0x330774fc, indoor_X[1]);
				WRITEU32(0x33077504, indoor_Y[1]);
			}
			else //If noting is pressed then restore slot0
			{
				WRITEU32(0x330774fc, indoor_X[0]);
				WRITEU32(0x33077504, indoor_Y[0]);
			}
		}
	}
}

void	warping_usa(void)
{
	if (upper_left_touched())
	{
		WRITEU32(0x17321518, 0x4427405E);
		WRITEU32(0x17321514, 0x42E00000);
		WRITEU32(0x17321510, 0x44253715);
		wait_keys_released(KEY_TOUCH);
	}
	if (upper_right_touched())
	{
		WRITEU32(0x17321518, 0x442C4000);
		WRITEU32(0x17321514, 0x42E00000);
		WRITEU32(0x17321510, 0x45239943);
		wait_keys_released(KEY_TOUCH);
	}
	if (lower_left_touched())
	{
		WRITEU32(0x17321518, 0x450A7F48);
		WRITEU32(0x17321514, 0x42E00000);
		WRITEU32(0x17321510, 0x4442761E);
		wait_keys_released(KEY_TOUCH);
	}
	if (lower_right_touched())
	{
		WRITEU32(0x17321518, 0x45071000);
		WRITEU32(0x17321514, 0x42E00000);
		WRITEU32(0x17321510, 0x451E028E);
		wait_keys_released(KEY_TOUCH);
	}
}

void	speed_usa(void)
{
	u32			  velocity;
	if (is_pressed(BUTTON_B))
	{
		velocity = READU32(0x330773Fc;
		if (velocity >= 0x41A79DB3)
		{
			WRITEU32(0x1732153C, 0x41A79DB3);
		}
		else if (velocity > 0)
		{
		ADDTOFLOAT(0x330773Fc, 2.0);
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

void quench_usa()
{
  // define flowers (include wilted)
static const u16 flowers[] = {
    // src, replace
    0x009F, 0x009F, // Red Tulips
    0x00A0, 0x00A0, // White Tulips
    0x00A1, 0x00A1, // Yellow Tulips
    0x00A2, 0x00A2, // Pink Tulips
    0x00A3, 0x00A3, // Purple Tulips
    0x00A4, 0x00A4, // Black Tulips
    0x00A5, 0x00A5, // Orange Tulips
    0x00A6, 0x00A6, // White Pansies
    0x00A7, 0x00A7, // Yellow Pansies
    0x00A8, 0x00A8, // Red Pansies
    0x00A9, 0x00A9, // Purple Pansies
    0x00AA, 0x00AA, // Orange Pansies
    0x00AB, 0x00AB, // Blue Pansies
    0x00AC, 0x00AC, // White Comsos
    0x00AD, 0x00AD, // Red Cosmos
    0x00AE, 0x00AE, // Sun Cosmos
    0x00AF, 0x00AF, // Pink Cosmos
    0x00B0, 0x00B0, // Orange Cosmos
    0x00B1, 0x00B1, // Black Cosmos
    0x00B2, 0x00B2, // Red Roses
    0x00B3, 0x00B3, // White Roses
    0x00B4, 0x00B4, // Yellow Roses
    0x00B5, 0x00B5, // Pink Roses
    0x00B6, 0x00B6, // Orange Roses
    0x00B7, 0x00B7, // Purple Roses
    0x00B8, 0x00B8, // Black Roses
    0x00B9, 0x00B9, // Blue Roses
    0x00BB, 0x00BB, // Red Carnations
    0x00BC, 0x00BC, // Pink Carnations
    0x00BD, 0x00BD, // White Carnations
    0x00BE, 0x00BE, // White Lilies
    0x00BF, 0x00BF, // Yellow Lilies
    0x00C0, 0x00C0, // Red Lilies
    0x00C1, 0x00C1, // Orange Lilies
    0x00C2, 0x00C2, // Pink Lilies
    0x00C3, 0x00C3, // Black Lilies
    0x00C4, 0x00C4, // Purple Violets
    0x00C5, 0x00C5, // Blue Violets
    0x00C6, 0x00C6, // White Violets
    0x00C7, 0x00C7, // Yellow Violets
    0x00C8, 0x00C8, // Jacob's Ladder
    0x00CE, 0x009F, // Red Tulips (Wilted)
    0x00CF, 0x00A0, // White Tulips (Wilted)
    0x00D0, 0x00A1, // Yellow Tulips (Wilted)
    0x00D1, 0x00A2, // Pink Tulips (Wilted)
    0x00D2, 0x00A3, // Purple Tulips (Wilted)
    0x00D3, 0x00A4, // Black Tulips (Wilted)
    0x00D4, 0x00A5, // Orange Tulips (Wilted)
    0x00D5, 0x00A6, // White Pansies (Wilted)
    0x00D6, 0x00A7, // Yellow Pansies (Wilted)
    0x00D7, 0x00A8, // Red Pansies (Wilted)
    0x00D8, 0x00A9, // Purple Pansies (Wilted)
    0x00D9, 0x00AA, // Orange Pansies (Wilted)
    0x00DA, 0x00AB, // Blue Pansies (Wilted)
    0x00DB, 0x00AC, // White Cosmos (Wilted)
    0x00DC, 0x00AD, // Red Cosmos (Wilted)
    0x00DD, 0x00AE, // Sun Cosmos (Wilted)
    0x00DE, 0x00AF, // Pink Cosmos (Wilted)
    0x00DF, 0x00B0, // Orange Cosmos (Wilted)
    0x00E0, 0x00B1, // Black Cosmos (Wilted)
    0x00E1, 0x00B2, // Red Roses (Wilted)
    0x00E2, 0x00B3, // White Roses (Wilted)
    0x00E3, 0x00B4, // Yellow Roses (Wilted)
    0x00E4, 0x00B5, // Pink Roses (Wilted)
    0x00E5, 0x00B6, // Orange Roses (Wilted)
    0x00E6, 0x00B7, // Purple Roses (Wilted)
    0x00E7, 0x00B8, // Black Roses (Wilted)
    0x00E8, 0x00B9, // Blue Roses (Wilted)
    0x00E9, 0x00BA, // Gold Roses (Wilted)
    0x00EA, 0x00BB, // Red Carnations (Wilted)
    0x00EB, 0x00BC, // Pink Carnations (Wilted)
    0x00EC, 0x00BD, // White Carnations (Wilted)
    0x00ED, 0x00BE, // White Lilies (Wilted)
    0x00EE, 0x00BF, // Yellow Lilies (Wilted)
    0x00EF, 0x00C0, // Red Lilies (Wilted)
    0x00F0, 0x00C1, // Orange Lilies (Wilted)
    0x00F1, 0x00C2, // Pink Lilies (Wilted)
    0x00F2, 0x00C3, // Black Lilies (Wilted)
    0x00F3, 0x00C4, // Purple Violets (Wilted)
    0x00F4, 0x00C5, // Blue Violets (Wilted)
    0x00F5, 0x00C6, // White Violets (Wilted)
    0x00F6, 0x00C7, // Yellow Violets (Wilted)
    0x00F7, 0x00C8, // Jacob's Ladder (Wilted)
};
  int i;
  u32 address, item;
	if (is_pressed(BUTTON_R + BUTTON_A))
  // find all items in Town
  for(address = OFFSET_TOWN_ITEMS; address < OFFSET_TOWN_ITEMS + RANGE_TOWN_ITEMS; address += ITEM_BYTES){
    item = READU16(address);

    // find flowers
    for(i = 0; i < sizeof(flowers) / sizeof(u16); i += 2){
      if(item == flowers[i]){
        // replace item
        WRITEU16(address, flowers[i + 1]);

        // add water flag
        WRITEU16(address + 0x02, 0x4000);
        break;
			}
		}
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
	u32		dupe0 = 0;
	u32		dupe1 = 0;
	u32		dupe2 = 0;
	u32		dupe3 = 0;
	u32		dupe4 = 0;
	
	if (is_pressed(BUTTON_R))
	{
		dupe = READU32(0x15FBEAD0); 
		dupe0 = READU32(0xAF8C28); //online pointer0
		dupe1 = READU32(0xB02B38); //online pointer1
		dupe2 = READU32(0xB0CA48); //online pointer2
		dupe3 = READU32(0xB15958);
		dupe4 = READU32(0xB16958);
		WRITEU32(0x15FBEAD4, dupe);
		WRITEU32(0xAF8C2C, dupe0);
		WRITEU32(0xB02B3C, dupe1);
		WRITEU32(0xB0CA4C, dupe2);
		WRITEU32(0xB1595C, dupe3);
		WRITEU32(0xB1695C, dupe4);
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
	WRITEU16(0x160146E0, 0x0101);
	WRITEU8(0x16018B70, 0x2);
}

void	nook2_usa(void)
{
	WRITEU16(0x160146E0, 0x0202);
	WRITEU8(0x16018B70, 0x2);
}

void	nook3_usa(void)
{
	WRITEU16(0x160146E0, 0x0303);
	WRITEU8(0x16018B70, 0x3);
}

void	nook4_usa(void)
{
	WRITEU16(0x160146E0, 0x0404);
	WRITEU8(0x16018B70, 0x4);
}

void	tan_usa(void)
{
	WRITEU8(0x15FB7F28, 0xF);
}

void	moonjump_usa(void)
{
	int	loc;
	u32 Z;

    if (!(any_is_pressed(R)) && is_pressed(BUTTON_L)) //it's better to test the negation first
	{
		loc = READU32(0x33077504);
		Z = READU32(0x330773D4);
		if (Z >= 0x440F0000)
		{
			if (loc == -1)
			{
				WRITEU32(0x330773D4, 0x440F0000);
			}
			else
			{
				WRITEU32(0x33077500, 0x440F0000);
			}
		}
		else
		{
			if (loc == -1)
			{
				ADDTOFLOAT(0x330773D4, 6.0);
			}
			else
			{
				ADDTOFLOAT(0x33077500, 6.0);
			}
		}	
	}
}

void    text2item2_usa(void)
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
	WRITEU16(0x15fc89e0, result);
	WRITEU16(0xAF8C28, result);
	WRITEU16(0xB0CA48, result);
	WRITEU16(0xB02B38, result);
	WRITEU16(0xB16958, result);
	WRITEU16(0xB15958, result);
	wait_all_released();
}

void    text2item3_usa(void)
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
	WRITEU16(0x15fd28f0, result);
	WRITEU16(0xAF8C28, result);
	WRITEU16(0xB0CA48, result);
	WRITEU16(0xB02B38, result);
	WRITEU16(0xB16958, result);
	WRITEU16(0xB15958, result);
	wait_all_released();
}

void    text2item4_usa(void)
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
	WRITEU16(0x15fdc800, result);
	WRITEU16(0xAF8C28, result);
	WRITEU16(0xB0CA48, result);
	WRITEU16(0xB02B38, result);
	WRITEU16(0xB16958, result);
	WRITEU16(0xB15958, result);
	wait_all_released();
}

void	duplicate2_usa(void)
{
	u32		dupe = 0;
	u32		dupe0 = 0;
	u32		dupe1 = 0;
	u32		dupe2 = 0;
	u32		dupe3 = 0;
	u32		dupe4 = 0;
	
	if (is_pressed(BUTTON_R))
	{
		dupe = READU32(0x15fc89e0); 
		dupe0 = READU32(0xAF8C28); //online pointer0
		dupe1 = READU32(0xB02B38); //online pointer1
		dupe2 = READU32(0xB0CA48); //online pointer2
		dupe3 = READU32(0xB15958);
		dupe4 = READU32(0xB16958);
		WRITEU32(0x15fc89e4, dupe);
		WRITEU32(0xAF8C2C, dupe0);
		WRITEU32(0xB02B3C, dupe1);
		WRITEU32(0xB0CA4C, dupe2);
		WRITEU32(0xB1595C, dupe3);
		WRITEU32(0xB1695C, dupe4);
	}
}

void	duplicate3_usa(void)
{
	u32		dupe = 0;
	u32		dupe0 = 0;
	u32		dupe1 = 0;
	u32		dupe2 = 0;
	u32		dupe3 = 0;
	u32		dupe4 = 0;
	
	if (is_pressed(BUTTON_R))
	{
		dupe = READU32(0x15fd28f0); 
		dupe0 = READU32(0xAF8C28); //online pointer0
		dupe1 = READU32(0xB02B38); //online pointer1
		dupe2 = READU32(0xB0CA48); //online pointer2
		dupe3 = READU32(0xB15958);
		dupe4 = READU32(0xB16958);
		WRITEU32(0x15fd28f4, dupe);
		WRITEU32(0xAF8C2C, dupe0);
		WRITEU32(0xB02B3C, dupe1);
		WRITEU32(0xB0CA4C, dupe2);
		WRITEU32(0xB1595C, dupe3);
		WRITEU32(0xB1695C, dupe4);
	}
}

void	duplicate4_usa(void)
{
	u32		dupe = 0;
	u32		dupe0 = 0;
	u32		dupe1 = 0;
	u32		dupe2 = 0;
	u32		dupe3 = 0;
	u32		dupe4 = 0;
	
	if (is_pressed(BUTTON_R))
	{
		dupe = READU32(0x15fd28f0); 
		dupe0 = READU32(0xAF8C28); //online pointer0
		dupe1 = READU32(0xB02B38); //online pointer1
		dupe2 = READU32(0xB0CA48); //online pointer2
		dupe3 = READU32(0xB15958);
		dupe4 = READU32(0xB16958);
		WRITEU32(0x15fdc804, dupe);
		WRITEU32(0xAF8C2C, dupe0);
		WRITEU32(0xB02B3C, dupe1);
		WRITEU32(0xB0CA4C, dupe2);
		WRITEU32(0xB1595C, dupe3);
		WRITEU32(0xB1695C, dupe4);
	}
}

void	tan2_usa(void)
{
	WRITEU8(0x15fc1e38, 0xF);
}

void	tan3_usa(void)
{
	WRITEU8(0x15fcbd48, 0xF);
}

void	tan4_usa(void)
{
	WRITEU8(0x15fd5c58, 0xF);
}

void	walkThru_usa(void)
{
    int        loc;
    int        execution;

    if (is_pressed(BUTTON_L + BUTTON_DU))
    {
        WRITEU8(0xAAE710, 0x1);
    }
    else if    (is_pressed(BUTTON_L + BUTTON_DD))
    {
        WRITEU8(0xAAE710, 0x0);
    }
    if    (READU8(0xAAE710) == 0x1)
    {
        loc = READU32(0x17321644);
            if (loc == -1)
            {
 				WRITEU32(0x17321514, 0xCD7FFFFA);
            }
            else
            {
                SUBTOFLOAT(0x17321640, 0x00000006);
            }
    }           
    }

void	edibleItems_usa(void)
{
	u16		*id = (u16 *)0x16F4C160;
	char	id_str[5] = { 0 };
	int		i;
	u16		result;

	if (is_pressed(BUTTON_L))
	{
	id = (u16 *)0x16F4C160;
    for (i = 0; i < 4; i++)
		id_str[i] = (char)READU8(id + i);
	result = (u16)strtoul(id_str, NULL, 16);
	WRITEU16(0x17321DC4, result);
	}
}

void    seederV2_usa(void)
{
    u16        result;
    u16        *id;
    char        id_str[5];
    int        i;

    if (is_pressed(BUTTON_L))
    {
        id = (u16 *)0x16F4C160;
        for (i = 0; i < 4; i++)
            id_str[i] = (char)READU8(id + i);
        result = (u16)strtoul(id_str, NULL, 16);
        WRITEU16(0xA37bd8, result);

    }
    if (is_pressed(BUTTON_L + BUTTON_A))
    {
        id = (u16 *)0x16F4C160;
        for (i = 0; i < 4; i++)
            id_str[i] = (char)READU8(id + i);
        result = (u16)strtoul(id_str, NULL, 16);
        WRITEU32(0xA37bd8, 0x80000000 + result);
    }
}

void	walkThru_usaV2(void)
{
	int		loc;
	
	if (is_pressed(BUTTON_L + BUTTON_DU))
	{
		loc = READU32(0x17321644);
		if	(loc == -1)
		{
			WRITEU8(0x33066120, 0x1);
			WRITEU8(0x17321677, 0x1);
		}
		else
		{
			SUBTOFLOAT(0x17321640, 0x00000006);
		}
	}
	if (is_pressed(BUTTON_L + BUTTON_DD))
	{
		WRITEU8(0x1730F3EC, 0x0);
		WRITEU8(0x17321677, 0x0);
		
	}
}	

void	timeMachine_usa(void)
{
    u16         *id = (u16 *)0x16F4C160;
    char        yy_str[3] = { 0 };
    char        mm_str[3] = { 0 };
    char        dd_str[3] = { 0 };
    char        hh_str[3] = { 0 };
    char        mz_str[3] = { 0 };
    char        pm_str[2] = { 0 };
    s64         res_year = 0;
    s64         res_month = 0;
    s64         res_day = 0;
    s64         res_hour = 0;
    s64         res_min = 0;
    s64         res_nansec = 0;
    s64         res_plmn = 1;

    if (is_pressed(BUTTON_Y + BUTTON_DR))
	{
		yy_str[0] = (char)READU8(id + 0);
		yy_str[1] = (char)READU8(id + 1);
		mm_str[0] = (char)READU8(id + 2);
		mm_str[1] = (char)READU8(id + 3);
		dd_str[0] = (char)READU8(id + 4);
		dd_str[1] = (char)READU8(id + 5);
		hh_str[0] = (char)READU8(id + 6);
		hh_str[1] = (char)READU8(id + 7);
		mz_str[0] = (char)READU8(id + 8);
		mz_str[1] = (char)READU8(id + 9);
		if ((char)READU8(id + 10) == 45) //minus
			res_plmn = -1;
		res_year = (s64)strtoul(yy_str, NULL, 16);
			res_month = (s64)strtoul(mm_str, NULL, 16);
		res_day = (s64)strtoul(dd_str, NULL, 16);
		res_hour = (s64)strtoul(hh_str, NULL, 16);
		res_min = (s64)strtoul(mz_str, NULL, 16);
	
		res_year = res_year * (365 * 24 * 60 * 60) * (1000000000); //(year to seconds) * (seconds to nanoseconds)
		res_month = res_month * (28 * 24 * 60 * 60) * (1000000000); //("month" to seconds) * (seconds to nanoseconds)
		res_day = res_day * (24 * 60 * 60) * (1000000000); //(day to seconds) * (seconds to nanoseconds)
		res_hour = res_hour * (60 * 60) * (1000000000); //(hour to seconds) * (seconds to nanoseconds)
		res_min = res_min * (60) * (1000000000); //(minute to seconds) * (seconds to nanoseconds)
	
		res_nansec = (res_year + res_month + res_day + res_hour + res_min) * res_plmn;

		ADD64(0x16014620, res_nansec);
		ADD64(0x9E8AB0, res_nansec);
		wait_keys_released(DR);
	}
	
	if (is_pressed(BUTTON_Y + BUTTON_DL))
	{
		yy_str[0] = (char)READU8(id + 0);
		yy_str[1] = (char)READU8(id + 1);
		mm_str[0] = (char)READU8(id + 2);
		mm_str[1] = (char)READU8(id + 3);
		dd_str[0] = (char)READU8(id + 4);
		dd_str[1] = (char)READU8(id + 5);
		hh_str[0] = (char)READU8(id + 6);
		hh_str[1] = (char)READU8(id + 7);
		mz_str[0] = (char)READU8(id + 8);
		mz_str[1] = (char)READU8(id + 9);
		if ((char)READU8(id + 10) == 45) //minus
			res_plmn = -1;
		res_year = (s64)strtoul(yy_str, NULL, 16);
		res_month = (s64)strtoul(mm_str, NULL, 16);
		res_day = (s64)strtoul(dd_str, NULL, 16);
		res_hour = (s64)strtoul(hh_str, NULL, 16);
		res_min = (s64)strtoul(mz_str, NULL, 16);
	
		res_year = res_year * (365 * 24 * 60 * 60) * (1000000000); //(year to seconds) * (seconds to nanoseconds)
		res_month = res_month * (28 * 24 * 60 * 60) * (1000000000); //("month" to seconds) * (seconds to nanoseconds)
		res_day = res_day * (24 * 60 * 60) * (1000000000); //(day to seconds) * (seconds to nanoseconds)
		res_hour = res_hour * (60 * 60) * (1000000000); //(hour to seconds) * (seconds to nanoseconds)
		res_min = res_min * (60) * (1000000000); //(minute to seconds) * (seconds to nanoseconds)
	
		res_nansec = (res_year + res_month + res_day + res_hour + res_min) * res_plmn;

		SUB64(0x16014620, res_nansec);
		SUB64(0x9E8AB0, res_nansec);
		wait_keys_released(DL);
	}
}

void	timeTravel_usa(void)
{
	if(is_pressed(BUTTON_B + BUTTON_DR))
	{
		ADD64(0x16014620, 0x34630B8A000);
		ADD64(0x9E8AB0, 0x34630B8A000);
		wait_keys_released(DR);
	}
	if(is_pressed(BUTTON_B + BUTTON_DL))
	{
		SUB64(0x16014620, 0x34630B8A000);
		SUB64(0x9E8AB0, 0x34630B8A000);
		wait_keys_released(DL);
	}
	if(is_pressed(BUTTON_B + BUTTON_DD))
	{
		WRITES64(0x16014620, 0x0000000000000000);
		WRITES64(0x9E8AB0, 0x0000000000000000);
	}
	if(is_pressed(BUTTON_R + BUTTON_DR))
	{
		ADD64(0x16014620, 0xdf8475800);
		ADD64(0x9E8AB0, 0xdf8475800);
	}
	if(is_pressed(BUTTON_R + BUTTON_DL))
	{
		SUB64(0x16014620, 0xdf8475800);
		SUB64(0x9E8AB0, 0xdf8475800);
	}
}