#ifndef CTRPLUGINFRAMEWORK_SYSTEM_FWKSETTINGS_HPP
#define CTRPLUGINFRAMEWORK_SYSTEM_FWKSETTINGS_HPP

#include "types.h"
#include "CTRPluginFramework/System/Time.hpp"
#include "CTRPluginFramework/Graphics/Color.hpp"

namespace CTRPluginFramework
{
    struct PluginHeader
    {
        u32             magic;
        u32             version;
        u32             heapVA;
        u32             heapSize;
        u32             pluginSize;
        const char*     pluginPathPA;
        u32             isDefaultPlugin;
        u32             reserved[25];
        u32             config[32];
    };

    struct FwkSettings
    {
        // Plugin init options
        u32     ThreadPriority; ///< Pri ority for the main thread of the plugin must be within 0x3E - 0x18 | Default: 0x30
        bool    AllowActionReplay; ///< Enable the Action Replay's handler, if this is set to off, even if the menu allows to create codes, they won't be executed
        bool    AllowSearchEngine; ///< If false then the search engine won't be available | Default: true
        Time    WaitTimeToBoot; ///< Time to wait for the plugin to starts (from when the game will starts) | Default: 5 seconds

        // UI colors
        Color   MainTextColor;  ///< The color of all texts within the plugin | Default: Blank
        Color   WindowTitleColor; ///< The color of all window's titles | Default: Blank
        Color   MenuSelectedItemColor; ///< The color of the text for the selected item | Default: Blank
        Color   MenuUnselectedItemColor; ///< The color of the text for the items not selected | Default: Silver
        Color   BackgroundMainColor; ///< The color of the background | Default: Black
        Color   BackgroundSecondaryColor; ///< The color of the background 2 | Default: black/grey (RGB: 15,  15, 15)
        Color   BackgroundBorderColor; ///< The color of the border around the window | Default: Blank
        float   CursorFadeValue; ///< The value to be used to draw the cursor (Shade: [-1.0f - 0f], Tint: [0.f - 1.f]) | Default: 0.2f

        // Keyboard colors
        struct
        {
            Color   Background; ///< Color of the window's background | Default: Black
            Color   KeyBackground; ///< Color of the key's background | Default: Black
            Color   KeyBackgroundPressed; ///< Color of the key's background while pressed | Default: Silver
            Color   KeyText; ///< Color of the key's text | Default: Blank
            Color   KeyTextPressed; ///< Color of the key's text while pressed | Default: Blank
            Color   Cursor; ///< Color of the cursor | Default: Blank
            Color   Input; ///< Color of the input | Default: Blank
        } Keyboard;

        // Custom Keyboard colors
        struct
        {
            Color   BackgroundMain; ///< The color of the background | Default: Black
            Color   BackgroundSecondary; ///< The color of the background 2 | Default: black/grey (RGB: 15,  15, 15)
            Color   BackgroundBorder; ///< The color of the border around the window | Default: Blank
            Color   KeyBackground;  ///< Color of the background of a key | Default: sort of Grey (51, 51, 51)
            Color   KeyBackgroundPressed; ///< Color of the background of a key when it's being touched | Default: Gainsboro
            Color   KeyText; ///< Color of the text of a key | Default: Blank
            Color   KeyTextPressed; ///< Color of the text of a key when being touched | Default: Black
            Color   ScrollBarBackground; ///< Color of the scrollbar's background | Default: Silver
            Color   ScrollBarThumb; ///< Color of the scrollbar's thumb | Default: DimGrey
        } CustomKeyboard;

        /**
         * \brief Returns a reference to the FwkSettings instance used by the framework
         * Allows runtime theme edition
         * \return The instance of FwkSettings
         */
        static FwkSettings& Get(void);
        static PluginHeader *Header;

        /**
         * \brief Reset all colors to their default values
         */
        static void         SetThemeDefault(void);
    };
}

#endif
