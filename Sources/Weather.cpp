#include "cheats.hpp"

namespace CTRPluginFramework
{

    void WeatherMod(MenuEntry *entry)
    {
        static u8 weather = 0;
        static u8 Oldweather = 0;
        static bool btn = false;
        static bool active = false;
        static const StringVector Weathers = {"Clear", "Cloudy", "Dark Sky", "Light Rain", "Heavy Rain w/ T&L", "Light Snow", "Heavy Snow w/ Fog", "Invalid"};
        static const Color colours[] = {Color::Red, Color::Orange, Color::Yellow, Color::Green, Color::Blue, Color(75, 0, 130), Color(238, 130, 238), Color::White};

        static u32 offset = Game::Weather;

        if (entry->Hotkeys[1].IsDown() && !btn && active)
        {
            btn = true;
            weather++;
            if (weather > 7)
                weather = 0;
        }

        if (entry->Hotkeys[2].IsDown() && !btn && active)
        {
            btn = true;
            weather--;
            if (weather > 7) //Wraps to 0xFF, which is greater
                weather = 7;
        }

        if (entry->Hotkeys[0].IsDown() && !btn) //Controller::IsKeysDown(L + DPadLeft)
        {
            if (!active)
            {
                Process::Patch(offset, 0xE3A00000 | (weather & 0xFF));
                OSD::Notify("Weather Mod: Enabled!");
                OSD::Notify("Weather Mod: " << colours[weather] << "Set weather to " << Weathers[weather] << "!");
                active = true;
                btn = true;
            }

            else if (active)
            {
                Process::Patch(offset, 0xE1A00004);
                OSD::Notify("Weather Mod: Disabled!");
                active = false;
                btn = true;
            }
        }

        else if (!entry->Hotkeys[0].IsDown() && !entry->Hotkeys[1].IsDown() && !entry->Hotkeys[2].IsDown())
            btn = false;

        if (weather != Oldweather && active)
        {
            Oldweather = weather;
            Process::Patch(offset, 0xE3A00000 | (weather & 0xFF));
            OSD::Notify("Weather Mod: " << colours[weather] << "Set weather to " << Weathers[weather] << "!");
        }
    }

    void CherryBlossomMod(MenuEntry *entry)
    {
        static u16 amount = 0x3C;
        static u16 Oldamount = 0x3C;
        static bool btn = false;
        static bool active = false;
        static u32 offset = Game::CherryBlossom;

        if (entry->Hotkeys[1].IsDown() && !btn && active)
        {
            btn = true;
            amount += 10;
            if (amount > 0xFF)
                amount = 0;
        }

        if (entry->Hotkeys[2].IsDown() && !btn && active)
        {
            btn = true;
            amount -= 10;
            if (amount > 0xFF) //Wraps to 0xFF, which is greater
                amount = 0xFF;
        }

        if (entry->Hotkeys[0].IsDown() && !btn) //Controller::IsKeysDown(L + DPadLeft)
        {
            if (!active)
            {
                Process::Patch(offset, 0xE3A00001);
                Process::Patch(offset + 0x28, 0xE3A00001);
                Process::Patch(offset + 0x50, 0xE3A00004);
                Process::Patch(offset + 0x60, 0xE3A01001);
                Process::Patch(offset + 0x68, 0x93A00000 | (amount & 0xFF));
                OSD::Notify("Cherry Blossoms: " << Color::Green << "Enabled!");
                OSD::Notify(Format("Cherry Blossoms Mod: Current amount is %d!", amount));
                active = true;
                btn = true;
            }

            else if (active)
            {
                Process::Patch(offset, 0xE5960000);
                Process::Patch(offset + 0x28, 0xEB0E6479);
                Process::Patch(offset + 0x50, 0xE5DD0004);
                Process::Patch(offset + 0x60, 0xE2401007);
                Process::Patch(offset + 0x68, 0x93A0003C);
                OSD::Notify("Cherry Blossoms: " << Color::Red << "Disabled!");
                active = false;
                btn = true;
            }
        }

        else if (!entry->Hotkeys[0].IsDown() && !entry->Hotkeys[1].IsDown() && !entry->Hotkeys[2].IsDown())
            btn = false;

        if (amount != Oldamount && active)
        {
            Oldamount = amount;
            Process::Patch(offset + 0x68, 0x93A00000 | (amount & 0xFF));
            OSD::Notify(Format("Cherry Blossoms Mod: Set amount to %d!", amount));
        }
    }

    void ConfettiMod(MenuEntry *entry)
    {
        static u16 amount = 0x78;
        static u16 Oldamount = 0x78;
        static bool btn = false;
        static bool active = false;
        static u32 offset = Game::Confetti;

        if (entry->Hotkeys[1].IsDown() && !btn && active)
        {
            btn = true;
            amount += 10;
            if (amount > 0xFF)
                amount = 0;
        }

        if (entry->Hotkeys[2].IsDown() && !btn && active)
        {
            btn = true;
            amount -= 10;
            if (amount > 0xFF) //Wraps to 0xFF, which is greater
                amount = 0xFF;
        }

        if (entry->Hotkeys[0].IsDown() && !btn) //Controller::IsKeysDown(L + DPadLeft)
        {
            if (!active)
            {
                Process::Patch(offset, 0xE3A00001);
                Process::Patch(offset + 0x30, 0xE3A00000 | (amount & 0xFF));
                OSD::Notify("Confetti: " << Color::Green << "Enabled!");
                OSD::Notify(Format("Confetti Mod: Current amount is %d!", amount));
                active = true;
                btn = true;
            }

            else if (active)
            {
                Process::Patch(offset, 0xE5950000);
                Process::Patch(offset + 0x30, 0x13A00078);
                OSD::Notify("Confetti: " << Color::Red << "Disabled!");
                active = false;
                btn = true;
            }
        }

        else if (!entry->Hotkeys[0].IsDown() && !entry->Hotkeys[1].IsDown() && !entry->Hotkeys[2].IsDown())
            btn = false;

        if (amount != Oldamount && active)
        {
            Oldamount = amount;
            Process::Patch(offset + 0x30, 0xE3A00000 | (amount & 0xFF));
            OSD::Notify(Format("Confetti Mod: Set amount to %d!", amount));
        }
    }
}