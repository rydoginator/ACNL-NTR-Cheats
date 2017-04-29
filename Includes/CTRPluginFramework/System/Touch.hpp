#ifndef CTRPLUGINFRAMEWORK_TOUCH_HPP
#define CTRPLUGINFRAMEWORK_TOUCH_HPP

namespace CTRPluginFramework
{
    class UIntVector;
    class Touch
    {

    public:
        static bool         IsDown(void);
        static UIntVector   GetPosition(void);
    };
}

#endif