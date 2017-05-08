#ifndef CTRPLUGINFRAMEWORK_MENUENTRY_HPP
#define CTRPLUGINFRAMEWORK_MENUENTRY_HPP

#include <string>
#include <memory>

namespace CTRPluginFramework
{
    class MenuEntry;
    
    using FuncPointer = void (*)(MenuEntry*);

    class MenuEntryImpl;
    class MenuEntry
    {

    public:

        explicit MenuEntry(std::string name, std::string note = "");
        MenuEntry(std::string name, FuncPointer gameFunc, std::string note = "");
        MenuEntry(std::string name, FuncPointer gameFunc, FuncPointer menuFunc, std::string note = "");
        MenuEntry(int radioGroup, std::string name, FuncPointer gameFunc, std::string note = "");
        MenuEntry(int radioGroup, std::string name, FuncPointer gameFunc, FuncPointer menuFunc, std::string note = "");
        ~MenuEntry();

        // Disable the entry
        void    Disable(void) const;
        // Hide the entry from the menu. Will disable it too
        void    Hide(void) const;
        // Reinsert an entry previously hidden in the menu
        void    Show(void) const;
        // Set the entry as radio, an ID must be provided
        void    SetRadio(int id) const;
        // Set an argument for the entry
        void    SetArg(void *arg) const;
        // Get the argument of the entry
        void    *GetArg(void) const;
        // Return if the entry just got activated
        bool    WasJustActivated(void) const;
        // Return if the entry is activated
        bool    IsActivated(void) const;

        void    SetGameFunc(FuncPointer func) const;
        void    SetMenuFunc(FuncPointer func) const;

        std::string &Name(void) const;
        std::string &Note(void) const;

    private:
        friend class MenuFolder;
        friend class PluginMenu;
        std::unique_ptr<MenuEntryImpl>  _item;
    };
}

#endif