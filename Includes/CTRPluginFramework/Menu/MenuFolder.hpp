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
        ~MenuFolder();

        // Hide the folder from the menu. Will disable every sub entries
        void    Hide(void) const;
        // Reinsert a folder previously hidden in the menu
        void    Show(void) const;
        // Return is the folder is visible in the menu
        bool    IsVisible(void) const;

        void    Append(MenuEntry *item) const;
        void    Append(MenuFolder *item) const;
        u32     ItemsCount(void) const;
        MenuFolder    *operator += (const MenuEntry *entry);
        MenuFolder    *operator += (const MenuFolder *folder);

    private:
        friend class PluginMenu;
        std::unique_ptr<MenuFolderImpl> _item;
    };
}

#endif
