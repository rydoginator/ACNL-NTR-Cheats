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
    void    FurnitureKeyboard(void);

    /*
    ** Helpers
    ********************/
    u32     DecryptACNLMoney(u64 money);
    u64     EncryptACNLMoney(int dec);
    void    StartMsg(void);
    u8      *memsearch(u8 *startPos, const void *pattern, u32 size, u32 patternSize);


    // Cheats functions

    /*
    ** Garden
    ********************/
    void    SetNameTo(MenuEntry *entry);
    void    GardenDumper(MenuEntry *entry);
    void    GardenRestore(MenuEntry *entry);
    void    ChangeNativeFruit(MenuEntry *entry);
    void    PWPUnlock(MenuEntry *entry);
    void    ChangeGrass(MenuEntry *entry);
    void    Permit(MenuEntry *entry);
    void    BuildingPlacer(MenuEntry *entry);

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
    void    TeleportTo(int person);

    /*
    ** Inventory
    ********************/
    void    Text2Item(MenuEntry *entry);
    void    Duplication(MenuEntry *entry);
    void    DuplicationAll(void);
    void    ShowBuriedItems(MenuEntry *entry);
    void    PickBuriedItems(MenuEntry *entry);
    void    ExtendedInventoryBox(MenuEntry *entry);
    void    GenerateFossils(MenuEntry *entry);
    void    Encyclopedia(MenuEntry *entry);
    void    Emoticons(MenuEntry *entry);
    void    Songs(MenuEntry *entry);
    void    MaxMoneyBank(MenuEntry *entry);
    void    InfiniteCoupons(MenuEntry *entry);
    void    InfiniteMedals(MenuEntry *entry);
    void    InfiniteWallet(MenuEntry * entry);
    void    WalletEditorSetter(MenuEntry *entry);
    void    WalletEditor(MenuEntry *entry);
    void    BankEditorSetter(MenuEntry *entry);
    void    BankEditor(MenuEntry *entry);


    /*
    ** Environment
    ********************/
    void    RemoveAllItems(MenuEntry *entry);
    void    RemoveAllWeeds(MenuEntry *entry);
    void    WaterAllFlowers(MenuEntry *entry);
    void    WorldEdit(MenuEntry *entry); ///< Maybe add a check on input ?
    void    DestroyGrass(MenuEntry *entry);
    void    FillGrass(MenuEntry *entry);
    void    SearchReplace(MenuEntry *entry);

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
    void    TimePicker(void);

    /*
    ** Misc.
    ********************/
    void    GhostMode(MenuEntry *entry);
    void    CameraMod(MenuEntry *entry); ///< Probably need a rework
    void	CustomKB(MenuEntry *entry);
    void    KeyboardExtender(MenuEntry *entry);
    void    FastGameSpeed(MenuEntry *entry);
    void    ItemFormChanger(MenuEntry *entry);
    void    ItemFormEditor(MenuEntry *entry);
    void    ItemEffectChanger(MenuEntry *entry);
    void    ItemEffectEditor(MenuEntry *entry);
    int     ItemChangerKeyboard(void);
    void    AnimalChangerKeyboard(MenuEntry *entry);
    void    AnimalChanger(MenuEntry *entry);
    void    ChangeAnimal(const char* name);
    void    StorageEverywhere(MenuEntry *entry);
    void    Faint(MenuEntry *entry);
    
    /*
    ** Appearance
    ********************/
    void    AppearanceModifierMenu(void);

    /*
    ** Main Street
    ****************/
    void    FillCatalog(MenuEntry *entry);
    void    FillMainStreet(MenuEntry *entry);
    void    NooklingKeyboard(MenuEntry *entry);
    void    SetNook(int value);
    void    CatalogToPockets(MenuEntry *entry);

    /*
    ** Callbacks
    ********************/
    void    CheatsKeyboard(void);
    void    PlayerUpdateCallback(void);
    void    MiniGame(void);
}
#endif
