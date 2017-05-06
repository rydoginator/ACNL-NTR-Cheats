#include "cheats.hpp"
#include "Player.hpp"
#include <cstring>
#include <stdio.h>
#include "ctrulib/util/utf.h"

namespace CTRPluginFramework
{
    #define READU32(x) *(u32 *)(x)
	#define READU16(x) *(u16 *)(x)
    #define READU8(x) *(u8 *)(x)
    #define READFLOAT(x) *(float *)(x)

    #define WRITEU8(a, v) 	*(u8 *)(a) = (u8)v
    #define WRITEU16(a, v) 	*(u16 *)(a) = (u16)v
    #define WRITEU32(a, v) 	*(u32 *)(a) = (u32)v 
    #define WRITEU64(a, v)	*(u64 *)(a) = (u64)v

	#define ADD32(a, v)  *(u32 *)a += v
	#define SUB32(a, v)  *(u32 *)a -= v
	#define ADD64(a, v)  *(vs64 *)a += v
	#define SUB64(a, v)  *(vs64 *)a -= v
	#define	ADD16(a, v)  *(u16 *)a += v
	#define	SUB16(a, v)	 *(u16 *)a -= v
	#define ADDTOFLOAT(a, v)  *((float*)(a)) += (float)v
	#define SUBTOFLOAT(a, v)  *((float*)(a)) -= (float)v

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
	extern u32	g_playerPointer;
	u32     g_inv;
	u32     g_velocity;
	u32     g_grass_start;
	u32     g_grass_end;
	u32     g_nook;
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
	u32		g_medals;
	u32     g_camera_asm;
	u32     g_camera_x;
	u32     g_camera_y;
	u32     g_camera_z;
	u32     g_camera_pointer;
	u32     g_camstop_pointer;
	u32     g_coordinates_pointer;
	u32		g_thought;
	u32		g_club_items;
	u32		g_building_addr;
	u32 	g_garden;
	u32 	g_gender;
	u32		g_name;

	u32     g_find[100];
	u32     g_replace[100];
	int     g_i = 0;


	bool g_command = false;
	// Function to assign our aesses

