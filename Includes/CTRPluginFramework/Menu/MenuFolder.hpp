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
        MenuFolder(const std::string &name, const std::string &note = "");
        MenuFolder(const std::string &name, const std::vector<MenuEntry *> &entries);
        MenuFolder(const std::string &name, const std::string &note, const std::vector<MenuEntry *> &entries);
        ~MenuFolder();

        // Hide the folder from the menu. Will disable every sub entries
        void    Hide(void) const;
        // Reinsert a folder previously hidden in the menu
        void    Show(void) const;
        // Return is the folder is visible in the menu
        bool    IsVisible(void) const;

        /**
         * \brief Append a MenuEntry object to this folder
         * \param item The entry to append
         */
        void    Append(MenuEntry *item) const;

        /**
         * \brief Append a MenuFolder object to this folder
         * \param item The folder to append
         */
        void    Append(MenuFolder *item) const;

        /**
         * \brief Get all entries present in this folder (doesn't contain subfolder's)
         * \return A std::vector with pointers to all MenuEntry objects
         */
        std::vector<MenuEntry *>    GetEntryList(void) const;

        /**
         * \brief Get all folders present in this folder (doesn't contain subfolder's)
         * \return A std::vector with pointers to all MenuEntry objects
         */
        std::vector<MenuFolder *>   GetFolderList(void) const;

        u32     ItemsCount(void) const;
        MenuFolder    *operator += (const MenuEntry *entry);
        MenuFolder    *operator += (const MenuFolder *folder);

    private:
        friend class PluginMenu;
        std::unique_ptr<MenuFolderImpl> _item;
    };
}

#endif
