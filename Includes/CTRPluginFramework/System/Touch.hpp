#ifndef CTRPLUGINFRAMEWORK_TOUCH_HPP
#define CTRPLUGINFRAMEWORK_TOUCH_HPP

#include "CTRPluginFramework/System/Vector.hpp"

namespace CTRPluginFramework
{
    class Touch
    {
    public:
        static bool         IsDown(void);
        static UIntVector   GetPosition(void);
    };
}

#endif