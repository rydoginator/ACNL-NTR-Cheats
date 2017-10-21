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

        /**
         * \brief Check if the cfw is Luma3DS or not\n
         * A version number can be passed and if it's the case the function will return whether the version of the cfw is the same or higher (true) or inferior (false)
         * \param major An optional version
         * \param minor An optional version
         * \param revision An optional version
         * \return If the cfw is Luma3DS or not
         */
        static bool         CfwIsLuma3DS(u8 major = 0, u8 minor = 0, u8 revision = 0);
    };
}

#endif