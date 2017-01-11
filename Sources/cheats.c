#include "cheats.h"

// We're defining globals for each addresses needed

u32     g_location;
u32     g_indoor_pos_x;
u32     g_indoor_pos_y;
u32     g_indoor_pos_z;
u32     g_outdoor_pos_x;
u32     g_outdoor_pos_y;
u32     g_outdoor_pos_z;
u32     g_town_items;
u32     g_island_items;
u32     g_player;
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
u32     g_online0_inv;
u32     g_online1_inv;
u32     g_online2_inv;
u32     g_online3_inv;
u32     g_online4_inv;
u32     g_online5_inv;
u32     g_online6_inv;
u32     g_keyboard;
u32     g_island_bubble;
u32     g_island_keyboard;
u32     g_abd;
u32     g_walkOver;
u32     g_kpointer;
u32        g_bank;
u32     g_online0_bank;
u32     g_online1_bank;
u32     g_online2_bank;
u32     g_online3_bank;
u32     g_online4_bank;
u32     g_online5_bank;
u32     g_online6_bank;
u32        g_meow;
u32     g_online0_meow;
u32     g_online1_meow;
u32     g_online2_meow;
u32     g_online3_meow;
u32     g_online4_meow;
u32     g_online5_meow;
u32     g_online6_meow;
u32        g_wallet;
u32     g_online0_wallet;
u32     g_online1_wallet;
u32     g_online2_wallet;
u32     g_online3_wallet;
u32     g_online4_wallet;
u32     g_online5_wallet;
u32     g_online6_wallet;
u32     g_confirm;
u32     g_nook1Price;
u32     g_nook2Price;
u32     g_room;
u32     g_isabelle;
u32     g_kappn;
u32     g_npc;
u32     g_badge;
u32     g_collision;
u32     g_cond;
u32     g_cond0;
u32     g_col0;
u32     g_col1;
u32     g_grav;
u32     g_grav0;
u32     g_turnip;


u32     g_find[100];
u32     g_replace[100];
int     g_i = 0;

