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
    public:

        PluginMenu(std::string name = "Cheats", std::string note = "");
        ~PluginMenu(void){};

        void    Append(MenuEntry *item);
        void    Append(MenuFolder *item);
        void    Callback(CallbackPointer callback);
        int     Run(void);

    private:
        
        PluginMenuImpl *_menu;
        //std::unique_ptr<PluginMenuImpl> _menu;
    };
}

#endif