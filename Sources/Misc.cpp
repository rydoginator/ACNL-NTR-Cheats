#include "cheats.hpp"

namespace CTRPluginFramework
{
    void    BuildingPlacer(MenuEntry *entry)
    {
        u32     offset = 0;
        u8      input;

        if (Controller::IsKeysDown(R + DPadDown))
        {
            Keyboard keyboard("What building would you like to place?");
            
            //Exit if the user cancel the keyboard
            if (keyboard.Open(input) == -1)
                return;
            
            u8      x = static_cast<u8>(Game::WorldPos->x);
            u8      y = static_cast<u8>(Game::MainStreetPos->y);
            u32     building = reinterpret_cast<u32>(Game::Building);

            while (READU8(building + offset) != 0xFC && offset < 0xE5)
            {
                offset += 0x4;
            }
            if (offset >= 0xE5)
            {
                OSD::Notify("All building slots are filled!");
            }
            else
            {
                WRITEU8(building + offset, input);
                WRITEU8(building + offset + 0x2, x);
                WRITEU8(building + offset + 0x3, y);
            }
        }

        if (Controller::IsKeysDown(R + DPadUp))
        {
            Keyboard keyboard("What building would you like to remove?");

            // Exit if the user cancel the keyboard
            if (keyboard.Open(input) == -1)
                return;

            u32  building = reinterpret_cast<u32>(Game::Building);

            while (READU8(building + offset) != input && offset < 0xE5)
            {
                offset += 0x4;
            }
            if (offset == 0xE5)
            {
                OSD::Notify("Could not find your building");
            }
            else
            {
                WRITEU8(building + offset, 0xFC);
                WRITEU8(building + offset + 0x2, 0x00);
                WRITEU8(building + offset + 0x3, 0x00);
            }
        }
    }

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
}