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

    template <typename T,
        typename std::enable_if<
        !std::is_same<T, const char *>::value
        && !std::is_same<T, Color>::value
    >::type* = nullptr>
    std::string operator <<(const std::string &left, T right)
    {
        return (left + std::to_string(right));
    }
}

#endif
