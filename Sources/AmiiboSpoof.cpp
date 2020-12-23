#include <CTRPluginFramework.hpp>
#include "cheats.hpp"
#include "RAddress.hpp"

/*
    Amiibo Spoofer 3.0 by Slattz
    For non-exclusive use by anyone who wants it.
*/

enum class SpecieID : u8 {
    Alligator = 0,
    Anteater,
    Bear,
    Bird,
    Bull,
    Cat,
    Chicken,
    Cow,
    Cub,
    Deer,
    Dog,
    Duck,
    Eagle,
    Elephant,
    Frog,
    Goat,
    Gorilla,
    Hamster,
    Hippo,
    Horse,
    Koala,
    Kangaroo,
    Lion,
    Monkey,
    Mouse,
    Octopus,
    Ostrich,
    Penguin,
    Pig,
    Rabbit,
    Rhino,
    Sheep,
    Squirrel,
    Tiger,
    Wolf,
    Special
};

struct AmiiboInfo {
    const char* Name; //Name of NPC for populating keyboard
    u32 ID0; //Amiibo ID0 for spoofing
    u32 ID1; //Amiibo ID1 for spoofing
    SpecieID Species; //ID of NPC's species to differentiate NPCs
};

namespace CTRPluginFramework {
    extern const char* const amiiboSpecies[36];
    extern const AmiiboInfo amiiboVillagers[452];

    s32 AmiiboChooser(void* arg) {
        u32 offset = *(u32*)arg;
        Process::Pause(); //Pause game while user selects, so the timeout doesn't occur

        Keyboard keyboard("Select a species."); //TODO: TRANSLATE
        std::vector<std::string> keyVec;

        for (const char* specie : amiiboSpecies)
            keyVec.push_back(std::string(specie));

        keyboard.Populate(keyVec);
        int res = keyboard.Open(); //Pick a species
        Sleep(Milliseconds(100));

        Process::Write32(offset+0x10C, 0); //Game always sets this in the original function, so I'll do it too 
        if (res >= 0) { //User picked a species
            keyboard.GetMessage() = std::string("Select a villager to spoof."); //TODO: TRANSLATE
            keyVec.clear();

            std::vector<AmiiboInfo> amiiboVec;
            for (const AmiiboInfo& amiibo : amiiboVillagers) {
                if (amiibo.Species == (SpecieID)res) {
                    amiiboVec.push_back(amiibo);
                    keyVec.push_back(std::string(amiibo.Name));
                }
            }

            keyboard.Populate(keyVec);
            res = keyboard.Open(); //Pick villager based on species
            Sleep(Milliseconds(100));

            if (res >= 0) { //User picked a specific villager
                Process::Write32(offset+0xA8, 0x2); //"Successfully read tag" nfc flag
                Process::Write32(offset+0xAC, 0x0); //success 3ds nfc result code

                const AmiiboInfo& amiibo = amiiboVec[res];

                //Setup NFC Info into Amiibo buffer
                Process::Write32(offset+0x38C, (amiibo.ID0 >> 8)); //amiibo ID (3 bytes, converted to 4)
                Process::Write8(offset+0x390, (amiibo.ID0 & 0xFF)); //Tag type (1 byte)
                Process::Write8(offset+0x391, ((amiibo.ID1 >> 8) & 0xFF)); //series ID (1 byte)
                Process::Write16(offset+0x393, (amiibo.ID1 >> 16)); //Amiibo number (2 bytes)
            }

            amiiboVec.clear();
        }

        keyVec.clear();
        if (res < 0) { //User Aborted one of the keyboards
            Process::Write32(offset+0xA8, 0x3); //"There was an error" nfc flag
            Process::Write32(offset+0xAC, 0xC8A18600); //"There was an error" 3ds nfc result code
        }

        Process::Play(); //Resume game after user selects/cancels
        return 0;
    }

    void AmiiboHook(u32 offset) {
        Task task(AmiiboChooser, &offset); // Task needed here, otherwise Process::Pause breaks
        task.Start();
        task.Wait();
    }

    void AmiiboSpoofer(MenuEntry *entry) {
        static const u32 offsetPatch = AutoRegion(0x51C104, 0x51B14C, 0x51AA68, 0x51BA58, 0x51B14C, 0x51AA68)();
        static const u32 offsetHook = AutoRegion(0x51BBDC, 0x51AC24, 0x51A540, 0x51B530, 0x51AC24, 0x51A540)();
        static const u32 offsetPatch_o3ds1 = AutoRegion(0x3DAA7C, 0x3D9AC4, 0x3D975C, 0x3DA48C, 0x3D9AC4, 0x3D975C)();
        static const u32 offsetPatch_o3ds2 = AutoRegion(0x3DA824, 0x3D986C, 0x3D9504, 0x3DA234, 0x3D986C, 0x3D9504)();
        static u32 originalCode[3] = {0};
        static Hook nfcHook;

		if (entry->WasJustActivated()) {
			Process::Patch(offsetPatch, 0xE3A00003, (void*)&originalCode); //Force tell nfc code that there's an amiibo ready (NFC_TagState_InRange)

            if (!System::IsNew3DS()) {
                Process::Patch(offsetPatch_o3ds1, 0xE3A00002, (void*)&originalCode[1]); //Tells the o3ds the nfc reader is init'd
                Process::Patch(offsetPatch_o3ds2, 0xE3A00000, (void*)&originalCode[2]); //Forces the game to think nfc sysmodule has started scanning
            }

            nfcHook.Initialize(offsetHook, (u32)AmiiboHook);
            nfcHook.SetFlags(USE_LR_TO_RETURN);
            nfcHook.SetReturnAddress(offsetHook + 0x90); //skip over most the function as the scanning is ''done''
            nfcHook.Enable();
		}
		
		else if (!entry->IsActivated()) {
			Process::Patch(offsetPatch, originalCode[0]);

            if (!System::IsNew3DS()) {
                Process::Patch(offsetPatch_o3ds1, originalCode[1]);
                Process::Patch(offsetPatch_o3ds2, originalCode[2]);
            }
            nfcHook.Disable();
		}
    }

    const char* const amiiboSpecies[36] = {
        "Alligator", "Anteater", "Bear", "Bird", "Bull", "Cat", "Chicken", "Cow", "Cub", //0x0, 0x1, 0x2, etc
        "Deer", "Dog", "Duck", "Eagle", "Elephant", "Frog", "Goat", "Gorilla", "Hamster", //0x9, 0xA, 0xB, etc
        "Hippo", "Horse", "Koala", "Kangaroo", "Lion", "Monkey", "Mouse", "Octopus", "Ostrich", //0x12, 0x13, 0x14, etc
        "Penguin", "Pig", "Rabbit", "Rhino", "Sheep", "Squirrel", "Tiger", "Wolf", "Special Characters" //0x1B, 0x1C, 0x1D, etc
    };

