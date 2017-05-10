#include "cheats.hpp"
#include <cstring>
#include <cstdlib>

namespace CTRPluginFramework
{
    extern u32  g_find[100];
    extern u32  g_replace[100];
    extern int  g_i;
    extern u32  g_input_text_buffer;

    void    find_and_replace_multiple(u32 start_addr, u32 length)
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

    void    retrieve_input_string(char *output, int size)
    {
        // TODO: properly managing wide char
        char    buffer[0x100];
        int     i;

        if (!output || size < 1)
            goto error;
        size *= 2;
        memcpy(buffer, (void *)g_input_text_buffer, size > 0x100 ? 0x100 : size);
        for (i = 0; i < size; i++)
            *output++ = *(buffer + i++);
        error:
            return;
    }

    void    get_input_id(int *first, int *second)
    {
        char    buffer[13];
        char    *pointer_id;
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

    bool    match(const char *str, const char *pattern)
    {
        int     pattern_size;

        pattern_size = strlen(pattern);
        if (strncmp(str, pattern, pattern_size) == 0)
            return (true);
        return (false);
    }
}