// Function to assign our addresses

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
    g_player = USA_PLAYER_ADDR;
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
    g_online0_inv = USA_ONLINE0_INV_ADDR;
    g_online1_inv = USA_ONLINE1_INV_ADDR;
    g_online2_inv = USA_ONLINE2_INV_ADDR;
    g_online3_inv = USA_ONLINE3_INV_ADDR;
    g_online4_inv = USA_ONLINE4_INV_ADDR;
    g_online5_inv = USA_ONLINE5_INV_ADDR;
    g_online6_inv = USA_ONLINE6_INV_ADDR;
    g_keyboard = USA_KEYBOARD_ADDR;
    g_island_keyboard = USA_KEYBOARD_ISLAND_ADDR;
    g_island_bubble = USA_INPUT_TEXT_ISLAND_ADDR;
    g_abd = USA_ABD_ADDR;
    g_walkOver = USA_WALKOVER_ADDR;
    g_kpointer = USA_KEYBOARD_POINTER;
    g_bank = USA_BANK_ADDR;
    g_online0_bank = USA_ONLINE0_BANK_ADDR;
    g_online1_bank = USA_ONLINE1_BANK_ADDR;
    g_online2_bank = USA_ONLINE2_BANK_ADDR;
    g_online3_bank = USA_ONLINE3_BANK_ADDR;
    g_online4_bank = USA_ONLINE4_BANK_ADDR;
    g_online5_bank = USA_ONLINE5_BANK_ADDR;
    g_online6_bank = USA_ONLINE6_BANK_ADDR;
    g_meow = USA_MEOW_ADDR;
    g_online0_meow = USA_ONLINE0_MEOW_ADDR;
    g_online1_meow = USA_ONLINE1_MEOW_ADDR;
    g_online2_meow = USA_ONLINE2_MEOW_ADDR;
    g_online3_meow = USA_ONLINE3_MEOW_ADDR;
    g_online4_meow = USA_ONLINE4_MEOW_ADDR;
    g_online5_meow = USA_ONLINE5_MEOW_ADDR;
    g_online6_meow = USA_ONLINE6_MEOW_ADDR;
    g_wallet = USA_WALLET_ADDR;
    g_online0_wallet = USA_ONLINE0_WALLET_ADDR;
    g_online1_wallet = USA_ONLINE1_WALLET_ADDR;
    g_online2_wallet = USA_ONLINE2_WALLET_ADDR;
    g_online3_wallet = USA_ONLINE3_WALLET_ADDR;
    g_online4_wallet = USA_ONLINE4_WALLET_ADDR;
    g_online5_wallet = USA_ONLINE5_WALLET_ADDR;
    g_online6_wallet = USA_ONLINE6_WALLET_ADDR;
    g_confirm = USA_CONFIRM_BOOL_ADDR;
    g_nook1Price = USA_NOOKLING1_PRICE_ADDR;
    g_nook2Price = USA_NOOKLING2_PRICE_ADDR;
    g_room = USA_ROOM_ID_ADDR;
    g_isabelle = USA_ISABELLE_ADDR;
    g_kappn = USA_KAPPN_ADDR;
    g_npc = USA_NPC_ADDR;
    g_badge = USA_BADGE_ADDR;

    g_collision = USA_COLLISION_OUTDOOR_ADDR;
    g_cond = USA_CONDITIONAL_ADDR;
    g_cond0 = USA_CONDITIONAL0_ADDR;
    g_col0 = USA_COLLISION0_OUTDOOR_ADDR;
    g_col1 = USA_COLLISION1_OUTDOOR_ADDR;
    g_grav = USA_GRAVITY_ADDR;
    g_grav0 = USA_GRAVITY0_ADDR;
    g_turnip = USA_TURNIP_ADDR;

    // applying offset or particular address
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
            g_collision -= EUR_DIFFERENCE;
            g_hours = 0x9505B7;
            g_minutes = 0x9505B6;
            g_realtime = 0x95c500;
            g_seed = 0x9B4268;
            g_player = 0xAAD990;
            g_visitor_indoor_x -= EUR_DIFFERENCE;
            g_visitor_indoor_z -= EUR_DIFFERENCE;
            g_visitor_outdoor_x -= EUR_DIFFERENCE;
            g_visitor_outdoor_z -= EUR_DIFFERENCE;
            g_online0_inv -= 0x1000;
            g_online1_inv -= 0x1000;
            g_online2_inv -= 0x1000;
            g_online3_inv -= 0x1000;
            g_online4_inv -= 0x1000;
            g_online5_inv -= 0x1000;
            g_online6_inv -= 0x1000;
            g_keyboard -= EUR_DIFFERENCE;
            g_island_bubble -= EUR_DIFFERENCE;
            g_island_keyboard = EUR_KEYBOAD_ISLAND_ADDR;
            g_abd -= EUR_DIFFERENCE;
            g_walkOver -= EUR_DIFFERENCE;
            g_input_text_buffer = EUR_INPUT_TEXT_ADDR;
            g_bank -= EUR_DIFFERENCE;
            g_online0_bank -= 0x1000;
            g_online1_bank -= 0x1000;
            g_online2_bank -= 0x1000;
            g_online3_bank -= 0x1000;
            g_online4_bank -= 0x1000;
            g_online5_bank -= 0x1000;
            g_online6_bank -= 0x1000;
            g_meow -= EUR_DIFFERENCE;
            g_online0_meow -= 0x1000;
            g_online1_meow -= 0x1000;
            g_online2_meow -= 0x1000;
            g_online3_meow -= 0x1000;
            g_online4_meow -= 0x1000;
            g_online5_meow -= 0x1000;
            g_online6_meow -= 0x1000;
            g_wallet -= EUR_DIFFERENCE;
            g_online0_wallet -= 0x1000;
            g_online1_wallet -= 0x1000;
            g_online2_wallet -= 0x1000;
            g_online3_wallet -= 0x1000;
            g_online4_wallet -= 0x1000;
            g_online5_wallet -= 0x1000;
            g_online6_wallet -= 0x1000;
            g_nook1Price -= EUR_DIFFERENCE;
            g_nook2Price -= EUR_DIFFERENCE;
            g_room = EUR_ROOM_ID_ADDR;
            g_isabelle -= EUR_DIFFERENCE;
            g_kappn -= EUR_DIFFERENCE;
            g_npc = EUR_NPC_ADDR;
            g_badge -= EUR_DIFFERENCE;

            g_collision -= EUR_DIFFERENCE;
            g_cond -= EUR_DIFFERENCE;
            g_cond0 -= EUR_DIFFERENCE;
            g_col0 -= EUR_DIFFERENCE;
            g_col1 -= EUR_DIFFERENCE;
            g_grav -= EUR_DIFFERENCE;
            g_grav0 -= EUR_DIFFERENCE;
            g_turnip -= EUR_DIFFERENCE;

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
            g_collision += JAP_DIFFERENCE;
            g_seed = 0x9AD248;
            g_player = 0xAA7990;
            g_visitor_indoor_x += JAP_DIFFERENCE;
            g_visitor_indoor_z += JAP_DIFFERENCE;
            g_visitor_outdoor_x += JAP_DIFFERENCE;
            g_visitor_outdoor_z += JAP_DIFFERENCE;
            g_online0_inv += 0x7000;
            g_online1_inv += 0x7000;
            g_online2_inv += 0x7000;
            g_online3_inv += 0x7000;
            g_online4_inv += 0x7000;
            g_online5_inv += 0x7000;
            g_online6_inv += 0x7000;
            g_keyboard += JAP_DIFFERENCE;
            g_island_bubble += JAP_DIFFERENCE;
            g_island_keyboard += JAP_DIFFERENCE;
            g_abd+= JAP_DIFFERENCE;
            g_walkOver += JAP_DIFFERENCE; 
            g_input_text_buffer = JAP_INPUT_TEXT_ADDR;
            g_bank += JAP_DIFFERENCE;
            g_online0_bank += 0x7000;
            g_online1_bank += 0x7000;
            g_online2_bank += 0x7000;
            g_online3_bank += 0x7000;
            g_online4_bank += 0x7000;
            g_online5_bank += 0x7000;
            g_online6_bank += 0x7000;
            g_bank += JAP_DIFFERENCE;
            g_online0_meow += 0x7000;
            g_online1_meow += 0x7000;
            g_online2_meow += 0x7000;
            g_online3_meow += 0x7000;
            g_online4_meow += 0x7000;
            g_online5_meow += 0x7000;
            g_online6_meow += 0x7000;
            g_wallet += JAP_DIFFERENCE;
            g_online0_wallet += 0x7000;
            g_online1_wallet += 0x7000;
            g_online2_wallet += 0x7000;
            g_online3_wallet += 0x7000;
            g_online4_wallet += 0x7000;
            g_online5_wallet += 0x7000;
            g_online6_wallet += 0x7000;
            g_nook1Price += JAP_DIFFERENCE;
            g_nook2Price += JAP_DIFFERENCE;
            g_room = JAP_ROOM_ID_ADDR;
            g_isabelle += JAP_DIFFERENCE;
            g_kappn += JAP_DIFFERENCE;
            g_npc = JAP_NPC_ADDR;
            g_badge += JAP_DIFFERENCE;
            g_collision += JAP_DIFFERENCE;
            g_cond += JAP_DIFFERENCE;
            g_cond0 += JAP_DIFFERENCE;
            g_col0 += JAP_DIFFERENCE;
            g_col1 += JAP_DIFFERENCE;
            g_grav += JAP_DIFFERENCE;
            g_grav0 += JAP_DIFFERENCE;
            g_turnip += JAP_DIFFERENCE;
            break;
    }
}

void    keyboardInput(void)
{
    // Static variable to keep the state of the cheat
    static int state = 0;
    static u32 bubble = 0;

    /*if (!state)
    {
        bubble = g_input_text_buffer;
        if (READU32(g_kpointer) != 0x0)
        {
            g_input_text_buffer = READU32(g_kpointer);
        }
        state = 1;
    }*/
    if (!state)
    {
        bubble = g_input_text_buffer;
        g_input_text_buffer = g_island_keyboard;
        state = 1;
    }
    else
    {
        g_input_text_buffer = bubble;
        state = 0;
    }
    //We add the [on] or [off] to the entry according to the state
    update_status(state, KEYBOARDINPUT);
    disable_entry(KEYBOARDINPUT);
}

// Our cheats using our globals
bool    g_text_activated = false;
bool    g_teleport_save = true;

inline void save_teleport(void)
{
    g_teleport_save = true;
    teleport();
}

inline void restore_teleport(void)
{
    g_teleport_save = false;
    teleport();
}

enum
{
    BIS = 1,
    QUENCH,
    SAVETP,
    RESTORETP,
    MIDNIGHT,
    MORNING,
    NOON,
    STALK1,
    GORGEOUSSET,
    CLEARINV
};

