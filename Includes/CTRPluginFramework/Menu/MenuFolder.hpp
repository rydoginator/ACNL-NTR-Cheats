#ifndef CTRPLUGINFRAMEWORK_MENUFOLDER_HPP
#define CTRPLUGINFRAMEWORK_MENUFOLDER_HPP

#include "types.h"
#include <string>
#include <memory>

namespace CTRPluginFramework
{
    class MenuFolderImpl;
    class MenuFolder
    {

    public:
        MenuFolder(std::string name, std::string note = "");
        ~MenuFolder(){};

        void    Append(MenuEntry *item);
        void    Append(MenuFolder *item);
        u32     ItemsCount(void);

    private:
        friend class PluginMenu;
        MenuFolderImpl *_item;
        //std::unique_ptr<MenuFolderImpl> _item;
    };
}

#endif
