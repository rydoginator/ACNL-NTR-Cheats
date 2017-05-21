#ifndef CTRPLUGINFRAMEWORK_KEYBOARD_HPP
#define CTRPLUGINFRAMEWORK_KEYBOARD_HPP

#include "types.h"
#include <string>
#include <vector>
#include <memory>

namespace CTRPluginFramework
{
    class KeyboardImpl;
    class Keyboard
    {
        /**
         * \brief The signature of the callback called to check the input
         * \param input     A void pointer to the input, must be casted to the correct type (as passed to Keyboard::Open)
         * \param error     A reference to the string that hold the error message. You can edit it according to what you want to display
         * \return A boolean \n Return true if the input is valid, false if it's not
         */
        using   CompareCallback = bool (*)(const void *, std::string&);

        /**
         * \brief The signature of the callback called when the input change (user enter / delete a character)
         * \param keyboard  A reference to the Keyboard object that called the callback
         */
        using   OnInputChangeCallback = void(*)(Keyboard&);
    public:

        /**
         * \brief Keyboard constructor
         * \param text  The message to display on the top screen if displayed
         */
        Keyboard(std::string text = "");
        ~Keyboard(void);

        /**
         * \brief Set if the user can abort the keybord by pressing B
         * \param canAbort  Whether the user can press B to close the keyboard and abort the current operation
         */
        void    CanAbort(bool canAbort);

        /**
         * \brief Define if the input must be hexadecimal or not \n
         * Have no effect for float, double, string
         * \param isHex  If the input must be hexadecimal
         */
        void    IsHexadecimal(bool isHex);

        /**
         * \brief Define a callback to check the input \n
         * The callback is called each time the input is changed \n
         * See CompareCallback's description for more infos
         * \param callback The callback that must be called
         */
        void    SetCompareCallback(CompareCallback callback);

        /**
         * \brief Define a callback that will be called when the user change the input \n
         * Note that if a CompareCallback is set, CompareCallback is called before OnInputChange \n
         * See OnInputChangeCallback's description for more infos
         * \param callback 
         */
        void    OnInputChange(OnInputChangeCallback callback);

        /**
         * \brief Set the error flag and an error message \n
         * When the error flag is set, the user can't valid the input
         * \param error The error message that must be displayed
         */
        void    SetError(std::string error);

        /**
         * \brief Populate a keyboard with the strings contained in an std::vector
         * \param input  A std::vector that contain a list of strings
         */
        void    Populate(std::vector<std::string> &input);

        /**
         * \brief Open a keyboard which is populated with strings
         * \return -1 : user abort / not populated \n
         * >= 0 : index of the user choice in the vector
         */
        int     Open(void);

        /**
         * \brief Open the keyboard and wait for user input
         * \param output Where to place the user's input
         * \return -1 : user abort / error \n
         * 0 : Success
         */
        int     Open(u8 &output);

        /**
         * \brief Open the keyboard and wait for user input
         * \param output Where to place the user's input
         * \param start The keyboard will start with this value as input
         * \return -1 : user abort / error \n
         * 0 : Success
         */
        int     Open(u8 &output, u8 start);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(u16 &output);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \param start The keyboard will start with this value as input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(u16 &output, u16 start);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(u32 &output);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \param start The keyboard will start with this value as input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(u32 &output, u32 start);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(u64 &output);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \param start The keyboard will start with this value as input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(u64 &output, u64 start);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(float &output);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \param start The keyboard will start with this value as input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(float &output, float start);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(double &output);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \param start The keyboard will start with this value as input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(double &output, double start);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(std::string &output);

        /**
        * \brief Open the keyboard and wait for user input
        * \param output Where to place the user's input
        * \param start The keyboard will start with this value as input
        * \return -1 : user abort / error \n
        * 0 : Success
        */
        int     Open(std::string &output, std::string start);

        /**
         * \brief Forcefully close the keyboard without any regard to the error flag \n
         * (This can only be called from an OnInputChange callback)
         */
        void    Close(void);

        /**
         * \brief Get a reference to the Keyboard's input string
         * \return A reference to the Keyboard's input string
         */
        std::string     &GetInput(void);

        /**
        * \brief Get a reference to the top screen's message string
        * \return A reference to the top screen's message string
        */
        std::string     &GetMessage(void);        
        
        /**
         * \brief This property define if the top screen must be displayed or not \n
         * Note that when disabled, errors messages can't be displayed
         */
        bool    DisplayTopScreen;

    private:
        std::unique_ptr<KeyboardImpl>   _keyboard;
        bool                            _hexadecimal;
        bool                            _isPopulated;
    };
}

#endif