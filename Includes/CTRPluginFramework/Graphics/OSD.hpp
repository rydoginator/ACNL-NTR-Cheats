#ifndef CTRPLUGINFRAMEWORK_OSD_HPP
#define CTRPLUGINFRAMEWORK_OSD_HPP

#include "CTRPluginFramework/Graphics/Color.hpp"
#include "ctrulib/services/gspgpu.h"
#include <string>

namespace CTRPluginFramework
{
    using GSPFormat = GSPGPU_FramebufferFormats;

    class Screen
    {
    public:
        bool      IsTop;
        bool      Is3DEnabled;
        u32       LeftFramebuffer;
        u32       RightFramebuffer;
        u32       Stride;
        u32       BytesPerPixel;
        GSPFormat Format;

        u8 *    GetFramebuffer(u32 posX, u32 posY, bool useRightFb = false) const;
        u32     Draw(const std::string &str, u32 posX, u32 posY, const Color &foreground = Color::Blank, const Color &background = Color::Black) const;
        void    DrawRect(u32 posX, u32 posY, u32 width, u32 height, const Color &color, bool filled = true) const;
        void    DrawPixel(u32 posX, u32 posY, const Color &color) const;
        void    ReadPixel(u32 posX, u32 posY, Color &pixel, bool fromRightFb = false) const;
    private:
        friend class OSDImpl;
        Screen() {};
    };

    using OSDCallback = bool(*)(const Screen &);
    class OSD
    {
    public:

        /**
         * \brief Send a notification on the top screen, a notification duration is 5 seconds\n
         * A maximum of 50 notifications can be queued
         * \param str Text of the notification
         * \param foreground The color of the text (Default: blank)
         * \param background The color of the background (Default: black)
         * \return 0 if success, -1 if the notification couldn't be added
         */
        static int      Notify(std::string str, Color foreground = Color(255, 255, 255), Color background = Color());
        
        /**
         * \brief Add a callback to the OSD system which will be called at each game's frame
         * \param cb The callback to add
         */
        static void     Run(OSDCallback cb);

        /**
         * \brief Remove a callback from the OSD system
         * \param cb The callback to remove
         */
        static void     Stop(OSDCallback cb);

        static void     Lock(void);
        static bool     TryLock(void); //false success, true failure
        static void     Unlock(void);
    };
}

#endif
