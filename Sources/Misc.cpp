#include "cheats.hpp"

namespace CTRPluginFramework
{

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

	void	FastGameSpeed(MenuEntry *entry)
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
}