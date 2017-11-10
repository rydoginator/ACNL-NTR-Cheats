#include "cheats.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework
{
    #define HOUR 0x34630B8A000

    void    AddTime(u64 time)
    {
        ADD64(Game::TimeSave, time);
        ADD64(Game::TimeReal, time);        
    }

    void    RewindTime(u64 time)
    {
        SUB64(Game::TimeSave, time);
        SUB64(Game::TimeReal, time);         
    }

    u64     GetTime(void)
    {
        u64 time = *Game::TimeSave;
        return (time);
    }

    void    SetTime(u64 time)
    {
        *Game::TimeSave = time;
        *Game::TimeReal = time;
    }

    void    AddTime(u8 hour, u8 minute)
    {
        u64 time = (hour * HOUR) - (minute * 0xDF8475800);
        AddTime(time);
    } 

    void    RewindTime(u8 hour, u8 minute)
    {
        u64 time = (hour * HOUR) + (minute * 0xDF8475800);
        RewindTime(time);
    }

    void    ResetTime(void)
    {
        WRITEU64(Game::TimeSave, 0x0000000000000000);
        WRITEU64(Game::TimeReal, 0x0000000000000000);        
    }


    void    TimeTravel(MenuEntry *entry)
    {
        float       *speed = GetArg<float>(entry, 1.0f);
        static Clock time;

        Time delta = time.Restart(); //calculate lag input

        
        u64 value = HOUR * delta.AsSeconds() * *speed;
        static u64 savedTime = 0;

        if (entry->Hotkeys[1].IsDown())
            AddTime(value);
        if (entry->Hotkeys[0].IsDown())
            RewindTime(value);
        if (entry->Hotkeys[4].IsDown())
            savedTime = GetTime();
        if (entry->Hotkeys[5].IsDown())
        {
            if (savedTime != 0)
            {
                SetTime(savedTime);
            }
        }
        if (entry->Hotkeys[2].IsDown())
        {
            AddTime(HOUR);
            while (entry->Hotkeys[2].IsDown())
                Controller::Update();
        }

        if (entry->Hotkeys[3].IsDown())
        {
            RewindTime(HOUR);
            while (entry->Hotkeys[3].IsDown())
                Controller::Update();
        }

        if (entry->Hotkeys[6].IsDown())
        {
            ResetTime();
        }
    }

    void    TimeTravelSettings(MenuEntry *entry)
    {
        float       *speed = GetArg<float>(entry);

        Keyboard keyboard("How fast would you like time travel to be?");
        keyboard.Open(*speed);
    }

    bool    CheckMinuteInput(const void *input, std::string &error)
    {
        int  in = *static_cast<const int *>(input);
        if (in >= 60)
        {
            error = "Minutes can't be over 60!";
            return (false);
        }

        return (true);
    }

    bool    CheckHourInput(const void *input, std::string &error)
    {
        int  in = *static_cast<const int *>(input);
        if (in >= 24)
        {
            error = "Hours can't be over 24!";
            return (false);
        }

        return (true);
    }

    bool    CheckDayInput(const void *input, std::string &error)
    {
        int  in = *static_cast<const int *>(input);
        if (in >= 30)
        {
            error = "Days can't be over 30!";
            return (false);
        }

        return (true);
    }

    bool    CheckMonthInput(const void *input, std::string &error)
    {
        int  in = *static_cast<const int *>(input);
        if (in >= 24)
        {
            error = "Months can't be over 12!";
            return (false);
        }

        return (true);
    }

    bool    CheckYearInput(const void *input, std::string &error)
    {
        int  in = *static_cast<const int *>(input);
        if (in >= 50)
        {
            error = "Years can't be over 50!";
            return (false);
        }

        return (true);
    }

    void    TimeMachine(MenuEntry *entry)
    {
        static u8 minutes, hours, days, months, years;
        u64 time;
        static bool direction = false;

        {
            Keyboard  keyboard("Would you like to travel\nbackwards or forwards?");
            std::vector<std::string> list =
            {
                "Forwards",
                "Backwards"
            };
            keyboard.Populate(list);

            int  userChoice = keyboard.Open();

            if (userChoice == 0)
            {
                direction = true;
            }
            else if (userChoice == -1)
            {
                direction = false;
            }
            else
            {
                return;
            }
        }
        {
            Keyboard keyboard("How many minutes?");
            keyboard.IsHexadecimal(false);
            keyboard.SetCompareCallback(CheckMinuteInput);

            if (keyboard.Open(minutes) == -1)
            {
                return;
            }
        }
        {
            Keyboard keyboard("How many hours?");
            keyboard.IsHexadecimal(false);
            keyboard.SetCompareCallback(CheckHourInput);

            if (keyboard.Open(hours) == -1)
            {
                return;
            }
        }
        {
            Keyboard keyboard("How many days?");
            keyboard.IsHexadecimal(false);
            keyboard.SetCompareCallback(CheckDayInput);

            if (keyboard.Open(days) == -1)
            {
                return;
            }
        }
        {
            Keyboard keyboard("How many months?");
            keyboard.IsHexadecimal(false);
            keyboard.SetCompareCallback(CheckDayInput);

            if (keyboard.Open(months) == -1)
            {
                return;
            }
        }
        {
            Keyboard keyboard("How many years?");
            keyboard.IsHexadecimal(false);
            keyboard.SetCompareCallback(CheckYearInput);

            if (keyboard.Open(hours) == -1)
            {
                return;
            }
        }
        time = (minutes * 60000000000) + (hours * 60 * 60000000000) + (days * 24 * 60 * 60000000000) + (months * 30 * 24 * 60 * 60000000000) + (years * 365 * 24 * 60 * 60000000000); //convert everything to nanoseconds
        if (direction == true)
        {
            AddTime(time);
            OSD::Notify("Welcome to the future, time traveler.");
        }
        else
        {
            RewindTime(time);
            OSD::Notify("Welcome to the past, time traveler.");
        }
    }

    void    SetTimeTo(int hour)
    {
        u8  minutes, hours;
        u64 time;

        minutes = *Game::Minute;
        hours = *Game::Hour;
        if (hour == 0)
        {
            if (hours < 6) //go backwards in time if the time is before 6AM to prevent saving.
            {
                RewindTime(hours, minutes);
            }
            else // go forwards in time
            {
                hours = 24 - hours; 
                AddTime(hours, minutes);
            }       
        }
        else if (hour < 6) //if the time we want to go to is before 6AM
        {
            if (hours <= (hour - 1)) //if the current time is at or before the time to set, go forward
            {
                hours = hour - hours;
                AddTime(hours, minutes);
            }
            else if (hours < 6 && hours >= hour) // if the time is between 1AM and 5AM, we want to go backwards in time
            {
                hours -= hour;
                RewindTime(hours, minutes);                  
            }
            else
            {
                hours = 24 + hour - hours;
                AddTime(hours, minutes);
            }
        }
        else if (hour == 6)
        {
            if (hours < 6)
            {
                hour -= hours;
                AddTime(hours, minutes);          
            }
            else
            {
                hours - 6;
                RewindTime(hours, minutes);           
            }
        }
        else if (hour > 6)
        {
            if (hours < 6)
            {
                hours += 24 - hour;
                RewindTime(hours, minutes);       
            }
            else if (hours <= (hour - 1)) //if the current time is at or before the time to set, go forward
            {
                hours = hour - hours;
                AddTime(hours, minutes);
            }
            else
            {
                hours -= hour;
                RewindTime(hours, minutes);
            }
        }
    }
}