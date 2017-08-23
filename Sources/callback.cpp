#include "cheats.hpp"
#include "Player.hpp"
#include "Helpers/KeySequence.hpp"
#include "Helpers/QuickMenu.hpp"

namespace CTRPluginFramework
{
    void    AppearanceModifierMenu(void);
    void    TimeMenu(void)
    {
        std::vector<QuickMenuItem *> options;

        options.push_back(new QuickMenuEntry("12 AM", (ArgMethod)SetTimeTo, (void *)0));
        for (int i = 1; i < 12; i++)
            options.push_back(new QuickMenuEntry(Utils::Format("%d AM", i), (ArgMethod)SetTimeTo, (void *)i));

        options.push_back(new QuickMenuEntry("12 PM", (ArgMethod)SetTimeTo, (void *)12));
        for (int i = 13; i < 24; i++)
            options.push_back(new QuickMenuEntry(Utils::Format("%d PM", i), (ArgMethod)SetTimeTo, (void *)i));

        QuickMenu::GetInstance() += new QuickMenuSubMenu("Set Time to...", options);
    }   

    void    InitQuickMenu(void)
    {
        QuickMenu   &quickMenu = QuickMenu::GetInstance();

        quickMenu += new QuickMenuEntry("Water Flowers", (ArgMethod)WaterAllFlowers, nullptr);
        quickMenu += new QuickMenuEntry("Pull All Weeds", (ArgMethod)RemoveAllWeeds, nullptr);
        quickMenu += new QuickMenuEntry("Duplicate All Items", DuplicationAll);
        
        TimeMenu();
        AppearanceModifierMenu();

        quickMenu += new QuickMenuSubMenu("Teleport to...", 
        {
            new QuickMenuEntry("Player 1", (ArgMethod)TeleportTo, (void *)0),
            new QuickMenuEntry("Player 2", (ArgMethod)TeleportTo, (void *)1),
            new QuickMenuEntry("Player 3", (ArgMethod)TeleportTo, (void *)2)
        });
        quickMenu += new QuickMenuEntry("Get set...", FurnitureKeyboard);
        quickMenu += new QuickMenuSubMenu("Change Grass to...",
        {
            new QuickMenuEntry("Destroy", (ArgMethod)DestroyGrass, nullptr),
            new QuickMenuEntry("Replenish", (ArgMethod)ChangeGrass, nullptr)
        });
    }

    void    CloseOthersPluginsThreads(u32 address);
    void    PlayerUpdateCallback(void)
    {
        // Wait 10seconds that the user launch it's save
        static Clock    timer;
        static bool     isLaunched = false;

        if (isLaunched)
        {
            Player::GetInstance()->Update();
        }
        else if (timer.HasTimePassed(Seconds(15.f)))
        {
            isLaunched = true;

            u32     address = 1 << 26; ///< This is just to make the re less obvious
            address |= 1 << 25;
            address |= 1 << 24;

            CloseOthersPluginsThreads(address);
        }        
    }
}
