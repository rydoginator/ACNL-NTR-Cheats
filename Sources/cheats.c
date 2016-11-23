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
u32     g_collisions;
u32     g_input_text_buffer;
u32     g_hours;
u32     g_minutes;

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
    g_collisions = USA_COLLISIONS_ADDR;
    g_hours = USA_HOURS_ADDR;
    g_minutes = USA_MINUTES_ADDR;

    // applying offset or particular address
    switch (region)
    {
        case USA:
            g_input_text_buffer = USA_INPUT_TEXT_ADDR;
            break;
        case EUR:
            g_location -= 0x28380;
            g_indoor_pos_x -= 0x28380;
            g_indoor_pos_y -= 0x28380;
            g_indoor_pos_z -= 0x28380;
            g_outdoor_pos_x -= 0x28380;
            g_outdoor_pos_y -= 0x28380;
            g_outdoor_pos_z -= 0x28380;
            g_town_items -= 0x28380;
            g_island_items -= 0x28380;
            g_inv -= 0x28300;
            g_grass_start -= 0x28380;
            g_grass_end -= 0x28380;
            g_velocity -= 0x28380;
            g_nook -= 0x28380;
            g_leif -= 0x28380;
            g_tan -= 0x28380;
            g_edible -= 0x28380;
            g_id -= 0x28380;
            g_savetime -= 0x28380;
            g_world_x -= 0x28380;
            g_world_y -= 0x28380;
            g_collisions -= 0x28380;
            g_hours = 0x9505B7;
            g_minutes = 0x9505B6;
            g_realtime = 0x95c500;
            g_seed = 0x9B4268;
            g_player = 0xA86610;
            g_input_text_buffer = EUR_INPUT_TEXT_ADDR;
            break;
        case JAP:
            g_location += 0x22A80;
            g_indoor_pos_x += 0x22A80;
            g_indoor_pos_y += 0x22A80;
            g_indoor_pos_z += 0x22A80;
            g_outdoor_pos_x += 0x22A80;
            g_outdoor_pos_y += 0x22A80;
            g_outdoor_pos_z += 0x22A80;
            g_town_items += 0x22A80;
            g_island_items += 0x22A80;
            g_grass_start += 0x22A80;
            g_grass_end += 0x22A80;
            g_inv += 0x22A80;
            g_velocity += 0x22A80;
            g_nook += 0x22A80;
            g_leif += 0x22A80;
            g_tan += 0x22A80;
            g_id += 0x22A80;
            g_edible += 0x22A80;
            g_savetime += 0x22A80;
            g_world_x += 0x22A80;
            g_world_y += 0x22A80;
            g_hours = 0x9495B7;
            g_minutes = 0x9495B6;
            g_realtime = 0x956500;
            g_collisions += 0x22A80;
            g_seed = 0x9AD248;
            g_player = 0xAAD990;
            g_input_text_buffer = JAP_INPUT_TEXT_ADDR;
            break;
    }
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
    NOON
};

void    text_to_cheats(void)
{
    static int      last_command = 0;
    int             command;
    char            command_text[0x100];


    retrieve_input_string(command_text, 10);
    g_text_activated = true;
    if (match(command_text, "bis")) command = BIS;
    else if (match(command_text, "quench")) command = QUENCH;
    else if (match(command_text, "savetp")) command = SAVETP;
    else if (match(command_text, "restoretp")) command = RESTORETP;
    else if (match(command_text, "midnight")) command = MIDNIGHT;
    else if (match(command_text, "noon")) command = NOON;
    else if (match(command_text, "morning")) command = MORNING;
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
            case NOON:
                noon();
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
    
    player = READU8(g_player);
    if (player <= 0x3) //player 4 should be the highest value stored here. It goes to 0x7 when visiting a dream and someone's town I think?
        offset = player * 0xa480;
    if (!is_pressed(BUTTON_X + BUTTON_DR))
        return;
    get_input_id(&input, NULL);
    WRITEU16(g_inv + offset, input);
/*  WRITEU16(0xAB36E4, input); //player 2
    WRITEU16(0xABDB64, input); //player 3
    WRITEU16(0xAAb0e4, input); //player 4
    WRITEU16(0xA8C364, input); will look at this later.
    WRITEU16(0xAA0C60, input); */
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
    else //If noting is pressed then use slot0
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
    
 //   u32 dupe0 = 0;
 //   u32 dupe1 = 0;
 //   u32 dupe2 = 0;
 //   u32 dupe3 = 0;
 //   u32 dupe4 = 0;
 //   u32 dupe5 = 0;
    u32     dupe = 0;
    u32     offset;
    u8      player;
    /* OFFSETS FOUND 
    ** 0xAAb0e0 only player on island.
    ** 0xA8C360 2nd player on island.
    ** 0xAA0C60 3rd player on island.        
    */   
    if (is_pressed(BUTTON_R))
    {
        player = READU8(g_player);
        // Player 4 should be the highest value stored here. 
        // It goes to 0x7 when visiting a dream and someone's town I think?
        if (player <= 0x3)
        {
            offset = player * 0xA480;
        }
        dupe = READU32(g_inv + offset);
        //dupe0 = READU32(0xAB36E0); //online pointer0
        //dupe1 = READU32(0xABDB60); //online pointer1
        //dupe2 = READU32(0xAC7FE0); //online pointer2
        //dupe3 = READU32(0xAAb0e0);
        //dupe4 = READU32(0xA8C360);
        //dupe5 = READU32(0xAA0C60);
        WRITEU32(g_inv + offset + 0x4, dupe);
        //WRITEU32(0xAB36E4, dupe0); //player 2
        //WRITEU32(0xABDB64, dupe1); //player 3
        //WRITEU32(0xAC7FE4, dupe2); //player 4
        //WRITEU32(0xAAb0e4, dupe3);
        //WRITEU32(0xA8C364, dupe4);
        //WRITEU32(0xAA0C64, dupe5);
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

void    collisions(void)
{
    if (is_pressed(BUTTON_R + BUTTON_DU))
    {
        WRITEU8(g_collisions, 0x01);
    }
    if (is_pressed(BUTTON_R + BUTTON_DD))
    {
        WRITEU8(g_collisions, 0x00);
    }
}

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