#ifndef VALUES_HPP
#define VALUES_HPP

#include "types.h"

struct IDs
{
    u8              id;
    const char *    Name;
};

struct Building
{
    u8 id;
    const char *Name;
    bool IsEvent;
};

extern const Building buildingIDS[178];
extern const IDs    rooms[129];
extern const IDs    regions[15];

/*
** Values
*/

#define     EUR_DIFFERENCE                      0x28380
#define     JAP_DIFFERENCE                      0x22A80

#define     ITEM_BYTES                          0x04
#define     RANGE_TOWN_ITEMS                    0x5000

#endif