void    text_to_cheats(void)
{
    static int      last_command = 0;
    int             command;
    char            command_text[0x100];

    //islandFinder();
    retrieve_input_string(command_text, 10);
    g_text_activated = true;
    if (match(command_text, "bis")) command = BIS;
    else if (match(command_text, "quench")) command = QUENCH;
    else if (match(command_text, "savetp")) command = SAVETP;
    else if (match(command_text, "restoretp")) command = RESTORETP;
    else if (match(command_text, "midnight")) command = MIDNIGHT;
    else if (match(command_text, "noon")) command = NOON;
    else if (match(command_text, "morning")) command = MORNING;
    else if (match(command_text, "stalk1")) command = STALK1;
    else if (match(command_text, "gorgeset")) command = GORGEOUSSET;
    else if (match(command_text, "clearinv")) command = CLEARINV;
    if (command != last_command)
    {
    bis:
        switch (command)
        {
            case BIS:
                command = last_command;
                goto bis;
                break;
            case MIDNIGHT:
                midnight();
                break;
            case QUENCH:
                quench();
                break;
            case SAVETP:
                save_teleport();
                break;
            case RESTORETP:
                restore_teleport();
                break;
            case MORNING:
                morning();
                break;
            case NOON:
                noon();
                break;
            case STALK1:
                stalking_1();
                break;
            case GORGEOUSSET:
                gorgeous_set();
                break;
            case CLEARINV:
                clear_inv();
                break;
            default:
                break;
        }
        last_command = command;
    }
    g_text_activated = false;  
}

void    coord(void)
{
    static int  loc = 0;

    if (!is_pressed(BUTTON_A))
        return;
    loc = READU32(g_location);
    if (loc == -1) //FFFFFFFF=outdoors
    {
        if (is_pressed(BUTTON_A + BUTTON_DD))
            ADDTOFLOAT(g_outdoor_pos_z, 1.0);
        if (is_pressed(BUTTON_A + BUTTON_DU))
            SUBTOFLOAT(g_outdoor_pos_z, 1.0);
        if (is_pressed(BUTTON_A + BUTTON_DL))
            SUBTOFLOAT(g_outdoor_pos_x, 1.0);
        if (is_pressed(BUTTON_A + BUTTON_DR))
            ADDTOFLOAT(g_outdoor_pos_x, 1.0);
    }
    else //if it's anything but FFFFFFFF then you're indoors
    {
        if (is_pressed(BUTTON_A + BUTTON_DD))
            ADDTOFLOAT(g_indoor_pos_z, 1.0);
        if (is_pressed(BUTTON_A + BUTTON_DU))
            SUBTOFLOAT(g_indoor_pos_z, 1.0);
        if (is_pressed(BUTTON_A + BUTTON_DL))
            SUBTOFLOAT(g_indoor_pos_x, 1.0);
        if (is_pressed(BUTTON_A + BUTTON_DR))
            ADDTOFLOAT(g_indoor_pos_x, 1.0);
    }
}
void    search(void)
{
    int     search;
    int     replace;

    if (is_pressed(BUTTON_L + BUTTON_DL))
    {
        get_input_id(&search, &replace);
        reset_search();
        add_search_replace(search, replace);
        find_and_replace_multiple((void *)g_town_items, 0x5000);
        find_and_replace_multiple((void *)g_island_items, 0x1000);
    }
}