	void    assign_region(u32 region)
	{
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
	    g_nook = USA_NOOK_ADDR;
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
	    g_garden = USA_GARDENRAM_ADDR;
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
	            g_nook -= EUR_DIFFERENCE;
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
	            g_nook += JAP_DIFFERENCE;
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

	void    coord(MenuEntry *entry)
	{
	    static u32 offset;

	    offset = READU32(g_camstop_pointer);
	    if (offset != 0)
	    {
	    	offset += 0x14;
		    if (Controller::IsKeysDown(A + DPadDown))
		        ADDTOFLOAT(offset + 8, 0.01f);
		    if (Controller::IsKeysDown(A + DPadUp))
		        SUBTOFLOAT(offset + 8, 0.01f);
		    if (Controller::IsKeysDown(A + DPadLeft))
		        SUBTOFLOAT(offset, 0.01f);
		    if (Controller::IsKeysDown(A + DPadRight))
		        ADDTOFLOAT(offset, 0.01f);
		}
	}

    bool    CheckItemInput(const void *input, std::string &error)
    {
        // Cast the input into the appropriate type (must match the type provided to Open)
        u32  in = *static_cast<const u32 *>(input);

        // Check the value
        if (in < 0x1000)
        {
            error = "The value must be between 1000 - FFFF";
            // Return that the value isn't valid
            return (false);
        }

        // The value is valid
        return (true);
    }

    bool 	CheckMinuteInput(const void *input, std::string &error)
    {
        int  in = *static_cast<const int *>(input);
        if (in >= 60) 
        {
        	error = "Minutes can't be over 60!";
        	return (false);
        }

        return (true);   	
    }

    bool 	CheckHourInput(const void *input, std::string &error)
    {
        int  in = *static_cast<const int *>(input);
        if (in >= 24) 
        {
        	error = "Hours can't be over 24!";
        	return (false);
        }

        return (true);   	
    }

	bool 	CheckDayInput(const void *input, std::string &error)
    {
        int  in = *static_cast<const int *>(input);
        if (in >= 30) 
        {
        	error = "Days can't be over 30!";
        	return (false);
        }

        return (true);   	
    }

    bool 	CheckMonthInput(const void *input, std::string &error)
    {
        int  in = *static_cast<const int *>(input);
        if (in >= 24) 
        {
        	error = "Months can't be over 12!";
        	return (false);
        }

        return (true);   	
    }

    bool 	CheckYearInput(const void *input, std::string &error)
    {
        int  in = *static_cast<const int *>(input);
        if (in >= 50) 
        {
        	error = "Years can't be over 50!";
        	return (false);
        }

        return (true);   	
    }



	void    teleport(MenuEntry *entry)
	{
		static u32 offset;
	    static u32    X[3] = { 0 };
	    static u32    Y[3] = { 0 };
	    int           loc;
	    int           slot;

	    if (Controller::IsKeysDown(L))
	    {
        	slot = 2;
        }
    	else if (Controller::IsKeysDown(R))
    	{
        	slot = 1;
    	}
    	else
    	{
        	slot = 0;
    	}
        offset = READU32(g_camstop_pointer);
	    if (offset != 0)
	    {
	    	offset += 0x14;
		    if (Controller::IsKeysDown(B + DPadUp))
		    {
		    	X[slot] = READU32(offset);
		    	Y[slot] = READU32(offset + 8);
		    }
		    else if (Controller::IsKeysDown(B + DPadDown))
		    {
		    	WRITEU32(offset, X[slot]);
		    	WRITEU32(offset + 8, Y[slot]);
		    }
	    }
	}

	void    walkOver(MenuEntry *entry)
	{
		u32 offsets[] = {0x6503FC, 0x650414, 0x650578, 0x6505F0, 0x6506A4, 0x6506BC, 0x6506C0, 0x6506ec};
		u32 original[]={0x0A000094, 0x0A000052, 0x0A000001, 0xDA000014, 0xED841A05, 0xED840A07, 0x0A000026, 0x0A000065};
		u32 patch[]= {0xEA000094, 0xEA000052, 0xEA000001, 0xEA000014, 0xE1A00000, 0xE1A00000, 0xEA000026, 0xEA000065};
		if (Controller::IsKeysDown(L + DPadUp))
		{
			for (int i = 0; i < 8; i++)
			{
				Process::Patch(offsets[i], (u8 *)&patch[i], 4); 
			}
		}

		if (Controller::IsKeysDown(L + DPadDown))
		{
			for (int i = 0; i < 8; i++)
			{
				Process::Patch(offsets[i], (u8 *)&original[i], 4); 
			}
		}
	}

	void    speed(MenuEntry *entry)
	{
		char buffer[0x100];
	    u32     velocity;
	    float	acceleration;

	    if (Controller::IsKeysDown(B))
	    {
	        velocity = READU32(g_velocity);
	        if (velocity >= 0x41A79DB3)
	        {
	            WRITEU32(g_velocity, 0x41A79DB3);
	        }
	        else if (velocity > 0)
	        {
	            ADDTOFLOAT(g_velocity, 0.1f);
	        }
	    }
	}

	void    moonJump(MenuEntry *entry)
	{
	    u32		offset;

	    offset = READU32(g_coordinates_pointer);
	    if (Controller::IsKeysDown(L + DPadUp))
	    {
		    if (offset != 0)
		    {
		    	offset += 0x24;
		    	WRITEU16(g_out_grav, 0xFFFF);
		    	ADDTOFLOAT(offset + 4, 0.005f);
		    }
		}
		if (Controller::IsKeysDown(L + DPadDown))
	    {
		    if (offset != 0)
		    {
		    	offset += 0x24;
		    	SUBTOFLOAT(offset + 4, 0.005f);
		    }
		}
	}


	u32        computeOffset(u32 x, u32 y)
	{
	    u32   reg0;
	    u32   reg1;
	    u8    room = READU8(g_room);

	    if (room == 0x01)
	    {
		    reg0 = x % 0x10;
		    x /= 0x10;
		    reg1 = y % 0x10;
		    y /= 0x10;
		    reg0 *= 0x4;
		    reg1 *= 0x40;
		    x *= 0x400;
		    y *= 0x1400;
		}
		else
		{
			x -= 0x10;
			y -= 0x10;
		    reg0 = x % 0x10;
		    x /= 0x10;
		    reg1 = y % 0x10;
		    y /= 0x10;
		    reg0 *= 0x4;
		    reg1 *= 0x40;
		    x *= 0x400;
		    y *= 0x1400;			
		}
	    return (reg0 + reg1 + x + y);
	}

	u32        getItem(u32 location)
	{
	    u8    room = READU8(g_room);
	    u32   x = room == 0x01 ? READU32(g_main_x) : READU32(g_world_x);
	    u32   y = room == 0x01 ? READU32(g_main_y) : READU32(g_world_y);
	    u32   offset = computeOffset(x, y);
	           
	    return (READU32(location + offset));
	}

	void     writeLocation(u32 location, u32 item)
	{
	    u8    room = READU8(g_room);
	    u32   x = room == 0x01 ? READU32(g_main_x) : READU32(g_world_x);
	    u32   y = room == 0x01 ? READU32(g_main_y) : READU32(g_world_y);
	    u32   dst = room == 0x01 ? g_main_items : location;
	    u32   offset = computeOffset(x, y);       
	    
	    WRITEU32(dst + offset, item);
	}

	void 	text2item(MenuEntry *entry)
	{
		if (Controller::IsKeysDown(X + DPadRight))
		{
			u32 output;
            // New keyboard, hint being:
            Keyboard keyboard("What item would you like ?");

            // Add the function to check the input entered by the user
            keyboard.SetCompareCallback(CheckItemInput);

            // If the function return -1, then the user canceled the keyboard, so do nothing 
            if (keyboard.Open(output) != -1)
            {
            	g_player->WriteSlot(0, output);  
            }                      
		}
	}

	void 	duplication(MenuEntry *entry)
	{
		u32 item;
		if (Controller::IsKeyDown(R))
		{
			g_player->ReadSlot(0, item);
			g_player->WriteSlot(1, item);
		}
	}

	void 	duplicationAll(void)
	{
		u32 item[16]; //store the entire inventory into an array so that we can check the contents of the inventory


		for (int i = 0; i < 16; i++)
		{
			g_player->ReadSlot(i, item[i]);
		}

		for (int i = 0; i < 16; i++)
		{
			if (item[i] == 0x00007FFE) //check to see if the current index of the inventory is blank
				g_player->WriteSlot(i, item[0]); //duplicate all the items from slot 0
		}
	}

    void     worldEdit(MenuEntry *entry)
    {
        static u32 item;
        static int valid = -1;
        char buffer[0x100];

        u32 output;

        if (Controller::IsKeysDown(R + DPadLeft))
        {
            Keyboard keyboard("What item would you like to use?");
            keyboard.IsHexadecimal(true);
            
            int result = keyboard.Open(output);

            // if result == -1, output is undefined so do nothing
            if (result != -1)
            {
                item = output;
                valid = 0;
            }
            else
                valid = -1;
        }
        if (Controller::IsKeysDown(R + DPadDown))
        {
            if (READU8(g_room) == 0x01)
                writeLocation(g_main_items, item);
            else if (READU8(g_room) == 0x00)
                writeLocation(g_town_items, item);
            else if (READU8(g_room) == 0x68)
                writeLocation(g_island_items, item);
        }
        if (Controller::IsKeysDown(R + DPadUp))
        {
        	if (READU8(g_room) == 0x01)
        	{
                item = getItem(g_main_items);
                sprintf(buffer, "%08X -> %08X", g_main_items, getItem(g_main_items));
    			OSD::Notify(buffer);
        	}
            else if (READU8(g_room) == 0x00)
            {
                item = getItem(g_town_items);
            }
            else if (READU8(g_room) == 0x68)
            {
                item = getItem(g_island_items);
            }
        }
        if (Controller::IsKeyPressed(R))
        {
        	u8    room = READU8(g_room);
		    u32   x = room == 0x01 ? READU32(g_main_x) : READU32(g_world_x);
		    u32   y = room == 0x01 ? READU32(g_main_y) : READU32(g_world_y);
        	u32   offset = computeOffset(x, y);
        	u32   item;
        	if (room == 0x01)
        	{
                item = getItem(g_main_items);
                sprintf(buffer, "%08X -> %08X", offset + g_main_items, item);
    			OSD::Notify(buffer);
        	}
            else if (room == 0x00)
            {
                item = getItem(g_town_items);
                sprintf(buffer, "%08X -> %08X", offset + g_town_items, item);
    			OSD::Notify(buffer);
            }
            else if (room == 0x68)
            {
                item = getItem(g_island_items);
                sprintf(buffer, "%08X -> %08X", offset + g_island_items, item);
    			OSD::Notify(buffer);
            }

        }
    }

    void 	showBuried(MenuEntry *entry)
    {
    	u8    room = READU8(g_room);
   		u32   x = room == 0x01 ? READU32(g_main_x) : READU32(g_world_x);
		u32   y = room == 0x01 ? READU32(g_main_y) : READU32(g_world_y);
        u32   offset = computeOffset(x, y);
        u32   patch  = 0xE1A00000;
        u32   original = 0xA000049;
        u16	  item;


        if (room == 0x00)
        {
	        if (READU16(g_town_items + offset + 0x2) == 0x8000) //check to see if you're on a buried spot
	        {
	        	item = getItem(g_town_items);
	        	WRITEU16(g_thought, item);
            	Process::Patch(0x002160BC, (u8 *)&patch, 4); //nop the instruction that overwrites external thought bubbles
	        }
	        else
	        {
	        	if (READU32(0x002160BC) != original)
	        	{
	        		Process::Patch(0x002160BC, (u8 *)&original, 4); 
	        		WRITEU16(g_thought, 0x7FFE);
	        	}
	        }
        }
        else if (room == 0x6F)
        {
	        if (READU16(g_club_items + offset + 0x2) == 0x8000) //check to see if you're on a buried spot
	        {
	        	item = getItem(g_club_items);
	        	WRITEU16(g_thought, item);
            	Process::Patch(0x002160BC, (u8 *)&patch, 4); //nop the instruction that overwrites external thought bubbles
	        }
	        else
	        {
	        	if (READU32(0x002160BC) != original)
	        	{
	        		Process::Patch(0x002160BC, (u8 *)&original, 4); 
	        		WRITEU16(g_thought, 0x7FFE);
	        	}	        	
	        }        	
        }
    }

    void 	pickBuried(MenuEntry *entry)
	{
	  	u8    room = READU8(g_room);
		u32   x = room == 0x01 ? READU32(g_main_x) : READU32(g_world_x);
		u32   y = room == 0x01 ? READU32(g_main_y) : READU32(g_world_y);
	    u32   offset = computeOffset(x, y);
	    u16	  item;


	    if (room == 0x00)
	    {
		    if (READU16(g_town_items + offset + 0x2) == 0x8000)
		    {
		      	if (Controller::IsKeysDown(Y))
		       	{
		       		WRITEU16(g_town_items + offset + 0x2, 0x0000);
		       	}
		    }
	    }
	    else if (room == 0x6F)
	    {
		    if (READU16(g_club_items + offset + 0x2) == 0x8000)
		    {
		      	if (Controller::IsKeysDown(Y))
		       	{
		       		WRITEU16(g_club_items + offset + 0x2, 0x0000);
		       	}
		    }	    	
	    }   	
	}

    void 	ghostMode(MenuEntry *entry)
    {
    	u32   patch  = 0xE38110FF;
        u32   original = 0xE3811004;

    	if (Controller::IsKeysDown(Y + DPadUp))
    	{
    		Process::Patch(0x00654594, (u8 *)&patch, 4); 
    	}
    	if (Controller::IsKeysDown(Y + DPadDown))
    	{
    		Process::Patch(0x00654594, (u8 *)&original, 4); 
    	}
    }

    void 	customBuilding(MenuEntry *entry)
    {
    	u32 offset = 0;
    	u8 input;
    	u8 x = READU8(g_world_x);
    	u8 y = READU8(g_main_y);
    	if (Controller::IsKeysDown(R + DPadDown))
    	{
    		Keyboard keyboard("What building would you like to place?");

    		//Exit if the user cancel the keyboard
            if (keyboard.Open(input) == -1)
            	return;

    		while (READU8(g_building_addr + offset) != 0xFC && offset < 0xE5)
    		{
    			offset += 0x4;
    		}
    		if (offset == 0xE5)
    		{
    			OSD::Notify("All building slots are filled!");
    		}
    		else 
    		{
    			WRITEU8(g_building_addr + offset, input);
    			WRITEU8(g_building_addr + offset + 0x2, x);
    			WRITEU8(g_building_addr + offset + 0x3, y);
    		}
    	}
    	if (Controller::IsKeysDown(R + DPadUp))
    	{
    		Keyboard keyboard("What building would you like to remove?");

    		// Exit if the user cancel the keyboard
            if (keyboard.Open(input) == -1)
            	return;

    		while (READU8(g_building_addr + offset) != input && offset < 0xE5)
    		{
    			offset += 0x4;
    		}
    		if (offset == 0xE5)
    		{
    			OSD::Notify("Could not find your building");
    		}
    		else 
    		{
    			WRITEU8(g_building_addr + offset, 0xFC);
    			WRITEU8(g_building_addr + offset + 0x2, 0x00);
    			WRITEU8(g_building_addr + offset + 0x3, 0x00);
    		}
    	}
    }

    void 	deleteAll(MenuEntry *entry)
	{
	    if (Controller::IsKeysPressed(R + A))
	    {
	        for (int i = 0; i < 0x1400; i++)
	        {
	            WRITEU32(g_town_items + (i * 4), 0x00007FFE);
	        }
	    }
	}

	void 	weeder(MenuEntry *entry)
	{
		u16 weeds[] = {0x007C, 0x007D, 0x007E, 0x007F, 0x00CB, 0x00CC, 0x00CD, 0x00F8};

	    if (!Controller::IsKeysPressed(R + A) && g_command)
	    	return;
	    for (int i = 0; i < 7; i++)
	    {
	        reset_search();
	        add_search_replace(weeds[i], 0x7FFE);
	        find_and_replace_multiple(g_town_items, 0x5000);
	    }
	}

  void    backup(MenuEntry *entry)
    {        
        Keyboard        keyboard("GardenRam Dumper\n\nName the dump you'd like to create.");
        std::string     input;
        File            file;
        Directory       dir;

        if (keyboard.Open(input) != -1)
        {
            // Add extension to the name if user didn't
            if (input.find(".bin") == std::string::npos)
                input += ".bin";
            // Open dumps folder, create it if it doesn't exist
            if (Directory::Open(dir, "dumps", true) == 0)
            {
                // Folder successfully opened
                
                // Let's create and open the file
                if (dir.OpenFile(file, input, true) == 0)
                {
                    // Successfully opened the file 
                    
                    // Dump to the file
                    if (file.Dump(g_garden, 0x89A80) == 0)
                    {
                        // Success
                        
                        std::string     path; 
                        std::string     message;

                        // Assemble full path
                        path = dir.GetPath();
                        path += input;

                        // Assemble message for MessageBox
                        message = "File dumped to:\n";
                        message += path;

                        // Create MessageBox and open it
                        MessageBox      msgBox(message);

                        msgBox(); 
                    }
                    else
                    {
                        //  Failed
                        
                        MessageBox msgBox("Error\nDump failed.");

                        msgBox();
                    }
                }
            }
            else
            {
                // Failed to open the folder, notify the user
                MessageBox msgBox("Error\nCouldn't open dumps folder.");

                msgBox();
            }

            // Close file and directory
            file.Close();
            dir.Close(); 
        }
    }

    void    restore(MenuEntry *entry)
    {
        File            file;
        Directory       dir;
        std::vector<std::string> list;
    	if (Directory::Open(dir, "dumps", true) == 0)
    	{
    		dir.ListFiles(list, ".bin");
    		if (!list.empty())
    		{
    			Keyboard keyboard("Select which dump to restore.");
    			keyboard.Populate(list);

    			int userChoice = keyboard.Open();

    			if (userChoice != -1)
    			{
    				if (dir.OpenFile(file, list[userChoice], File::READ) == 0)
    				{
    					if (file.Inject(g_garden, 0x89A80) == 0)
    					{
							MessageBox      msgBox("Successfully restored your\nsave!");

							msgBox();   						
    					}
    					else
    					{
    						MessageBox msgBox("Error\nError injecting dump!");
    					}
    				}
    				else
    				{
			             MessageBox msgBox("Error\nCouldn't open the dump!");

			            msgBox();    					
    				}
    			}
    		}
    		else
    		{
    			MessageBox msgBox("Error\nCouldn't find any dumps!");
    			msgBox();
    		}
    	}
    	else
    	{
            // Failed to open the folder, notify the user
            MessageBox msgBox("Error\nCouldn't open dumps folder.");

            msgBox();   		
    	}
    	file.Close();
    	dir.Close();
    }

    void    InjectTCP(MenuEntry *entry)
	{
        File file;
        if (!entry->IsActivated())
        return;
        int ret = File::Open(file, "image.jpg", File::READ);
        if (ret == 0)
        {
            int res = file.Inject(g_garden + 0x5758, file.GetSize());
            file.Close(); 
            entry->Disable();
        }
	}

	void    timeTravel(MenuEntry *entry)
	{
		if (Controller::IsKeysDown(R + DPadRight))
		{
	        ADD64(g_savetime, 0x9EF21AA);
	        ADD64(g_realtime, 0x9EF21AA);
		}
		if (Controller::IsKeysDown(R + DPadLeft))
		{
	        SUB64(g_savetime, 0x9EF21AA);
	        SUB64(g_realtime, 0x9EF21AA);
		}
	    if (!Controller::IsKeyDown(Key::B))
	        return;
	    if (Controller::IsKeyPressed(Key::DPadRight))
	    {
	        ADD64(g_savetime, 0x34630B8A000);
	        ADD64(g_realtime, 0x34630B8A000);
	    }
	    if (Controller::IsKeyPressed(Key::DPadLeft))
	    {
	        SUB64(g_savetime, 0x34630B8A000);
	        SUB64(g_realtime, 0x34630B8A000);
	    }
	    if (Controller::IsKeyPressed(Key::DPadDown))
	    {
	        WRITEU64(g_savetime, 0x0000000000000000);
	        WRITEU64(g_realtime, 0x0000000000000000);	    	
	    }
	}

	void 	timeMachine(MenuEntry *entry)
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
	    		ADD64(g_realtime, time); 
			    ADD64(g_savetime, time);
			    OSD::Notify("Welcome to the future, time traveler.");
	    	}
	    	else
	    	{
	    		SUB64(g_realtime, time); 
			    SUB64(g_savetime, time);
			    OSD::Notify("Welcome to the past, time traveler.");   		
	    	}
	    }
	}

	void 	quench(MenuEntry *entry)
	{
	    u32     address;
	    u32     item;

	    if (!Controller::IsKeysPressed(R + A) && g_command)
	        return;
	    // Parse all items in Town
	    for (address = g_town_items; address < g_town_items + RANGE_TOWN_ITEMS; address += ITEM_BYTES)
	    {
	        item = READU16(address);
	        // Deal with wilted flower
	        if (item >= 0xCE && item <= 0xF7)
	        {
	            item -= 0x2F;
	        }
	        // If item is a flower add water flag
	        if (item >= 0x9F && item <= 0xC8)
	        {
	            item |= 0x40000000;
	            WRITEU32(address, item);
	        }
	    }
	}

	void    cameraMod(MenuEntry *entry)
	{
	    u32 offset;
	    static u32 pointer;
	    static u32 x;
	    static u32 z;
	    static u32 storage;
        u32   patch  = 0xEA000020;
        u32   original = 0x2A000020;

	    if (!Controller::IsKeyPressed(B))
	    {
	        Process::Patch(g_camera_asm, (u8 *)&original, 4);
	    }
	    if (READU32(g_camera_pointer) != 0)
	    {
	        if (!Controller::IsKeyDown(CPad))
	        {
	            if (READU32(g_coordinates_pointer) != 0)
	            {
	                pointer = READU32(g_coordinates_pointer);
	                x = READU32(pointer + 0x24);
	                z = READU32(pointer + 0x2C);
	            }
	        }
	        offset = READU32(g_camera_pointer);
	        if (Controller::IsKeysDown(R + CPadDown))
	        {
	            offset += 0x12C;
	            ADD16(offset, 0x1);
	        }
	        if (Controller::IsKeysDown(R + CPadUp))
	        {
	            offset += 0x12C;  
	            SUB16(offset, 0x1);
	        }
	        if (Controller::IsKeysDown(R + CPadRight))
	        {
	            offset += 0x12E;
	            ADD16(offset, 0x1);
	        }
	        if (Controller::IsKeysDown(R + CPadLeft))
	        {
	            offset += 0x12E;
	            SUB16(offset, 0x1);
	        }
	        if (Controller::IsKeysDown(R + CPadDown))
	        {
	            if (READU32(g_coordinates_pointer) != 0)
	            {
	                pointer = READU32(g_coordinates_pointer);
	                WRITEU32(pointer + 0x24, x);
	                WRITEU32(pointer + 0x2C, z);
	            }            
	        }
	        if (Controller::IsKeysDown(R + X))
	        {
	            if (READU32(g_camstop_pointer) != 0)
	            {
	                storage = READU32(g_camstop_pointer);
	                WRITEU32(g_camstop_pointer, 0x00000000);
	            }
	        }
	        if (Controller::IsKeysDown(R + Y))
	        {
	            if (storage != 0)
	            {
	                WRITEU32(g_camstop_pointer, storage);
	            }
	        }
	    }
	    if (Controller::IsKeysDown(B + DPadLeft))
	    {
	        Process::Patch(g_camera_asm, (u8 *)&patch, 4); //change the asm instruction to b, allows overwriting camera coordinates
	        SUBTOFLOAT(g_camera_x, 0.1f);
	    }
	    if (Controller::IsKeysDown(B + DPadRight))
	    {
	        Process::Patch(g_camera_asm, (u8 *)&patch, 4);
	        ADDTOFLOAT(g_camera_x, 0.1f);
	    }
	    if (Controller::IsKeysDown(B + DPadDown))
	    {
	        Process::Patch(g_camera_asm, (u8 *)&patch, 4);
	        ADDTOFLOAT(g_camera_z, 0.1f);
	    }
	    if (Controller::IsKeysDown(B + DPadUp))
	    {
	        Process::Patch(g_camera_asm, (u8 *)&patch, 4);
	        SUBTOFLOAT(g_camera_z, 0.1f);
	    }
	    if (Controller::IsKeysDown(B + R))
	    {
	        Process::Patch(g_camera_asm, (u8 *)&patch, 4);
	        ADDTOFLOAT(g_camera_y, 0.1f);
	    }
	    if (Controller::IsKeysDown(B + L))
	    {
	        Process::Patch(g_camera_asm, (u8 *)&patch, 4);
	        SUBTOFLOAT(g_camera_y, 0.1f);
	    }
	}

    void    changeGender(void)
    {
        Keyboard  keyboard("Which gender would you like?");
        std::vector<std::string> list = 
        {
            "Male", //there are only two genders, folks
            "Female"
        };
        keyboard.Populate(list);

        int userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            g_player->Write(0x55BA, userChoice);
            appearanceMod();
        }
        else
        {
            OSD::Notify("You must load your save to use this cheat!");
        }
    }


	void 	appearanceMod(void)
	{
		Keyboard  keyboard("Choose what to edit");
	    std::vector<std::string> list = 
	    {
	        "Gender",
	        "Hair",
	        "Face",
	        "Tan",
	        "Apparel",
	        "Return to main menu..."
	    };
	    keyboard.Populate(list);
	    int userChoice = keyboard.Open();

	    switch (userChoice)
	    {
	    	case 0:
	    		changeGender();
				break;
			default:
				break;
	    }

	}

	void 	KeyboardExtender(MenuEntry *entry)
	{
		u32 offset = 0;

		Process::Read32(0x95F11C, offset);
		if (offset != 0)
		{
			Process::Write32(0xC + offset, 0x36);
			Process::Write32(0x12B + offset, 0x45);
			Process::Write8(0xAD7253, 0x01);
		}
	}


    void    SetNameTo(MenuEntry *entry)
    {
    	if (!entry->IsActivated())
        	return;
        Keyboard keyboard("Name Changer\n\nEnter the name you'd like to have:");

        std::string     input;
        u16             output[0x100] = {0};

        if (keyboard.Open(input) != -1)
        {
            // Ask for a second line name
            MessageBox msgBox("Do you want your name to\nappear below the bubble?", DialogType::DialogYesNo);

            if (msgBox())
            {
                std::string secondLine = "\n";

                secondLine += input;
                input = secondLine;
            }

            // Convert input to game's format
            int res = utf8_to_utf16(output, reinterpret_cast<const u8*>(input.c_str()), 0x100);

            if (res > 0)
            {
                g_player->CopyMemory(0x55a8, output);
                entry->Disable();
            }
        }
        else
        	entry->Disable();
    }

	void 	setTimeTo(int hour)
	{
	    u8  minutes = READU8(g_minutes);
	    u8 hours = READU8(g_hours);
	    u64 time;

	    if (hour != -1 && hour < 24)
	    {
		    switch(hour)
		    {
		    	case 0:
		    		if (hours < 6) //go backwards in time if the time is before 6AM to prevent saving.
		    		{
		    			time = (hours * 0x34630B8A000) + (minutes * 0xDF8475800);
		    			SUB64(g_realtime, time); 
		        		SUB64(g_savetime, time); 
		    		}
		    		else // go forwards in time
		    		{
		    			hours = 24 - hours; 
		    			time = (hours * 0x34630B8A000) - (minutes * 0xDF8475800); //we want to subtract minutes for this time
		    			ADD64(g_realtime, time); //since you're before entered time, you need to travel forward in time
		        		ADD64(g_savetime, time);
		    		}
		    		break;
		    	case 1:
		    		if (hours == 0) //if it's midnight, we only want to go forward an hour
		    		{
		    			hours += 1;
		    			time = (hours * 0x34630B8A000) - (minutes * 0xDF8475800); //and subtract the minutes 
		    			ADD64(g_realtime, time); 
		        		ADD64(g_savetime, time);
		    		}
		    		else if (hours < 6 && hours >= 1) // if the time is between 1AM and 5AM, we want to go backwards in time
		    		{
		    			hours -= 1;
		    			time = (hours * 0x34630B8A000) + (minutes * 0xDF8475800);
		    			SUB64(g_realtime, time); 
		        		SUB64(g_savetime, time); 	    			
		    		}
		    		else
		    		{
		    			hours = 25 - hours; // 25 - whatever the current hour is will get you to how far away it is from 1am (example: 25 - 13(1pm) = 12 hours away)
		    			time = (hours * 0x34630B8A000) - (minutes * 0xDF8475800);
		    			ADD64(g_realtime, time); 
		        		ADD64(g_savetime, time);
		    		}
		    		break;
		    	case 2:
		    		if (hours <= 1) //if it's 1AM or midnight, we want to go forward 2 or 3 hours
		    		{
		    			hours = 2 + hours;
		    			time = (hours * 0x34630B8A000) - (minutes * 0xDF8475800); //and subtract the minutes 
		    			ADD64(g_realtime, time); 
		        		ADD64(g_savetime, time);
		    		}
		    		else if (hours < 6 && hours >= 2) // if the time is between 1AM and 5AM, we want to go backwards in time
		    		{
		    			hours -= 2;
		    			time = (hours * 0x34630B8A000) + (minutes * 0xDF8475800);
		    			SUB64(g_realtime, time); 
		        		SUB64(g_savetime, time); 	    			
		    		}
		    		else
		    		{
		    			hours = 26 - hours; 
		    			time = (hours * 0x34630B8A000) - (minutes * 0xDF8475800);
		    			ADD64(g_realtime, time); 
		        		ADD64(g_savetime, time);		    			
		    		}
		    		break;
		    	case 12:
		    		if (hours >= 6 && hours <= 11) //if the time is between 6AM and 11AM, we go forward in time
		    		{
		    			hours = 12 - hours;
		    			time = (hours * 0x34630B8A000) - (minutes * 0xDF8475800);
		    			ADD64(g_realtime, time); 
		        		ADD64(g_savetime, time);
		    		}
		    		else if (hours >= 12 && hours <= 23)// if the time is between 12PM and 11PM, we want to go backwards in time
		    		{
		    			hours = 12 - hours;
		    			time = (hours * 0x34630B8A000) + (minutes * 0xDF8475800);
		    			SUB64(g_realtime, time); 
		        		SUB64(g_savetime, time); 
		    		}
		    		else //we'll have to travel backwards if the time is between 12AM and 5AM in order to prevent a new day cycle.
		    		{
		    			hours = 12 + hours;
		    			time = (hours * 0x34630B8A000) - (minutes * 0xDF8475800);
		    			SUB64(g_realtime, time); 
		        		SUB64(g_savetime, time);
		    		}
		    		break;
		    	default:
		    		break;
		    }
		}
	}
}