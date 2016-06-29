#include "global.h"

#define     add_search_replace(find, replace)   g_find[g_i] = find; g_replace[g_i] = replace; g_i++
#define     reset_search()						memset(g_find, 0, sizeof(g_find)); memset(g_replace, 0, sizeof(g_find)); g_i = 0
#define     WRITEU8(addr, data)                    *(volatile unsigned char*)(addr) = data
#define     WRITEU16(addr, data)                *(volatile unsigned short*)(addr) = data
#define     WRITEU32(addr, data)                *(volatile unsigned int*)(addr) = data
#define     READU8(addr)                        *(volatile unsigned char*)(addr)
#define     READU16(addr)                        *(volatile unsigned short*)(addr)
#define     READU32(addr)                        *(volatile unsigned int*)(addr)
#define     BUTTON_A                            0x00000001
#define     BUTTON_B                            0x00000002
#define     BUTTON_SE                            0x00000004
#define     BUTTON_ST                            0x00000008
#define     BUTTON_DR                            0x00000010
#define     BUTTON_DL                            0x00000020
#define     BUTTON_DU                            0x00000040
#define     BUTTON_DD                            0x00000080
#define     BUTTON_R                            0x00000100
#define     BUTTON_L                            0x00000200
#define     BUTTON_X                            0x00000400
#define     BUTTON_Y                            0x00000800
#define     IO_BASE_PAD                            1
#define     IO_BASE_LCD                            2
#define     IO_BASE_PDC                            3
#define     IO_BASE_GSPHEAP                        4

enum
{
    FREEZE = 1,
    NOTFREEZE = 0
};

/*
** Globals
*/

Handle                    fsUserHandle;
FS_archive                sdmcArchive;
GAME_PLUGIN_MENU        gamePluginMenu;
u32                        threadStack[0x1000];
u32                        IoBasePad = 0xFFFD4000;
u32                        g_find[100];
u32                        g_replace[100];
int                        g_i = 0;
s32                        isNewNtr = 0;
u8                        g_cheatEnabled[64];
u8                        g_state[64];
void                    (*g_functions[64])(void);

/*
**
*/

/*
** Prototypes
*/

u32        plgGetIoBase(u32 IoType);
u32        getCurrentProcessId();

/*
**
*/

u32     getKey()
{
    return (*(vu32*)(IoBasePad) ^ 0xFFF) & 0xFFF;
}

void     waitKeyChange(u32 key)
{
    while (key == getKey());
}

void     waitKeyUp()
{
    while (getKey() != 0);
}

void     initMenu()
{
    memset(&gamePluginMenu, 0, sizeof(GAME_PLUGIN_MENU));
    memset(&g_cheatEnabled, 0, sizeof(g_cheatEnabled));
    memset(&g_state, 0, sizeof(g_state));
    memset(&g_functions, 0, sizeof(g_functions));
}

void     addMenuEntry(u8 *str)
{
    u32     pos;
    u32     len;
 
    if (gamePluginMenu.count > 64)
        return;
    pos = gamePluginMenu.count;
    len = strlen(str) + 1;
    gamePluginMenu.offsetInBuffer[pos] = gamePluginMenu.bufOffset;
    strcpy(&(gamePluginMenu.buf[gamePluginMenu.bufOffset]), str);
    gamePluginMenu.count += 1;
    gamePluginMenu.bufOffset += len;
}

void     addCheatMenuEntry(u8 *str, void (*f)(void), u8 state)
{
    u8 buf[100];
 
    g_functions[gamePluginMenu.count] = f;
    g_state[gamePluginMenu.count] = state;
    xsprintf(buf, "[ ] %s", str);
    addMenuEntry(buf);
}

u32     updateMenu()
{
    u32     ret;
    u32     hProcess;
    u32     homeMenuPid;
 
    PLGLOADER_INFO *plgLoaderInfo = (void*)0x07000000;
    plgLoaderInfo->gamePluginPid = getCurrentProcessId();
    plgLoaderInfo->gamePluginMenuAddr = (u32)&gamePluginMenu;
    ret = 0;
    homeMenuPid = plgGetIoBase(5);
    if (homeMenuPid == 0)
        return(1);
    ret = svc_openProcess(&hProcess, homeMenuPid);
    if (ret != 0)
        return (ret);
    copyRemoteMemory(hProcess, &(plgLoaderInfo->gamePluginPid), CURRENT_PROCESS_HANDLE, &(plgLoaderInfo->gamePluginPid), 8);
final:
    svc_closeHandle(hProcess);
    return (ret);
}