void    text2item(void) 
{
    int     input;
    u8      player;
    u32     offset;
    
    //islandFinder();
    if (!is_pressed(BUTTON_X + BUTTON_DR))
        return;
    player = READU8(g_player);
    get_input_id(&input, NULL);
    if (player <= 0x3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
    {
        offset = player * 0xa480;
        WRITEU16(g_inv + offset, input);
        if (READU16(g_online4_inv) != 0)
            WRITEU16(g_online4_inv, input); 
        if (READU16(g_online5_inv) != 0)
            WRITEU16(g_online5_inv, input); 
        if (READU16(g_online6_inv) != 0)
            WRITEU16(g_online6_inv, input);
    }
    if (player >= 0x3)
    {
        if (READU16(g_online0_inv) != 0)
            WRITEU16(g_online0_inv, input);
        if (READU16(g_online1_inv) != 0)
            WRITEU16(g_online1_inv, input); 
        if (READU16(g_online2_inv) != 0)
            WRITEU16(g_online2_inv, input); 
        if (READU16(g_online3_inv) != 0)
            WRITEU16(g_online3_inv, input);
    }  
   wait_all_released();
}

void    teleport(void)
{
    static u32    indoor_X[3] = { 0 };
    static u32    indoor_Y[3] = { 0 };
    static u32    outdoor_X[3] = { 0 };
    static u32    outdoor_Y[3] = { 0 };
    int           loc;
    int           slot;

    if (!is_pressed(BUTTON_B) && !g_text_activated)
        return;

    //Pointer to define whether player is indoors or not
    loc = READU32(g_location);
    if (is_pressed(BUTTON_L)) //If L is pressed then use slot3
        slot = 2;
    else if (is_pressed(BUTTON_R)) //If R is pressed then use slot2
        slot = 1;
    else //If nothing is pressed then use slot0
        slot = 0;
    if (is_pressed(BUTTON_B + BUTTON_DU)
        || (g_teleport_save && g_text_activated))
    {       
        if (loc == -1) 
        {           
            outdoor_X[slot] = READU32(g_outdoor_pos_x);
            outdoor_Y[slot] = READU32(g_outdoor_pos_z);
        }
        else
        {
            indoor_X[slot] = READU32(g_indoor_pos_x);
            indoor_Y[slot] = READU32(g_indoor_pos_z);
        }
    }
    else if (is_pressed(BUTTON_B + BUTTON_DD)
             || (!g_teleport_save && g_text_activated))
    {
        if (loc == -1)
        {
            WRITEU32(g_outdoor_pos_x, outdoor_X[slot]);
            WRITEU32(g_outdoor_pos_z, outdoor_Y[slot]);
        }
        else
        {
            WRITEU32(g_indoor_pos_x, indoor_X[slot]);
            WRITEU32(g_indoor_pos_z, indoor_Y[slot]);
        }
    }
}

void    warping(void)
{
    if (upper_left_touched())
    {
        WRITEU32(g_outdoor_pos_x, 0x4427405E);
        WRITEU32(g_outdoor_pos_y, 0x42E00000);
        WRITEU32(g_outdoor_pos_z, 0x44253715);
        wait_keys_released(KEY_TOUCH);
    }
    if (upper_right_touched())
    {
        WRITEU32(g_outdoor_pos_x, 0x442C4000);
        WRITEU32(g_outdoor_pos_y, 0x42E00000);
        WRITEU32(g_outdoor_pos_z, 0x45239943);
        wait_keys_released(KEY_TOUCH);
    }
    if (lower_left_touched())
    {
        WRITEU32(g_outdoor_pos_x, 0x450A7F48);
        WRITEU32(g_outdoor_pos_z, 0x42E00000);
        WRITEU32(g_outdoor_pos_z, 0x4442761E);
        wait_keys_released(KEY_TOUCH);
    }
    if (lower_right_touched())
    {
        WRITEU32(g_outdoor_pos_x, 0x45071000);
        WRITEU32(g_outdoor_pos_y, 0x42E00000);
        WRITEU32(g_outdoor_pos_z, 0x451E028E);
        wait_keys_released(KEY_TOUCH);
    }
}

void    speed(void)
{
    u32     velocity;

    if (is_pressed(BUTTON_B))
    {
        velocity = READU32(g_velocity);
        if (velocity >= 0x41A79DB3)
        {
            WRITEU32(g_velocity, 0x41A79DB3);
        }
        else if (velocity > 0)
        {
            ADDTOFLOAT(g_velocity, 2.0);
        }
    }
}

void    weeder(void)
{
    if (is_pressed(BUTTON_R + BUTTON_A))
    {
        reset_search();
        add_search_replace(0x0000007C, 0x00007FFE);
        add_search_replace(0x0000007D, 0x00007FFE);
        add_search_replace(0x0000007E, 0x00007FFE);
        add_search_replace(0x0000007F, 0x00007FFE);
        add_search_replace(0x000000CB, 0x00007FFE);
        add_search_replace(0x000000CC, 0x00007FFE);
        add_search_replace(0x000000CD, 0x00007FFE);
        add_search_replace(0x000000F8, 0x00007FFE);
        find_and_replace_multiple((void *)g_town_items, 0x5000);
        wait_all_released();
    }
}

void quench(void)
{
    u32     address;
    u32     item;

    if (!is_pressed(BUTTON_R + BUTTON_A) && !g_text_activated)
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

void    tree(void)
{
    if (is_pressed(BUTTON_X))
    {
        reset_search();
        add_search_replace(0x003A, 0x003E);
        add_search_replace(0x003F, 0x0043);
        add_search_replace(0x0044, 0x0048);
        add_search_replace(0x0049, 0x004D);
        add_search_replace(0x004E, 0x0052);
        add_search_replace(0x0022, 0x0026);
        add_search_replace(0x0027, 0x002B);
        add_search_replace(0x002C, 0x0030);
        add_search_replace(0x0031, 0x0035);
        add_search_replace(0x0036, 0x0039);
        add_search_replace(0x0053, 0x0057);
        add_search_replace(0x0058, 0x005C);
        add_search_replace(0x005D, 0x0061);
        add_search_replace(0x0062, 0x0066);
        add_search_replace(0x0067, 0x006B);
        add_search_replace(0x006C, 0x0043);
        find_and_replace_multiple((void *)g_town_items, 0x5000);
        find_and_replace_multiple((void *)g_island_items, 0x1000);
    }
}

void    duplicate(void)
{
    u32     offset;
    u8      player;
    u32     dupe;
    u32     dupe0;
    u32     dupe1;
    u32     dupe2;
    u32     dupe3;
    u32     dupe4;
    u32     dupe5;
    u32     dupe6;

    if (is_pressed(BUTTON_R))
    {
        player = READU8(g_player);
        // Player 4 should be the highest value stored here. 
        // It goes to 0x7 when visiting a dream and someone's town I think?
        if (player <= 0x3)
        {
            offset = player * 0xA480;
            dupe = READU32(g_inv + offset);
            WRITEU32(g_inv + offset + 0x4, dupe);
            if (READU16(g_online4_inv) != 0)
                dupe4 = READU32(g_online4_inv);
                WRITEU32(g_online4_inv + 0x4, dupe4);
            if (READU16(g_online5_inv) != 0)
                dupe5 = READU32(g_online5_inv);
                WRITEU32(g_online5_inv + 0x4, dupe5); 
            if (READU16(g_online6_inv) != 0)
                dupe6 = READU32(g_online6_inv);
                WRITEU32(g_online6_inv, dupe6); 
        }
        if (player >= 0x3)
        {
            if (READU16(g_online0_inv) != 0)
                dupe0 = READU32(g_online0_inv);
                WRITEU32(g_online0_inv + 0x4, dupe0);
            if (READU16(g_online1_inv) != 0)
                dupe1 = READU32(g_online1_inv);
                WRITEU32(g_online1_inv + 0x4, dupe1);
            if (READU16(g_online2_inv) != 0)
                dupe2 = READU32(g_online2_inv);
                WRITEU32(g_online2_inv + 0x4, dupe2);
            if (READU16(g_online3_inv) != 0)
                dupe3 = READU32(g_online3_inv);
                WRITEU32(g_online3_inv + 0x4, dupe3);
        }  
    }
}

void    grass(void)
{
    if (is_pressed(BUTTON_R + BUTTON_A))
    {
        int i;

        for (i = g_grass_start; i < g_grass_end; i++)
            *(u32 *)i = 0xFFFFFFFF;
        wait_all_released();
    }
}

void    desert(void)
{
    if (is_pressed(BUTTON_R + BUTTON_A))
    {
        int i;

        for (i = g_grass_start; i < g_grass_end; i++)
            *(u32 *)i = 0x00000000;
        wait_all_released();
    }
}

void    nook_common(int value)
{
    WRITEU16(g_nook, 0x0101 * value);
    WRITEU8(g_leif, value == 1 ? 2 : value);
}

void    nook1(void)
{
    nook_common(1);
}

void    nook2(void)
{
    nook_common(2);
}

void    nook3(void)
{
    nook_common(3);
}

void    nook4(void)
{
    nook_common(4);
}

extern char    tan_level_buffer[40];
extern int     g_increase_menu_index;
extern int     g_decrease_menu_index;

void    set_current_tan_level(u8 value)
{
    u8      player;
    u32     offset;

    offset = 0;
    player = READU8(g_player);
    if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
    {
        offset = player * 0xA480;
    }
    WRITEU8(g_tan + offset, value);
}

u8      get_current_tan_level(void)
{
    u8      player;
    u32     offset;
    u8      current_level;

    offset = 0;
    player = READU8(g_player);
    if (player <= 3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
    {
        offset = player * 0xA480;
    }
    current_level = READU8(g_tan + offset);
    return (current_level);
}

void    update_tan_entry(void)
{
    u8 current_level;

    current_level = get_current_tan_level();
    xsprintf(tan_level_buffer, "Current tan level: %d", current_level);
}

void    increase_tan_level(void)
{
    u8  current_level;

    current_level = get_current_tan_level();
    if (current_level < 0xF)
        current_level++;
    else
        current_level = 0;
    set_current_tan_level(current_level);
    update_tan_entry();
    disableCheat(g_increase_menu_index);
}

void    decrease_tan_level(void)
{
    u8  current_level;

    current_level = get_current_tan_level();
    if (current_level > 0)
        current_level--;
    else
        current_level = 0xF;
    set_current_tan_level(current_level);
    update_tan_entry();
    disableCheat(g_decrease_menu_index);
}

void    moonjump(void)
{
    int     loc;
    u32     height;

    if (!(any_is_pressed(R)) && is_pressed(BUTTON_L)) //it's better to test the negation first
    {
        loc = READU32(g_location);
        height = READU32(g_outdoor_pos_y);
        if (height >= 0x440F0000)
        {
            if (loc == -1)
            {
                WRITEU32(g_outdoor_pos_y, 0x440F0000);
            }
            else
            {
                WRITEU32(g_indoor_pos_y, 0x440F0000);
            }
        }
        else
        {
            if (loc == -1)
            {
                ADDTOFLOAT(g_outdoor_pos_y, 6.0);
            }
            else
            {
                ADDTOFLOAT(g_indoor_pos_y, 6.0);
            }
        }   
    }
}

void    edibleItems(void)
{
    int     input;

    //islandFinder();
    if (is_pressed(BUTTON_L))
    {
        get_input_id(&input, NULL);
        WRITEU16(g_edible, input);
    }
}

void    seeder(void)
{
    int     input;

    if (!is_pressed(BUTTON_R))
        return;
    get_input_id(&input, NULL);
    if (is_pressed(BUTTON_R + A))
    {
        WRITEU32(g_seed, 0x80000000 + input);
    }
    else
    {        
        WRITEU16(g_seed, input);
    }
}

void    timeMachine(void)
{
    u16         *id = (u16 *)g_id;
    char        yy_str[3] = { 0 };
    char        mm_str[3] = { 0 };
    char        dd_str[3] = { 0 };
    char        hh_str[3] = { 0 };
    char        mz_str[3] = { 0 };
    s64         res_year = 0;
    s64         res_month = 0;
    s64         res_day = 0;
    s64         res_hour = 0;
    s64         res_min = 0;
    s64         res_nansec = 0;
    s64         res_plmn = 1;

    if (is_pressed(BUTTON_Y + BUTTON_DR))
    {
        yy_str[0] = (char)READU8(id + 0);
        yy_str[1] = (char)READU8(id + 1);
        mm_str[0] = (char)READU8(id + 2);
        mm_str[1] = (char)READU8(id + 3);
        dd_str[0] = (char)READU8(id + 4);
        dd_str[1] = (char)READU8(id + 5);
        hh_str[0] = (char)READU8(id + 6);
        hh_str[1] = (char)READU8(id + 7);
        mz_str[0] = (char)READU8(id + 8);
        mz_str[1] = (char)READU8(id + 9);
        if ((char)READU8(id + 10) == 45) //minus
            res_plmn = -1;
        res_year = (s64)strtoul(yy_str, NULL, 16);
        res_month = (s64)strtoul(mm_str, NULL, 16);
        res_day = (s64)strtoul(dd_str, NULL, 16);
        res_hour = (s64)strtoul(hh_str, NULL, 16);
        res_min = (s64)strtoul(mz_str, NULL, 16);
    
        res_year = res_year * (365 * 24 * 60 * 60) * (1000000000); //(year to seconds) * (seconds to nanoseconds)
        res_month = res_month * (28 * 24 * 60 * 60) * (1000000000); //("month" to seconds) * (seconds to nanoseconds)
        res_day = res_day * (24 * 60 * 60) * (1000000000); //(day to seconds) * (seconds to nanoseconds)
        res_hour = res_hour * (60 * 60) * (1000000000); //(hour to seconds) * (seconds to nanoseconds)
        res_min = res_min * (60) * (1000000000); //(minute to seconds) * (seconds to nanoseconds)
    
        res_nansec = (res_year + res_month + res_day + res_hour + res_min) * res_plmn;

        ADD64(g_savetime, res_nansec);
        ADD64(g_realtime, res_nansec);
        wait_keys_released(DR);
    }
    
    if (is_pressed(BUTTON_Y + BUTTON_DL))
    {
        yy_str[0] = (char)READU8(id + 0);
        yy_str[1] = (char)READU8(id + 1);
        mm_str[0] = (char)READU8(id + 2);
        mm_str[1] = (char)READU8(id + 3);
        dd_str[0] = (char)READU8(id + 4);
        dd_str[1] = (char)READU8(id + 5);
        hh_str[0] = (char)READU8(id + 6);
        hh_str[1] = (char)READU8(id + 7);
        mz_str[0] = (char)READU8(id + 8);
        mz_str[1] = (char)READU8(id + 9);
        if ((char)READU8(id + 10) == 45) //minus
            res_plmn = -1;
        res_year = (s64)strtoul(yy_str, NULL, 16);
        res_month = (s64)strtoul(mm_str, NULL, 16);
        res_day = (s64)strtoul(dd_str, NULL, 16);
        res_hour = (s64)strtoul(hh_str, NULL, 16);
        res_min = (s64)strtoul(mz_str, NULL, 16);
    
        res_year = res_year * (365 * 24 * 60 * 60) * (1000000000); //(year to seconds) * (seconds to nanoseconds)
        res_month = res_month * (28 * 24 * 60 * 60) * (1000000000); //("month" to seconds) * (seconds to nanoseconds)
        res_day = res_day * (24 * 60 * 60) * (1000000000); //(day to seconds) * (seconds to nanoseconds)
        res_hour = res_hour * (60 * 60) * (1000000000); //(hour to seconds) * (seconds to nanoseconds)
        res_min = res_min * (60) * (1000000000); //(minute to seconds) * (seconds to nanoseconds)
    
        res_nansec = (res_year + res_month + res_day + res_hour + res_min) * res_plmn;

        SUB64(g_savetime, res_nansec);
        SUB64(g_realtime, res_nansec);
        wait_keys_released(DL);
    }
}

void    timeTravel(void)
{
    if(is_pressed(BUTTON_B + BUTTON_DR))
    {
        ADD64(g_savetime, 0x34630B8A000);
        ADD64(g_realtime, 0x34630B8A000);
        wait_keys_released(DR);
    }
    if(is_pressed(BUTTON_B + BUTTON_DL))
    {
        SUB64(g_savetime, 0x34630B8A000);
        SUB64(g_realtime, 0x34630B8A000);
        wait_keys_released(DL);
    }
    if(is_pressed(BUTTON_B + BUTTON_DD))
    {
        WRITES64(g_savetime, 0x0000000000000000);
        WRITES64(g_realtime, 0x0000000000000000);
    }
    if(is_pressed(BUTTON_R + BUTTON_DR))
    {
        ADD64(g_savetime, 0xdf8475800);
        ADD64(g_realtime, 0xdf8475800);
    }
    if(is_pressed(BUTTON_R + BUTTON_DL))
    {
        SUB64(g_savetime, 0xdf8475800);
        SUB64(g_realtime, 0xdf8475800);
    }
}

void    real(void)
{
    u32            x;
    u32            y;
    u32            reg0;
    u32            reg1;
    u32            offset;
    static u32     item;
    int            input;

    if (is_pressed(BUTTON_R + BUTTON_DD))
    {
        x = READU32(g_world_x);
        y = READU32(g_world_y);
        if (x >= 0x10 && y >= 0x10)
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
            offset = reg0 + reg1 + x + y;           
            get_input_id(&input, NULL);
            WRITEU16(g_town_items + offset, input);
        }
    }
    if (is_pressed(BUTTON_L + BUTTON_DU))
    {
        x = READU32(g_world_x);
        y = READU32(g_world_y);
        if (x >= 0x10 && y >= 0x10)
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
            offset = reg0 + reg1 + x + y;           
            item = READU32(g_town_items + offset);
        }
    }
    if (is_pressed(BUTTON_L + BUTTON_DD))
    {
        x = READU32(g_world_x);
        y = READU32(g_world_y);
        if (x >= 0x10 && y >= 0x10)
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
            offset = reg0 + reg1 + x + y;           
            WRITEU32(g_town_items + offset, item);
        }
    }
}


