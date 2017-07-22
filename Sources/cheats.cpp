#include "cheats.hpp"
#include <cstring>
#include <stdio.h>
#include "ctrulib/util/utf.h"

namespace CTRPluginFramework
{
    u32     g_location;
    u32     g_indoor_pos_x;
    u32     g_indoor_pos_y;
    u32     g_indoor_pos_z;
    u32     g_outdoor_pos_x;
    u32     g_outdoor_pos_y;
    u32     g_outdoor_pos_z;
    u32     g_town_items;
    u32     g_island_items;
    u32     g_playerId;
    u32     g_playerPointer;
    u32     g_inv;
    u32     g_velocity;
    u32     g_grass_start;
    u32     g_grass_end;
    u32     g_leif;
    u32     g_tan;
    u32     g_edible;
    u32     g_seed;
    u32     g_id;
    u32     g_realtime;
    u32     g_savetime;
    u32     g_world_x;
    u32     g_world_y;
    u32     g_input_text_buffer;
    u32     g_hours;
    u32     g_minutes;
    u32     g_visitor_indoor_x;
    u32     g_visitor_indoor_z;
    u32     g_visitor_outdoor_x;
    u32     g_visitor_outdoor_z;
    u32     g_visitor1_indoor_x;
    u32     g_visitor1_indoor_z;
    u32     g_visitor1_outdoor_x;
    u32     g_visitor1_outdoor_z;
    u32     g_visitor2_indoor_x;
    u32     g_visitor2_indoor_z;
    u32     g_visitor2_outdoor_x;
    u32     g_visitor2_outdoor_z;
    u32     g_keyboard;
    u32     g_island_bubble;
    u32     g_island_keyboard;
    u32     g_abd;
    u32     g_walkOver;
    u32     g_kpointer;
    u32     g_confirm;
    u32     g_nook1Price;
    u32     g_nook2Price;
    u32     g_room;
    u32     g_isabelle;
    u32     g_kappn;
    u32     g_npc;
    u32     g_badge;
    u32     g_collision;
    u32     g_turnip;
    u32     g_main_x;
    u32     g_main_y;
    u32     g_main_items;
    u32     g_in_cond;
    u32     g_out_cond;
    u32     g_in_col;
    u32     g_out_col;
    u32     g_quick;
    u32     g_out_grav;
    u32     g_medals;
    u32     g_camera_asm;
    u32     g_camera_x;
    u32     g_camera_y;
    u32     g_camera_z;
    u32     g_camera_pointer;
    u32     g_camstop_pointer;
    u32     g_coordinates_pointer;
    u32     g_thought;
    u32     g_club_items;
    u32     g_building_addr;
    u32     g_garden;
    u32     g_gender;
    u32     g_name;

    u32     g_find[100];
    u32     g_replace[100];
    int     g_i = 0;


    bool g_command = false;
    // Function to assign our aesses

