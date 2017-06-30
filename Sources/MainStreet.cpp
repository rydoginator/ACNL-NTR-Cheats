#include "cheats.hpp"

namespace CTRPluginFramework
{
	void	FillMainStreet(MenuEntry *entry)
	{
		u32 nook = reinterpret_cast<u32>(Game::Nook);  
    	Process::Write8(nook + 0x45C8, 0x2); //Kicks
    	Process::Write8(nook + 0x8A58, 0x1); //Museum Shop
    	Process::Write8(nook + 0x8B1E, 0x2); //Club LOL
    	Process::Write8(nook + 0x8B3E, 0x1); //Dream Suite
        Process::Write8(nook + 0x8B40, 0x1); //Fortune Teller
        Process::Write8(nook + 0x8B50, 0x2); //Shampoodle
	}

	void 	FillCatalog(MenuEntry *entry)
	{
		for (int i = 0; i < 0x90; i++)
		{
			Player::GetInstance()->Write32(0x6C90 + (i * 4), 0xFFFFFFFF);
		}
	}
}