void    dynamicMod(void)
{
    u32     offset;
    u8      player;
    u16     data;

    if (is_pressed(BUTTON_Y + BUTTON_DR))
    {
        data = READU16(g_abd);
        player = READU8(g_player);
        if (player <= 0x3)
        {
            offset = player * 0xA480;
            WRITEU16(g_inv + offset, data);
            if (READU16(g_online4_inv) != 0)
                WRITEU16(g_online4_inv, data);
            if (READU16(g_online5_inv) != 0)
                WRITEU16(g_online5_inv, data); 
            if (READU16(g_online6_inv) != 0)
                WRITEU16(g_online6_inv, data); 
        }
        if (player >= 0x3)
        {
            if (READU16(g_online0_inv) != 0)
                WRITEU16(g_online0_inv, data);
            if (READU16(g_online1_inv) != 0)
                WRITEU16(g_online1_inv, data);
            if (READU16(g_online2_inv) != 0)
                WRITEU16(g_online2_inv, data);
            if (READU16(g_online3_inv) != 0)
                WRITEU16(g_online3_inv, data);
        }  
    }   
}

void    walkOver(void)
{
    if (is_pressed(BUTTON_L + BUTTON_DU))
    {
        WRITEU8(g_walkOver, 0x83);
    }
    if (is_pressed(BUTTON_L + BUTTON_DD))
    {
        WRITEU8(g_walkOver, 0x00);
    }
}

