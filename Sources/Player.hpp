#include "CTRPluginFramework.hpp"
namespace CTRPluginFramework
{
    class Player
    {
    public:

        Player(void);
        ~Player(void){};

        // Return current player's ID
        int     GetId(void) const;
        // Return current player's offset
        u32     GetOffset(void) const;

        // Update current offset & ID
        void    Update(void);

        // Write data relative to player's offset
        //template <typename T>
        bool    Write(u32 offset, u32 value) const;


        //Copy memory relative to player's offset
        bool    CopyMemory(u32 offset, u16 value[]) const;

        // Return current Player instance
        static Player *GetInstance(void);
    private:
        int     _playerID;
        u32     _offset;

        static Player  *_instance;
    };
}