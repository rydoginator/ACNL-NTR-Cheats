#include "cheats.h"

extern u32  g_find[100];
extern u32  g_replace[100];
extern int  g_i;

void    find_and_replace_multiple(void *start_addr, u32 length)
{
    u32 find_value;
    u32 replace_value;
    int i;

    i = 0;
    while (length-- > 0)
    {
        for (i = 0; i < g_i; i++)
        {
            find_value = g_find[i];
            replace_value = g_replace[i];
            if (*(u16 *)start_addr == find_value)
            {
                *(u16 *)start_addr = replace_value;
                break;
            }
        }
        start_addr += 4;
    }
}

void    keep_it_off(void)
{
    // Keep the warning entry disabled
    disableCheat(3);
}

void    retrieve_input_string(char *output, int size)
{
    const u32   input_buffer_address = 0x32cb0f60;

    if (!output || size < 1)
        goto error;
    memcpy(output, (void *)input_buffer_address, size);
    error:
        return;
}

void    get_input_id(int *first, int *second)
{
    char    buffer[13];
    char    *pointer_id;
    int     input;
    int     hex_pattern;

    if (!first)
        goto error;
    memset(buffer, 0, 13);
    retrieve_input_string(buffer, second ? 12 : 6);
    // Checking for 0x or 0X pattern before ID
    if (buffer[0] == '0' 
    && (buffer[1] == 'x' || buffer[1] == 'X'))
        hex_pattern = 1;
    else
        hex_pattern = 0;
    // If we want to fetch two ids
    if (second)
    {
        if (hex_pattern)
        {
            if (buffer[6] == '0' 
            && (buffer[7] == 'x' || buffer[7] == 'X'))
                pointer_id = buffer + 8;
            else
            {
                pointer_id = buffer + 6;
                buffer[10] = 0;
            }
        }
        else
        {
            if (buffer[4] == '0' 
            && (buffer[5] == 'x' || buffer[5] == 'X'))
            {
                pointer_id = buffer + 6;
                buffer[10] = 0;
            }
            else
            {
                pointer_id = buffer + 4;
                buffer[8] = 0;
            }
        }
        *second = (int)strtoul(pointer_id, NULL, 16);       
    }
    if (hex_pattern)
    {
        pointer_id = buffer + 2;
        buffer[6] = 0;
    }
    else
    {
        pointer_id = buffer;
        buffer[4] = 0;
    }
    *first = (int)strtoul(pointer_id, NULL, 16);
error:
    return;
}
