#include "cheats.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework
{

    struct NPC
    {
        const char *File;
        std::string Name;
    };

    const std::vector<NPC> villagers =
    {
        { "alp.bcres", "Cyrus" },
        { "alw.bcres", "Reese" },
        { "bev.bcres", "Chip" },
        { "bln.bcres", "Phineas" },
        { "boa.bcres", "Joan" },
        { "bpt.bcres", "Katrina" },
        { "chm.bcres", "Nat" },
        { "cml.bcres", "Sahara" },
        { "end.bcres", "Totakeke" },
        { "enj.bcres", "Totakeke" },
        { "fob.bcres", "Redd" },
        { "fox.bcres", "Red" },
        { "grf.bcres", "Grace" },
        { "hgc.bcres", "Labelle" },
        { "hgh.bcres", "Mable" },
        { "hgs.bcres", "Sable" },
        { "kpg.bcres", "Grams" },
        { "kpm.bcres", "Leilani" },
        { "kpp.bcres", "Kapp'n" },
        { "kps.bcres", "Leila" },
        { "liz.bcres", "Isabelle" },
        { "lom.bcres", "Katie" },
        { "lrc.bcres", "Timmy/Tommy" },
        { "lrd.bcres", "Timmy/Tommy" },
        { "lrh.bcres", "Timmy/Tommy" },
        { "lrn.bcres", "Timmy/Tommy" },
        { "lrs.bcres", "Timmy/Tommy" },
        { "mka.bcres", "Blanca?" },
        { "mnk.bcres", "Porter" },
        { "moc.bcres", "Don" },
        { "mod.bcres", "Don (No hat)" },
        { "mof.bcres", "Resetti (No Hat)" },
        { "moo.bcres", "Resetti" },
        { "ott.bcres", "Lyle" },
        { "owl.bcres", "Blathers" },
        { "ows.bcres", "Celeste" },
        { "pck.bcres", "Pave" },
        { "pga.bcres", "Pelly" },
        { "pgb.bcres", "Phyllis" },
        { "pge.bcres", "Brewster" },
        { "pkn.bcres", "Jack" },
        { "pla.bcres", "Booker" },
        { "plb.bcres", "Pete" },
        { "plc.bcres", "Copper" },
        { "poo.bcres", "Shampoodle" },
        { "pyn.bcres", "Zipper T." },
        { "rci.bcres", "Tom Nook" },
        { "rcn.bcres", "Isabelle" },
        { "rco.bcres", "Tom Nook" },
        { "seg.bcres", "Gulliver" },
        { "seo.bcres", "Pascal" },
        { "skk.bcres", "Kicks" },
        { "slo.bcres", "Lief" },
        { "snt.bcres", "Jingle" },
        { "sza.bcres", "Isabelle" },
        { "szo.bcres", "Digby" },
        { "szr.bcres", "Digby (Rain Jacket)" },
        { "tap.bcres", "Luna" },
        { "ttl.bcres", "Tortimer" },
        { "tuk.bcres", "Franklin" },
        { "upa.bcres", "Shrunk" },
        { "wrl.bcres", "Wendell" },
        { "xct.bcres", "Rover" },
    };

    void    GhostMode(MenuEntry *entry)
    {
        u32   patch = 0xE38110FF;
        u32   original = 0xE3811004;

        if (Controller::IsKeysDown(Y + DPadUp))
        {
            Process::Patch(0x00654594, (u8 *)&patch, 4);
        }
        if (Controller::IsKeysDown(Y + DPadDown))
        {
            Process::Patch(0x00654594, (u8 *)&original, 4);
        }
    }

    void    FastGameSpeed(MenuEntry *entry)
    {
        static u32 offset = reinterpret_cast<u32>(Game::GameSpeed);
        Process::Write32(offset, 0x00FFFFFF);
    }

    void    CameraMod(MenuEntry *entry)
    {
        // Pointers & addresses
        static const u32    cameraAsm = AutoRegion(USA_CAMERA_ASM_ADDR, EUR_CAMERA_ASM_ADDR, JAP_CAMERA_ASM_ADDR)();
        static u32  * const cameraPointer = reinterpret_cast<u32 * const>(AutoRegion(USA_CAMERA_POINTER, EUR_CAMERA_POINTER, JAP_CAMERA_POINTER)());
        static u32  * const cameraStop = reinterpret_cast<u32 * const>(AutoRegion(USA_CAMSTOP_POINTER, EUR_CAMSTOP_POINTER, JAP_CAMSTOP_POINTER)());
        static Coordinates * const cameraCoordinates = reinterpret_cast<Coordinates * const>(AutoRegion(USA_CAMERA_X_ADDR, EUR_CAMERA_X_ADDR, JAP_CAMERA_X_ADDR)());
        
        // Variables
        static const u32    patch = 0xEA000020;
        static const u32    original = 0x2A000020;

        static Coordinates  coord; ///< Saved player's coordinates
        static u32          storage;
        static bool         isPatched = false;
        


        // Unpatch when B is released
        if (isPatched && Controller::IsKeyReleased(B))
        {
            Process::Patch(cameraAsm, (u8 *)&original, 4);
            isPatched = false;
        }

        if (*cameraPointer)
        {
            // Fetch player's coordinates
            if (!Controller::IsKeyDown(CPad))
                coord = Player::GetInstance()->GetCoordinates();

            // Restore player's coordinates
            if (Controller::IsKeysDown(R + CPadDown))
                Player::GetInstance()->SetCoordinates(coord);

            // Move camera
            if (Controller::IsKeysDown(R + CPadDown))
                ADD16((*cameraPointer + 0x12C), 0x2);

            if (Controller::IsKeysDown(R + CPadUp))
                SUB16((*cameraPointer + 0x12C), 0x2);

            if (Controller::IsKeysDown(R + CPadRight))
                ADD16((*cameraPointer + 0x12E), 0x2);

            if (Controller::IsKeysDown(R + CPadLeft))
                SUB16((*cameraPointer + 0x12E), 0x2);

            // Fetch camera stop value
            if (Controller::IsKeysDown(R + X))
            {
                if (*cameraStop != 0)
                {
                    storage = *cameraStop;
                    *cameraStop = 0;
                }
            }

            // Restore camera stop value
            if (Controller::IsKeysDown(R + Y))
            {
                if (storage != 0)
                    *cameraStop = storage;
            }
        }

        // Next codes require B to be pressed, exit if not
        if (!Controller::IsKeyDown(B))
            return;

        if (Controller::IsKeysDown(B + DPadLeft))
        {
            cameraCoordinates->x -= 0.1f;
            goto patch;
        }

        if (Controller::IsKeysDown(B + DPadRight))
        {
            cameraCoordinates->x += 0.1f;
            goto patch;
        }

        if (Controller::IsKeysDown(B + DPadDown))
        {
            cameraCoordinates->z += 0.1f;
            goto patch;
        }

        if (Controller::IsKeysDown(B + DPadUp))
        {
            cameraCoordinates->z -= 0.1f;
            goto patch;
        }

        if (Controller::IsKeysDown(B + R))
        {
            cameraCoordinates->y += 0.1f;
            goto patch;
        }

        if (Controller::IsKeysDown(B + L))
        {
            cameraCoordinates->y -= 0.1f;
            goto patch;
        }

        return;
    patch:
        if (!isPatched)
        {
            // Change the asm instruction to b, allows overwriting camera coordinates
            Process::Patch(cameraAsm, (u8 *)&patch, 4);
            isPatched = true;
        }
    }

    void    KeyboardExtender(MenuEntry *entry)
    {
        u32 offset = 0;

        Process::Read32(0x95F11C, offset);
        if (offset != 0)
        {
            Process::Write32(0xC + offset, 0x36);
            Process::Write32(0x12B + offset, 0x45);
            Process::Write8(0xAD7253, 0x01);
        }
    }

    void    ItemFormChanger(MenuEntry *entry)
    {
        u16     item = *GetArg<u16>(entry);

        if (*Game::Location == -1)
            Process::Write16(Game::ItemForm, 0x334F + item);
    }

    void    ItemFormEditor(MenuEntry *entry)
    {
        u16   *item = GetArg<u16>(entry);

        *item = ItemChangerKeyboard();
    }

    void    ItemEffectChanger(MenuEntry *entry)
    {
        u16     item = *GetArg<u16>(entry);

        if (*Game::Location == -1)
            Process::Write16(Game::ItemForm - 0x3AD8, 0x334F + item);
    }

    void    ItemEffectEditor(MenuEntry *entry)
    {
        u16     *item = GetArg<u16>(entry);

        *item = ItemChangerKeyboard();
    }

    int     ItemChangerKeyboard(void)
    {
        Keyboard keyboard("Item Effect Changer\nWhat form would you like ?");
        static std::vector<std::string> list =
        {
            "Axe",
            "Net",
            "Rod",
            "Shovel",
            "Watering Can",
            "Slingshot",
            "Hammer",
            "MegaPhone",
            "Sparkler",
            "Roman Candle",
            "Party Popper",
            "Bubble Wand",
            "Balloon",
            "Pinwheel",
            "Drink",
            "Beans",
            "Good Luck Roll",
            "Ice Cream",
            "Wand",
            "Tweeter",
            "Frying Pan"
        };

        keyboard.Populate(list);
        keyboard.CanAbort(false);

        int userChoice = keyboard.Open();

        if (userChoice < 5)
            return (userChoice * 4);
        else if (userChoice == 5)
            return (20);
        else if (userChoice > 5 && userChoice < 8)
            return (16 + userChoice);
        else if (userChoice >= 8 && userChoice < 13)
            return (17 + userChoice);
        else if (userChoice == 13)
            return (53);
        else if (userChoice > 13 && userChoice < 18)
            return (48 + userChoice);
        else if (userChoice == 18)
            return (73);
        else if (userChoice == 19)
            return (79);

        return (986); //userChoice == 20
    }   


    void ChangeAnimal(const char* name)
    {
        static u32 isabelle = Game::DynamicNPC;
        static u32 offset = Game::StaticNPC;
        const char * original = "%s.bcres";
        if (name != "")
        {
            if (*Game::Room != 0x27)
            {
                if (*Game::Room == 0x63)
                {
                    Process::CopyMemory(reinterpret_cast<void *>(offset), (void*)original, 9);
                    Process::CopyMemory(reinterpret_cast<void *>(isabelle), (void*)name, 3);
                }
                else if (*Game::Room == 0)
                {
                    Process::CopyMemory(reinterpret_cast<void *>(offset), (void*)original, 9);
                    Process::CopyMemory(reinterpret_cast<void *>(isabelle + 0x1180), (void*)name, 3);
                }
                else
                {
                    Process::CopyMemory(reinterpret_cast<void *>(offset), (void*)name, 9);
                }
            }
            else
            {
                svcSleepThread(6000000000);
            }
        }
    }

    using StringVector = std::vector<std::string>;

    void    AnimalChangerKeyboard(MenuEntry *entry)
    {
        int *index = GetArg<int>(entry);
        Keyboard    keyboard("What would you like to change all Special NPCS to?");
        StringVector    entryNames;

        for (const NPC &entryName : villagers)
            entryNames.push_back(entryName.Name);

        keyboard.Populate(entryNames);

        int userChoice = keyboard.Open();


        *index = userChoice;

    }

    void    AnimalChanger(MenuEntry *entry)
    {
        int index = *GetArg<int>(entry);
        const NPC &NPCPicked = villagers[index];
        ChangeAnimal(NPCPicked.File);
    }
}