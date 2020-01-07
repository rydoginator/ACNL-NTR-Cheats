#ifndef CTRPLUGINFRAMEWORK_SYSTEM_TASK_HPP
#define CTRPLUGINFRAMEWORK_SYSTEM_TASK_HPP

#include "types.h"
#include "ctrulib/synchronization.h"

namespace CTRPluginFramework
{
    using TaskFunc = s32 (*)(void *);

    struct TaskContext
    {
        int         refcount{0};
        u32         flags{0};
        s32         affinity{-1};
        s32         result{0};
        void *      arg{nullptr};
        TaskFunc    func{nullptr};
        LightEvent  event{};
    };

    struct Task
    {
        enum
        {
            Idle = 0,
            Scheduled = 1,
            Processing = 2,
            Finished = 4
        };

        enum
        {
            AppCore = 1 << 0,
            SysCore = 1 << 1,
            NewAppCore = 1 << 2,
            NewSysCore = 1 << 3,

            AppCores = AppCore | NewAppCore,
            SysCores = SysCore | NewSysCore,
            AllCores = AppCores | SysCores
        };

        TaskContext     *context;

        explicit Task(TaskFunc func, void *arg = nullptr, s32 affinity = -1);
        Task(const Task &task);
        Task(Task &&task) noexcept;
        ~Task(void);

        Task &operator=(const Task &right) = delete;

        /**
         * \brief Schedule a Task and starts it
         * \return 0 on operation success
         */
        int     Start(void) const;

        /**
         * \brief Wait for the Task to be completed
         * \return The result of the Task (returned by TaskFunc)
         */
        s32     Wait(void) const;

        /**
         * \brief Get the current status of the Task
         * \return Task status (see enum)
         */
        u32     Status(void) const;
    };
}

#endif
