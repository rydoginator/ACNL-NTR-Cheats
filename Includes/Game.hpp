#ifndef GAME_HPP
#define GAME_HPP

#include "types.h"

namespace CTRPluginFramework
{
    struct Position
    {
        u32     x;
        u32     y;
    };

    class Game
    {
    public:

        // Initialize properties
        static void     Initialize(void);

        // Return current world offset
        static u32      GetWorldOffset(void);
        // Return item's address at current position.
        // nullptr is returned is Room is unknown
        static u32      *GetItem(void);

        // Properties

        static u32      Building;   ///<
        static u32      *ClubItem;      ///< Address of the first item in club
        static u32      Garden;         ///< Address of the garden
        static u32      Gravity;        ///< Address of gravity
        static u32      *IslandItem;    ///< Address of the first item in the Island
        static u32      *MainStreetItem; ///< Address of the first item in MainStreet
        static Position *MainStreetPos; ///< Position of the player on MainStreet
        static u8       *Room;          ///< Address of the current room
        static u32      TCPImage;       ///< Address of the TCP picture
        static u64      *TimeReal;      ///< Address of the real game's time
        static u64      *TimeSave;      ///< Address of the save game's time
        static u32      *TownItem;      ///< Address of the first item in town
        static u32      Velocity;       ///< Address of velocity
        static u8       *Hour;          ///< Current hour that is read in the ingame clock
        static u8       *Minute;        ///< Current minute that is read in the ingame clock
        static Position *WorldPos;      ///< Position of the player in the world
        static u8      *BuildingSlots; ///<Address of how many building slots are being taken up
        static u32      *CodeDifference;///<Differenc between walk through walls ASM addresses
        static u32      *Nook;          ///<Nookling Offset
        static u32      TownFruit;     ///< Offset of town fruit
        static u32      TownGrass;     ///< Offset Town Grass Type
        static u32      TownTree;      ///< Offset of Town Tree 1st offset
        static u32      PWP;            ///< Offset of Mayor's PWP
        static u32      Permit;         ///<Offset of Mayor Permit rating
        static u32      *Grass;         ///<Offset of where grass starts
        static u32      *GrassEnd;
        static u32      *GameSpeed;     ///<offset of game speed found by Scotline and Mega Mew
        static u32      ItemForm;
        static u32      *Location;      //<Return -1 if you're outdoors
        static u32      Keyboard;      ///<Offset of Keyboard Symbols
        static u32      WispSpoof;   ///<Offset for Wisp Amiibo Spoof
        static u32      DIESpoof;   ///<Offset for Desert Island Escape Minigame Amiibo Spoof
        static u32      StaticNPC; ///<Offset of code.bin NPC loader address
        static u32      DynamicNPC; ///<Offset used by isabelle's file loading address in the 0x30000000 region since the game soft locks if code.bin is patched for some reason
        static u8       *BottomScreen; ///<Offset of what screen the bottom screen is
        static u16      *Consciousness; ///<Offset that makes your character faint
        static u32      *KeyboardText;  ///<Pointer to text config of text that represents how big the text can be and how much text can be put in
        static u8       *EnterBool;     ///<Allows the user to press enter in their keyboard
        static u32      Visibility;     ///<ASM address that makes your character invisible
        static u16      *CatalogItem;   ///<The item that you're on inside of your catalog
        static u8       *MapBool;       ///<Address of boolean that tells if you're showing your map or not
        static u32      *Tours;         ///<Pointer to Tours that are enabled/disabled
        static u32      EmoteASM;       ///<ASM offset for Emoticons
        static u32      PatternEdit;    ///<ASM offset for Edit Any Pattern
        static u32      NoBreakFlowers; ///<ASM offset for Breaking Flowers
        static u32      CountryASM;     ///<ASM offset for Country Spoofer
        static u32      Weather; ///<ASM offset for Weather Mod
        static u32      Confetti; ///<ASM offset for Confetti Mod
        static u32      CherryBlossom; ///<ASM offset for Cherry Blossom Mod
    };
}

#endif