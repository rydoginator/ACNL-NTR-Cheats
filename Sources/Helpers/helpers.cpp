#include "cheats.hpp"

namespace CTRPluginFramework
{
    int    RandomNum(int start, int end)
    {
        srand(svcGetSystemTick());

        int r[20];

        for (int i = 0; i < 20; i++)
            r[i] = rand() % (end - start + 1) + start;

        return (r[rand() % 20]);
    }

    //Credit to SciresM for this code! :)
    u32     DecryptACNLMoney(u64 money)
    {
        // Unpack 64-bit value into (u32, u16, u8, u8) values.
        u32 enc = (money & 0xFFFFFFFF);
        u16 adjust = ((money >> 32) & 0xFFFF);
        u8  shift_val = ((money >> 48) & 0xFF);
        u8  chk = ((money >> 56) & 0xFF);

        // Validate 8-bit checksum
        if ((((enc >> 0) + (enc >> 8) + (enc >> 16) + (enc >> 24) + 0xBA) & 0xFF) != chk) return 0;
        
        u8  left_shift = ((0x1C - shift_val) & 0xFF);
        u8  right_shift = 0x20 - left_shift;

        // Handle error case: Invalid shift value.
        if (left_shift >= 0x20)
        {
            return 0 + (enc << right_shift) - (adjust + 0x8F187432);
        }

        // This case should occur for all game-generated values.
        return (enc << left_shift) + (enc >> right_shift) - (adjust + 0x8F187432);
    }

    u64     EncryptACNLMoney(int dec)
    {
        // Make a new RNG
        u16 adjust = RandomNum(0, 0x10000);
        u8  shift_val = RandomNum(0, 0x1A);

        // Encipher value
        u32 enc = dec + adjust + 0x8F187432;
        enc = (enc >> (0x1C - shift_val)) + (enc << (shift_val + 4));

        // Calculate Checksum
        u8  chk = (((enc >> 0) + (enc >> 8) + (enc >> 16) + (enc >> 24) + 0xBA) & 0xFF);

        // Pack result
        return ((u64)enc << 0) | ((u64)adjust << 32) | ((u64)shift_val << 48) | ((u64)chk << 56);
    }
}