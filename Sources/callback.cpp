#include "cheats.hpp"
#include "Player.hpp"
#include "Helpers/KeySequence.hpp"
#include "Helpers/QuickMenu.hpp"

namespace CTRPluginFramework
{
    void    AppearanceModifierMenu(void);
    static inline void    TimeMenu(void)
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
        quickMenu += new QuickMenuEntry("Clear Inventory", ClearInv);


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

    void    PlayerUpdateCallback(void)
    {
        Player::GetInstance()->Update();
    }
}
