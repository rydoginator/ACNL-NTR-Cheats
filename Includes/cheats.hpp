#ifndef CHEATS_H
#define CHEATS_H

#include "CTRPluginFramework.hpp"
#include "Game.hpp"
#include "HoldKey.hpp"
#include "Player.hpp"
#include "Offsets.hpp"
#include "RAddress.hpp"
#include "Unicode.h"
#include "Values.hpp"
#include "Strings.hpp"

#define READU32(x)      *(u32 *)(x)
#define READU16(x)      *(u16 *)(x)
#define READU8(x)       *(u8 *)(x)
#define READFLOAT(x)    *(float *)(x)

#define WRITEU8(a, v)   *(u8 *)(a) = (u8)v
#define WRITEU16(a, v)  *(u16 *)(a) = (u16)v
#define WRITEU32(a, v)  *(u32 *)(a) = (u32)v 
#define WRITEU64(a, v)  *(u64 *)(a) = (u64)v

#define ADD32(a, v)     *(u32 *)a += v
#define SUB32(a, v)     *(u32 *)a -= v
#define ADD64(a, v)     *(vs64 *)a += v
#define SUB64(a, v)     *(vs64 *)a -= v
#define ADD16(a, v)     *(u16 *)a += v
#define SUB16(a, v)     *(u16 *)a -= v
#define ADD8(a, v)      *(u8 *)a += v
#define SUB8(a, v)      *(u8 *)a -= v
#define ADDTOFLOAT(a, v)  *((float*)(a)) += (float)v
#define SUBTOFLOAT(a, v)  *((float*)(a)) -= (float)v

enum Region
{
    USA = 0,
    EUR,
    JAP
};

enum
{
    KEYBOARDINPUT,
    ISLANDFINDER
};

namespace CTRPluginFramework
{
    extern bool g_command;

    // Need to be cleaned:
    void    Assign(void);
    
    void    assign_region(Region region);

  
    void    timePicker(void);

    void    appearanceMod(void);
    void    duplicationAll(void);

    void    GetSet(int set);
    void    FurnitureKeyboard(void);

    /*
    ** Helpers
    ********************/
    int     RandomNum(int start, int end);
    u32     DecryptACNLMoney(u64 money);
    u64     EncryptACNLMoney(int dec);

    // Cheats functions

    /*
    ** Garden
    ********************/
    void    SetNameTo(MenuEntry *entry);
    void    GardenDumper(MenuEntry *entry);
    void    GardenRestore(MenuEntry *entry);
    void    InjectTCP(MenuEntry *entry);

    /*
    ** Movement
    ********************/
    void    CoordinateModifier(MenuEntry *entry);
    void    TouchCoordinates(MenuEntry *entry);
    void    Teleporter(MenuEntry *entry);
    void    WalkOverThings(MenuEntry *entry);
    void    SpeedHack(MenuEntry *entry);
    void    SpeedHackEditor(MenuEntry *entry);
    void    MoonJump(MenuEntry *entry);

    /*
    ** Inventory
    ********************/
    void    Text2Item(MenuEntry *entry);
    void    Duplication(MenuEntry *entry);
    void    ShowBuriedItems(MenuEntry *entry);
    void    PickBuriedItems(MenuEntry *entry);
    void    ShowBells(MenuEntry *entry); ///< Need fix ?
    void    SetBells(MenuEntry *entry);  ///< Need fix ?
    void    ExtendedInventoryBox(MenuEntry *entry);
    void    GenerateFossils(MenuEntry *entry);

    /*
    ** Environment
    ********************/
    void    RemoveAllItems(MenuEntry *entry);
    void    RemoveAllWeeds(MenuEntry *entry);
    void    WaterAllFlowers(MenuEntry *entry);
    void    WorldEdit(MenuEntry *entry); ///< Maybe add a check on input ?

    /*
    ** Time Travel
    ********************/
    void    AddTime(u64 time);
    void    RewindTime(u64 time);
    void    AddTime(u8 hour, u8 minute);
    void    RewindTime(u8 hour, u8 minute);
    void    ResetTime(void);
    void    TimeTravel(MenuEntry *entry);
    void    TimeMachine(MenuEntry *entry);
    void    SetTimeTo(int hour);

    /*
    ** Misc.
    ********************/
    void    BuildingPlacer(MenuEntry *entry);
    void    GhostMode(MenuEntry *entry);
    void    CameraMod(MenuEntry *entry); ///< Probably need a rework
    void    KeyboardExtender(MenuEntry *entry);
	
	/*
    ** Appearance
    ********************/
    void    changeGender(void);
    void    changeHair(void);
	void    changeFace(void);
    void    changeHairCol(void);
	void    changeEyeCol(void);
	void    changeTan(void);
	void    changeHat(void);
	void    changeAccessory(void);
	void    changeTop(void);
	void    changePants(void);
	void    changeSocks(void);
	void    changeShoes(void);
	void    apparelMod(void);
	void    appearanceMod(void);

    /*
    ** Callbacks
    ********************/
    void    SleepThread(void);
    void    CheatsKeyboard(void);
    void    PlayerUpdateCallback(void);
}
#endif
