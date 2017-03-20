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

        MenuEntry(std::string name, std::string note = "");
        MenuEntry(std::string name, FuncPointer func, std::string note = "");
        MenuEntry(int radioGroup, std::string name, FuncPointer func, std::string note = "");
        ~MenuEntry(){};

        // Disable the entry
        void    Disable(void);
        // Set the entry as radio, an ID must be provided
        void    SetRadio(int id);        
        // Set an argument for the entry
        void    SetArg(void *arg);
        // Get the argument
        void    *GetArg(void);
        // Return if the entry just got activated
        bool    WasJustActivated(void);
        // Return if the entry is activated
        bool    IsActivated(void);

        void    SetGameFunc(FuncPointer func);
        void    SetMenuFunc(FuncPointer func);

        std::string &Name(void);
        std::string &Note(void);

    private:
        friend class MenuFolder;
        friend class PluginMenu;
        MenuEntryImpl       *_item;
        //std::unique_ptr<MenuEntryImpl>  _item;
    };
}

#endif