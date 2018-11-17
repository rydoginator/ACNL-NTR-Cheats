#ifndef AMIIBOSPOOF_HPP
#define AMIIBOSPOOF_HPP

#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{

    struct Villagers
    {
        const char  *Name; //Villager Name
        const u16   VID; //Villager ID
        const char  *Filename; //Villager Model ROMFS Filename
        const u16   AMIIBO_ID; //Villager Amiibo ID
    };

    struct Species
    {
        const char  *Name;
        const u32   Start;
        const u32   End;
    };

    struct AmiiboChecks
    {
        u32 Offset;
        u8  UIOpen;
        u8  CanScanAmiibo;
    };

    typedef enum
    {
        MODE_WISP = 0,
        MODE_DIE  = 1,
        MODE_PL   = 2,
        MODE_AMC  = 3,

    } AmiiboSpoof_Modes;

    extern const Species        g_species[36];
    extern const Villagers      g_villagers[454];

    /* Functions */
    u32     GetWispOffset(void);
    void    WispSpoofer(u16 Amiibo_ID);
    void    DIESpoofer(const char* Model);
    void    VillagersKeyboard(u8 mode);
    void    AmiiboSpoof(MenuEntry *entry);
}

#endif