    void    assign_region(Region region)
    {
        extern Region   g_region;
        g_region = region;

        g_location = USA_LOCATION_ADDR;
        g_indoor_pos_x = USA_INDOOR_POS_X_ADDR;
        g_indoor_pos_y = USA_INDOOR_POS_Y_ADDR;
        g_indoor_pos_z = USA_INDOOR_POS_Z_ADDR;
        g_outdoor_pos_x = USA_OUTDOOR_POS_X_ADDR;
        g_outdoor_pos_y = USA_OUTDOOR_POS_Y_ADDR;
        g_outdoor_pos_z = USA_OUTDOOR_POS_Z_ADDR;
        g_town_items = USA_TOWN_ITEMS_ADDR;
        g_island_items = USA_ISLAND_ITEMS_ADDR;
        g_playerId = USA_PLAYER_ADDR;
        g_inv = USA_INV_ADDR;
        g_velocity = USA_VELOCITY_ADDR;
        g_grass_start = USA_GRASS_START_ADDR;
        g_grass_end = USA_GRASS_END_ADDR;
        g_leif = USA_LEIF_ADDR;
        g_tan = USA_TAN_ADDR;
        g_edible = USA_EDIBLE_ADDR;
        g_seed = USA_SEED_ADDR;
        g_id = USA_ID_ADDR;
        g_savetime = USA_SAVETIME_ADDR;
        g_realtime = USA_REALTIME_ADDR;
        g_world_x = USA_WORLD_X_ADDR;
        g_world_y = USA_WORLD_Y_ADDR;
        g_hours = USA_HOURS_ADDR;
        g_minutes = USA_MINUTES_ADDR;
        g_visitor_outdoor_x = USA_VISITOR_OUTDOOR_X_ADDR;
        g_visitor_outdoor_z = USA_VISITOR_OUTDOOR_Z_ADDR;
        g_visitor_indoor_x = USA_VISITOR_INDOOR_X_ADDR;
        g_visitor_indoor_z = USA_VISITOR_INDOOR_Z_ADDR;
        g_visitor1_outdoor_x = USA_VISITOR1_OUTDOOR_X_ADDR;
        g_visitor1_outdoor_z = USA_VISITOR1_OUTDOOR_Z_ADDR;
        g_visitor1_indoor_x = USA_VISITOR1_INDOOR_X_ADDR;
        g_visitor1_indoor_z = USA_VISITOR1_INDOOR_Z_ADDR;
        g_visitor2_outdoor_x = USA_VISITOR2_OUTDOOR_X_ADDR;
        g_visitor2_outdoor_z = USA_VISITOR2_OUTDOOR_Z_ADDR;
        g_visitor2_indoor_x = USA_VISITOR2_INDOOR_X_ADDR;
        g_visitor2_indoor_z = USA_VISITOR2_INDOOR_Z_ADDR;
        g_keyboard = USA_KEYBOARD_ADDR;
        g_island_keyboard = USA_KEYBOARD_ISLAND_ADDR;
        g_island_bubble = USA_INPUT_TEXT_ISLAND_ADDR;
        g_abd = USA_ABD_ADDR;
        g_walkOver = USA_WALKOVER_ADDR;
        g_kpointer = USA_KEYBOARD_POINTER;
        g_confirm = USA_CONFIRM_BOOL_ADDR;
        g_nook1Price = USA_NOOKLING1_PRICE_ADDR;
        g_nook2Price = USA_NOOKLING2_PRICE_ADDR;
        g_room = USA_ROOM_ID_ADDR;
        g_isabelle = USA_ISABELLE_ADDR;
        g_kappn = USA_KAPPN_ADDR;
        g_npc = USA_NPC_ADDR;
        g_badge = USA_BADGE_ADDR;
        g_turnip = USA_TURNIP_ADDR;
        g_main_x = USA_MAINSTREET_X;
        g_main_y = USA_MAINSTREET_Y;
        g_main_items = USA_MAINSTREET_ITEMS;
        g_in_cond = USA_CONDITIONAL_IN_ADDR;
        g_out_cond = USA_CONDITIONAL_OUT_ADDR;
        g_in_col = USA_COLLISION_IN_ADDR;
        g_out_col = USA_COLLISION_OUT_ADDR;
        g_quick = USA_QUICKFIRE_ADDR;
        g_out_grav = USA_GRAVITY_OUT_ADDR;
        g_medals = USA_MEDALS_ADDR;
        g_camera_asm = USA_CAMERA_ASM_ADDR;
        g_camera_x = USA_CAMERA_X_ADDR;
        g_camera_y = USA_CAMERA_Y_ADDR;
        g_camera_z = USA_CAMERA_Z_ADDR;
        g_camera_pointer = USA_CAMERA_POINTER;
        g_camstop_pointer = USA_CAMSTOP_POINTER;
        g_coordinates_pointer = USA_COORDINATES_POINTER;
        g_thought = USA_THOUGHT_ADDR;
        g_club_items = USA_CLUB_ADDR;
        g_building_addr = USA_BUILDING_ADDR;
        g_garden = USA_GARDEN;
        g_gender = USA_GENDER_ADDR;
        g_name = USA_NAME_ADDR;
        g_playerPointer = USA_PLAYER_POINTER;

        // applying offset or particular aess
        switch (region)
        {
            case USA:
                g_input_text_buffer = USA_INPUT_TEXT_ADDR;
                break;
            case EUR:
                g_location -= EUR_DIFFERENCE;
                g_indoor_pos_x -= EUR_DIFFERENCE;
                g_indoor_pos_y -= EUR_DIFFERENCE;
                g_indoor_pos_z -= EUR_DIFFERENCE;
                g_outdoor_pos_x -= EUR_DIFFERENCE;
                g_outdoor_pos_y -= EUR_DIFFERENCE;
                g_outdoor_pos_z -= EUR_DIFFERENCE;
                g_town_items -= EUR_DIFFERENCE;
                g_island_items -= EUR_DIFFERENCE;
                g_inv -= EUR_DIFFERENCE;
                g_grass_start -= EUR_DIFFERENCE;
                g_grass_end -= EUR_DIFFERENCE;
                g_velocity -= EUR_DIFFERENCE;
                g_leif -= EUR_DIFFERENCE;
                g_tan -= EUR_DIFFERENCE;
                g_edible -= EUR_DIFFERENCE;
                g_id -= EUR_DIFFERENCE;
                g_savetime -= EUR_DIFFERENCE;
                g_world_x -= EUR_DIFFERENCE;
                g_world_y -= EUR_DIFFERENCE;
                g_hours = 0x9505B7;
                g_minutes = 0x9505B6;
                g_realtime = 0x95c500;
                g_seed = 0x9B4268;
                g_playerId = 0xAAD990;
                g_visitor_indoor_x -= EUR_DIFFERENCE;
                g_visitor_indoor_z -= EUR_DIFFERENCE;
                g_visitor_outdoor_x -= EUR_DIFFERENCE;
                g_visitor_outdoor_z -= EUR_DIFFERENCE;
                g_visitor1_indoor_x -= EUR_DIFFERENCE;
                g_visitor1_indoor_z -= EUR_DIFFERENCE;
                g_visitor1_outdoor_x -= EUR_DIFFERENCE;
                g_visitor1_outdoor_z -= EUR_DIFFERENCE;
                g_visitor2_indoor_x -= EUR_DIFFERENCE;
                g_visitor2_indoor_z -= EUR_DIFFERENCE;
                g_visitor2_outdoor_x -= EUR_DIFFERENCE;
                g_visitor2_outdoor_z -= EUR_DIFFERENCE;
                g_keyboard -= EUR_DIFFERENCE;
                g_island_bubble -= EUR_DIFFERENCE;
                g_island_keyboard = EUR_KEYBOAD_ISLAND_ADDR;
                g_abd -= EUR_DIFFERENCE;
                g_walkOver -= EUR_DIFFERENCE;
                g_input_text_buffer = EUR_INPUT_TEXT_ADDR;
                g_nook1Price -= EUR_DIFFERENCE;
                g_nook2Price -= EUR_DIFFERENCE;
                g_room = EUR_ROOM_ID_ADDR;
                g_isabelle -= EUR_DIFFERENCE;
                g_kappn -= EUR_DIFFERENCE;
                g_npc = EUR_NPC_ADDR;
                g_badge -= EUR_DIFFERENCE;
                g_turnip -= EUR_DIFFERENCE;
                g_main_x -= EUR_DIFFERENCE;
                g_main_y -= EUR_DIFFERENCE;
                g_main_items -= EUR_DIFFERENCE;
                g_in_cond -= EUR_DIFFERENCE;
                g_out_cond -= EUR_DIFFERENCE;
                g_in_col -= EUR_DIFFERENCE;
                g_out_col -= EUR_DIFFERENCE;
                g_quick -= EUR_DIFFERENCE;
                g_out_grav -= EUR_DIFFERENCE;
                g_medals -= EUR_DIFFERENCE;
                g_camera_asm = EUR_CAMERA_ASM_ADDR;
                g_camera_x = EUR_CAMERA_X_ADDR;
                g_camera_y = EUR_CAMERA_Y_ADDR;
                g_camera_z = EUR_CAMERA_Z_ADDR;
                g_camera_pointer = EUR_CAMERA_POINTER;
                g_camstop_pointer = EUR_CAMSTOP_POINTER;
                g_coordinates_pointer = EUR_COORDINATES_POINTER;
                g_building_addr -= EUR_DIFFERENCE;
                g_garden -= EUR_DIFFERENCE;
                g_gender -= EUR_DIFFERENCE;
                g_name -= EUR_DIFFERENCE;
                break;
            case JAP:
                g_location += JAP_DIFFERENCE;
                g_indoor_pos_x += JAP_DIFFERENCE;
                g_indoor_pos_y += JAP_DIFFERENCE;
                g_indoor_pos_z += JAP_DIFFERENCE;
                g_outdoor_pos_x += JAP_DIFFERENCE;
                g_outdoor_pos_y += JAP_DIFFERENCE;
                g_outdoor_pos_z += JAP_DIFFERENCE;
                g_town_items += JAP_DIFFERENCE;
                g_island_items += JAP_DIFFERENCE;
                g_grass_start += JAP_DIFFERENCE;
                g_grass_end += JAP_DIFFERENCE;
                g_inv += JAP_DIFFERENCE;
                g_velocity += JAP_DIFFERENCE;
                g_leif += JAP_DIFFERENCE;
                g_tan += JAP_DIFFERENCE;
                g_id += JAP_DIFFERENCE;
                g_edible += JAP_DIFFERENCE;
                g_savetime += JAP_DIFFERENCE;
                g_world_x += JAP_DIFFERENCE;
                g_world_y += JAP_DIFFERENCE;
                g_hours = 0x9495B7;
                g_minutes = 0x9495B6;
                g_realtime = 0x956500;
                g_seed = 0x9AD248;
                g_playerId = 0xAA7990;
                g_visitor_indoor_x += JAP_DIFFERENCE;
                g_visitor_indoor_z += JAP_DIFFERENCE;
                g_visitor_outdoor_x += JAP_DIFFERENCE;
                g_visitor_outdoor_z += JAP_DIFFERENCE;
                g_visitor1_indoor_x += JAP_DIFFERENCE;
                g_visitor1_indoor_z += JAP_DIFFERENCE;
                g_visitor1_outdoor_x += JAP_DIFFERENCE;
                g_visitor1_outdoor_z += JAP_DIFFERENCE;
                g_visitor2_indoor_x += JAP_DIFFERENCE;
                g_visitor2_indoor_z += JAP_DIFFERENCE;
                g_visitor2_outdoor_x += JAP_DIFFERENCE;
                g_visitor2_outdoor_z += JAP_DIFFERENCE;
                g_keyboard += JAP_DIFFERENCE;
                g_island_bubble += JAP_DIFFERENCE;
                g_island_keyboard += JAP_DIFFERENCE;
                g_abd+= JAP_DIFFERENCE;
                g_walkOver += JAP_DIFFERENCE; 
                g_input_text_buffer = JAP_INPUT_TEXT_ADDR;
                g_nook1Price += JAP_DIFFERENCE;
                g_nook2Price += JAP_DIFFERENCE;
                g_room = JAP_ROOM_ID_ADDR;
                g_isabelle += JAP_DIFFERENCE;
                g_kappn += JAP_DIFFERENCE;
                g_npc = JAP_NPC_ADDR;
                g_badge += JAP_DIFFERENCE;
                g_turnip += JAP_DIFFERENCE;
                g_main_x += JAP_DIFFERENCE;
                g_main_y += JAP_DIFFERENCE;
                g_main_items += JAP_DIFFERENCE;
                g_in_cond += JAP_DIFFERENCE;
                g_out_cond += JAP_DIFFERENCE;
                g_in_col += JAP_DIFFERENCE;
                g_out_col += JAP_DIFFERENCE;
                g_quick += JAP_DIFFERENCE;
                g_out_grav += JAP_DIFFERENCE;
                g_medals += JAP_DIFFERENCE;
                g_camera_asm = JAP_CAMERA_ASM_ADDR;
                g_camera_x = JAP_CAMERA_X_ADDR;
                g_camera_y = JAP_CAMERA_Y_ADDR;
                g_camera_z = JAP_CAMERA_Z_ADDR;
                g_camera_pointer = JAP_CAMERA_POINTER;
                g_camstop_pointer = JAP_CAMSTOP_POINTER;
                g_coordinates_pointer = JAP_COORDINATES_POINTER;
                g_building_addr += JAP_DIFFERENCE;
                g_garden += JAP_DIFFERENCE;
                g_gender += JAP_DIFFERENCE;
                g_name += JAP_DIFFERENCE;
                break;
        }
    }

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