// Text to cheat functions

void    midnight(void)
{
    u8  hours;
    u8  minutes;
    u32 reg0;
    u32 reg1;
    u64 time;

    hours = READU8(g_hours);
    minutes = READU8(g_minutes);
    reg0 = 0x17 - hours;
    reg1 = 0x3c - minutes;
    time = (reg0 * 0x34630B8A000) + (reg1 * 0xDF8475800);
    ADD64(g_realtime, time);
    ADD64(g_savetime, time);
}

void    morning(void)
{
    u8  hours;
    u8  minutes;
    u32 reg0;
    u32 reg1;
    u64 time;

    hours = READU8(g_hours);
    minutes = READU8(g_minutes);
    if (hours <= 0x6)
    {
        reg0 = 0x6 - hours;
        reg1 = 0x3c - minutes;
        time = (reg0 * 0x34630B8A000) + (reg1 * 0xDF8475800);
        ADD64(g_realtime, time);
        ADD64(g_savetime, time);    
    }
    else
    {
        reg0 = hours - 0x6;
        reg1 = minutes;
        time = (reg0 * 0x34630B8A000) + (reg1 * 0xDF8475800);
        SUB64(g_realtime, time);
        SUB64(g_savetime, time);            
    }
}

void    noon(void)
{
    u8  hours;
    u8  minutes;
    u32 reg0;
    u32 reg1;
    u64 time;

    hours = READU8(g_hours);
    minutes = READU8(g_minutes);
    if (hours <= 0xB)
    {
        reg0 = 0xB - hours;
        reg1 = 0x3c - minutes;
        time = (reg0 * 0x34630B8A000) + (reg1 * 0xDF8475800);
        ADD64(g_realtime, time);
        ADD64(g_savetime, time);    
    }
    else
    {
        reg0 = hours - 0xB;
        reg1 = minutes;
        time = (reg0 * 0x34630B8A000) + (reg1 * 0xDF8475800);
        SUB64(g_realtime, time);
        SUB64(g_savetime, time);            
    }    
}

void    stalking_1(void)
{
    static int loc;
    u32 x;
    u32 z;

    loc = READU32(g_location);
    if (loc == -1)
    {
        x = READU32(g_visitor_outdoor_x);
        z = READU32(g_visitor_outdoor_z);
        if (X != 0)
            WRITEU32(g_outdoor_pos_x, x);
            WRITEU32(g_outdoor_pos_z, z);
    }
    else
    {
        x = READU32(g_visitor_indoor_x);
        z = READU32(g_visitor_indoor_z);
        if (x != 0)
            WRITEU32(g_indoor_pos_x, x);
            WRITEU32(g_indoor_pos_z, z);
    }
}