int     scanMenu()
{
    u32 i;
 
    for (i = 0; i < gamePluginMenu.count; i++)
    {
        if (gamePluginMenu.state[i])
        {
            gamePluginMenu.state[i] = 0;
            return (i);
        }
    }
    return (-1);
}

int     detectLanguage()
{
    return(0);
}

void     updateCheatEnableDisplay(u32 id)
{
    if(gamePluginMenu.buf[gamePluginMenu.offsetInBuffer[id]] == '[' && gamePluginMenu.buf[gamePluginMenu.offsetInBuffer[id] + 2] == ']')
        gamePluginMenu.buf[gamePluginMenu.offsetInBuffer[id] + 1] = g_cheatEnabled[id] ? 'X' : ' ';
}

void     disableCheat(int index)
{
    g_cheatEnabled[index] = !g_cheatEnabled[index];
    updateCheatEnableDisplay(index);
}

void     onCheatItemChanged(int id, int enable)
{
    if(enable)
    {
        g_functions[id]();
        if(!g_state[id])
            disableCheat(id);
    }
}

void     scanCheatMenu()
{
    int ret = scanMenu();
 
    if (ret != -1)
    {
        g_cheatEnabled[ret] = !g_cheatEnabled[ret];
        updateCheatEnableDisplay(ret);
        onCheatItemChanged(ret, g_cheatEnabled[ret]);
    }
}

void    find_and_replace_multiple(void *start_addr, u32 length)
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

/*
** Cheats functions
*/

u32        add_to_address(void *address, u32 value_to_add)
{
    *(u32 *)address += value_to_add;
}

u32        sub_to_address(void *address, u32 value_to_sub)
{
    *(u32 *)address -= value_to_sub;
}

void    coord(void)
{
    static int           loc = 0;
    u32        key = getKey();

    if (key == BUTTON_A)
    {
        loc = READU32(0x17321644);
    }
    if (loc == -1) //FFFFFFFF=outdoors
    {
        if (key == BUTTON_A + BUTTON_DD)
            add_to_address((void *)0x17321518, 0x00000200);
        if (key == BUTTON_A + BUTTON_DU)
            sub_to_address((void *)0x17321518, 0x00000200);
        if (key == BUTTON_A + BUTTON_DL)
            sub_to_address((void *)0x17321510, 0x00000200);
        if (key == BUTTON_A + BUTTON_DR)
            add_to_address((void *)0x17321510, 0x00000200);
    }
    else //if it's anything but FFFFFFFF then you're indoors
    {
        if (key == BUTTON_A + BUTTON_DD)
            add_to_address((void *)0x17321644, 0x00000800);
        if (key == BUTTON_A + BUTTON_DU)
            sub_to_address((void *)0x17321644, 0x00000800);
        if (key == BUTTON_A + BUTTON_DL)
            sub_to_address((void *)0x1732163c, 0x00000600);
        if (key == BUTTON_A + BUTTON_DR)
            add_to_address((void *)0x1732163c, 0x00000600);
    }
}
void    search(void)
{
    u16        result;
    u32        key = getKey();

    if (key != BUTTON_R + BUTTON_DD)
        return;
	    u16        *id = (u16 *)0x16F4C160;
    char    id_str[5] = { 0 };
    int        i;
    for (i = 0; i < 4; i++)
        id_str[i] = (char)READU16(id + i);
    result = (u16)strtoul(id_str, NULL, 16);
	reset_search();
    add_search_replace(0x20A7, result);
    find_and_replace_multiple((void *)0x16005958, 0x5000);
	find_and_replace_multiple((void *)0x16022328, 0x1000);
    waitKeyUp();
}

void    destroy(void)
{
    u16        result;
    u32        key = getKey();

    if (key != BUTTON_R + BUTTON_DU)
        return;
	u16        *id = (u16 *)0x16F4C160;
    char    id_str[5] = { 0 };
    int        i;
    for (i = 0; i < 4; i++)
        id_str[i] = (char)READU16(id + i);
    result = (u16)strtoul(id_str, NULL, 16);
	reset_search();
    add_search_replace(result, 0x7FFE);
    find_and_replace_multiple((void *)0x16005958, 0x5000);
	find_and_replace_multiple((void *)0x16022328, 0x1000);
    waitKeyUp();
}

