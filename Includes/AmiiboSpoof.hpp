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

    const std::vector<Species>   g_species = 
    {
        {"Alligator", 0, 6},
        {"Anteater", 7, 13},
        {"Bear", 14, 27},
        {"Bird", 28, 41},
        {"Bull", 42, 47},
        {"Cat", 48, 70},
        {"Chicken", 71, 79},
        {"Cow", 80, 83},
        {"Cub", 84, 99},
        {"Deer", 100, 110},
        {"Dog", 111, 126},
        {"Duck", 127, 143},
        {"Eagle", 144, 152},
        {"Elephant", 153, 163},
        {"Frog", 164, 181},
        {"Goat", 182, 188},
        {"Gorilla", 189, 198},
        {"Hamster", 199, 207},
        {"Hippo", 208, 214},
        {"Horse", 215, 230},
        {"Koala", 231, 239},
        {"Kangaroo", 240, 247},
        {"Lion", 248, 254},
        {"Monkey", 255, 262},
        {"Mouse", 263, 277},
        {"Octopus", 278, 281},
        {"Ostrich", 282, 291},
        {"Penguin", 292, 304},
        {"Pig", 305, 320},
        {"Rabbit", 321, 341},
        {"Rhino", 342, 347},
        {"Sheep", 348, 360},
        {"Squirrel", 361, 380},
        {"Tiger", 381, 387},
        {"Wolf", 388, 398},
        {"Special Characters", 399, 453},
    };

    const std::vector<Villagers>   g_villagers =
    {
        {"Alfonso", 0x005d, "crd00", 0x02C3}, // Alligator
        {"Alli", 0x005e, "crd01", 0x02C4}, // Alligator 
        {"Boots", 0x005f, "crd02", 0x02C5}, // Alligator 
        {"Del", 0x0060, "crd04", 0x02C7}, // Alligator 
        {"Drago", 0x0063, "crd08", 0x02CB}, // Alligator 
        {"Gayle", 0x0062, "crd07", 0x02CA}, // Alligator 
        {"Sly", 0x0061, "crd06", 0x0290}, // Alligator 
        {"Anabelle", 0x0003, "ant03", 0x0203}, // Anteater 
        {"Annalisa", 0x0005, "ant08", 0x0208}, // Anteater 
        {"Antonio", 0x0001, "ant01", 0x0201}, // Anteater 
        {"Cyrano", 0x0000, "ant00", 0x2000}, // Anteater 
        {"Olaf", 0x0006, "ant09", 0x0209}, // Anteater 
        {"Pango", 0x0002, "ant02", 0x0202}, // Anteater 
        {"Snooty", 0x0004, "ant06", 0x0206}, // Anteater 
        {"Beardo", 0x0013, "bea13", 0x0221}, // Bear 
        {"Charlise", 0x0012, "bea12", 0x0220}, // Bear 
        {"Chow", 0x000a, "bea03", 0x0217}, // Bear 
        {"Curt", 0x0009, "bea02", 0x0216}, // Bear 
        {"Grizzly", 0x000f, "bea09", 0x021D}, // Bear 
        {"Groucho", 0x000c, "bea06", 0x021A}, // Bear 
        {"Ike", 0x0011, "bea11", 0x021F}, // Bear 
        {"Klaus", 0x0014, "bea14", 0x0222}, // Bear 
        {"Nate", 0x000b, "bea05", 0x0219}, // Bear 
        {"Paula", 0x0010, "bea10", 0x021E}, // Bear 
        {"Pinky", 0x0008, "bea01", 0x0215}, // Bear 
        {"Teddy", 0x0007, "bea00", 0x0214}, // Bear 
        {"Tutu", 0x000d, "bea07", 0x021B}, // Bear 
        {"Ursala", 0x000e, "bea08", 0x021C}, // Bear 
        {"Admiral", 0x001b, "brd06", 0x0233}, // Bird 
        {"Anchovy", 0x0017, "brd02", 0x022F}, // Bird 
        {"Jacques", 0x001f, "brd16", 0x023D}, // Bird 
        {"Jakey/Jacob", 0x001d, "brd11", 0x0238}, // Bird 
        {"Jay", 0x0015, "brd00", 0x022D}, // Bird 
        {"Jitters", 0x0019, "brd04", 0x0231}, // Bird 
        {"Lucha", 0x001e, "brd15", 0x023C}, // Bird 
        {"Medli", 0x0022, "brd19", 0x0101}, // Bird
        {"Midge", 0x001c, "brd08", 0x0235}, // Bird 
        {"Peck", 0x0020, "brd17", 0x023E}, // Bird 
        {"Piper", 0x001a, "brd05", 0x0232}, // Bird 
        {"Robin", 0x0016, "brd01", 0x022E}, // Bird 
        {"Sparro", 0x0021, "brd18", 0x023F}, // Bird 
        {"Twiggy", 0x0018, "brd03", 0x0230}, // Bird 
        {"Angus", 0x0023, "bul00", 0x024A}, // Bull 
        {"Coach", 0x0027, "bul07", 0x0251}, // Bull 
        {"Rodeo", 0x0024, "bul01", 0x024B}, // Bull 
        {"Stu", 0x0025, "bul03", 0x024D}, // Bull 
        {"T-Bone", 0x0026, "bul05", 0x024F}, // Bull 
        {"Vic", 0x0028, "bul08", 0x0252}, // Bull 
        {"Ankha", 0x003c, "cat19", 0x0270}, // Cat 
        {"Bob", 0x0029, "cat00", 0x025D}, // Cat 
        {"Felicity", 0x003a, "cat17", 0x026E}, // Cat 
        {"Felyne", 0x003f, "cat22", 0x3501}, // Cat
        {"Kabuki", 0x0032, "cat09", 0x0266}, // Cat 
        {"Katt", 0x003e, "cat21", 0x0272}, // Cat 
        {"Kid Cat", 0x0033, "cat10", 0x0267}, // Cat 
        {"Kiki", 0x002d, "cat04", 0x0261}, // Cat 
        {"Kitty", 0x0037, "cat14", 0x026B}, // Cat 
        {"Lolly", 0x003b, "cat18", 0x026F}, // Cat 
        {"Merry", 0x0039, "cat16", 0x026D}, // Cat 
        {"Mitzi", 0x002a, "cat01", 0x025E}, // Cat 
        {"Moe", 0x0031, "cat08", 0x0265}, // Cat 
        {"Monique", 0x0034, "cat11", 0x0268}, // Cat 
        {"Olivia", 0x002c, "cat03", 0x0260}, // Cat 
        {"Punchy", 0x002f, "cat06", 0x0263}, // Cat 
        {"Purrl", 0x0030, "cat07", 0x0264}, // Cat 
        {"Rosie", 0x002b, "cat02", 0x025F}, // Cat 
        {"Rudy", 0x003d, "cat20", 0x0271}, // Cat 
        {"Stinky", 0x0036, "cat13", 0x026A}, // Cat 
        {"Tabby", 0x0035, "cat12", 0x0269}, // Cat 
        {"Tangy", 0x002e, "cat05", 0x0262}, // Cat 
        {"Tom", 0x0038, "cat15", 0x026C}, // Cat 
        {"Ava", 0x0053, "chn05", 0x029E}, // Chicken 
        {"Becky", 0x0054, "chn09", 0x02A2}, // Chicken 
        {"Benedict", 0x0051, "chn01", 0x029A}, // Chicken 
        {"Broffina", 0x0057, "chn12", 0x02A5}, // Chicken 
        {"Egbert", 0x0052, "chn02", 0x029B}, // Chicken 
        {"Goose", 0x0050, "chn00", 0x0299}, // Chicken 
        {"Ken", 0x0058, "chn13", 0x02A6}, // Chicken 
        {"Knox", 0x0056, "chn11", 0x02A4}, // Chicken 
        {"Plucky", 0x0055, "chn10", 0x02A3}, // Chicken 
        {"Naomi", 0x005c, "cow07", 0x02B8}, // Cow 
        {"Norma", 0x005b, "cow06", 0x02B7}, // Cow 
        {"Patty", 0x0059, "cow00", 0x02B1}, // Cow 
        {"Tipper", 0x005a, "cow01", 0x02B2}, // Cow 
        {"Barold", 0x004d, "cbr16", 0x028D}, // Cub 
        {"Bluebear", 0x0040, "cbr00", 0x027D}, // Cub 
        {"Cheri", 0x0049, "cbr10", 0x0287}, // Cub 
        {"Chester", 0x004c, "cbr15", 0x028C}, // Cub 
        {"June", 0x004a, "cbr13", 0x028A}, // Cub 
        {"Kody", 0x0044, "cbr04", 0x0281}, // Cub 
        {"Maple", 0x0041, "cbr01", 0x027E}, // Cub 
        {"Marty", 0x004f, "cbr18", 0x028F}, // Cub 
        {"Murphy", 0x0047, "cbr07", 0x0284}, // Cub 
        {"Olive", 0x0048, "cbr09", 0x0286}, // Cub 
        {"Pekoe", 0x004b, "cbr14", 0x028B}, // Cub 
        {"Poncho", 0x0042, "cbr02", 0x027F}, // Cub 
        {"Pudge", 0x0043, "cbr03", 0x0280}, // Cub 
        {"Stitches", 0x0045, "cbr05", 0x0282}, // Cub 
        {"Tammy", 0x004e, "cbr17", 0x028E}, // Cub 
        {"Vladimir", 0x0046, "cbr06", 0x0283}, // Cub 
        {"Bam", 0x0065, "der01", 0x02D7}, // Deer 
        {"Beau", 0x006b, "der07", 0x02DD}, // Deer 
        {"Bruce", 0x0067, "der03", 0x02D9}, // Deer 
        {"Chelsea", 0x006e, "der10", 0x02E0}, // Deer 
        {"Deirdre", 0x0068, "der04", 0x02DA}, // Deer 
        {"Diana", 0x006c, "der08", 0x02DE}, // Deer 
        {"Erik", 0x006d, "der09", 0x02DF}, // Deer 
        {"Fauna", 0x0064, "der00", 0x02D6}, // Deer 
        {"Fuchsia", 0x006a, "der06", 0x02DC}, // Deer 
        {"Lopez", 0x0069, "der05", 0x02DB}, // Deer 
        {"Zell", 0x0066, "der02", 0x02D8}, // Deer 
        {"Bea", 0x0079, "dog10", 0x02F4}, // Dog 
        {"Benjamin", 0x007c, "dog16", 0x02FA}, // Dog 
        {"Biskit", 0x0072, "dog03", 0x02ED}, // Dog 
        {"Bones", 0x0073, "dog04", 0x02EE}, // Dog 
        {"Butch", 0x0070, "dog01", 0x02EB}, // Dog 
        {"Cherry", 0x007d, "dog17", 0x02FB}, // Dog 
        {"Cookie", 0x0077, "dog08", 0x02F2}, // Dog 
        {"Daisy", 0x0076, "dog07", 0x02F1}, // Dog 
        {"Goldie", 0x006f, "dog00", 0x02EA}, // Dog 
        {"Lucky", 0x0071, "dog02", 0x02EC}, // Dog 
        {"Mac", 0x007a, "dog14", 0x02F8}, // Dog 
        {"Maddie", 0x0078, "dog09", 0x02F3}, // Dog 
        {"Marcel", 0x007b, "dog15", 0x02F9}, // Dog 
        {"Portia", 0x0074, "dog05", 0x02EF}, // Dog 
        {"Shep", 0x007e, "dog18", 0x02FC}, // Dog 
        {"Walker", 0x0075, "dog06", 0x02F0}, // Dog 
        {"Bill", 0x007f, "duk00", 0x0307}, // Duck 
        {"Deena", 0x0083, "duk04", 0x030B}, // Duck 
        {"Derwin", 0x0087, "duk08", 0x030F}, // Duck 
        {"Drake", 0x0088, "duk09", 0x0310}, // Duck 
        {"Freckles", 0x0086, "duk07", 0x030E}, // Duck 
        {"Gloria", 0x008d, "duk15", 0x0316}, // Duck 
        {"Joey", 0x0080, "duk01", 0x0308}, // Duck 
        {"Ketchup", 0x008c, "duk13", 0x0314}, // Duck 
        {"Maelle", 0x0082, "duk03", 0x030A}, // Duck 
        {"Mallary", 0x0085, "duk06", 0x030D}, // Duck 
        {"Miranda", 0x008b, "duk12", 0x0313}, // Duck 
        {"Molly", 0x008e, "duk16", 0x0317}, // Duck 
        {"Pate", 0x0081, "duk02", 0x0309}, // Duck 
        {"Pompom", 0x0084, "duk05", 0x030C}, // Duck 
        {"Quillson", 0x008f, "duk17", 0x0318}, // Duck 
        {"Scoot", 0x0089, "duk10", 0x0311}, // Duck 
        {"Weber", 0x008a, "duk11", 0x0312}, // Duck 
        {"Amelia", 0x011c, "pbr01", 0x044C}, // Eagle 
        {"Apollo", 0x011b, "pbr00", 0x044B}, // Eagle 
        {"Avery", 0x011f, "pbr05", 0x0450}, // Eagle 
        {"Buzz", 0x011e, "pbr03", 0x044E}, // Eagle 
        {"Celia", 0x0123, "pbr09", 0x0454}, // Eagle 
        {"Frank", 0x0120, "pbr06", 0x0451}, // Eagle 
        {"Keaton", 0x0122, "pbr08", 0x0453}, // Eagle 
        {"Pierce", 0x011d, "pbr02", 0x044D}, // Eagle 
        {"Sterling", 0x0121, "pbr07", 0x0452}, // Eagle 
        {"Axel", 0x0096, "elp06", 0x0329}, // Elephant 
        {"Big Top", 0x0092, "elp02", 0x0325}, // Elephant 
        {"Chai", 0x009a, "elp11", 0x032E}, // Elephant 
        {"Dizzy", 0x0091, "elp01", 0x0324}, // Elephant 
        {"Ellie", 0x0097, "elp07", 0x032A}, // Elephant 
        {"Eloise", 0x0093, "elp03", 0x0326}, // Elephant 
        {"Margie", 0x0094, "elp04", 0x0327}, // Elephant 
        {"Opal", 0x0090, "elp00", 0x0323}, // Elephant 
        {"Paolo", 0x0095, "elp05", 0x0328}, // Elephant 
        {"Tia", 0x0099, "elp10", 0x032D}, // Elephant 
        {"Tucker", 0x0098, "elp09", 0x032C}, // Elephant 
        {"Camofrog", 0x009e, "flg03", 0x033B}, // Frog 
        {"Cousteau", 0x00a4, "flg10", 0x0342}, // Frog 
        {"Croque", 0x00aa, "flg17", 0x0349}, // Frog 
        {"Diva", 0x00ab, "flg18", 0x034A}, // Frog 
        {"Drift", 0x009f, "flg04", 0x033C}, // Frog 
        {"Frobert", 0x009d, "flg02", 0x033A}, // Frog 
        {"Gigi", 0x00a9, "flg16", 0x0348}, // Frog 
        {"Henry", 0x00ac, "flg19", 0x034B}, // Frog 
        {"Huck", 0x00a5, "flg11", 0x0343}, // Frog 
        {"Jambette", 0x00a7, "flg13", 0x0345}, // Frog 
        {"Jeremiah", 0x00a2, "flg07", 0x033F}, // Frog 
        {"Lily", 0x009b, "flg00", 0x0338}, // Frog 
        {"Prince", 0x00a6, "flg12", 0x0344}, // Frog 
        {"Puddles", 0x00a1, "flg06", 0x033E}, // Frog 
        {"Raddle", 0x00a8, "flg15", 0x0347}, // Frog 
        {"Ribbot", 0x009c, "flg01", 0x0339}, // Frog 
        {"Tad", 0x00a3, "flg09", 0x0341}, // Frog 
        {"Wart Jr.", 0x00a0, "flg05", 0x033D}, // Frog 
        {"Billy", 0x00af, "goa02", 0x0358}, // Goat 
        {"Chevre", 0x00ad, "goa00", 0x0356}, // Goat 
        {"Gruff", 0x00b0, "goa04", 0x0358}, // Goat 
        {"Kidd", 0x00b2, "goa07", 0x035D}, // Goat 
        {"Nan", 0x00ae, "goa01", 0x0357}, // Goat 
        {"Pashmina", 0x00b3, "goa08", 0x035E}, // Goat 
        {"Velma", 0x00b1, "goa06", 0x035C}, // Goat 
        {"Al", 0x00ba, "gor08", 0x0371}, // Gorilla 
        {"Boone", 0x00b6, "gor02", 0x036B}, // Gorilla 
        {"Boyd", 0x00b8, "gor05", 0x036E}, // Gorilla 
        {"Cesar", 0x00b4, "gor00", 0x0369}, // Gorilla 
        {"Hans", 0x00bc, "gor10", 0x0373}, // Gorilla 
        {"Louie", 0x00b7, "gor04", 0x036D}, // Gorilla 
        {"Peewee", 0x00b5, "gor01", 0x036A}, // Gorilla 
        {"Rilla", 0x00bd, "gor11", 0x0374}, // Gorilla 
        {"Rocket", 0x00bb, "gor09", 0x0372}, // Gorilla 
        {"Violet", 0x00b9, "gor07", 0x0370}, // Gorilla 
        {"Apple", 0x00bf, "ham01", 0x037F}, // Hamster 
        {"Clay", 0x00c3, "ham05", 0x0383}, // Hamster 
        {"Flurry", 0x00c4, "ham06", 0x0384}, // Hamster 
        {"Graham", 0x00c0, "ham02", 0x0380}, // Hamster 
        {"Hamlet", 0x00be, "ham00", 0x037E}, // Hamster 
        {"Hamphrey", 0x00c5, "ham07", 0x0385}, // Hamster 
        {"Holden (N/A)", 0x00c6, "ham08", 0x0386}, // Hamster /* Holden has no real Amiibo ID, wisp says it can't possess this ID  */
        {"Rodney", 0x00c1, "ham03", 0x0381}, // Hamster 
        {"Soleil", 0x00c2, "ham04", 0x0382}, // Hamster 
        {"Bertha", 0x00c9, "hip03", 0x0393}, // Hippo 
        {"Biff", 0x00ca, "hip04", 0x0394}, // Hippo 
        {"Bitty", 0x00cb, "hip05", 0x0395}, // Hippo 
        {"Bubbles", 0x00c8, "hip02", 0x0392}, // Hippo 
        {"Harry", 0x00cc, "hip08", 0x0398}, // Hippo 
        {"Hippeux", 0x00cd, "hip09", 0x0399}, // Hippo 
        {"Rocco", 0x00c7, "hip00", 0x0390}, // Hippo 
        {"Annalise", 0x00d7, "hrs09", 0x03AD}, // Horse 
        {"Buck", 0x00ce, "hrs00", 0x03A4}, // Horse 
        {"Cleo", 0x00d5, "hrs07", 0x03AB}, // Horse 
        {"Clyde", 0x00d8, "hrs10", 0x03AE}, // Horse 
        {"Colton", 0x00d9, "hrs11", 0x03AF}, // Horse 
        {"Ed", 0x00d4, "hrs06", 0x03AA}, // Horse 
        {"Elmer", 0x00d1, "hrs03", 0x03A7}, // Horse 
        {"Epona", 0x00dd, "hrs15", 0x0100}, // Horse
        {"Filly (N/A)", 0x00dc, "hrs14", 0x03B2}, // Horse /* Filly has no real Amiibo ID, wisp says it can't possess this ID  */
        {"Julian", 0x00db, "hrs13", 0x03B1}, // Horse 
        {"Papi", 0x00da, "hrs12", 0x03B0}, // Horse 
        {"Peaches", 0x00d6, "hrs08", 0x03AC}, // Horse 
        {"Roscoe", 0x00d2, "hrs04", 0x03A8}, // Horse
        {"Savannah", 0x00d0, "hrs02", 0x03A6}, // Horse 
        {"Victoria", 0x00cf, "hrs01", 0x03A5}, // Horse 
        {"Winnie", 0x00d3, "hrs05", 0x03A9}, // Horse 
        {"Alice", 0x00df, "kal01", 0x03BD}, // Koala 
        {"Canberra", 0x00e4, "kal08", 0x03C4}, // Koala 
        {"Eugene", 0x00e6, "kal10", 0x03C6}, // Koala 
        {"Gonzo", 0x00e2, "kal04", 0x03C0}, // Koala 
        {"Lyman", 0x00e5, "kal09", 0x03C5}, // Koala 
        {"Melba", 0x00e0, "kal02", 0x03BE}, // Koala 
        {"Ozzie", 0x00e3, "kal05", 0x03C1}, // Koala 
        {"Sydney", 0x00e1, "kal03", 0x03BF}, // Koala 
        {"Yuka", 0x00de, "kal00", 0x03BC}, // Koala 
        {"Astrid", 0x00ea, "kgr05", 0x03D6}, // Kangaroo 
        {"Carrie", 0x00e9, "kgr02", 0x03D3}, // Kangaroo 
        {"Kitt", 0x00e7, "kgr00", 0x03D1}, // Kangaroo 
        {"Marcie", 0x00ee, "kgr10", 0x03DB}, // Kangaroo 
        {"Mathilda", 0x00e8, "kgr01", 0x03D2}, // Kangaroo 
        {"Rooney", 0x00ed, "kgr09", 0x03DA}, // Kangaroo 
        {"Sylvia", 0x00eb, "kgr06", 0x03D7}, // Kangaroo 
        {"Walt", 0x00ec, "kgr08", 0x03D9}, // Kangaroo 
        {"Bud", 0x00ef, "lon00", 0x03D6}, // Lion 
        {"Elvis", 0x00f0, "lon01", 0x03E7}, // Lion 
        {"Leopold", 0x00f2, "lon04", 0x03EA}, // Lion 
        {"Lionel", 0x00f5, "lon08", 0x03EE}, // Lion 
        {"Mott", 0x00f3, "lon06", 0x03EC}, // Lion 
        {"Rex", 0x00f1, "lon02", 0x03E8}, // Lion 
        {"Rory", 0x00f4, "lon07", 0x03ED}, // Lion 
        {"Deli", 0x00fd, "mnk08", 0x0401}, // Monkey 
        {"Elise", 0x00fa, "mnk05", 0x03FE}, // Monkey 
        {"Flip", 0x00fb, "mnk06", 0x03FF}, // Monkey 
        {"Monty", 0x00f9, "mnk04", 0x03FD}, // Monkey 
        {"Nana", 0x00f6, "mnk01", 0x03FA}, // Monkey 
        {"Shari", 0x00fc, "mnk07", 0x0400}, // Monkey 
        {"Simon", 0x00f7, "mnk02", 0x03FB}, // Monkey 
        {"Tammi", 0x00f8, "mnk03", 0x03FC}, // Monkey 
        {"Anicotti", 0x0106, "mus10", 0x0416}, // Mouse 
        {"Bella", 0x0100, "mus02", 0x040E}, // Mouse 
        {"Bettina", 0x0109, "mus15", 0x041B}, // Mouse 
        {"Bree", 0x0101, "mus03", 0x040F}, // Mouse 
        {"Broccolo", 0x0107, "mus12", 0x0418}, // Mouse 
        {"Candi", 0x0104, "mus08", 0x0414}, // Mouse 
        {"Chadder", 0x010c, "mus18", 0x041E}, // Mouse 
        {"Dora", 0x00fe, "mus00", 0x040C}, // Mouse 
        {"Greta", 0x010a, "mus16", 0x041C}, // Mouse 
        {"Limberg", 0x00ff, "mus01", 0x040D}, // Mouse 
        {"Moose", 0x0108, "mus14", 0x041A}, // Mouse 
        {"Penelope", 0x010b, "mus17", 0x041D}, // Mouse 
        {"Rizzo", 0x0105, "mus09", 0x0415}, // Mouse 
        {"Rod", 0x0103, "mus05", 0x0411}, // Mouse 
        {"Samson", 0x0102, "mus04", 0x0410}, // Mouse 
        {"Inkwell", 0x0110, "oct03", 0x0800}, // Octopus
        {"Marina", 0x010e, "oct01", 0x042A}, // Octopus 
        {"Octavian", 0x010d, "oct00", 0x0429}, // Octopus 
        {"Zucker", 0x010f, "oct02", 0x042B}, // Octopus 
        {"Blanche", 0x0118, "ost08", 0x043E}, // Ostrich 
        {"Cranston", 0x0116, "ost06", 0x043C}, // Ostrich 
        {"Flora", 0x0119, "ost09", 0x043F}, // Ostrich 
        {"Gladys", 0x0112, "ost01", 0x0437}, // Ostrich 
        {"Julia", 0x0115, "ost05", 0x043B}, // Ostrich 
        {"Phil", 0x0117, "ost07", 0x043D}, // Ostrich 
        {"Phoebe", 0x011a, "ost10", 0x0440}, // Ostrich 
        {"Queenie", 0x0111, "ost00", 0x0436}, // Ostrich 
        {"Sandy", 0x0113, "ost02", 0x0438}, // Ostrich 
        {"Sprocket", 0x0114, "ost03", 0x0439}, // Ostrich 
        {"Aurora", 0x0124, "pgn00", 0x045F}, // Penguin 
        {"Boomer", 0x012c, "pgn10", 0x0469}, // Penguin 
        {"Cube", 0x0126, "pgn02", 0x0461}, // Penguin 
        {"Flo", 0x012f, "pgn13", 0x046C}, // Penguin 
        {"Friga", 0x0128, "pgn04", 0x0463}, // Penguin 
        {"Gwen", 0x0129, "pgn05", 0x0464}, // Penguin 
        {"Hopper", 0x0127, "pgn03", 0x0462}, // Penguin 
        {"Iggly", 0x012d, "pgn11", 0x046A}, // Penguin 
        {"Puck", 0x012a, "pgn06", 0x0465}, // Penguin 
        {"Roald", 0x0125, "pgn01", 0x0460}, // Penguin 
        {"Sprinkle", 0x0130, "pgn14", 0x046D}, // Penguin 
        {"Tex", 0x012e, "pgn12", 0x046B}, // Penguin 
        {"Wade", 0x012b, "pgn09", 0x0468}, // Penguin 
        {"Agnes", 0x013f, "pig17", 0x0489}, // Pig 
        {"Boris", 0x0138, "pig09", 0x0481}, // Pig 
        {"Chops", 0x013c, "pig14", 0x0486}, // Pig 
        {"Cobb", 0x0137, "pig08", 0x0480}, // Pig 
        {"Curly", 0x0131, "pig00", 0x0478}, // Pig 
        {"Crackle/Spork", 0x0136, "pig05", 0x047D}, // Pig 
        {"Gala", 0x013b, "pig13", 0x0485}, // Pig 
        {"Ganon", 0x0140, "pig18", 0x0102}, // Pig
        {"Hugh", 0x0134, "pig03", 0x047B}, // Pig 
        {"Kevin", 0x013d, "pig15", 0x0487}, // Pig 
        {"Lucy", 0x0135, "pig04", 0x047C}, // Pig 
        {"Maggie", 0x0139, "pig10", 0x0482}, // Pig 
        {"Pancetti", 0x013e, "pig16", 0x0488}, // Pig 
        {"Peggy", 0x013a, "pig11", 0x0483}, // Pig 
        {"Rasher", 0x0133, "pig02", 0x047A}, // Pig 
        {"Truffles", 0x0132, "pig01", 0x0479}, // Pig 
        {"Bonbon", 0x0152, "rbt17", 0x04A5}, // Rabbit 
        {"Bunnie", 0x0141, "rbt00", 0x0494}, // Rabbit 
        {"Carmen", 0x0151, "rbt16", 0x04A4}, // Rabbit 
        {"Chrissy", 0x014e, "rbt13", 0x04A1}, // Rabbit 
        {"Claude", 0x014c, "rbt11", 0x049F}, // Rabbit 
        {"Coco", 0x0143, "rbt02", 0x0496}, // Rabbit 
        {"Cole", 0x0153, "rbt18", 0x04A6}, // Rabbit 
        {"Doc", 0x014b, "rbt10", 0x049E}, // Rabbit 
        {"Dotty", 0x0142, "rbt01", 0x0495}, // Rabbit 
        {"Francine", 0x014d, "rbt12", 0x04A0}, // Rabbit 
        {"Gabi", 0x0146, "rbt05", 0x0499}, // Rabbit 
        {"Gaston", 0x0145, "rbt04", 0x0498}, // Rabbit 
        {"Genji", 0x0149, "rbt08", 0x049C}, // Rabbit 
        {"Hopkins", 0x014f, "rbt14", 0x04A2}, // Rabbit 
        {"Mira", 0x0154, "rbt19", 0x04A7}, // Rabbit 
        {"O'Hare", 0x0150, "rbt15", 0x04A3}, // Rabbit 
        {"Pippy", 0x0147, "rbt06", 0x049A}, // Rabbit 
        {"Ruby", 0x014a, "rbt09", 0x049D}, // Rabbit 
        {"Snake", 0x0144, "rbt03", 0x0497}, // Rabbit 
        {"Tiffany", 0x0148, "rbt07", 0x049B}, // Rabbit 
        {"Toby", 0x0155, "rbt20", 0x04A8}, // Rabbit 
        {"Hornsby", 0x0159, "rhn04", 0x04B6}, // Rhino 
        {"Merengue", 0x015a, "rhn07", 0x04B9}, // Rhino 
        {"Renée", 0x015b, "rhn08", 0x04BA}, // Rhino 
        {"Rhonda", 0x0157, "rhn01", 0x04B3}, // Rhino 
        {"Spike", 0x0158, "rhn02", 0x04B4}, // Rhino 
        {"Tank", 0x0156, "rhn00", 0x04B2}, // Rhino 
        {"Baabara", 0x015d, "shp01", 0x04C6}, // Sheep 
        {"Cashmere", 0x0160, "shp04", 0x04C9}, // Sheep 
        {"Curlos", 0x0162, "shp08", 0x04CD}, // Sheep 
        {"Étoile", 0x0168, "shp14", 0x04D3}, // Sheep 
        {"Eunice", 0x015e, "shp02", 0x04C7}, // Sheep 
        {"Frita", 0x0165, "shp11", 0x04D0}, // Sheep 
        {"Muffy", 0x0166, "shp12", 0x04D1}, // Sheep 
        {"Pietro", 0x0167, "shp13", 0x04D2}, // Sheep 
        {"Stella", 0x015f, "shp03", 0x04C8}, // Sheep 
        {"Timbra", 0x0164, "shp10", 0x04CF}, // Sheep 
        {"Vesta", 0x015c, "shp00", 0x04C5}, // Sheep 
        {"Wendy", 0x0163, "shp09", 0x04CE}, // Sheep 
        {"Willow", 0x0161, "shp07", 0x04CC}, // Sheep 
        {"Agent S", 0x016e, "squ05", 0x04E2}, // Squirrel 
        {"Blaire", 0x016a, "squ01", 0x04DE}, // Squirrel 
        {"Cally", 0x0174, "squ11", 0x04E8}, // Squirrel 
        {"Caroline", 0x016f, "squ06", 0x04E3}, // Squirrel 
        {"Cece", 0x017b, "squ19", 0x0801}, // Squirrel
        {"Filbert", 0x016b, "squ02", 0x04DF}, // Squirrel 
        {"Hazel", 0x017a, "squ18", 0x04EF}, // Squirrel 
        {"Marshal", 0x0179, "squ17", 0x04EE}, // Squirrel 
        {"Mint", 0x0172, "squ09", 0x04E6}, // Squirrel 
        {"Nibbles", 0x016d, "squ04", 0x04E1}, // Squirrel 
        {"Peanut", 0x0169, "squ00", 0x04DD}, // Squirrel 
        {"Pecan", 0x016c, "squ03", 0x04E0}, // Squirrel 
        {"Poppy", 0x0177, "squ15", 0x04EC}, // Squirrel 
        {"Ricky", 0x0173, "squ10", 0x04E7}, // Squirrel 
        {"Sally", 0x0170, "squ07", 0x04E4}, // Squirrel 
        {"Sheldon", 0x0178, "squ16", 0x04ED}, // Squirrel 
        {"Static", 0x0171, "squ08", 0x04E5}, // Squirrel 
        {"Sylvana", 0x0176, "squ14", 0x04EB}, // Squirrel 
        {"Tasha", 0x0175, "squ13", 0x04EA}, // Squirrel 
        {"Viché", 0x017c, "squ20", 0x0802}, // Squirrel
        {"Bangle", 0x0180, "tig03", 0x04FD}, // Tiger 
        {"Bianca", 0x0183, "tig06", 0x0500}, // Tiger 
        {"Claudia", 0x0182, "tig05", 0x04FF}, // Tiger 
        {"Leonardo", 0x0181, "tig04", 0x04FE}, // Tiger 
        {"Rolf", 0x017d, "tig00", 0x04FA}, // Tiger 
        {"Rowan", 0x017e, "tig01", 0x04FB}, // Tiger 
        {"Tybalt", 0x017f, "tig02", 0x04FC}, // Tiger 
        {"Chief", 0x0184, "wol00", 0x050B}, // Wolf 
        {"Dobie", 0x0188, "wol04", 0x050F}, // Wolf 
        {"Fang", 0x018a, "wol06", 0x0511}, // Wolf 
        {"Freya", 0x0189, "wol05", 0x0510}, // Wolf 
        {"Kyle", 0x018d, "wol10", 0x0515}, // Wolf 
        {"Lobo", 0x0185, "wol01", 0x050C}, // Wolf 
        {"Skye", 0x018c, "wol09", 0x0514}, // Wolf 
        {"Vivian", 0x018b, "wol08", 0x0513}, // Wolf 
        {"Whitney", 0x0187, "wol03", 0x050E}, // Wolf 
        {"Wolfgang", 0x0186, "wol02", 0x050D}, // Wolf 
        {"W. Link", 0x018e, "wol11", 0x0103}, // Wolf
        {"Villager", 0x018e, "wol11", 0x0180}, // Special
        {"Isabelle", 0x018e, "wol11", 0x0181}, // Special
        {"K. K. Slider", 0x018e, "wol11", 0x0182}, // Special
        {"Tom Nook", 0x018e, "wol11", 0x0183}, // Special
        {"Timmy&Tommy", 0x018e, "wol11", 0x0184}, // Special
        {"Timmy", 0x018e, "wol11", 0x0185}, // Special
        {"Tommy", 0x018e, "wol11", 0x0186}, // Special
        {"Sable", 0x018e, "wol11", 0x0187}, // Special
        {"Mable", 0x018e, "wol11", 0x0188}, // Special
        {"Labelle", 0x018e, "wol11", 0x0189}, // Special
        {"Reese", 0x018e, "wol11", 0x018A}, // Special
        {"Cyrus", 0x018e, "wol11", 0x018B}, // Special
        {"Digby", 0x018e, "wol11", 0x018C}, // Special
        {"Rover", 0x018e, "wol11", 0x018D}, // Special
        {"Resetti", 0x018e, "wol11", 0x018E}, // Special
        {"Don Resetti", 0x018e, "wol11", 0x018F}, // Special
        {"Brewster", 0x018e, "wol11", 0x0190}, // Special
        {"Harriet", 0x018e, "wol11", 0x0191}, // Special
        {"Blathers", 0x018e, "wol11", 0x0192}, // Special
        {"Celeste", 0x018e, "wol11", 0x0193}, // Special
        {"Kicks", 0x018e, "wol11", 0x0194}, // Special
        {"Porter", 0x018e, "wol11", 0x0195}, // Special
        {"Kapp'n", 0x018e, "wol11", 0x0196}, // Special
        {"Leilani", 0x018e, "wol11", 0x0197}, // Special
        {"Lelia", 0x018e, "wol11", 0x0198}, // Special
        {"Grams", 0x018e, "wol11", 0x0199}, // Special
        {"Nat", 0x018e, "wol11", 0x019A}, // Special
        {"Chip", 0x018e, "wol11", 0x019B}, // Special
        {"Phineas", 0x018e, "wol11", 0x019C}, // Special
        {"Copper", 0x018e, "wol11", 0x019D}, // Special
        {"Booker", 0x018e, "wol11", 0x019E}, // Special
        {"Pete", 0x018e, "wol11", 0x019F}, // Special
        {"Pelly", 0x018e, "wol11", 0x01A0}, // Special
        {"Phyllis", 0x018e, "wol11", 0x01A1}, // Special
        {"Gulliver", 0x018e, "wol11", 0x01A2}, // Special
        {"Joan", 0x018e, "wol11", 0x01A3}, // Special
        {"Pascal", 0x018e, "wol11", 0x01A4}, // Special
        {"Katrina", 0x018e, "wol11", 0x01A5}, // Special
        {"Sahara", 0x018e, "wol11", 0x01A6}, // Special
        {"Wendell", 0x018e, "wol11", 0x01A7}, // Special
        {"Redd", 0x018e, "wol11", 0x01A8}, // Special
        {"Gracie", 0x018e, "wol11", 0x01A9}, // Special
        {"Lyle", 0x018e, "wol11", 0x01AA}, // Special
        {"Pave", 0x018e, "wol11", 0x01AB}, // Special
        {"Zipper", 0x018e, "wol11", 0x01AC}, // Special
        {"Jack", 0x018e, "wol11", 0x01AD}, // Special
        {"Franklin", 0x018e, "wol11", 0x01AE}, // Special
        {"Jingle", 0x018e, "wol11", 0x01AF}, // Special
        {"Tortimer", 0x018e, "wol11", 0x01B0}, // Special
        {"Dr. Shrunk", 0x018e, "wol11", 0x01B1}, // Special
        {"Blanca", 0x018e, "wol11", 0x01B3}, // Special
        {"Leif", 0x018e, "wol11", 0x01B4}, // Special
        {"Luna", 0x018e, "wol11", 0x01B5}, // Special
        {"Katie", 0x018e, "wol11", 0x01B6}, // Special
        {"Lottie", 0x018e, "wol11", 0x01C1} // Special
    }; 

    /* Functions */
    u32     GetWispOffset(void);
    void    WispSpoofer(u16 Amiibo_ID);
    void    DIESpoofer(const char* Model);
    void    VillagersKeyboard(u8 mode);
    void    AmiiboSpoof(MenuEntry *entry);

}

#endif