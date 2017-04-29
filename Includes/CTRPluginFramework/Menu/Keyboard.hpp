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
        using   CompareCallback = bool (*)(const void *, std::string&);
    public:
        Keyboard(std::string text = "");
        ~Keyboard(void);

        /*
        ** Define if the input must be hexadecimal or not
        ** Have no effect for float, double, string
        **************************************************/
        void    IsHexadecimal(bool isHex);
        /*
        ** Define a callback to check the input
        ** Return value: true if the value is valid, false otherwise
        ***************************************************************/
        void    SetCompareCallback(CompareCallback callback);

        /*
        ** Populate a keyboard with strings
        ************************************************/
        void    Populate(std::vector<std::string> &input);

        /*
        ** Open(void)
        ** Only usable with a keyboard that you populated with strings
        ** Return value: 
        **    -1 : user abort / not populated
        **    >= 0 : index of the user choice in the vector
        ************************************************/
        int     Open(void);
        /*
        ** Open the keyboard and wait for user input
        ** Return value: 0 = success, -1 = user abort
        ************************************************/
        int     Open(u8 &output);
        int     Open(u8 &output, u8 start);
        int     Open(u16 &output);
        int     Open(u16 &output, u16 start);
        int     Open(u32 &output);
        int     Open(u32 &output, u32 start);
        int     Open(u64 &output);
        int     Open(u64 &output, u64 start);

        int     Open(float &output);
        int     Open(float &output, float start);
        int     Open(double &output);
        int     Open(double &output, double start);

        int     Open(std::string &output);
        int     Open(std::string &output, std::string start);


        bool    DisplayTopScreen;
    private:
        std::unique_ptr<KeyboardImpl>   _keyboard;
        bool                            _hexadecimal;
        bool                            _isPopulated;
    };
}

#endif