#ifndef CTRPLUGINFRAMEWORK_SYSTEM_MUTEX_HPP
#define CTRPLUGINFRAMEWORK_SYSTEM_MUTEX_HPP

#include "ctrulib/synchronization.h"

namespace CTRPluginFramework
{
    class Mutex
    {
    public:
        Mutex(void);
        ~Mutex(void);

        void    Lock(void);
        // Return true on failure
        bool    TryLock(void);
        void    Unlock(void);

    private:
        RecursiveLock _lock;
    };
}

#endif
