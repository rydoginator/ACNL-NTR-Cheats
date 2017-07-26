#include "cheats.hpp"

#include "ctrulib/util/utf.h"

namespace CTRPluginFramework
{
    u32     g_find[100];
    u32     g_replace[100];
    int     g_i = 0;


    bool g_command = false;

    Player  *g_player = nullptr;

    void    Assign(void)
    {
        // Create a new Player object
        g_player = new Player();
        //...
    }    

    void    duplicationAll(void)
    {
        u32 item[15]; //store the entire inventory into an array so that we can check the contents of the inventory


        for (int i = 0; i < 15; i++)
        {
            g_player->ReadInventorySlot(i, item[i]);
        }

        for (int i = 0; i < 15; i++)
        {
            if (item[i] == 0x00007FFE) //check to see if the current index of the inventory is blank
                g_player->WriteInventorySlot(i, item[0]); //duplicate all the items from slot 0
        }
    }

    void 	GetSet(int set)
    {
    	u16 wallpaper[] = {0x234C, 0x234F, 0x234E,
    		0x2353, 0x2351, 0x2350, 0x2354,
    		0x2355, 0x2352, 0x2356, 0x234D,
    		0x2357, 0x23E9, 0x2358, 0x2359,
    		0x235A, 0x235B, 0x235C, 0x235D,
    		0x235E, 0x235F, 0x2360, 0x2361,
    		0x2362, 0x23B8, 0x23A7}; //put the wallpaper in an array with its index that corresponds to the set id
    	u16 item = (0x29df + (set * 11)); //there are 11 furniture items in each set

		switch (set)
		{
			case 26:
				g_player->WriteInventorySlot(0, 0x23DE);
				g_player->WriteInventorySlot(1, 0x2486);
				g_player->WriteInventorySlot(2, 0x2671);
				g_player->WriteInventorySlot(3, 0x26E8);
				g_player->WriteInventorySlot(4, 0x27DF);
				g_player->WriteInventorySlot(5, 0x287F);
				for (int i = 0; i < 8; i++)
				{
					g_player->WriteInventorySlot(i + 6, 0x3052 + i);
				}
				break;
			case 27:
				g_player->WriteInventorySlot(0, 0x23E1);
				g_player->WriteInventorySlot(1, 0x2489);
				g_player->WriteInventorySlot(2, 0x2673);
				g_player->WriteInventorySlot(3, 0x26EA);
				g_player->WriteInventorySlot(4, 0x279D);
				g_player->WriteInventorySlot(5, 0x27E1);
				g_player->WriteInventorySlot(6, 0x2881);
				for (int i = 0; i < 6; i++)
				{
					g_player->WriteInventorySlot(i + 7, 0x3066 + i);
				}
				g_player->WriteInventorySlot(13, 0x339D);
				break;
			case 28:
				g_player->WriteInventorySlot(0, 0x23E2);
				g_player->WriteInventorySlot(1, 0x248A);
				g_player->WriteInventorySlot(2, 0x266F);
				g_player->WriteInventorySlot(3, 0x2675);
				g_player->WriteInventorySlot(4, 0x27E3);
				g_player->WriteInventorySlot(5, 0x2882);
				for (int i = 0; i < 6; i++)
				{
					g_player->WriteInventorySlot(6 + i, 0x306C + i);
				}
				break;
			case 29:
				g_player->WriteInventorySlot(0, 0x23DF);
				g_player->WriteInventorySlot(1, 0x2487);
				g_player->WriteInventorySlot(2, 0x2672);
				g_player->WriteInventorySlot(3, 0x26E9);
				g_player->WriteInventorySlot(4, 0x27E0);
				g_player->WriteInventorySlot(5, 0x2880);
				g_player->WriteInventorySlot(6, 0x2880);
				for (int i = 0; i < 6; i++)
				{
					g_player->WriteInventorySlot(7 + i, 0x3059 + i);
				}
				break;
			case 30:
				g_player->WriteInventorySlot(0, 0x23E3);
				g_player->WriteInventorySlot(1, 0x248B);
				g_player->WriteInventorySlot(2, 0x2773);
				g_player->WriteInventorySlot(3, 0x279E);
				g_player->WriteInventorySlot(4, 0x27E4);
				g_player->WriteInventorySlot(5, 0x2670);
				g_player->WriteInventorySlot(6, 0x2883);
				for (int i = 0; i < 5; i++)
				{
					g_player->WriteInventorySlot(7 + i, 0x3072 + i);
				}
				break;
			case 31:
				g_player->WriteInventorySlot(0, 0x23E0);
				g_player->WriteInventorySlot(1, 0x2488);
				g_player->WriteInventorySlot(2, 0x2674);
				g_player->WriteInventorySlot(3, 0x26EB);
				g_player->WriteInventorySlot(4, 0x27E2);
				g_player->WriteInventorySlot(5, 0x28F2);
				for (int i = 0; i < 7; i++)
				{
					g_player->WriteInventorySlot(6 + i, 0x305F + i);
				}
				break;
			case 32:
				g_player->WriteInventorySlot(0, 0x23B3);
				g_player->WriteInventorySlot(1, 0x244F);
				for (int i = 0; i < 11; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2DC3 + i);
				}
				break;
			case 33:
				for (int i = 0; i < 9; i++)
				{
					g_player->WriteInventorySlot(i, 0x26EE + i);
				}
				g_player->WriteInventorySlot(10, 0x26ED);
				break;
			case 34:
				g_player->WriteInventorySlot(0, 0x23CA);
				g_player->WriteInventorySlot(1, 0x2463);
				g_player->WriteInventorySlot(2, 0x25C4);
				g_player->WriteInventorySlot(3, 0x25EC);
				g_player->WriteInventorySlot(4, 0x2D2F);
				g_player->WriteInventorySlot(5, 0x2D52);
				g_player->WriteInventorySlot(6, 0x2EC9);
				g_player->WriteInventorySlot(7, 0x2ECA);
				g_player->WriteInventorySlot(8, 0x2ECB);
				g_player->WriteInventorySlot(9, 0x2ECC);
				g_player->WriteInventorySlot(10, 0x2ECD);
				break;
			case 35:
				g_player->WriteInventorySlot(0, 0x2ECE);
				g_player->WriteInventorySlot(1, 0x2ECF);
				g_player->WriteInventorySlot(2, 0x2FF9);
				for (int i = 0; i < 6; i++)
				{
					g_player->WriteInventorySlot(3 + i, 0x3028 + i);
				}
				g_player->WriteInventorySlot(9, 0x3099);
				g_player->WriteInventorySlot(10, 0x309A);
				break;
			case 36:
				g_player->WriteInventorySlot(0, 0x23AE);
				g_player->WriteInventorySlot(1, 0x244C);
				for (int i = 0; i < 0xB; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2E10 + i);
				}
				break;
			case 37:
				for (int i = 0; i < 4; i++)
				{
					g_player->WriteInventorySlot(i, 0x2E3E + i);
				}
				g_player->WriteInventorySlot(5, 0x2C79);
				g_player->WriteInventorySlot(6, 0x2E42);
				break;
			case 38:
				g_player->WriteInventorySlot(0, 0x23B1);
				g_player->WriteInventorySlot(1, 0x244A);
				for (int i = 0; i < 11; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2D81 + i);
				}
				break;
			case 39:
				g_player->WriteInventorySlot(0, 0x23A3);
				g_player->WriteInventorySlot(1, 0x2440);
				for (int i = 0; i < 8; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2B4E + i);
				}
				break;
			case 40:
				for (int i = 0; i < 13; i++)
				{
					g_player->WriteInventorySlot(i, 0x292F + i);
				}
				break;
			case 41:
				for (int i = 0; i < 15; i++)
				{
					g_player->WriteInventorySlot(i, 0x293C + i);
				}
				break;
			case 42:
				for (int i = 0; i < 16; i++)
				{
					g_player->WriteInventorySlot(i, 0x294B + i);
				}
				break;
			case 43:
				g_player->WriteInventorySlot(0, 0x23E8);
				g_player->WriteInventorySlot(1, 0x2490);
				g_player->WriteInventorySlot(2, 0x267b);
				g_player->WriteInventorySlot(3, 0x2775);
				g_player->WriteInventorySlot(4, 0x2884);
				g_player->WriteInventorySlot(5, 0x309D);
				g_player->WriteInventorySlot(6, 0x309E);
				g_player->WriteInventorySlot(7, 0x309F);
				g_player->WriteInventorySlot(8, 0x30A0);
				g_player->WriteInventorySlot(9, 0x30A1);
				break;
			case 44:
				g_player->WriteInventorySlot(0, 0x23BA);
				g_player->WriteInventorySlot(1, 0x2455);
				g_player->WriteInventorySlot(2, 0x286C);
				for (int i = 0; i < 11; i++)
				{
					g_player->WriteInventorySlot(3 + i, 0x2E89 + i);
				}
				break;
			case 45:
				g_player->WriteInventorySlot(0, 0x23BB);
				g_player->WriteInventorySlot(1, 0x2456);
				g_player->WriteInventorySlot(2, 0x2def);
				for (int i = 0; i < 10; i++)
				{
					g_player->WriteInventorySlot(3 + i, 0x2DF0 + i);
				}
				break;
			case 46:
				g_player->WriteInventorySlot(0, 0x23B0);
				g_player->WriteInventorySlot(1, 0x245C);
				for (int i = 0; i < 11; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2DD9 + i);
				}
				break;
			case 47:
				g_player->WriteInventorySlot(0, 0x23B7);
				g_player->WriteInventorySlot(1, 0x245D);
				for (int i = 0; i < 11; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2DE4 + i);
				}
				break;
			case 48:
				g_player->WriteInventorySlot(0, 0x23AD);
				g_player->WriteInventorySlot(1, 0x244B);
				for (int i = 0; i < 11; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2DCE + i);
				}
				break;
			case 49:
				g_player->WriteInventorySlot(0, 0x23B4);
				g_player->WriteInventorySlot(1, 0x2450);
				for (int i = 0; i < 11; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2DAD + i);
				}
				break;
			case 50:
				g_player->WriteInventorySlot(0, 0x23B2);
				g_player->WriteInventorySlot(1, 0x244E);
				for (int i = 0; i < 11; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2BD8 + i);
				}
				break;
			case 51:
				g_player->WriteInventorySlot(0, 0x23B6);
				g_player->WriteInventorySlot(1, 0x2452);
				for (int i = 0; i < 11; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2E05 + i);
				}
				break;
			case 52:
				g_player->WriteInventorySlot(0, 0x23B5);
				g_player->WriteInventorySlot(1, 0x2451);
				for (int i = 0; i < 11; i++)
				{
					g_player->WriteInventorySlot(2 + i, 0x2DFA + i);
				}
				break;
			default:
				if (set < 26) //prevent typing in numbers that are outside of the case
				{
					for (int i = 0; i < 11; i++)
					{
						g_player->WriteInventorySlot(i, item + i);
					}
					g_player->WriteInventorySlot(11, wallpaper[set]);
					g_player->WriteInventorySlot(12, wallpaper[set] + 0x9F);
				}
				break;

			}
    }

    void 	FurnitureKeyboard(void)
    {
    	Keyboard keyboard("Which set would you like?");
    	std::vector<std::string> list =
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