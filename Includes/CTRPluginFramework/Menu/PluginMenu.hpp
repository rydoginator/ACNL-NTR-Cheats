#ifndef CTRPLUGINFRAMEWORK_PLUGINMENU_HPP
#define CTRPLUGINFRAMEWORK_PLUGINMENU_HPP

#include "CTRPluginFramework/Menu/MenuEntry.hpp"
#include "CTRPluginFramework/Menu/MenuFolder.hpp"

#include <string>
#include <memory>

namespace CTRPluginFramework
{
    class PluginMenuImpl;
    class PluginMenu
    {
        using CallbackPointer = void (*)(void);
        using DecipherPointer = void(*)(std::string &, void *);
    public:

        /*
        ** Create a new PluginMenu
        ** name = The name of the menu / main folder
        ** about = text to display on the bottom screen of Tools section
        ******************************/
        explicit PluginMenu(std::string name = "Cheats", std::string about = "");

        /*
        ** Create a new PluginMenu
        ** name = The name of the menu / main folder
        ** about = pointer to encrypted about's text data
        ** func = function to decrypt the about's data
        ******************************/
        PluginMenu(std::string name, void *about, DecipherPointer func);

        /*
        ** Destructor
        ******************************/
        ~PluginMenu(void);

        /*
        ** Append a new entry to the menu (root)
        ** item = pointer to a MenuEntry object
        ******************************/
        void    Append(MenuEntry *item) const;

        /*
        ** Append a new folder to the menu (root)
        ** item = pointer to a MenuFolder object
        ******************************/
        void    Append(MenuFolder *item) const;

        /*
        ** Add a callback to the menu
        ** A callback is a function which is always executed in the menu's main loop
        ** callback = function to add as callback
        ******************************/
        void    Callback(CallbackPointer callback) const;

        /*
        ** Run the menu
        ** This call is blocking so be sure to do everyting before calling this function
        ******************************/
        int     Run(void) const;

        /**
         * \brief Enable / Disable the Search button in the main menu
         * \param isEnabled If the button must be enabled or not
         */
        void    SetSearchButtonState(bool isEnabled) const;

        /**
         * \brief Enable / Disable the ActionReplay button in the main menu
         * \param isEnabled If the button must be enabled or not
         */
        void    SetActionReplayButtonState(bool isEnabled) const;

        /**
         * \brief Enable / Disable the FreeCheats in Tools
         * \param isEnabled If FreeCheats must be enabled or not
         */
        void    SetFreeCheatsState(bool isEnabled) const;

        /**
         * \brief Check if the menu is currently open
         * \return true if the menu is open, false otherwise
         */
        bool    IsOpen(void);

        /**
         * \brief Check if the menu was opened since last Func execution
         * \return true if the menu was opened, false otherwise
         */
        bool    WasOpened(void);

        /**
         * \brief Get a reference to the PluginMenu currently running
         * \return A reference to a PluginMenu that is currently running
         */
        static PluginMenu   &GetRunningInstance(void);

        

    private:
        std::unique_ptr<PluginMenuImpl> _menu;
    };
}

#endif