void    gorgeous_set(void)
{
    u32 offset;
    u8 player;
    int i;

    player = READU8(g_player);
    if (player <= 0x3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
        offset = player * 0xa480;
        WRITEU16(g_inv + offset, 0x2401);
        WRITEU16(g_inv + offset + 0x4, 0x2362);
        for (i = 0; i < 10; i++)
        {
            WRITEU16(g_inv + offset + 0x8 + (0x4 * i), 0x2ADC + i);
        }
        if (READU16(g_online4_inv != 0x0))
            WRITEU16(g_online4_inv, 0x2401);
            WRITEU16(g_online4_inv + 0x4, 0x2362);
            for (i = 0; i < 10; i++)
            {
                WRITEU16(g_online4_inv + 0x8 + (0x4 * i), 0x2ADC + i);
            }
       if (READU16(g_online5_inv != 0x0))
            WRITEU16(g_online5_inv, 0x2401);
            WRITEU16(g_online5_inv + 0x4, 0x2362);
            for (i = 0; i < 10; i++)
            {
                WRITEU16(g_online5_inv + 0x8 + (0x4 * i), 0x2ADC + i);
            }
       if (READU16(g_online6_inv != 0x0))
            WRITEU16(g_online6_inv, 0x2401);
            WRITEU16(g_online6_inv + 0x4, 0x2362);
            for (i = 0; i < 10; i++)
            {
                WRITEU16(g_online5_inv + 0x8 + (0x4 * i), 0x2ADC + i);
            }
    if (player >= 0x3)
    {
        if (READU16(g_online0_inv != 0x0))
            WRITEU16(g_online0_inv, 0x2401);
            WRITEU16(g_online0_inv + 0x4, 0x2362);
            for (i = 0; i < 10; i++)
            {
                WRITEU16(g_online0_inv + 0x8 + (0x4 * i), 0x2ADC + i);
            }
       if (READU16(g_online1_inv != 0x0))
            WRITEU16(g_online1_inv, 0x2401);
            WRITEU16(g_online1_inv + 0x4, 0x2362);
            for (i = 0; i < 10; i++)
            {
                WRITEU16(g_online1_inv + 0x8 + (0x4 * i), 0x2ADC + i);
            }
       if (READU16(g_online2_inv != 0x0))
            WRITEU16(g_online2_inv, 0x2401);
            WRITEU16(g_online2_inv + 0x4, 0x2362);
            for (i = 0; i < 10; i++)
            {
                WRITEU16(g_online2_inv + 0x8 + (0x4 * i), 0x2ADC + i);
            }
       if (READU16(g_online3_inv != 0x0))
            WRITEU16(g_online3_inv, 0x2401);
            WRITEU16(g_online3_inv + 0x4, 0x2362);
            for (i = 0; i < 10; i++)
            {
                WRITEU16(g_online3_inv + 0x8 + (0x4 * i), 0x2ADC + i);
            }
    }
}

void    clear_inv(void)
{
    u32 offset;
    u8 player;
    int i;

    player = READU8(g_player);
    if (player <= 0x3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
        offset = player * 0xa480;
        for (i = 0; i < 16; i++)
        {
            WRITEU16(g_inv + offset + (0x4 * i), 0x7FFE);
        }
        if (READU16(g_online4_inv) != 0)
            for (i = 0; i < 16; i++)
            {
                WRITEU16(g_online4_inv + offset + (0x4 * i), 0x7FFE);
            }
        if (READU16(g_online5_inv) != 0)
            for (i = 0; i < 16; i++)
            {
                WRITEU16(g_online5_inv + offset + (0x4 * i), 0x7FFE);
            }
        if (READU16(g_online6_inv) != 0)
            for (i = 0; i < 16; i++)
            {
                WRITEU16(g_online1_inv + offset + (0x4 * i), 0x7FFE);
            }
    if (player >= 0x3)
    {
        if (READU16(g_online0_inv) != 0)
            for (i = 0; i < 16; i++)
            {
                WRITEU16(g_online0_inv + offset + (0x4 * i), 0x7FFE);
            }
        if (READU16(g_online1_inv) != 0)
            for (i = 0; i < 16; i++)
            {
                WRITEU16(g_online1_inv + offset + (0x4 * i), 0x7FFE);
            }
        if (READU16(g_online2_inv) != 0)
            for (i = 0; i < 16; i++)
            {
                WRITEU16(g_online2_inv + offset + (0x4 * i), 0x7FFE);
            }
        if (READU16(g_online3_inv) != 0)
            for (i = 0; i < 16; i++)
            {
                WRITEU16(g_online3_inv + offset + (0x4 * i), 0x7FFE);
            }
    }
}

void    bank_common(u32 enc1, u32 enc2)
{
    u32     offset;
    u8      player;

    {   
        player = READU8(g_player);
        if (player <= 0x3)
        {
            offset = player * 0xA480;
            WRITEU32(g_bank + offset, enc1);
            WRITEU32(g_bank + offset + 0x4, enc2);
            if (READU32(g_online4_bank) != 0)
                WRITEU32(g_online4_bank, enc1);
                WRITEU32(g_online4_bank + 0x4, enc2);
            if (READU32(g_online5_bank) != 0)
                WRITEU32(g_online5_bank, enc1);
                WRITEU32(g_online5_bank + 0x4, enc2);
            if (READU32(g_online5_bank) != 0);
                WRITEU32(g_online6_bank, enc1);
                WRITEU32(g_online6_bank + 0x4, enc2);
        }
  
        if (player >= 0x3)
        {
            if (READU32(g_online0_bank) != 0);
                WRITEU32(g_online0_bank, enc1);
                WRITEU32(g_online0_bank + 0x4, enc2);
            if (READU32(g_online1_bank) != 0);
                WRITEU32(g_online1_bank, enc1);
                WRITEU32(g_online1_bank + 0x4, enc2);
            if (READU32(g_online2_bank) != 0);
                WRITEU32(g_online2_bank, enc1);
                WRITEU32(g_online2_bank + 0x4, enc2);
            if (READU32(g_online3_bank) != 0);
                WRITEU32(g_online3_bank, enc1);
                WRITEU32(g_online3_bank + 0x4, enc2);
        }
    }
}

void    bank_999m(void)
{
    bank_common(bell999M1, bell999M2);
}

void   bank_1m(void)
{
    bank_common(bell1M1, bell1M2);
}

void    bank_0m(void)
{
    bank_common(bell0k1, bell0k2);
}

void    wallet_common(u32 enc1, u32 enc2)
{
    u32     offset;
    u8      player;

    {   
        player = READU8(g_player);
        if (player <= 0x3)
        {
            offset = player * 0xA480;
            WRITEU32(g_wallet + offset, enc1);
            WRITEU32(g_wallet + offset + 0x4, enc2);
            if (READU32(g_online4_wallet) != 0)
                WRITEU32(g_online4_wallet, enc1);
                WRITEU32(g_online4_wallet + 0x4, enc2);
            if (READU32(g_online5_wallet) != 0)
                WRITEU32(g_online5_wallet, enc1);
                WRITEU32(g_online5_wallet + 0x4, enc2);
            if (READU32(g_online5_wallet) != 0);
                WRITEU32(g_online6_wallet, enc1);
                WRITEU32(g_online6_wallet + 0x4, enc2);
        }
  
        if (player >= 0x3)
        {
            if (READU32(g_online0_wallet) != 0);
                WRITEU32(g_online0_wallet, enc1);
                WRITEU32(g_online0_wallet + 0x4, enc2);
            if (READU32(g_online1_wallet) != 0);
                WRITEU32(g_online1_wallet, enc1);
                WRITEU32(g_online1_wallet + 0x4, enc2);
            if (READU32(g_online2_wallet) != 0);
                WRITEU32(g_online2_wallet, enc1);
                WRITEU32(g_online2_wallet + 0x4, enc2);
            if (READU32(g_online3_wallet) != 0);
                WRITEU32(g_online3_wallet, enc1);
                WRITEU32(g_online3_wallet + 0x4, enc2);
        }
    }
}

void    wallet_99k(void)
{
    wallet_common(bell99k1, bell99k2);
}

void   wallet_0k(void)
{
    wallet_common(bell0k1, bell0k2);
}

void    wallet_out(void)
{
    wallet_common(bellBound1, bellBound2);
}

void    wallet_neg(void)
{
    wallet_common(bellNeg1, bellNeg2);
}


void    canBuy(void)
{
    WRITEU8(g_confirm, 0x01);
}

void    nookFree(void)
{
    WRITEU32(g_nook1Price, 0x00000000);
    WRITEU32(g_nook2Price, 0x00000000);
}

void    changeAnimal(u8 symbols[], u8 name[])
{
    static u8 original[] = {0x25, 0x73, 0x2E, 0x62, 0x63, 0x72, 0x65, 0x73, 0x00};
    u8 roomID;
    roomID = READU8(g_room);

    if (roomID == 0x63)
    {
        memcpy((void *)(g_npc), original, 9);
        memcpy((void *)(g_isabelle), name, 3); 
    }
    else if (roomID == 0x00)
    {
        memcpy((void *)(g_npc), original, 9);
        memcpy((void *)(g_kappn), name, 3);
    }
    else
    {
        memcpy((void *)(g_npc), symbols, 9);        
    }
}

void   changeOwl(void)
{
    //0x9513CD is_loading boolean?
    static u8 name[] = {0x6f, 0x77, 0x6c};
    static u8 symbols[] = {0x6F, 0x77, 0x6C, 0x2E, 0x62, 0x63, 0x72, 0x65, 0x73};
    changeAnimal(symbols, name);
}

void changeNook(void)
{
    static u8 name[] = {0x72, 0x63, 0x69};
    static u8 symbols[] = {0x72, 0x63, 0x69, 0x2E, 0x62, 0x63, 0x72, 0x65, 0x73};
    changeAnimal(symbols, name);
}

void changeBrewster(void)
{
    static u8 name[] = {0x70, 0x67, 0x65};
    static u8 symbols[] = {0x70, 0x67, 0x65, 0x2e, 0x62, 0x63, 0x72, 0x65, 0x73};
    changeAnimal(symbols, name);
}


void    all_badges(u8 bdge)
{
    u32     offset;
    u8      player;
    int     i;

    if(is_pressed(BUTTON_Y))
    {
        player = READU8(g_player);
        if (player <= 0x3)
        {
            offset = player * 0xA480;
            for (i = 0; i < 24; i++)
            {
                WRITEU8(g_badge + offset + (0x1 * i), bdge);
            }
        }
    }
}

void    badge_gold(void)
{
    all_badges(0x3);
}

void    badge_silver(void)
{
    all_badges(0x2);
}

void    badge_bronze(void)
{
    all_badges(0x1);
}

void    badge_none(void)
{
    all_badges(0x0);
}
void collisions(void)
{
    if (is_pressed(BUTTON_L + BUTTON_DU))
    {
        if (READU16(g_cond) == 0x7FFE)
        {
            WRITEU16(g_collision, 0x00FF);
            WRITEU8(g_col0, 0x01);
            WRITEU16(g_col1, 0x003F);
        }
        else if (READU16(g_cond0) == 0x7FFE)
        {
            WRITEU8(g_grav, 0x00);
            WRITEU16(g_grav0, 0x00FF);
        }
    }
    if (is_pressed(BUTTON_R))
    {
        if (READU16(g_cond) == 0x7FFE)
        {
            WRITEU8(g_col0, 0x00);
            WRITEU16(g_collision, 0xFFFF);           
        }
        else if (READU16(g_cond0) == 0x7FFE)
        {
            WRITEU8(g_grav, 0x00);
            WRITEU16(g_grav0, 0xFFFF);
        }

    }
    if (is_pressed(BUTTON_L + BUTTON_DD))
    {
        if (READU16(g_cond) == 0x7FFE)
        {
            WRITEU16(g_collision, 0x00FA);
            WRITEU8(g_col0, 0x01);
            WRITEU16(g_col1, 0x0036);
        }
        else if (READU16(g_cond0) == 0x7FFE)
        {
            WRITEU16(g_grav, 0x0000);
            WRITEU16(g_grav0, 0x00FA);
        }
    }
}

void    turnip_all(u32 enc1, u32 enc2)
{
    int     i;

    if(is_pressed(BUTTON_Y))
    {
        for (i = 0; i < 12; i++)
        {
        WRITEU32(g_turnip + (0x8 * i), enc1);
        WRITEU32(g_turnip + 0x4 + (0x8 * i), enc2);
        }
    }
}

void    turnip_990(void)
{
    turnip_all(bell990_1, bell990_2);
}
void	turnip_990(void)
{
	turnip_all(bell990_1, bell990_2);
}
