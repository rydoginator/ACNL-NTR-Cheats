#ifndef CTRPLUGINFRAMEWORK_UTILS_STRINGEXTENSIONS_HPP
#define CTRPLUGINFRAMEWORK_UTILS_STRINGEXTENSIONS_HPP

#include "CTRPluginFramework/Graphics/Color.hpp"
#include <string>
#include <type_traits>

namespace CTRPluginFramework
{
    // Return a string with the charcter that reset the color (0x18)
    std::string     ResetColor(void);

    std::string operator <<(const std::string &left, const char *right);
    std::string operator <<(const std::string &left, const std::string &right);
    std::string operator <<(const std::string &left, const Color &color);
    std::string operator <<(const Color &color, const std::string &right);
    
    template <typename T, 
        typename std::enable_if<!std::is_same<T, const char *>::value>::type* = nullptr>
    std::string operator <<(const std::string &left, T right)
    {
        return (left + std::to_string(right));
    }

    template <typename T,
        typename std::enable_if<!std::is_same<T, const char *>::value>::type* = nullptr>
    std::string operator <<(const Color &color, T right)
    {
        char  strColor[5] = { 0 };

        strColor[0] = 0x1B;
        strColor[1] = std::max((u8)1, color.r);
        strColor[2] = std::max((u8)1, color.g);
        strColor[3] = std::max((u8)1, color.b);

        return (strColor + std::to_string(right));
    }
}

#endif
