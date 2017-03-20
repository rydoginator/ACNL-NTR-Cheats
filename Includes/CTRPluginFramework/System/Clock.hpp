#ifndef CTRPLUGINFRAMREWORK_CLOCK_HPP
#define CTRPLUGINFRAMREWORK_CLOCK_HPP

#include "CTRPluginFramework/System/Time.hpp"

namespace CTRPluginFramework
{
    class Clock
    {
    public:
        Clock(void);

        Time    GetElapsedTime(void) const;
        bool    HasTimePassed(Time time) const;
        Time    Restart(void);
    private:
        Time    _startTime;
    };
}

#endif