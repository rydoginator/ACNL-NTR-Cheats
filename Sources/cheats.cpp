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

    void    duplicationAll(void)
    {
        u32 item[16]; //store the entire inventory into an array so that we can check the contents of the inventory


        for (int i = 0; i < 16; i++)
        {
            g_player->ReadInventorySlot(i, item[i]);
        }

        for (int i = 0; i < 16; i++)
        {
            if (item[i] == 0x00007FFE) //check to see if the current index of the inventory is blank
                g_player->WriteInventorySlot(i, item[0]); //duplicate all the items from slot 0
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
            g_player->WriteByte(0x55BA, userChoice);
            appearanceMod();
        }
        else
        {
            OSD::Notify("You must load your save to use this cheat!");
        }
    }

    void    changeHair(void)
    {
        Keyboard  keyboard("Which hairstlye would you like?");
        std::vector<std::string> list = 
        {
            "Male 01", 
            "Male 02",
            "Male 03", 
            "Male 04",
            "Male 05", 
            "Male 06",
            "Male 07", 
            "Male 08", 
            "Male 09",
            "Male 10", 
            "Male 11",
            "Male 12", 
            "Male 13",
            "Male 14", 
            "Male 15", 
            "Male 16",
            "Messy Hair", 
            "Female 01", 
            "Female 02",
            "Female 03", 
            "Female 04",
            "Female 05", 
            "Female 06",
            "Female 07", 
            "Female 08", 
            "Female 09",
            "Female 10", 
            "Female 11",
            "Female 12", 
            "Female 13",
            "Female 14", 
            "Female 15", 
            "Female 16"
        };

        keyboard.Populate(list);

        u8 userChoice = keyboard.Open();

        if (userChoice != -1)
        {
            g_player->WriteByte(0x4, userChoice);
            appearanceMod();
        }       
    }


    void    appearanceMod(void)
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
            case 1:
                changeHair();
                break;
            default:
                break;
        }

    }

    void    setTimeTo(int hour)
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