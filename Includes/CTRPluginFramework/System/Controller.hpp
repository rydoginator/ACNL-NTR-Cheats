#ifndef CTRPLUGINFRAMEWORK_CONTROLLER_HPP
#define CTRPLUGINFRAMEWORK_CONTROLLER_HPP

#include "types.h"

namespace CTRPluginFramework
{
    enum Key
    {
        A           = 1,
        B           = 1 << 1,
        Select      = 1 << 2,
        Start       = 1 << 3,
        DPadRight   = 1 << 4,
        DPadLeft    = 1 << 5,
        DPadUp      = 1 << 6,
        DPadDown    = 1 << 7,
        R           = 1 << 8,
        L           = 1 << 9,
        X           = 1 << 10,
        Y           = 1 << 11,
        ZL          = 1 << 14,               ///< The ZL button (New 3DS only)
        ZR          = 1 << 15,               ///< The ZR button (New 3DS only)
        Touchpad    = 1 << 20,
        CStickRight = 1 << 24,
        CStickLeft  = 1 << 25,
        CStickUp    = 1 << 26,
        CStickDown  = 1 << 27,
        CPadRight   = 1 << 28,
        CPadLeft    = 1 << 29,
        CPadUp      = 1 << 30,
        CPadDown    = 1 << 31,
        Up          = DPadUp    | CPadUp,
        Down        = DPadDown  | CPadDown,
        Left        = DPadLeft  | CPadLeft,
        Right       = DPadRight | CPadRight,
        CPad        = CPadLeft  | CPadRight | CPadUp | CPadDown,
        CStick      = CStickLeft | CStickRight | CStickUp | CStickDown
    };
    class Controller
    {
    public:

        // Return all the keys currently down
        static u32      GetKeysDown(void);
        // Return all the keys which were released
        static u32      GetKeysReleased(void);
        // Return if the key is still being pressed
        static bool     IsKeyDown(Key key);
        // Return if the key just got pressed
        static bool     IsKeyPressed(Key key);
        // Return if the key was released
        static bool     IsKeyReleased(Key key);

        // Return if keyCombo is still being pressed
        static bool     IsKeysDown(u32 keys);
        // Return is the keys combo just got pressed
        static bool     IsKeysPressed(u32 keys);
        // Return is the keys combo just was released
        static bool     IsKeysReleased(u32 keys);
        // Update Controller status
        static void     Update(void);

        static void     InjectTouch(u16 posX, u16 posY);
        static void     InjectKey(u32 key);
    private:
        static u32      _keysDown;
        static u32      _keysHeld;
        static u32      _keysReleased;
    };
}

#endif