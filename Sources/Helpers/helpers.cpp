#include "cheats.hpp"
#include <cstring>
#include <cstdarg>

namespace CTRPluginFramework
{
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
		u16 adjust = Utils::Random(0, 0x10000);
		u8  shift_val = Utils::Random(0, 0x1A);

		// Encipher value
		u32 enc = dec + adjust + 0x8F187432;
		enc = (enc >> (0x1C - shift_val)) + (enc << (shift_val + 4));

		// Calculate Checksum
		u8  chk = (((enc >> 0) + (enc >> 8) + (enc >> 16) + (enc >> 24) + 0xBA) & 0xFF);

		// Pack result
		return ((u64)enc << 0) | ((u64)adjust << 32) | ((u64)shift_val << 48) | ((u64)chk << 56);
	}

	u8* memsearch(u8* startPos, const void* pattern, u32 size, u32 patternSize)
	{
		const u8* patternc = (const u8*)pattern;
		u32 table[256];

		//Preprocessing
		for (u32 i = 0; i < 256; i++)
			table[i] = patternSize;
		for (u32 i = 0; i < patternSize - 1; i++)
			table[patternc[i]] = patternSize - i - 1;

		//Searching
		u32 j = 0;
		while (j <= size - patternSize)
		{
			u8 c = startPos[j + patternSize - 1];
			if (patternc[patternSize - 1] == c && memcmp(pattern, startPos + j, patternSize - 1) == 0)
				return startPos + j;
			j += table[c];
		}

		return nullptr;
	}

	char Sstrncpy(char* dest, const char* src, size_t n) //'Safe' strncpy, always null terminates
	{
		strncpy(dest, src, n);
		return dest[n] = '\0';
	}

	bool	Range(u32 value, u32 low, u32 high)
	{
		return(low <= value && value <= high); // return whether or not if the value is in a range
	}

	u32		FollowPointer(u32 pointer, ...)
	{
		u32 offset;
		va_list pointers;
		va_start(pointers, pointer);
		if (!Process::Read32(pointer, offset) || !Range(offset, 0x100000, 0x40000000)) // since the inital pointer will be a valid offset(we assumme anyways...) do a read32 call to it and store in offset
			return -1;
		pointer = va_arg(pointers, u32); // go to next argument
		while (pointer != -1) // the last arg needs to be -1 in order for the while loop to exit
		{
			if (!Process::Read32(offset + pointer, offset) || !Range(offset, 0x100000, 0x40000000))
				return -1;
			pointer = va_arg(pointers, u32);
		}
		va_end(pointers);
		return offset;
	}
}
