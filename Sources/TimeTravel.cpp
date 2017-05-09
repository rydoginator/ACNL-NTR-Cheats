#include "cheats.hpp"

namespace CTRPluginFramework
{
    void    TimeTravel(MenuEntry *entry)
    {
        if (Controller::IsKeysDown(R + DPadRight))
        {
            ADD64(Game::TimeSave, 0x9EF21AA);
            ADD64(Game::TimeReal, 0x9EF21AA);
        }
        if (Controller::IsKeysDown(R + DPadLeft))
        {
            SUB64(Game::TimeSave, 0x9EF21AA);
            SUB64(Game::TimeReal, 0x9EF21AA);
        }
        if (!Controller::IsKeyDown(Key::B))
            return;
        if (Controller::IsKeyPressed(Key::DPadRight))
        {
            ADD64(Game::TimeSave, 0x34630B8A000);
            ADD64(Game::TimeReal, 0x34630B8A000);
        }
        if (Controller::IsKeyPressed(Key::DPadLeft))
        {
            SUB64(Game::TimeSave, 0x34630B8A000);
            SUB64(Game::TimeReal, 0x34630B8A000);
        }
        if (Controller::IsKeyPressed(Key::DPadDown))
        {
            WRITEU64(Game::TimeSave, 0x0000000000000000);
            WRITEU64(Game::TimeReal, 0x0000000000000000);
        }
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

        if (Controller::IsKeysDown(Y + DPadRight))
        {
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
                ADD64(Game::TimeReal, time);
                ADD64(Game::TimeSave, time);
                OSD::Notify("Welcome to the future, time traveler.");
            }
            else
            {
                SUB64(Game::TimeReal, time);
                SUB64(Game::TimeSave, time);
                OSD::Notify("Welcome to the past, time traveler.");
            }
        }
    }
}