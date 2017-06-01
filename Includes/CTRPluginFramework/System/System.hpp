#ifndef CTRPLUGINFRAMEWORK_SYSTEM_SYSTEM_HPP
#define CTRPLUGINFRAMEWORK_SYSTEM_SYSTEM_HPP

namespace CTRPluginFramework
{    
    enum class Language
    {
        Japanese = 0,
        English,
        French,
        German,
        Italian,
        Spanish,
        ChineseSimplified,
        Korean,
        Dutch,
        Portugese,
        Russian,
        ChineseTraditional
    };

    class System
    {
    public: 
        
        /**
         * \brief Check if the current console is a New3DS
         * \return true if the current console is a New3DS,\n false otherwise
         */
        static bool         IsNew3DS(void);

        /**
         * \brief Get the system's language (user defined)
         * \return The language of the system
         */
        static Language     GetSystemLanguage(void);

        /**
         * \brief Get if the 3DS is connected to Internet
         * \return true if connected \n false if not connected
         */
        static bool         IsConnectedToInternet(void);
    };
}

#endif