    //Based on: https://docs.google.com/spreadsheets/d/19E7pMhKN6x583uB6bWVBeaTMyBPtEAC-Bk59Y6cfgxA/edit#gid=95881524
    const AmiiboInfo amiiboVillagers[452] = {
        {"Alfonso", 0x02C30001, 0x00DC0502, SpecieID::Alligator}, //VID: 0x005d, Filename: crd00
        {"Alli", 0x02C40001, 0x00670502, SpecieID::Alligator}, //VID: 0x005e, Filename: crd01
        {"Boots", 0x02C50001, 0x03080502, SpecieID::Alligator}, //VID: 0x005f, Filename: crd02
        {"Del", 0x02C70001, 0x01220502, SpecieID::Alligator}, //VID: 0x0060, Filename: crd04
        {"Drago", 0x02CB0001, 0x01360502, SpecieID::Alligator}, //VID: 0x0063, Filename: crd08
        {"Gayle", 0x02CA0001, 0x01CA0502, SpecieID::Alligator}, //VID: 0x0062, Filename: crd07
        {"Sly", 0x02C90001, 0x00CD0502, SpecieID::Alligator}, //VID: 0x0061, Filename: crd06
        {"Anabelle", 0x02030001, 0x019A0502, SpecieID::Anteater}, //VID: 0x0003, Filename: ant03
        {"Annalisa", 0x02080001, 0x00960502, SpecieID::Anteater}, //VID: 0x0005, Filename: ant08
        {"Antonio", 0x02010001, 0x016A0502, SpecieID::Anteater}, //VID: 0x0001, Filename: ant01
        {"Cyrano", 0x02000001, 0x00A10502, SpecieID::Anteater}, //VID: 0x0000, Filename: ant00
        {"Olaf", 0x02090001, 0x019F0502, SpecieID::Anteater}, //VID: 0x0006, Filename: ant09
        {"Pango", 0x02020001, 0x01030502, SpecieID::Anteater}, //VID: 0x0002, Filename: ant02
        {"Snooty", 0x02060001, 0x03120502, SpecieID::Anteater}, //VID: 0x0004, Filename: ant06
        {"Beardo", 0x02210001, 0x013C0502, SpecieID::Bear}, //VID: 0x0013, Filename: bea13
        {"Charlise", 0x02200001, 0x00FD0502, SpecieID::Bear}, //VID: 0x0012, Filename: bea12
        {"Chow", 0x02170001, 0x01B30502, SpecieID::Bear}, //VID: 0x000a, Filename: bea03
        {"Curt", 0x02160001, 0x00570502, SpecieID::Bear}, //VID: 0x0009, Filename: bea02
        {"Grizzly", 0x021D0001, 0x01CD0502, SpecieID::Bear}, //VID: 0x000f, Filename: bea09
        {"Groucho", 0x021A0001, 0x00DA0502, SpecieID::Bear}, //VID: 0x000c, Filename: bea06
        {"Ike", 0x021F0001, 0x03170502, SpecieID::Bear}, //VID: 0x0011, Filename: bea11
        {"Klaus", 0x02220001, 0x01440502, SpecieID::Bear}, //VID: 0x0014, Filename: bea14
        {"Nate", 0x02190001, 0x007E0502, SpecieID::Bear}, //VID: 0x000b, Filename: bea05
        {"Paula", 0x021E0001, 0x01230502, SpecieID::Bear}, //VID: 0x0010, Filename: bea10
        {"Pinky", 0x02150001, 0x01820502, SpecieID::Bear}, //VID: 0x0008, Filename: bea01
        {"Teddy", 0x02140001, 0x00E40502, SpecieID::Bear}, //VID: 0x0007, Filename: bea00
        {"Tutu", 0x021B0001, 0x00800502, SpecieID::Bear}, //VID: 0x000d, Filename: bea07
        {"Ursala", 0x021C0001, 0x02F70502, SpecieID::Bear}, //VID: 0x000e, Filename: bea08
        {"Admiral", 0x02330001, 0x03060502, SpecieID::Bird}, //VID: 0x001b, Filename: brd06
        {"Anchovy", 0x022F0001, 0x011E0502, SpecieID::Bird}, //VID: 0x0017, Filename: brd02
        {"Jacques", 0x023D0001, 0x01B50502, SpecieID::Bird}, //VID: 0x001f, Filename: brd16
        {"Jakey/Jacob", 0x02380001, 0x02F80502, SpecieID::Bird}, //VID: 0x001d, Filename: brd11
        {"Jay", 0x022D0001, 0x00F20502, SpecieID::Bird}, //VID: 0x0015, Filename: brd00
        {"Jitters", 0x02310001, 0x006A0502, SpecieID::Bird}, //VID: 0x0019, Filename: brd04
        {"Lucha", 0x023C0001, 0x00BD0502, SpecieID::Bird}, //VID: 0x001e, Filename: brd15
        {"Medli", 0x01000100, 0x03500902, SpecieID::Bird}, //VID: 0x0022, Filename: brd19
        {"Midge", 0x02350001, 0x00840502, SpecieID::Bird}, //VID: 0x001c, Filename: brd08
        {"Peck", 0x023E0001, 0x00D10502, SpecieID::Bird}, //VID: 0x0020, Filename: brd17
        {"Piper", 0x02320001, 0x02EA0502, SpecieID::Bird}, //VID: 0x001a, Filename: brd05
        {"Robin", 0x022E0001, 0x01D30502, SpecieID::Bird}, //VID: 0x0016, Filename: brd01
        {"Sparro", 0x023F0001, 0x01660502, SpecieID::Bird}, //VID: 0x0021, Filename: brd18
        {"Twiggy", 0x02300001, 0x01D20502, SpecieID::Bird}, //VID: 0x0018, Filename: brd03
        {"Angus", 0x024A0001, 0x01D10502, SpecieID::Bull}, //VID: 0x0023, Filename: bul00
        {"Coach", 0x02510001, 0x00C10502, SpecieID::Bull}, //VID: 0x0027, Filename: bul07
        {"Rodeo", 0x024B0001, 0x01260502, SpecieID::Bull}, //VID: 0x0024, Filename: bul01
        {"Stu", 0x024D0001, 0x02F60502, SpecieID::Bull}, //VID: 0x0025, Filename: bul03
        {"T-Bone", 0x024F0001, 0x00810502, SpecieID::Bull}, //VID: 0x0026, Filename: bul05
        {"Vic", 0x02520001, 0x00FE0502, SpecieID::Bull}, //VID: 0x0028, Filename: bul08
        {"Ankha", 0x02700001, 0x00FF0502, SpecieID::Cat}, //VID: 0x003c, Filename: cat19
        {"Bob", 0x025D0001, 0x00550502, SpecieID::Cat}, //VID: 0x0029, Filename: cat00
        {"Felicity", 0x026E0001, 0x00BA0502, SpecieID::Cat}, //VID: 0x003a, Filename: cat17
        {"Felyne", 0x35010000, 0x02E30F02, SpecieID::Cat}, //VID: 0x003f, Filename: cat22
        {"Kabuki", 0x02660001, 0x00680502, SpecieID::Cat}, //VID: 0x0032, Filename: cat09
        {"Katt", 0x02720001, 0x01860502, SpecieID::Cat}, //VID: 0x003e, Filename: cat21
        {"Kid Cat", 0x02670001, 0x01080502, SpecieID::Cat}, //VID: 0x0033, Filename: cat10
        {"Kiki", 0x02610001, 0x00650502, SpecieID::Cat}, //VID: 0x002d, Filename: cat04
        {"Kitty", 0x026B0001, 0x00E90502, SpecieID::Cat}, //VID: 0x0037, Filename: cat14
        {"Lolly", 0x026F0001, 0x01900502, SpecieID::Cat}, //VID: 0x003b, Filename: cat18
        {"Merry", 0x026D0001, 0x013F0502, SpecieID::Cat}, //VID: 0x0039, Filename: cat16
        {"Mitzi", 0x025E0001, 0x01250502, SpecieID::Cat}, //VID: 0x002a, Filename: cat01
        {"Moe", 0x02650001, 0x01540502, SpecieID::Cat}, //VID: 0x0031, Filename: cat08
        {"Monique", 0x02680001, 0x007D0502, SpecieID::Cat}, //VID: 0x0034, Filename: cat11
        {"Olivia", 0x02600001, 0x00D20502, SpecieID::Cat}, //VID: 0x002c, Filename: cat03
        {"Punchy", 0x02630001, 0x00750502, SpecieID::Cat}, //VID: 0x002f, Filename: cat06
        {"Purrl", 0x02640001, 0x01AC0502, SpecieID::Cat}, //VID: 0x0030, Filename: cat07
        {"Rosie", 0x025F0001, 0x01D70502, SpecieID::Cat}, //VID: 0x002b, Filename: cat02
        {"Rudy", 0x02710001, 0x019B0502, SpecieID::Cat}, //VID: 0x003d, Filename: cat20
        {"Stinky", 0x026A0001, 0x01460502, SpecieID::Cat}, //VID: 0x0036, Filename: cat13
        {"Tabby", 0x02690001, 0x011F0502, SpecieID::Cat}, //VID: 0x0035, Filename: cat12
        {"Tangy", 0x02620001, 0x01370502, SpecieID::Cat}, //VID: 0x002e, Filename: cat05
        {"Tom", 0x026C0001, 0x00C30502, SpecieID::Cat}, //VID: 0x0038, Filename: cat15
        {"Ava", 0x029E0001, 0x013D0502, SpecieID::Chicken}, //VID: 0x0053, Filename: chn05
        {"Becky", 0x02A20001, 0x01BA0502, SpecieID::Chicken}, //VID: 0x0054, Filename: chn09
        {"Benedict", 0x029A0001, 0x00EE0502, SpecieID::Chicken}, //VID: 0x0051, Filename: chn01
        {"Broffina", 0x02A50001, 0x018C0502, SpecieID::Chicken}, //VID: 0x0057, Filename: chn12
        {"Egbert", 0x029B0001, 0x00CB0502, SpecieID::Chicken}, //VID: 0x0052, Filename: chn02
        {"Goose", 0x02990001, 0x00950502, SpecieID::Chicken}, //VID: 0x0050, Filename: chn00
        {"Ken", 0x02A60001, 0x01240502, SpecieID::Chicken}, //VID: 0x0058, Filename: chn13
        {"Knox", 0x02A40001, 0x00720502, SpecieID::Chicken}, //VID: 0x0056, Filename: chn11
        {"Plucky", 0x02A30001, 0x02FF0502, SpecieID::Chicken}, //VID: 0x0055, Filename: chn10
        {"Naomi", 0x02B80001, 0x019C0502, SpecieID::Cow}, //VID: 0x005c, Filename: cow07
        {"Norma", 0x02B70001, 0x030F0502, SpecieID::Cow}, //VID: 0x005b, Filename: cow06
        {"Patty", 0x02B10001, 0x00690502, SpecieID::Cow}, //VID: 0x0059, Filename: cow00
        {"Tipper", 0x02B20001, 0x00C40502, SpecieID::Cow}, //VID: 0x005a, Filename: cow01
        {"Barold", 0x028D0001, 0x01BD0502, SpecieID::Cub}, //VID: 0x004d, Filename: cbr16
        {"Bluebear", 0x027D0001, 0x00630502, SpecieID::Cub}, //VID: 0x0040, Filename: cbr00
        {"Cheri", 0x02870001, 0x005A0502, SpecieID::Cub}, //VID: 0x0049, Filename: cbr10
        {"Chester", 0x028C0001, 0x013E0502, SpecieID::Cub}, //VID: 0x004c, Filename: cbr15
        {"June", 0x028A0001, 0x02E90502, SpecieID::Cub}, //VID: 0x004a, Filename: cbr13
        {"Kody", 0x02810001, 0x01200502, SpecieID::Cub}, //VID: 0x0044, Filename: cbr04
        {"Maple", 0x027E0001, 0x01690502, SpecieID::Cub}, //VID: 0x0041, Filename: cbr01
        {"Marty", 0x028F0101, 0x031A0502, SpecieID::Cub}, //VID: 0x004f, Filename: cbr18
        {"Murphy", 0x02840001, 0x02FE0502, SpecieID::Cub}, //VID: 0x0047, Filename: cbr07
        {"Olive", 0x02860001, 0x03130502, SpecieID::Cub}, //VID: 0x0048, Filename: cbr09
        {"Pekoe", 0x028B0001, 0x00E30502, SpecieID::Cub}, //VID: 0x004b, Filename: cbr14
        {"Poncho", 0x027F0001, 0x00B90502, SpecieID::Cub}, //VID: 0x0042, Filename: cbr02
        {"Pudge", 0x02800001, 0x00830502, SpecieID::Cub}, //VID: 0x0043, Filename: cbr03
        {"Stitches", 0x02820001, 0x01D60502, SpecieID::Cub}, //VID: 0x0045, Filename: cbr05
        {"Tammy", 0x028E0001, 0x019E0502, SpecieID::Cub}, //VID: 0x004e, Filename: cbr17
        {"Vladimir", 0x02830001, 0x00C70502, SpecieID::Cub}, //VID: 0x0046, Filename: cbr06
        {"Bam", 0x02D70001, 0x01300502, SpecieID::Deer}, //VID: 0x0065, Filename: der01
        {"Beau", 0x02DD0001, 0x00EA0502, SpecieID::Deer}, //VID: 0x006b, Filename: der07
        {"Bruce", 0x02D90001, 0x01C80502, SpecieID::Deer}, //VID: 0x0067, Filename: der03
        {"Chelsea", 0x02E00101, 0x031D0502, SpecieID::Deer}, //VID: 0x006e, Filename: der10
        {"Deirdre", 0x02DA0001, 0x01330502, SpecieID::Deer}, //VID: 0x0068, Filename: der04
        {"Diana", 0x02DE0001, 0x009C0502, SpecieID::Deer}, //VID: 0x006c, Filename: der08
        {"Erik", 0x02DF0001, 0x01910502, SpecieID::Deer}, //VID: 0x006d, Filename: der09
        {"Fauna", 0x02D60001, 0x00560502, SpecieID::Deer}, //VID: 0x0064, Filename: der00
        {"Fuchsia", 0x02DC0001, 0x00BE0502, SpecieID::Deer}, //VID: 0x006a, Filename: der06
        {"Lopez", 0x02DB0001, 0x005E0502, SpecieID::Deer}, //VID: 0x0069, Filename: der05
        {"Zell", 0x02D80001, 0x00E20502, SpecieID::Deer}, //VID: 0x0066, Filename: der02
        {"Bea", 0x02F40001, 0x03050502, SpecieID::Dog}, //VID: 0x0079, Filename: dog10
        {"Benjamin", 0x02FA0001, 0x00970502, SpecieID::Dog}, //VID: 0x007c, Filename: dog16
        {"Biskit", 0x02ED0001, 0x015A0502, SpecieID::Dog}, //VID: 0x0072, Filename: dog03
        {"Bones", 0x02EE0001, 0x01990502, SpecieID::Dog}, //VID: 0x0073, Filename: dog04
        {"Butch", 0x02EB0001, 0x00DE0502, SpecieID::Dog}, //VID: 0x0070, Filename: dog01
        {"Cherry", 0x02FB0001, 0x00900502, SpecieID::Dog}, //VID: 0x007d, Filename: dog17
        {"Cookie", 0x02F20001, 0x00CC0502, SpecieID::Dog}, //VID: 0x0077, Filename: dog08
        {"Daisy", 0x02F10001, 0x01450502, SpecieID::Dog}, //VID: 0x0076, Filename: dog07
        {"Goldie", 0x02EA0001, 0x01D50502, SpecieID::Dog}, //VID: 0x006f, Filename: dog00
        {"Lucky", 0x02EC0001, 0x01C40502, SpecieID::Dog}, //VID: 0x0071, Filename: dog02
        {"Mac", 0x02F80001, 0x01380502, SpecieID::Dog}, //VID: 0x007a, Filename: dog14
        {"Maddie", 0x02F30001, 0x02F90502, SpecieID::Dog}, //VID: 0x0078, Filename: dog09
        {"Marcel", 0x02F90001, 0x01020502, SpecieID::Dog}, //VID: 0x007b, Filename: dog15
        {"Portia", 0x02EF0001, 0x00580502, SpecieID::Dog}, //VID: 0x0074, Filename: dog05
        {"Shep", 0x02FC0001, 0x018F0502, SpecieID::Dog}, //VID: 0x007e, Filename: dog18
        {"Walker", 0x02F00001, 0x00A70502, SpecieID::Dog}, //VID: 0x0075, Filename: dog06
        {"Bill", 0x03070001, 0x00640502, SpecieID::Duck}, //VID: 0x007f, Filename: duk00
        {"Deena", 0x030B0001, 0x00790502, SpecieID::Duck}, //VID: 0x0083, Filename: duk04
        {"Derwin", 0x030F0001, 0x016D0502, SpecieID::Duck}, //VID: 0x0087, Filename: duk08
        {"Drake", 0x03100001, 0x00F80502, SpecieID::Duck}, //VID: 0x0088, Filename: duk09
        {"Freckles", 0x030E0001, 0x012F0502, SpecieID::Duck}, //VID: 0x0086, Filename: duk07
        {"Gloria", 0x03160001, 0x01C00502, SpecieID::Duck}, //VID: 0x008d, Filename: duk15
        {"Joey", 0x03080001, 0x014D0502, SpecieID::Duck}, //VID: 0x0080, Filename: duk01
        {"Ketchup", 0x03140001, 0x02F40502, SpecieID::Duck}, //VID: 0x008c, Filename: duk13
        {"Maelle", 0x030A0001, 0x01C70502, SpecieID::Duck}, //VID: 0x0082, Filename: duk03
        {"Mallary", 0x030D0001, 0x01840502, SpecieID::Duck}, //VID: 0x0085, Filename: duk06
        {"Miranda", 0x03130001, 0x01210502, SpecieID::Duck}, //VID: 0x008b, Filename: duk12
        {"Molly", 0x03170001, 0x00A60502, SpecieID::Duck}, //VID: 0x008e, Filename: duk16
        {"Pate", 0x03090001, 0x00C60502, SpecieID::Duck}, //VID: 0x0081, Filename: duk02
        {"Pompom", 0x030C0001, 0x01B80502, SpecieID::Duck}, //VID: 0x0084, Filename: duk05
        {"Quillson", 0x03180001, 0x006C0502, SpecieID::Duck}, //VID: 0x008f, Filename: duk17
        {"Scoot", 0x03110001, 0x00D60502, SpecieID::Duck}, //VID: 0x0089, Filename: duk10
        {"Weber", 0x03120001, 0x03090502, SpecieID::Duck}, //VID: 0x008a, Filename: duk11
        {"Amelia", 0x044C0001, 0x008E0502, SpecieID::Eagle}, //VID: 0x011c, Filename: pbr01
        {"Apollo", 0x044B0001, 0x016C0502, SpecieID::Eagle}, //VID: 0x011b, Filename: pbr00
        {"Avery", 0x04500001, 0x00CF0502, SpecieID::Eagle}, //VID: 0x011f, Filename: pbr05
        {"Buzz", 0x044E0001, 0x03150502, SpecieID::Eagle}, //VID: 0x011e, Filename: pbr03
        {"Celia", 0x04540001, 0x01AE0502, SpecieID::Eagle}, //VID: 0x0123, Filename: pbr09
        {"Frank", 0x04510001, 0x015E0502, SpecieID::Eagle}, //VID: 0x0120, Filename: pbr06
        {"Keaton", 0x04530001, 0x01040502, SpecieID::Eagle}, //VID: 0x0122, Filename: pbr08
        {"Pierce", 0x044D0001, 0x01930502, SpecieID::Eagle}, //VID: 0x011d, Filename: pbr02
        {"Sterling", 0x04520001, 0x00730502, SpecieID::Eagle}, //VID: 0x0121, Filename: pbr07
        {"Axel", 0x03290001, 0x009D0502, SpecieID::Elephant}, //VID: 0x0096, Filename: elp06
        {"Big Top", 0x03250001, 0x010A0502, SpecieID::Elephant}, //VID: 0x0092, Filename: elp02
        {"Chai", 0x032E0101, 0x031C0502, SpecieID::Elephant}, //VID: 0x009a, Filename: elp11
        {"Dizzy", 0x03240001, 0x01890502, SpecieID::Elephant}, //VID: 0x0091, Filename: elp01
        {"Ellie", 0x032A0001, 0x03070502, SpecieID::Elephant}, //VID: 0x0097, Filename: elp07
        {"Eloise", 0x03260001, 0x01390502, SpecieID::Elephant}, //VID: 0x0093, Filename: elp03
        {"Margie", 0x03270001, 0x01C30502, SpecieID::Elephant}, //VID: 0x0094, Filename: elp04
        {"Opal", 0x03230001, 0x00760502, SpecieID::Elephant}, //VID: 0x0090, Filename: elp00
        {"Paolo", 0x03280001, 0x02EB0502, SpecieID::Elephant}, //VID: 0x0095, Filename: elp05
        {"Tia", 0x032D0001, 0x00BC0502, SpecieID::Elephant}, //VID: 0x0099, Filename: elp10
        {"Tucker", 0x032C0001, 0x01480502, SpecieID::Elephant}, //VID: 0x0098, Filename: elp09
        {"Camofrog", 0x033B0001, 0x00FA0502, SpecieID::Frog}, //VID: 0x009e, Filename: flg03
        {"Cousteau", 0x03420001, 0x01280502, SpecieID::Frog}, //VID: 0x00a4, Filename: flg10
        {"Croque", 0x03490001, 0x018D0502, SpecieID::Frog}, //VID: 0x00aa, Filename: flg17
        {"Diva", 0x034A0001, 0x01430502, SpecieID::Frog}, //VID: 0x00ab, Filename: flg18
        {"Drift", 0x033C0001, 0x01000502, SpecieID::Frog}, //VID: 0x009f, Filename: flg04
        {"Frobert", 0x033A0001, 0x01CC0502, SpecieID::Frog}, //VID: 0x009d, Filename: flg02
        {"Gigi", 0x03480001, 0x006B0502, SpecieID::Frog}, //VID: 0x00a9, Filename: flg16
        {"Henry", 0x034B0001, 0x009F0502, SpecieID::Frog}, //VID: 0x00ac, Filename: flg19
        {"Huck", 0x03430001, 0x02EF0502, SpecieID::Frog}, //VID: 0x00a5, Filename: flg11
        {"Jambette", 0x03450001, 0x005F0502, SpecieID::Frog}, //VID: 0x00a7, Filename: flg13
        {"Jeremiah", 0x033F0001, 0x008F0502, SpecieID::Frog}, //VID: 0x00a2, Filename: flg07
        {"Lily", 0x03380001, 0x011D0502, SpecieID::Frog}, //VID: 0x009b, Filename: flg00
        {"Prince", 0x03440001, 0x00C50502, SpecieID::Frog}, //VID: 0x00a6, Filename: flg12
        {"Puddles", 0x033E0001, 0x01A20502, SpecieID::Frog}, //VID: 0x00a1, Filename: flg06
        {"Raddle", 0x03470001, 0x03020502, SpecieID::Frog}, //VID: 0x00a8, Filename: flg15
        {"Ribbot", 0x03390001, 0x01B10502, SpecieID::Frog}, //VID: 0x009c, Filename: flg01
        {"Tad", 0x03410001, 0x030E0502, SpecieID::Frog}, //VID: 0x00a3, Filename: flg09
        {"Wart Jr.", 0x033D0001, 0x013A0502, SpecieID::Frog}, //VID: 0x00a0, Filename: flg05
        {"Billy", 0x03580001, 0x02FA0502, SpecieID::Goat}, //VID: 0x00af, Filename: goa02
        {"Chevre", 0x03560001, 0x01350502, SpecieID::Goat}, //VID: 0x00ad, Filename: goa00
        {"Gruff", 0x03580001, 0x02FA0502, SpecieID::Goat}, //VID: 0x00b0, Filename: goa04
        {"Kidd", 0x035D0001, 0x00C90502, SpecieID::Goat}, //VID: 0x00b2, Filename: goa07
        {"Nan", 0x03570001, 0x00EB0502, SpecieID::Goat}, //VID: 0x00ae, Filename: goa01
        {"Pashmina", 0x035E0001, 0x018E0502, SpecieID::Goat}, //VID: 0x00b3, Filename: goa08
        {"Velma", 0x035C0001, 0x01290502, SpecieID::Goat}, //VID: 0x00b1, Filename: goa06
        {"Al", 0x03710001, 0x005C0502, SpecieID::Gorilla}, //VID: 0x00ba, Filename: gor08
        {"Boone", 0x036B0001, 0x018B0502, SpecieID::Gorilla}, //VID: 0x00b6, Filename: gor02
        {"Boyd", 0x036E0001, 0x02FB0502, SpecieID::Gorilla}, //VID: 0x00b8, Filename: gor05
        {"Cesar", 0x03690001, 0x00D30502, SpecieID::Gorilla}, //VID: 0x00b4, Filename: gor00
        {"Hans", 0x03730001, 0x01340502, SpecieID::Gorilla}, //VID: 0x00bc, Filename: gor10
        {"Louie", 0x036D0001, 0x03040502, SpecieID::Gorilla}, //VID: 0x00b7, Filename: gor04
        {"Peewee", 0x036A0001, 0x019D0502, SpecieID::Gorilla}, //VID: 0x00b5, Filename: gor01
        {"Rilla", 0x03740101, 0x03190502, SpecieID::Gorilla}, //VID: 0x00bd, Filename: gor11
        {"Rocket", 0x03720001, 0x010B0502, SpecieID::Gorilla}, //VID: 0x00bb, Filename: gor09
        {"Violet", 0x03700001, 0x015D0502, SpecieID::Gorilla}, //VID: 0x00b9, Filename: gor07
        {"Apple", 0x037F0001, 0x01AA0502, SpecieID::Hamster}, //VID: 0x00bf, Filename: ham01
        {"Clay", 0x03830001, 0x009B0502, SpecieID::Hamster}, //VID: 0x00c3, Filename: ham05
        {"Flurry", 0x03840001, 0x00860502, SpecieID::Hamster}, //VID: 0x00c4, Filename: ham06
        {"Graham", 0x03800001, 0x01870502, SpecieID::Hamster}, //VID: 0x00c0, Filename: ham02
        {"Hamlet", 0x037E0001, 0x01560502, SpecieID::Hamster}, //VID: 0x00be, Filename: ham00
        {"Hamphrey", 0x03850001, 0x01060502, SpecieID::Hamster}, //VID: 0x00c5, Filename: ham07
        //{"Holden (N/A)", 0x00000000, 0x00000000, SpecieID::Hamster}, //VID: 0x00c6, Filename: ham08
        {"Rodney", 0x03810001, 0x00D50502, SpecieID::Hamster}, //VID: 0x00c1, Filename: ham03
        {"Soleil", 0x03820001, 0x016B0502, SpecieID::Hamster}, //VID: 0x00c2, Filename: ham04
        {"Bertha", 0x03930001, 0x00A00502, SpecieID::Hippo}, //VID: 0x00c9, Filename: hip03
        {"Biff", 0x03940001, 0x00890502, SpecieID::Hippo}, //VID: 0x00ca, Filename: hip04
        {"Bitty", 0x03950001, 0x02FC0502, SpecieID::Hippo}, //VID: 0x00cb, Filename: hip05
        {"Bubbles", 0x03920001, 0x01270502, SpecieID::Hippo}, //VID: 0x00c8, Filename: hip02
        {"Harry", 0x03980001, 0x00BF0502, SpecieID::Hippo}, //VID: 0x00cc, Filename: hip08
        {"Hippeux", 0x03990001, 0x01C20502, SpecieID::Hippo}, //VID: 0x00cd, Filename: hip09
        {"Rocco", 0x03900001, 0x01850502, SpecieID::Hippo}, //VID: 0x00c7, Filename: hip00
        {"Annalise", 0x03AD0001, 0x01B20502, SpecieID::Horse}, //VID: 0x00d7, Filename: hrs09
        {"Buck", 0x03A40001, 0x014F0502, SpecieID::Horse}, //VID: 0x00ce, Filename: hrs00
        {"Cleo", 0x03AB0001, 0x03160502, SpecieID::Horse}, //VID: 0x00d5, Filename: hrs07
        {"Clyde", 0x03AE0001, 0x00870502, SpecieID::Horse}, //VID: 0x00d8, Filename: hrs10
        {"Colton", 0x03AF0001, 0x012C0502, SpecieID::Horse}, //VID: 0x00d9, Filename: hrs11
        {"Ed", 0x03AA0001, 0x00E60502, SpecieID::Horse}, //VID: 0x00d4, Filename: hrs06
        {"Elmer", 0x03A70001, 0x01A10502, SpecieID::Horse}, //VID: 0x00d1, Filename: hrs03
        {"Epona", 0x01010100, 0x00170002, SpecieID::Horse}, //VID: 0x00dd, Filename: hrs15
        //{"Filly (N/A)", 0x00000000, 0x00000000, SpecieID::Horse}, //VID: 0x00dc, Filename: hrs14
        {"Julian", 0x03B10001, 0x00F00502, SpecieID::Horse}, //VID: 0x00db, Filename: hrs13
        {"Papi", 0x03B00001, 0x01A90502, SpecieID::Horse}, //VID: 0x00da, Filename: hrs12
        {"Peaches", 0x03AC0001, 0x01880502, SpecieID::Horse}, //VID: 0x00d6, Filename: hrs08
        {"Roscoe", 0x03A80001, 0x00910502, SpecieID::Horse}, //VID: 0x00d2, Filename: hrs04
        {"Savannah", 0x03A60001, 0x00C80502, SpecieID::Horse}, //VID: 0x00d0, Filename: hrs02
        {"Victoria", 0x03A50001, 0x015B0502, SpecieID::Horse}, //VID: 0x00cf, Filename: hrs01
        {"Winnie", 0x03A90001, 0x00710502, SpecieID::Horse}, //VID: 0x00d3, Filename: hrs05
        {"Alice", 0x03BD0001, 0x00F90502, SpecieID::Koala}, //VID: 0x00df, Filename: kal01
        {"Canberra", 0x03C40001, 0x012B0502, SpecieID::Koala}, //VID: 0x00e4, Filename: kal08
        {"Eugene", 0x03C60001, 0x00930502, SpecieID::Koala}, //VID: 0x00e6, Filename: kal10
        {"Gonzo", 0x03C00001, 0x03100502, SpecieID::Koala}, //VID: 0x00e2, Filename: kal04
        {"Lyman", 0x03C50001, 0x015C0502, SpecieID::Koala}, //VID: 0x00e5, Filename: kal09
        {"Melba", 0x03BE0001, 0x01980502, SpecieID::Koala}, //VID: 0x00e0, Filename: kal02
        {"Ozzie", 0x03C10001, 0x00BB0502, SpecieID::Koala}, //VID: 0x00e3, Filename: kal05
        {"Sydney", 0x03BF0001, 0x01BC0502, SpecieID::Koala}, //VID: 0x00e1, Filename: kal03
        {"Yuka", 0x03BC0001, 0x008A0502, SpecieID::Koala}, //VID: 0x00de, Filename: kal00
        {"Astrid", 0x03D60001, 0x01570502, SpecieID::Kangaroo}, //VID: 0x00ea, Filename: kgr05
        {"Carrie", 0x03D30001, 0x02F30502, SpecieID::Kangaroo}, //VID: 0x00e9, Filename: kgr02
        {"Kitt", 0x03D10001, 0x00C20502, SpecieID::Kangaroo}, //VID: 0x00e7, Filename: kgr00
        {"Marcie", 0x03DB0001, 0x006D0502, SpecieID::Kangaroo}, //VID: 0x00ee, Filename: kgr10
        {"Mathilda", 0x03D20001, 0x00E50502, SpecieID::Kangaroo}, //VID: 0x00e8, Filename: kgr01
        {"Rooney", 0x03DA0001, 0x01510502, SpecieID::Kangaroo}, //VID: 0x00ed, Filename: kgr09
        {"Sylvia", 0x03D70001, 0x01B40502, SpecieID::Kangaroo}, //VID: 0x00eb, Filename: kgr06
        {"Walt", 0x03D90001, 0x01A50502, SpecieID::Kangaroo}, //VID: 0x00ec, Filename: kgr08
        {"Bud", 0x03D60001, 0x01570502, SpecieID::Lion}, //VID: 0x00ef, Filename: lon00
        {"Elvis", 0x03E70001, 0x012A0502, SpecieID::Lion}, //VID: 0x00f0, Filename: lon01
        {"Leopold", 0x03EA0001, 0x030B0502, SpecieID::Lion}, //VID: 0x00f2, Filename: lon04
        {"Lionel", 0x03EE0001, 0x008B0502, SpecieID::Lion}, //VID: 0x00f5, Filename: lon08
        {"Mott", 0x03EC0001, 0x01830502, SpecieID::Lion}, //VID: 0x00f3, Filename: lon06
        {"Rex", 0x03E80001, 0x02F50502, SpecieID::Lion}, //VID: 0x00f1, Filename: lon02
        {"Rory", 0x03ED0001, 0x01A30502, SpecieID::Lion}, //VID: 0x00f4, Filename: lon07
        {"Deli", 0x04010001, 0x00660502, SpecieID::Monkey}, //VID: 0x00fd, Filename: mnk08
        {"Elise", 0x03FE0001, 0x01A40502, SpecieID::Monkey}, //VID: 0x00fa, Filename: mnk05
        {"Flip", 0x03FF0001, 0x00F40502, SpecieID::Monkey}, //VID: 0x00fb, Filename: mnk06
        {"Monty", 0x03FD0001, 0x01580502, SpecieID::Monkey}, //VID: 0x00f9, Filename: mnk04
        {"Nana", 0x03FA0001, 0x00D00502, SpecieID::Monkey}, //VID: 0x00f6, Filename: mnk01
        {"Shari", 0x04000001, 0x006F0502, SpecieID::Monkey}, //VID: 0x00fc, Filename: mnk07
        {"Simon", 0x03FB0001, 0x01CF0502, SpecieID::Monkey}, //VID: 0x00f7, Filename: mnk02
        {"Tammi", 0x03FC0001, 0x01470502, SpecieID::Monkey}, //VID: 0x00f8, Filename: mnk03
        {"Anicotti", 0x04160001, 0x00FB0502, SpecieID::Mouse}, //VID: 0x0106, Filename: mus10
        {"Bella", 0x040E0001, 0x00880502, SpecieID::Mouse}, //VID: 0x0100, Filename: mus02
        {"Bettina", 0x041B0001, 0x00F10502, SpecieID::Mouse}, //VID: 0x0109, Filename: mus15
        {"Bree", 0x040F0001, 0x01500502, SpecieID::Mouse}, //VID: 0x0101, Filename: mus03
        {"Broccolo", 0x04180001, 0x00D80502, SpecieID::Mouse}, //VID: 0x0107, Filename: mus12
        {"Candi", 0x04140001, 0x030A0502, SpecieID::Mouse}, //VID: 0x0104, Filename: mus08
        {"Chadder", 0x041E0001, 0x015F0502, SpecieID::Mouse}, //VID: 0x010c, Filename: mus18
        {"Dora", 0x040C0001, 0x01590502, SpecieID::Mouse}, //VID: 0x00fe, Filename: mus00
        {"Greta", 0x041C0001, 0x01410502, SpecieID::Mouse}, //VID: 0x010a, Filename: mus16
        {"Limberg", 0x040D0001, 0x00780502, SpecieID::Mouse}, //VID: 0x00ff, Filename: mus01
        {"Moose", 0x041A0001, 0x00E00502, SpecieID::Mouse}, //VID: 0x0108, Filename: mus14
        {"Penelope", 0x041D0001, 0x018A0502, SpecieID::Mouse}, //VID: 0x010b, Filename: mus17
        {"Rizzo", 0x04150001, 0x01BB0502, SpecieID::Mouse}, //VID: 0x0105, Filename: mus09
        {"Rod", 0x04110001, 0x01AB0502, SpecieID::Mouse}, //VID: 0x0103, Filename: mus05
        {"Samson", 0x04100001, 0x007F0502, SpecieID::Mouse}, //VID: 0x0102, Filename: mus04
        {"Inkwell", 0x08000300, 0x00400402, SpecieID::Octopus}, //VID: 0x0110, Filename: oct03
        {"Marina", 0x042A0001, 0x012D0502, SpecieID::Octopus}, //VID: 0x010e, Filename: oct01
        {"Octavian", 0x04290001, 0x00700502, SpecieID::Octopus}, //VID: 0x010d, Filename: oct00
        {"Zucker", 0x042B0001, 0x01AF0502, SpecieID::Octopus}, //VID: 0x010f, Filename: oct02
        {"Blanche", 0x043E0001, 0x01490502, SpecieID::Ostrich}, //VID: 0x0118, Filename: ost08
        {"Cranston", 0x043C0001, 0x01CB0502, SpecieID::Ostrich}, //VID: 0x0116, Filename: ost06
        {"Flora", 0x043F0001, 0x01550502, SpecieID::Ostrich}, //VID: 0x0119, Filename: ost09
        {"Gladys", 0x04370001, 0x01050502, SpecieID::Ostrich}, //VID: 0x0112, Filename: ost01
        {"Julia", 0x043B0001, 0x03030502, SpecieID::Ostrich}, //VID: 0x0115, Filename: ost05
        {"Phil", 0x043D0001, 0x007C0502, SpecieID::Ostrich}, //VID: 0x0117, Filename: ost07
        {"Phoebe", 0x04400001, 0x00CA0502, SpecieID::Ostrich}, //VID: 0x011a, Filename: ost10
        {"Queenie", 0x04360001, 0x01940502, SpecieID::Ostrich}, //VID: 0x0111, Filename: ost00
        {"Sandy", 0x04380001, 0x03000502, SpecieID::Ostrich}, //VID: 0x0113, Filename: ost02
        {"Sprocket", 0x04390001, 0x03110502, SpecieID::Ostrich}, //VID: 0x0114, Filename: ost03
        {"Aurora", 0x045F0001, 0x01A80502, SpecieID::Penguin}, //VID: 0x0124, Filename: pgn00
        {"Boomer", 0x04690001, 0x01640502, SpecieID::Penguin}, //VID: 0x012c, Filename: pgn10
        {"Cube", 0x04610001, 0x01610502, SpecieID::Penguin}, //VID: 0x0126, Filename: pgn02
        {"Flo", 0x046C0001, 0x008C0502, SpecieID::Penguin}, //VID: 0x012f, Filename: pgn13
        {"Friga", 0x04630001, 0x01310502, SpecieID::Penguin}, //VID: 0x0128, Filename: pgn04
        {"Gwen", 0x04640001, 0x00C00502, SpecieID::Penguin}, //VID: 0x0129, Filename: pgn05
        {"Hopper", 0x04620001, 0x00F60502, SpecieID::Penguin}, //VID: 0x0127, Filename: pgn03
        {"Iggly", 0x046A0001, 0x01D00502, SpecieID::Penguin}, //VID: 0x012d, Filename: pgn11
        {"Puck", 0x04650001, 0x006E0502, SpecieID::Penguin}, //VID: 0x012a, Filename: pgn06
        {"Roald", 0x04600001, 0x00A50502, SpecieID::Penguin}, //VID: 0x0125, Filename: pgn01
        {"Sprinkle", 0x046D0001, 0x00F30502, SpecieID::Penguin}, //VID: 0x0130, Filename: pgn14
        {"Tex", 0x046B0001, 0x01970502, SpecieID::Penguin}, //VID: 0x012e, Filename: pgn12
        {"Wade", 0x04680001, 0x02F20502, SpecieID::Penguin}, //VID: 0x012b, Filename: pgn09
        {"Agnes", 0x04890001, 0x00EF0502, SpecieID::Pig}, //VID: 0x013f, Filename: pig17
        {"Boris", 0x04810001, 0x02F10502, SpecieID::Pig}, //VID: 0x0138, Filename: pig09
        {"Chops", 0x04860001, 0x00FC0502, SpecieID::Pig}, //VID: 0x013c, Filename: pig14
        {"Cobb", 0x04800001, 0x008D0502, SpecieID::Pig}, //VID: 0x0137, Filename: pig08
        {"Curly", 0x04780001, 0x01630502, SpecieID::Pig}, //VID: 0x0131, Filename: pig00
        {"Crackle/Spork", 0x047D0001, 0x012E0502, SpecieID::Pig}, //VID: 0x0136, Filename: pig05
        {"Gala", 0x04850001, 0x014C0502, SpecieID::Pig}, //VID: 0x013b, Filename: pig13
        {"Ganon", 0x01020100, 0x001B0002, SpecieID::Pig}, //VID: 0x0140, Filename: pig18
        {"Hugh", 0x047B0001, 0x00F50502, SpecieID::Pig}, //VID: 0x0134, Filename: pig03
        {"Kevin", 0x04870001, 0x01BF0502, SpecieID::Pig}, //VID: 0x013d, Filename: pig15
        {"Lucy", 0x047C0001, 0x01A00502, SpecieID::Pig}, //VID: 0x0135, Filename: pig04
        {"Maggie", 0x04820001, 0x02FD0502, SpecieID::Pig}, //VID: 0x0139, Filename: pig10
        {"Pancetti", 0x04880001, 0x00980502, SpecieID::Pig}, //VID: 0x013e, Filename: pig16
        {"Peggy", 0x04830001, 0x01B00502, SpecieID::Pig}, //VID: 0x013a, Filename: pig11
        {"Rasher", 0x047A0001, 0x00600502, SpecieID::Pig}, //VID: 0x0133, Filename: pig02
        {"Truffles", 0x04790001, 0x00920502, SpecieID::Pig}, //VID: 0x0132, Filename: pig01
        {"Bonbon", 0x04A50001, 0x00740502, SpecieID::Rabbit}, //VID: 0x0152, Filename: rbt17
        {"Bunnie", 0x04940001, 0x009A0502, SpecieID::Rabbit}, //VID: 0x0141, Filename: rbt00
        {"Carmen", 0x04A40001, 0x00D40502, SpecieID::Rabbit}, //VID: 0x0151, Filename: rbt16
        {"Chrissy", 0x04A10001, 0x016F0502, SpecieID::Rabbit}, //VID: 0x014e, Filename: rbt13
        {"Claude", 0x049F0001, 0x03010502, SpecieID::Rabbit}, //VID: 0x014c, Filename: rbt11
        {"Coco", 0x04960001, 0x00D90502, SpecieID::Rabbit}, //VID: 0x0143, Filename: rbt02
        {"Cole", 0x04A60001, 0x00A30502, SpecieID::Rabbit}, //VID: 0x0153, Filename: rbt18
        {"Doc", 0x049E0001, 0x01B70502, SpecieID::Rabbit}, //VID: 0x014b, Filename: rbt10
        {"Dotty", 0x04950001, 0x01920502, SpecieID::Rabbit}, //VID: 0x0142, Filename: rbt01
        {"Francine", 0x04A00001, 0x016E0502, SpecieID::Rabbit}, //VID: 0x014d, Filename: rbt12
        {"Gabi", 0x04990001, 0x00DF0502, SpecieID::Rabbit}, //VID: 0x0146, Filename: rbt05
        {"Gaston", 0x04980001, 0x014A0502, SpecieID::Rabbit}, //VID: 0x0145, Filename: rbt04
        {"Genji", 0x049C0001, 0x01400502, SpecieID::Rabbit}, //VID: 0x0149, Filename: rbt08
        {"Hopkins", 0x04A20001, 0x02E80502, SpecieID::Rabbit}, //VID: 0x014f, Filename: rbt14
        {"Mira", 0x04A70001, 0x01A60502, SpecieID::Rabbit}, //VID: 0x0154, Filename: rbt19
        {"O'Hare", 0x04A30001, 0x01C90502, SpecieID::Rabbit}, //VID: 0x0150, Filename: rbt15
        {"Pippy", 0x049A0001, 0x014E0502, SpecieID::Rabbit}, //VID: 0x0147, Filename: rbt06
        {"Ruby", 0x049D0001, 0x00ED0502, SpecieID::Rabbit}, //VID: 0x014a, Filename: rbt09
        {"Snake", 0x04970001, 0x007A0502, SpecieID::Rabbit}, //VID: 0x0144, Filename: rbt03
        {"Tiffany", 0x049B0001, 0x00610502, SpecieID::Rabbit}, //VID: 0x0148, Filename: rbt07
        {"Toby", 0x04A80101, 0x031E0502, SpecieID::Rabbit}, //VID: 0x0155, Filename: rbt20
        {"Hornsby", 0x04B60001, 0x02EC0502, SpecieID::Rhino}, //VID: 0x0159, Filename: rhn04
        {"Merengue", 0x04B90001, 0x01600502, SpecieID::Rhino}, //VID: 0x015a, Filename: rhn07
        {"Renée", 0x04BA0001, 0x005D0502, SpecieID::Rhino}, //VID: 0x015b, Filename: rhn08
        {"Rhonda", 0x04B30001, 0x00DD0502, SpecieID::Rhino}, //VID: 0x0157, Filename: rhn01
        {"Spike", 0x04B40001, 0x030C0502, SpecieID::Rhino}, //VID: 0x0158, Filename: rhn02
        {"Tank", 0x04B20001, 0x01B90502, SpecieID::Rhino}, //VID: 0x0156, Filename: rhn00
        {"Baabara", 0x04C60001, 0x01670502, SpecieID::Sheep}, //VID: 0x015d, Filename: shp01
        {"Cashmere", 0x04C90001, 0x030D0502, SpecieID::Sheep}, //VID: 0x0160, Filename: shp04
        {"Curlos", 0x04CD0001, 0x01520502, SpecieID::Sheep}, //VID: 0x0162, Filename: shp08
        {"Étoile", 0x04D30101, 0x031B0502, SpecieID::Sheep}, //VID: 0x0168, Filename: shp14
        {"Eunice", 0x04C70001, 0x00940502, SpecieID::Sheep}, //VID: 0x015e, Filename: shp02
        {"Frita", 0x04D00001, 0x01960502, SpecieID::Sheep}, //VID: 0x0165, Filename: shp11
        {"Muffy", 0x04D10001, 0x009E0502, SpecieID::Sheep}, //VID: 0x0166, Filename: shp12
        {"Pietro", 0x04D20001, 0x01A70502, SpecieID::Sheep}, //VID: 0x0167, Filename: shp13
        {"Stella", 0x04C80001, 0x02ED0502, SpecieID::Sheep}, //VID: 0x015f, Filename: shp03
        {"Timbra", 0x04CF0001, 0x00E10502, SpecieID::Sheep}, //VID: 0x0164, Filename: shp10
        {"Vesta", 0x04C50001, 0x01010502, SpecieID::Sheep}, //VID: 0x015c, Filename: shp00
        {"Wendy", 0x04CE0001, 0x00DB0502, SpecieID::Sheep}, //VID: 0x0163, Filename: shp09
        {"Willow", 0x04CC0001, 0x00A40502, SpecieID::Sheep}, //VID: 0x0161, Filename: shp07
        {"Agent S", 0x04E20001, 0x01090502, SpecieID::Squirrel}, //VID: 0x016e, Filename: squ05
        {"Blaire", 0x04DE0001, 0x00CE0502, SpecieID::Squirrel}, //VID: 0x016a, Filename: squ01
        {"Cally", 0x04E80001, 0x01CE0502, SpecieID::Squirrel}, //VID: 0x0174, Filename: squ11
        {"Caroline", 0x04E30001, 0x01650502, SpecieID::Squirrel}, //VID: 0x016f, Filename: squ06
        {"Cece", 0x08010000, 0x025D0402, SpecieID::Squirrel}, //VID: 0x017b, Filename: squ19
        {"Filbert", 0x04DF0001, 0x00E80502, SpecieID::Squirrel}, //VID: 0x016b, Filename: squ02
        {"Hazel", 0x04EF0001, 0x013B0502, SpecieID::Squirrel}, //VID: 0x017a, Filename: squ18
        {"Marshal", 0x04EE0001, 0x014B0502, SpecieID::Squirrel}, //VID: 0x0179, Filename: squ17
        {"Mint", 0x04E60001, 0x00820502, SpecieID::Squirrel}, //VID: 0x0172, Filename: squ09
        {"Nibbles", 0x04E10001, 0x01BE0502, SpecieID::Squirrel}, //VID: 0x016d, Filename: squ04
        {"Peanut", 0x04DD0001, 0x00A20502, SpecieID::Squirrel}, //VID: 0x0169, Filename: squ00
        {"Pecan", 0x04E00001, 0x00F70502, SpecieID::Squirrel}, //VID: 0x016c, Filename: squ03
        {"Poppy", 0x04EC0001, 0x00770502, SpecieID::Squirrel}, //VID: 0x0177, Filename: squ15
        {"Ricky", 0x04E70001, 0x01320502, SpecieID::Squirrel}, //VID: 0x0173, Filename: squ10
        {"Sally", 0x04E40001, 0x01B60502, SpecieID::Squirrel}, //VID: 0x0170, Filename: squ07
        {"Sheldon", 0x04ED0001, 0x00620502, SpecieID::Squirrel}, //VID: 0x0178, Filename: squ16
        {"Static", 0x04E50001, 0x01AD0502, SpecieID::Squirrel}, //VID: 0x0171, Filename: squ08
        {"Sylvana", 0x04EB0001, 0x02F00502, SpecieID::Squirrel}, //VID: 0x0176, Filename: squ14
        {"Tasha", 0x04EA0001, 0x03180502, SpecieID::Squirrel}, //VID: 0x0175, Filename: squ13
        {"Viché", 0x08020000, 0x025E0402, SpecieID::Squirrel}, //VID: 0x017c, Filename: squ20
        {"Bangle", 0x04FD0001, 0x007B0502, SpecieID::Tiger}, //VID: 0x0180, Filename: tig03
        {"Bianca", 0x05000001, 0x00E70502, SpecieID::Tiger}, //VID: 0x0183, Filename: tig06
        {"Claudia", 0x04FF0001, 0x01620502, SpecieID::Tiger}, //VID: 0x0182, Filename: tig05
        {"Leonardo", 0x04FE0001, 0x00590502, SpecieID::Tiger}, //VID: 0x0181, Filename: tig04
        {"Rolf", 0x04FA0001, 0x01680502, SpecieID::Tiger}, //VID: 0x017d, Filename: tig00
        {"Rowan", 0x04FB0001, 0x01C60502, SpecieID::Tiger}, //VID: 0x017e, Filename: tig01
        {"Tybalt", 0x04FC0001, 0x02EE0502, SpecieID::Tiger}, //VID: 0x017f, Filename: tig02
        {"Chief", 0x050B0001, 0x00990502, SpecieID::Wolf}, //VID: 0x0184, Filename: wol00
        {"Dobie", 0x050F0001, 0x03140502, SpecieID::Wolf}, //VID: 0x0188, Filename: wol04
        {"Fang", 0x05110001, 0x01950502, SpecieID::Wolf}, //VID: 0x018a, Filename: wol06
        {"Freya", 0x05100001, 0x01070502, SpecieID::Wolf}, //VID: 0x0189, Filename: wol05
        {"Kyle", 0x05150001, 0x005B0502, SpecieID::Wolf}, //VID: 0x018d, Filename: wol10
        {"Lobo", 0x050C0001, 0x01C10502, SpecieID::Wolf}, //VID: 0x0185, Filename: wol01
        {"Skye", 0x05140001, 0x01530502, SpecieID::Wolf}, //VID: 0x018c, Filename: wol09
        {"Vivian", 0x05130001, 0x02E70502, SpecieID::Wolf}, //VID: 0x018b, Filename: wol08
        {"Whitney", 0x050E0001, 0x00D70502, SpecieID::Wolf}, //VID: 0x0187, Filename: wol03
        {"Wolfgang", 0x050D0001, 0x01420502, SpecieID::Wolf}, //VID: 0x0186, Filename: wol02
        {"W. Link", 0x01030000, 0x024F0902, SpecieID::Wolf}, //VID: 0x018e, Filename: wol11
        {"Villager", 0x01800000, 0x00080002, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Isabelle", 0x01810001, 0x00440502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"K. K. Slider", 0x01820001, 0x00A80502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Tom Nook", 0x01830001, 0x00450502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Timmy&Tommy", 0x01840000, 0x024D0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Timmy", 0x01850001, 0x004B0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Tommy", 0x01860301, 0x01750502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Sable", 0x01870001, 0x00470502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Mable", 0x01880001, 0x01120502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Labelle", 0x01890001, 0x00AB0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Reese", 0x018A0001, 0x00A90502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Cyrus", 0x018B0001, 0x01150502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Digby", 0x018C0001, 0x004C0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Rover", 0x018D0001, 0x010C0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Resetti", 0x018E0001, 0x00490502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Don Resetti", 0x018F0001, 0x00B30502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Brewster", 0x01900001, 0x01710502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Harriet", 0x01910001, 0x004E0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Blathers", 0x01920001, 0x010D0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Celeste", 0x01930001, 0x01740502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Kicks", 0x01940001, 0x00AA0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Porter", 0x01950001, 0x00B00502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Kapp'n", 0x01960001, 0x00480502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Leilani", 0x01970001, 0x01770502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Lelia", 0x01980001, 0x00B10502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Grams", 0x01990001, 0x01160502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Nat", 0x019B0001, 0x00B60502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Chip", 0x019A0001, 0x00B70502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Phineas", 0x019C0001, 0x01730502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Copper", 0x019D0001, 0x00AC0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Booker", 0x019E0001, 0x00AD0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Pete", 0x019F0001, 0x01110502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Pelly", 0x01A00001, 0x010F0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Phyllis", 0x01A10001, 0x01100502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Gulliver", 0x01A20001, 0x017D0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Joan", 0x01A30001, 0x004A0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Pascal", 0x01A40001, 0x004D0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Katrina", 0x01A50001, 0x01720502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Sahara", 0x01A60001, 0x00500502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Wendell", 0x01A70001, 0x01140502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Redd", 0x01A80001, 0x004F0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Gracie", 0x01A90001, 0x01760502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Lyle", 0x01AA0001, 0x00530502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Pave", 0x01AB0001, 0x017C0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Zipper", 0x01AC0001, 0x017F0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Jack", 0x01AD0001, 0x00B80502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Franklin", 0x01AE0001, 0x011B0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Jingle", 0x01AF0001, 0x011C0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Tortimer", 0x01B00001, 0x00520502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Dr. Shrunk", 0x01B10001, 0x00B20502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Blanca", 0x01B30001, 0x00B50502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Leif", 0x01B40001, 0x01130502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Luna", 0x01B50001, 0x00510502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Katie", 0x01B60001, 0x00AE0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
        {"Lottie", 0x01C10101, 0x017A0502, SpecieID::Special}, //VID: 0x018e, Filename: wol11
    };

}
