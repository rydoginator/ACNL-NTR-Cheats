#include "cheats.hpp"

#include "ctrulib/util/utf.h"

namespace CTRPluginFramework
{
    u32     g_find[100];
    u32     g_replace[100];
    int     g_i = 0;


    bool g_command = false;

    void    duplicationAll(void)
    {
        u32     item[15]; //store the entire inventory into an array so that we can check the contents of the inventory
        Player  *player = Player::GetInstance();

        for (int i = 0; i < 15; i++)
        {
            player->ReadInventorySlot(i, item[i]);
        }

        for (int i = 0; i < 15; i++)
        {
            if (item[i] == 0x00007FFE) //check to see if the current index of the inventory is blank
                player->WriteInventorySlot(i, item[0]); //duplicate all the items from slot 0
        }
    }

    void 	GetSet(int set)
    {
    	static const u16 wallpaper[] = 
        {
            0x234C, 0x234F, 0x234E,
    		0x2353, 0x2351, 0x2350, 0x2354,
    		0x2355, 0x2352, 0x2356, 0x234D,
    		0x2357, 0x23E9, 0x2358, 0x2359,
    		0x235A, 0x235B, 0x235C, 0x235D,
    		0x235E, 0x235F, 0x2360, 0x2361,
    		0x2362, 0x23B8, 0x23A7
        }; // put the wallpaper in an array with its index that corresponds to the set id
    	
        u16     item = (0x29df + (set * 11)); //there are 11 furniture items in each set
        Player  *player = Player::GetInstance();

		switch (set)
		{
			case 26:
				player->WriteInventorySlot(0, 0x23DE);
				player->WriteInventorySlot(1, 0x2486);
				player->WriteInventorySlot(2, 0x2671);
				player->WriteInventorySlot(3, 0x26E8);
				player->WriteInventorySlot(4, 0x27DF);
				player->WriteInventorySlot(5, 0x287F);
				for (int i = 0; i < 8; i++)
				{
					player->WriteInventorySlot(i + 6, 0x3052 + i);
				}
				break;
			case 27:
				player->WriteInventorySlot(0, 0x23E1);
				player->WriteInventorySlot(1, 0x2489);
				player->WriteInventorySlot(2, 0x2673);
				player->WriteInventorySlot(3, 0x26EA);
				player->WriteInventorySlot(4, 0x279D);
				player->WriteInventorySlot(5, 0x27E1);
				player->WriteInventorySlot(6, 0x2881);
				for (int i = 0; i < 6; i++)
				{
					player->WriteInventorySlot(i + 7, 0x3066 + i);
				}
				player->WriteInventorySlot(13, 0x339D);
				break;
			case 28:
				player->WriteInventorySlot(0, 0x23E2);
				player->WriteInventorySlot(1, 0x248A);
				player->WriteInventorySlot(2, 0x266F);
				player->WriteInventorySlot(3, 0x2675);
				player->WriteInventorySlot(4, 0x27E3);
				player->WriteInventorySlot(5, 0x2882);
				for (int i = 0; i < 6; i++)
				{
					player->WriteInventorySlot(6 + i, 0x306C + i);
				}
				break;
			case 29:
				player->WriteInventorySlot(0, 0x23DF);
				player->WriteInventorySlot(1, 0x2487);
				player->WriteInventorySlot(2, 0x2672);
				player->WriteInventorySlot(3, 0x26E9);
				player->WriteInventorySlot(4, 0x27E0);
				player->WriteInventorySlot(5, 0x2880);
				player->WriteInventorySlot(6, 0x2880);
				for (int i = 0; i < 6; i++)
				{
					player->WriteInventorySlot(7 + i, 0x3059 + i);
				}
				break;
			case 30:
				player->WriteInventorySlot(0, 0x23E3);
				player->WriteInventorySlot(1, 0x248B);
				player->WriteInventorySlot(2, 0x2773);
				player->WriteInventorySlot(3, 0x279E);
				player->WriteInventorySlot(4, 0x27E4);
				player->WriteInventorySlot(5, 0x2670);
				player->WriteInventorySlot(6, 0x2883);
				for (int i = 0; i < 5; i++)
				{
					player->WriteInventorySlot(7 + i, 0x3072 + i);
				}
				break;
			case 31:
				player->WriteInventorySlot(0, 0x23E0);
				player->WriteInventorySlot(1, 0x2488);
				player->WriteInventorySlot(2, 0x2674);
				player->WriteInventorySlot(3, 0x26EB);
				player->WriteInventorySlot(4, 0x27E2);
				player->WriteInventorySlot(5, 0x28F2);
				for (int i = 0; i < 7; i++)
				{
					player->WriteInventorySlot(6 + i, 0x305F + i);
				}
				break;
			case 32:
				player->WriteInventorySlot(0, 0x23B3);
				player->WriteInventorySlot(1, 0x244F);
				for (int i = 0; i < 11; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2DC3 + i);
				}
				break;
			case 33:
				for (int i = 0; i < 9; i++)
				{
					player->WriteInventorySlot(i, 0x26EE + i);
				}
				player->WriteInventorySlot(10, 0x26ED);
				break;
			case 34:
				player->WriteInventorySlot(0, 0x23CA);
				player->WriteInventorySlot(1, 0x2463);
				player->WriteInventorySlot(2, 0x25C4);
				player->WriteInventorySlot(3, 0x25EC);
				player->WriteInventorySlot(4, 0x2D2F);
				player->WriteInventorySlot(5, 0x2D52);
				player->WriteInventorySlot(6, 0x2EC9);
				player->WriteInventorySlot(7, 0x2ECA);
				player->WriteInventorySlot(8, 0x2ECB);
				player->WriteInventorySlot(9, 0x2ECC);
				player->WriteInventorySlot(10, 0x2ECD);
				break;
			case 35:
				player->WriteInventorySlot(0, 0x2ECE);
				player->WriteInventorySlot(1, 0x2ECF);
				player->WriteInventorySlot(2, 0x2FF9);
				for (int i = 0; i < 6; i++)
				{
					player->WriteInventorySlot(3 + i, 0x3028 + i);
				}
				player->WriteInventorySlot(9, 0x3099);
				player->WriteInventorySlot(10, 0x309A);
				break;
			case 36:
				player->WriteInventorySlot(0, 0x23AE);
				player->WriteInventorySlot(1, 0x244C);
				for (int i = 0; i < 0xB; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2E10 + i);
				}
				break;
			case 37:
				for (int i = 0; i < 4; i++)
				{
					player->WriteInventorySlot(i, 0x2E3E + i);
				}
				player->WriteInventorySlot(5, 0x2C79);
				player->WriteInventorySlot(6, 0x2E42);
				break;
			case 38:
				player->WriteInventorySlot(0, 0x23B1);
				player->WriteInventorySlot(1, 0x244A);
				for (int i = 0; i < 11; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2D81 + i);
				}
				break;
			case 39:
				player->WriteInventorySlot(0, 0x23A3);
				player->WriteInventorySlot(1, 0x2440);
				for (int i = 0; i < 8; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2B4E + i);
				}
				break;
			case 40:
				for (int i = 0; i < 13; i++)
				{
					player->WriteInventorySlot(i, 0x292F + i);
				}
				break;
			case 41:
				for (int i = 0; i < 15; i++)
				{
					player->WriteInventorySlot(i, 0x293C + i);
				}
				break;
			case 42:
				for (int i = 0; i < 16; i++)
				{
					player->WriteInventorySlot(i, 0x294B + i);
				}
				break;
			case 43:
				player->WriteInventorySlot(0, 0x23E8);
				player->WriteInventorySlot(1, 0x2490);
				player->WriteInventorySlot(2, 0x267b);
				player->WriteInventorySlot(3, 0x2775);
				player->WriteInventorySlot(4, 0x2884);
				player->WriteInventorySlot(5, 0x309D);
				player->WriteInventorySlot(6, 0x309E);
				player->WriteInventorySlot(7, 0x309F);
				player->WriteInventorySlot(8, 0x30A0);
				player->WriteInventorySlot(9, 0x30A1);
				break;
			case 44:
				player->WriteInventorySlot(0, 0x23BA);
				player->WriteInventorySlot(1, 0x2455);
				player->WriteInventorySlot(2, 0x286C);
				for (int i = 0; i < 11; i++)
				{
					player->WriteInventorySlot(3 + i, 0x2E89 + i);
				}
				break;
			case 45:
				player->WriteInventorySlot(0, 0x23BB);
				player->WriteInventorySlot(1, 0x2456);
				player->WriteInventorySlot(2, 0x2def);
				for (int i = 0; i < 10; i++)
				{
					player->WriteInventorySlot(3 + i, 0x2DF0 + i);
				}
				break;
			case 46:
				player->WriteInventorySlot(0, 0x23B0);
				player->WriteInventorySlot(1, 0x245C);
				for (int i = 0; i < 11; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2DD9 + i);
				}
				break;
			case 47:
				player->WriteInventorySlot(0, 0x23B7);
				player->WriteInventorySlot(1, 0x245D);
				for (int i = 0; i < 11; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2DE4 + i);
				}
				break;
			case 48:
				player->WriteInventorySlot(0, 0x23AD);
				player->WriteInventorySlot(1, 0x244B);
				for (int i = 0; i < 11; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2DCE + i);
				}
				break;
			case 49:
				player->WriteInventorySlot(0, 0x23B4);
				player->WriteInventorySlot(1, 0x2450);
				for (int i = 0; i < 11; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2DAD + i);
				}
				break;
			case 50:
				player->WriteInventorySlot(0, 0x23B2);
				player->WriteInventorySlot(1, 0x244E);
				for (int i = 0; i < 11; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2BD8 + i);
				}
				break;
			case 51:
				player->WriteInventorySlot(0, 0x23B6);
				player->WriteInventorySlot(1, 0x2452);
				for (int i = 0; i < 11; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2E05 + i);
				}
				break;
			case 52:
				player->WriteInventorySlot(0, 0x23B5);
				player->WriteInventorySlot(1, 0x2451);
				for (int i = 0; i < 11; i++)
				{
					player->WriteInventorySlot(2 + i, 0x2DFA + i);
				}
				break;
			default:
				if (set < 26) //prevent typing in numbers that are outside of the case
				{
					for (int i = 0; i < 11; i++)
					{
						player->WriteInventorySlot(i, item + i);
					}
					player->WriteInventorySlot(11, wallpaper[set]);
					player->WriteInventorySlot(12, wallpaper[set] + 0x9F);
				}
				break;

			}
    }

    void 	FurnitureKeyboard(void)
    {
    	Keyboard keyboard("Which set would you like ?");
    	static std::vector<std::string> list =
    	{
			"Exotic Set",
			"Ranch Set",
			"Classic Set",
			"Regal Set",
			"Blue Set",
			"Cabana Set",
			"Green Set",
			"Cabin Set",
			"Modern Set",
			"Kiddie Set",
			"Lovely Set",
			"Robo Set",
			"Polka-dot Set",
			"Snowman Set",
			"Mush Set",
			"Pave Set",
			"Egg Set",
			"Spoopy Set",
			"Harvest Set",
			"Jingle Set",
			"Princess Set",
			"Gracie Set",
			"Sweets Set",
			"Gorgeous Set",
			"Minimalist Set",
			"Golden Set",
			"Hello Kitty Set",
			"Kiki and Lala Set",
			"Cinamonroll Set",
			"My Melody Set",
			"Kerokerokeroppi Set",
			"Pompompurin Set",
			"Mermaid Set",
			"Wet Suits",
			"7 - 11 part 1",
			"7 - 11 part 2",
			"Sloppy Set",
			"Cardboard Set",
			"Insect Set",
			"Creepy Set",
			"Tulips and Pansies",
			"Cosmos and Roses",
			"Other Flowers",
			"Fueki Set",
			"balloon Set",
			"Astro Set",
			"Rococo Set",
			"Alpine Set",
			"Ice Set",
			"Sleek Set"
			"Modern Wood Set",
			"Stripe Set",
			"Card Set"
    	};
    	keyboard.Populate(list);
    	int userChoice = keyboard.Open();

    	if (userChoice != -1)
    	{
    		GetSet(userChoice);
    	}
    }
}