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
#include "Helpers/Strings.hpp"

#define MAJOR_VERSION       4
#define MINOR_VERSION       2
#define REVISION_VERSION    0
#define BETA_VERSION        2
#define STRINGIFY(x)        #x
#define TOSTRING(x)         STRINGIFY(x)
//#define STRING_VERSION      "[" TOSTRING(MAJOR_VERSION) "." TOSTRING(MINOR_VERSION) "." TOSTRING(REVISION_VERSION) " ]"
#define STRING_VERSION      "[" TOSTRING(MAJOR_VERSION) "." TOSTRING(MINOR_VERSION) "." TOSTRING(REVISION_VERSION) " Beta " TOSTRING(BETA_VERSION) " ]"

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
    JAP,
    w_USA,
    w_EUR,
    w_JAP
};

enum
{
    KEYBOARDINPUT,
    ISLANDFINDER
};

union Item
{
    u32     raw;
    struct
    {
        u16     ID;
        u16     Flags;
    };
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
    char    Sstrncpy(char *dest, const char *src, size_t n);
    bool    launchUpdater(void);


    // Cheats functions

    /*
    ** Garden
    ********************/
    void    ChangePlayerName(MenuEntry *entry);
    void    ChangeTownName(MenuEntry *entry);
    void    GardenDumper(MenuEntry *entry);
    void    GardenRestore(MenuEntry *entry);
    void    ChangeNativeFruit(MenuEntry *entry);
    void    PWPUnlock(MenuEntry *entry);
    void    ChangeGrass(MenuEntry *entry);
	void	FillMuseum(MenuEntry* entry);
    void    Permit(MenuEntry *entry);
    void    BuildingModifier(MenuEntry *entry);

    /*
    ** Movement
    ********************/
    void    SpeedSettings(MenuEntry *entry);
    void    CoordinateModifier(MenuEntry *entry);
    void    TouchCoordinates(MenuEntry *entry);
    void    Teleporter(MenuEntry *entry);
    void    WalkOverThings(MenuEntry *entry);
    void    SpeedHack(MenuEntry *entry);
    void    SpeedHackEditor(MenuEntry *entry);
    void    MoonJump(MenuEntry *entry);
    void    TeleportTo(int person);
    void    PWPTeleport(MenuEntry *entry);
    void    RoomPicker(MenuEntry *entry);

    /*
    ** Inventory
    ********************/
    void    Text2Item(MenuEntry *entry);
    void    Duplication(MenuEntry *entry);
    void    DuplicationAll(void);
    void    ClearInv(void);
    void    ShowBuriedItems(MenuEntry *entry);
    void    PickBuriedItems(MenuEntry *entry);
    void    ExtendedInventoryBox(MenuEntry *entry);
    void    GenerateFossils(MenuEntry *entry);
    void    Encyclopedia(MenuEntry *entry);
    void    Emoticons(MenuEntry *entry);
    void    Songs(MenuEntry *entry);
    void    FillCatalog(MenuEntry *entry);

    /*
	** Money Cheats
	*****************/

    void    MaxMoneyBank(MenuEntry *entry);
    void    InfiniteBank(MenuEntry *entry);
    void    MaxCoupons(MenuEntry *entry);
    void    InfiniteCoupons(MenuEntry *entry);
    void    MaxMedals(MenuEntry *entry);
    void    InfiniteMedals(MenuEntry *entry);
    void    MaxWallet(MenuEntry *entry);
    void    InfiniteWallet(MenuEntry *entry);
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
    void    FishIdEditorSetter(MenuEntry *entry);
    void    FishIdEditor(MenuEntry *entry);
    void    FishCantBeScared(MenuEntry *entry);
    void    FishAlwaysBiteRightAway(MenuEntry *entry);

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
    void    TimeTravelSettings(MenuEntry *entry);
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
    void    StorageEverywhereSettings(MenuEntry *entry);
    void    Corrupter(MenuEntry *entry);
    void    CorrupterSettings(MenuEntry *entry);
    void    Faint(MenuEntry *entry);
    std::vector<u8> FindItemCoordinates(std::vector<u16> & id, bool isFlag);
    void    UltimateWeedPuller(MenuEntry *entry);
    void    UnBuryItems(MenuEntry *entry);
    void    EnableAllTours(MenuEntry *entry);
    void    AmiiboSpoof(MenuEntry *entry);
    bool    CheckU8Input(const void *input, std::string &error);
    void    UseAnyEmote(MenuEntry *entry);
    void    EditAnyPattern(MenuEntry *entry);
    void    UnbreakableFlowers(MenuEntry *entry);
    void    CountrySpoofer(MenuEntry *entry);
    void    InstantText(MenuEntry *entry);
    void    EchoTheMusic(MenuEntry *entry);

    
    /*
    ** Appearance
    ********************/
    void    AppearanceModifierMenu(void);

    /*
    ** Main Street
    ****************/
    void    MainStreetKeyboard(MenuEntry *entry);
    int     NooklingStoreSelector(void);
    void    NooklingKeyboard(MenuEntry *entry);
    void    CatalogToPockets(MenuEntry *entry);
    void    ShopsAlwaysOpenKeyboard(MenuEntry *entry);

    /*
    ** Weather
    ****************/
    void    WeatherMod(MenuEntry *entry);
    void    CherryBlossomMod(MenuEntry *entry);
    void    ConfettiMod(MenuEntry *entry);

    /*
    ** Callbacks
    ********************/
    void    CheatsKeyboard(void);
    void    PlayerUpdateCallback(void);
    void    MiniGame(void);
}
#endif