void    text2item(void)
{
    u16        *id = (u16 *)0x16F4C160;
    char    id_str[5] = { 0 };
    int        i;
    u16        result;
    u32        key = getKey();

    if (key != BUTTON_X + BUTTON_DR)
        return;
    for (i = 0; i < 4; i++)
        id_str[i] = (char)READU16(id + i);
    result = (u16)strtoul(id_str, NULL, 16);
    WRITEU16(0x15FBEAD0, result);
    waitKeyUp();
}

void    moonjump(void)
{
	u32            key = getKey();
    static int           loc = 0;
    if (key == BUTTON_L)
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

void    teleport(void)
{
    u32            key = getKey();
    static u32    X = 0;
    static u32    Y = 0;
    static int    loc = 0;
    if (key == BUTTON_B)
	{
		loc = READU32(0x17321644);
	}
	if (key == BUTTON_B + BUTTON_DU)
    {
		if (loc == -1)
		{
			X = READU32(0x17321510);
			Y = READU32(0x17321518);
		}
		else
		{
			X = READU32(0x1732163c);
			Y = READU32(0x17321644);
		}
    }
    if (key == BUTTON_B + BUTTON_DD)
    {
		if (loc == -1)
		{
			WRITEU32(0x17321510, X);
			WRITEU32(0x17321518, Y);
		}
		else
		{
			WRITEU32(0x1732163c, X);
			WRITEU32(0x17321644, Y);
		}
    }
}

void	weeder(void)
{
    u32           key = getKey();
	if (key == BUTTON_R + BUTTON_A)
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
		waitKeyUp();
	}
}

void	quench(void)
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
}

void	tree(void)
{
	u32			key = getKey();
	if (key == BUTTON_X)
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

void	duplicate(void)
{
	u32			key = getKey();
	u32			dupe = 0;
	if (key == BUTTON_R)
	{
		dupe = READU32(0x15FBEAD0);
		WRITEU32(0x15FBEAD4, dupe);
	}
}

void	grass(void)
{
    int i;

    for (i = 0x1600BD80; i < 0x1600E57F; i++)
        *(u32 *)i = 0xFFFFFFFF;
}

void	desert(void)
{
    int i;

    for (i = 0x1600BD80; i < 0x1600E57F; i++)
        *(u32 *)i = 0x00000000;
}


/*
**
*/
void    initCheatMenu()
{
    initMenu();
	addMenuEntry("ACNL NTR Cheats Ver 2.0.2");
	addMenuEntry("Plugin by itsRyan");
	addMenuEntry("USA Version");
    addMenuEntry("--- Enviroment Codes ---"); 
	addCheatMenuEntry("Water all flowers", quench, FREEZE);
    addCheatMenuEntry("Seeder", search, FREEZE);
    addCheatMenuEntry("Destroyer", destroy, FREEZE);
	addCheatMenuEntry("Grass", grass, FREEZE);
	addCheatMenuEntry("Desert", desert, FREEZE);
	addCheatMenuEntry("Remove all weeds", weeder, FREEZE);
	addCheatMenuEntry("Instant Tree", tree, FREEZE);
    addMenuEntry("--- Inventory Codes ---"); //Exemple	
    addCheatMenuEntry("Text to Item", text2item, FREEZE);
	addCheatMenuEntry("Duplication", duplicate, FREEZE);
	addMenuEntry("--- Movement Codes ---");
    addCheatMenuEntry("Moon Jump", moonjump, FREEZE);
    addCheatMenuEntry("Teleport", teleport, FREEZE);
    addCheatMenuEntry("Coordinates Modifier", coord, FREEZE);
    updateMenu();
}

void gamePluginEntry()
{
    u32 i;
 
    INIT_SHARED_FUNC(plgGetIoBase, 8);
    INIT_SHARED_FUNC(copyRemoteMemory, 9);
    svc_sleepThread(5000000000);
    if (((NS_CONFIG*)(NS_CONFIGURE_ADDR))->sharedFunc[8])
        isNewNtr = 1;
    else
        isNewNtr = 0;
    if (isNewNtr)
        IoBasePad = plgGetIoBase(IO_BASE_PAD);
    initCheatMenu();
    while (1)
    {
        svc_sleepThread(10000);
        scanCheatMenu();
        for(i = 0; i < 64; i++)
            (g_cheatEnabled[i]) ? g_functions[i]() : 0 ;
    }
}