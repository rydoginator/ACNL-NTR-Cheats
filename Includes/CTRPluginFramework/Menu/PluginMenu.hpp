#ifndef CTRPLUGINFRAMEWORK_PLUGINMENU_HPP
#define CTRPLUGINFRAMEWORK_PLUGINMENU_HPP

#include "CTRPluginFramework/Menu/MenuEntry.hpp"
#include "CTRPluginFramework/Menu/MenuFolder.hpp"
#include "CTRPluginFramework/System/Time.hpp"

#include <string>
#include <vector>
#include <memory>

namespace CTRPluginFramework
{
    class PluginMenuImpl;
    class PluginMenu
    {
        using CallbackPointer = void (*)(void);
        using FrameCallback = void (*)(Time);
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

        /**
         * \brief Create a new PluginMenu
         * \param name The name of the menu / main folder
         * \param major The major version number of the plugin version
         * \param minor The minor version number of the plugin version
         * \param revision The revision version number of the plugin version
         * \param about Text to display in Tools About
         */
        PluginMenu(std::string name, u32 major, u32 minor, u32 revision, std::string about = "");

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

        void    operator += (const MenuEntry *entry) const;
        void    operator += (const MenuFolder *folder) const;
        void    operator += (CallbackPointer callback) const;
        void    operator -= (CallbackPointer callback) const;

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
         * \brief Get all entries present at the root of the menu
         * \return A std::vector with pointers to all MenuEntry objects
         */
        std::vector<MenuEntry *>    GetEntryList(void) const;

        /**
         * \brief Get all folders present at the root of the menu
         * \return A std::vector with pointers to all MenuFolder objects
         */
        std::vector<MenuFolder *>   GetFolderList(void) const;

        /**
        * \brief Enable / Disable the HexEditor in Tools
        * \param isEnabled If HexEditor must be enabled or not
        */
        void    SetHexEditorState(bool isEnabled) const;

        /**
        * \brief Choose to display or not the "plugin ready" message
        * \param showMsg If the message must be displayed or not
        */
        void    ShowWelcomeMessage(bool showMsg) const;

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
        static PluginMenu   *GetRunningInstance(void);

        /**
         * \brief If set to true, the plugin's loop will only be executed 1 per top screen's frame
         * \param useSync Wheter to wait for the top screen's frame or not
         */
        void         SynchronizeWithFrame(const bool useSync);

        /**
         * \brief If a callback is set, the callback will be called - Must be set before calling Run
         * when the menu is opened for the first time
         */
        CallbackPointer     OnFirstOpening;

        /**
         * \brief If a callback is set, the callback will be called  - Must be set before calling Run
         * when the menu is opened. Ideal to put the code that refresh the UI. ;)
         */
        CallbackPointer     OnOpening;

        /**
         * \brief The callback set will be called at each frame rendered while the menu is open
         * Ideal to put some UI effect
         * The function will receive the Time elapsed since last frame
         * Must be set before calling Run
         */
        FrameCallback       OnNewFrame;


        /**
         * \brief Returns the reference of the PluginMenu title string
         * \return the reference of the PluginMenu title string
         */
        std::string &       Title();


    private:
        std::unique_ptr<PluginMenuImpl> _menu;
    };
}

#endif
