#ifndef CTRPLUGINFRAMEWORK_SYSTEM_LOCK_HPP
#define CTRPLUGINFRAMEWORK_SYSTEM_LOCK_HPP

#include "ctrulib/synchronization.h"

namespace CTRPluginFramework
{
    class Mutex;
    class Lock
    {
    public:
        explicit Lock(LightLock &llock);
        explicit Lock(RecursiveLock &rlock);
        explicit Lock(Mutex &mutex);

        ~Lock(void);

    private:
        int     _type;
        union
        {
            LightLock       *_llock;
            RecursiveLock   *_rlock;
            Mutex           *_mutex;
        };
    };
}

#endif
