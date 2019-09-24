#ifndef OFFSETS_HPP
#define OFFSETS_HPP

#define     TO_EUR(x)   (x - EUR_DIFFERENCE)
#define     TO_JAP(x)   (x + JAP_DIFFERENCE)
#define     TO_WA_USA(x) (x - 0x42B00)
#define     TO_WA_EUR(x) (x - 0x41880)
#define     TO_WA_JAP(x) (x + 0x13200)

#define     USA_LOCATION_ADDR                   0x33077504
//#define     USA_INDOOR_POS_X_ADDR             0x330774fc
//#define     USA_INDOOR_POS_Y_ADDR             0x33077500
//#define     USA_INDOOR_POS_Z_ADDR             0x33077504
//#define     USA_OUTDOOR_POS_X_ADDR            0x330773D0
//#define     USA_OUTDOOR_POS_Y_ADDR            0x330773D4
//#define     USA_OUTDOOR_POS_Z_ADDR            0x330773D8
#define     USA_TOWN_ITEMS_ADDR                 0x31F7A458
#define     USA_ISLAND_ITEMS_ADDR               0x31F96E58
//#define     USA_PLAYER_ADDR                   0xAAE990 //0xAAD990, 0xAA6990
//#define     USA_INV_ADDR                      0x31F2DBF0
#define     USA_VELOCITY_ADDR                   0x330773FC
#define     USA_GRASS_START_ADDR                0x31F80880
#define     USA_GRASS_END_ADDR                  0x31F8307F
#define     USA_NOOK_ADDR                       0x31F891E4
//#define     USA_LEIF_ADDR                     0x31F8D674
//#define     USA_TAN_ADDR                      0x31F27028
//#define     USA_SEED_ADDR                     0x9B5268 //9AD248, 9B4268
//#define     USA_EDIBLE_ADDR                   0x33077C86
//#define     USA_ID_ADDR                       0x32CB0F60 
#define     USA_SAVETIME_ADDR                   0x31F89120

#define     USA_REALTIME_ADDR                   0x95D508 //955500, 95c500
#define     EUR_REALTIME_ADDR                   0x95c500
#define     JAP_REALTIME_ADDR                   0x956500
#define     USA_WA_REALTIME_ADDR                0x95C4E8
#define     EUR_WA_REALTIME_ADDR                0x95C500
#define     JAP_WA_REALTIME_ADDR                0x955500

#define     USA_WORLD_X_ADDR                    0x33077838
#define     USA_WORLD_Y_ADDR                    0x3307783C
//#define     USA_INPUT_TEXT_ADDR                 0x32CB0F60
//#define     EUR_INPUT_TEXT_ADDR                 0x32C88BE0
//#define     JAP_INPUT_TEXT_ADDR                 0x32CD39E0
#define     USA_BUILDING_ADDR                   0x31F72E08
//#define     USA_GENDER_ADDR                     0x31f2c5da
/*
#define     USA_VISITOR_OUTDOOR_X_ADDR          0x33079190
#define     USA_VISITOR1_OUTDOOR_X_ADDR         0x3307A2E0
#define     USA_VISITOR2_OUTDOOR_X_ADDR         0x3307B42C
#define     USA_VISITOR_OUTDOOR_Z_ADDR          0x33079198
#define     USA_VISITOR1_OUTDOOR_Z_ADDR         0x3307A2E8
#define     USA_VISITOR2_OUTDOOR_Z_ADDR         0x3307B434
#define     USA_VISITOR_INDOOR_X_ADDR           0x330792bc
#define     USA_VISITOR1_INDOOR_X_ADDR          0x3307A3F4
#define     USA_VISITOR2_INDOOR_X_ADDR          0x3307B77C
#define     USA_VISITOR_INDOOR_Z_ADDR           0x330792c4
#define     USA_VISITOR1_INDOOR_Z_ADDR          0x3307A3FC
#define     USA_VISITOR2_INDOOR_Z_ADDR          0x3307B784
*/
#define     USA_MINUTES_ADDR                    0x9515BA
#define     EUR_MINUTES_ADDR                    0x9505B6
#define     JAP_MINUTES_ADDR                    0x9840FB
#define     USA_WA_MINUTES_ADDR                 0x9505AA
#define     EUR_WA_MINUTES_ADDR                 0x9505B6
#define     JAP_WA_MINUTES_ADDR                 0x9495B6

#define     USA_HOURS_ADDR                      0x9515BB
#define     EUR_HOURS_ADDR                      0x9505B7
#define     JAP_HOURS_ADDR                      0x9840FC
#define     USA_WA_HOURS_ADDR                   0x9505AB
#define     EUR_WA_HOURS_ADDR                   0x9505B7
#define     JAP_WA_HOURS_ADDR                   0x9495B7


#define     USA_PLAYER_POINTER                  0xAB014C
#define     EUR_PLAYER_POINTER                  0xAAF14C
#define     JAP_PLAYER_POINTER                  0xAA914C
#define     USA_WA_PLAYER_POINTER               0xAAF14C
#define     EUR_WA_PLAYER_POINTER               0xAAF14C
#define     JAP_WA_PLAYER_POINTER               0xAA814C

#define     USA_GRAVITY_OUT_ADDR                0x33077537
/*
#define     USA_KEYBOARD_ADDR                   0x32DC4A10
#define     USA_KEYBOARD_ISLAND_ADDR            0x32DF7D14
#define     EUR_KEYBOAD_ISLAND_ADDR             0x32DCF994
#define     USA_INPUT_TEXT_ISLAND_ADDR          0x32CBD508
#define     USA_ABD_ADDR                        0x32DD1AC8 //this one stays in memory, so it is used to write to the inventory. nvm, it doesn't
#define     USA_ABD_REAL_ADDR                   0x32DD1EF8 //this one is the real decimal offset,
#define     USA_ABD_OFFLINE_ADDR                0x32DC5520
#define     USA_WALKOVER_ADDR                   0x33077533

#define     USA_CONDITIONAL_OUT_ADDR            0x33077524
#define     USA_CONDITIONAL_IN_ADDR             0x33077650
#define     USA_COLLISION_OUT_ADDR              0x33077534
#define     USA_COLLISION_IN_ADDR               0x33077663
#define     USA_QUICKFIRE_ADDR                  0x33077537

#define     USA_KEYBOARD_POINTER                0x95F110
#define     USA_BANK_ADDR                       0x31F2DBAC
#define     USA_ONLINE0_BANK_ADDR               0xAAB09C
#define     USA_ONLINE1_BANK_ADDR               0xA8C31C
#define     USA_ONLINE2_BANK_ADDR               0xA9679C
#define     USA_ONLINE3_BANK_ADDR               0xAA0C1C
#define     USA_ONLINE4_BANK_ADDR               0xA8C31C
#define     USA_ONLINE5_BANK_ADDR               0xA9679C
#define     USA_ONLINE6_BANK_ADDR               0xA9EC1C

#define     USA_MEOW_ADDR                       0x31F2FD3C

#define     USA_WALLET_ADDR                     0x31F2DF28

#define     USA_CONFIRM_BOOL_ADDR               0x32DC6555
#define     USA_NOOKLING1_PRICE_ADDR            0x330B9278
#define     USA_NOOKLING2_PRICE_ADDR            0x330BBA98
*/
#define     USA_ROOM_ID_ADDR                    0x958342
#define     EUR_ROOM_ID_ADDR                    0x95733A
#define     JAP_ROOM_ID_ADDR                    0x95133A
#define     USA_WA_ROOM_ID_ADDR                 0x957322
#define     EUR_WA_ROOM_ID_ADDR                 0x95733A
#define     JAP_WA_ROOM_ID_ADDR                 0x95033A

#define     USA_NPC_ADDR                        0x204ACE
#define     EUR_NPC_ADDR                        0x204AEE
#define     JAP_NPC_ADDR                        0x204A0E
#define     USA_WA_NPC_ADDR                     0x204512
#define     EUR_WA_NPC_ADDR                     0x204A0E
#define     JAP_WA_NPC_ADDR                     0x204512

#define     USA_ISABELLE_ADDR                   0x330B667E
//#define     USA_KAPPN_ADDR                      0x330B77FE

//#define     USA_BADGE_ADDR                      0x31F2C6BC
//#define     USA_TURNIP_ADDR                     0x31F91D60

#define     USA_MAINSTREET_ITEMS                0x305ACF38
#define     USA_MAINSTREET_X                    0x33077838
#define     USA_MAINSTREET_Y                    0x3307783C
/*
#define     USA_MEDALS_ADDR                     0x31F2DBC0
#define     USA_ONLINE0_MEDALS_ADDR             0xAAB0B0
#define     USA_ONLINE1_MEDALS_ADDR             0xA8C330
#define     USA_ONLINE2_MEDALS_ADDR             0xA967B0
#define     USA_ONLINE3_MEDALS_ADDR             0xAA0C30
#define     USA_ONLINE4_MEDALS_ADDR             0xA8C330
#define     USA_ONLINE5_MEDALS_ADDR             0xA967B0
#define     USA_ONLINE6_MEDALS_ADDR             0xA9EC30
*/
#define     USA_BUILDING_BYTE                   0x31F72E04

#define     USA_CAMERA_ASM_ADDR                 0x764504
#define     EUR_CAMERA_ASM_ADDR                 0x76350C
#define     JAP_CAMERA_ASM_ADDR                 0x762CA4
#define     USA_WA_CAMERA_ASM_ADDR              0x7634E8
#define     EUR_WA_CAMERA_ASM_ADDR              0x7634E4
#define     JAP_WA_CAMERA_ASM_ADDR              0x762CA4

//Camera Rotation ASM
#define     USA_CAMERA_ROT_ASM                  0x1A3230
#define     EUR_CAMERA_ROT_ASM                  0x1A3250
#define     JAP_CAMERA_ROT_ASM                  0x1A3190
#define     USA_WA_CAMERA_ROT_ASM               0x1A2C78
#define     EUR_WA_CAMERA_ROT_ASM               0x1A3250
#define     JAP_WA_CAMERA_ROT_ASM               0x1A3190

#define     USA_CAMERA_X_ADDR                   0x9866F4
#define     EUR_CAMERA_X_ADDR                   0x9856F4
#define     JAP_CAMERA_X_ADDR                   0x97F6F4
#define     USA_WA_CAMERA_X_ADDR                0x9856F4
#define     EUR_WA_CAMERA_X_ADDR                0x9856F4
#define     JAP_WA_CAMERA_X_ADDR                0x97E6F4

#define     USA_CAMERA_POINTER                  0x951884
#define     EUR_CAMERA_POINTER                  0x950880
#define     JAP_CAMERA_POINTER                  0x94A880
#define     USA_WA_CAMERA_POINTER               0x950880
#define     EUR_WA_CAMERA_POINTER               0x950880
#define     JAP_WA_CAMERA_POINTER               0x949880

//the current online slot of the player
#define     USA_PLAYER_SLOT                    0x82E93EC
#define     EUR_PLAYER_SLOT                    0x82E93EC 
#define     JAP_PLAYER_SLOT                    0x82E93EC 
#define     USA_WA_PLAYER_SLOT                 0x82E93EC
#define     EUR_WA_PLAYER_SLOT                 0x82D73EC
#define     JAP_WA_PLAYER_SLOT                 0x82E93EC

//
#define     USA_PLAYERINFO_POINTER             0xAAE994
#define     EUR_PLAYERINFO_POINTER             0xAAD994
#define     JAP_PLAYERINFO_POINTER             0xAA7994
#define     USA_WA_PLAYERINFO_POINTER          0xAAD994
#define     EUR_WA_PLAYERINFO_POINTER          0xAAD994
#define     JAP_WA_PLAYERINFO_POINTER          0xAA6994


#define     USA_THOUGHT_ADDR                    0x94FD88
#define     EUR_THOUGHT_ADDR                    0x94ED88
#define     JAP_THOUGHT_ADDR                    0x948D88
#define     USA_WA_THOUGHT_ADDR                 0x94ED78
#define     EUR_WA_THOUGHT_ADDR                 0x94ED88
#define     JAP_WA_THOUGHT_ADDR                 0x947D88
/*
#define     USA_THOUGHT_ASM                     0x2160BC
#define     EUR_THOUGHT_ASM                     0x2160DC
#define     JAP_THOUGHT_ASM                     0x215FFC
*/
#define     USA_BOTTOM_ASM                      0x6D2B50
#define     EUR_BOTTOM_ASM                      0x6D1B88
#define     JAP_BOTTOM_ASM                      0x6D1334
#define     USA_WA_BOTTOM_ASM                   0x6D2000
#define     EUR_WA_BOTTOM_ASM                   0x6D1B60
#define     JAP_WA_BOTTOM_ASM                   0x6D130C

//offset difference to be used in the walk over things code
#define     USA_CODE_DIFFERENCE                 0x0
#define     EUR_CODE_DIFFERENCE                -0xFC8
#define     JAP_CODE_DIFFERENCE                -0x1508
#define     USA_WA_CODE_DIFFERENCE             -0xAD8
#define     EUR_WA_CODE_DIFFERENCE             -0xFC8
#define     JAP_WA_CODE_DIFFERENCE             -0x1508

//#define     USA_THOUGHT_TEXT_ADDR               0x33077D50
#define     USA_CLUB_ADDR                       0x301b5aa0

#define     USA_GARDEN                          0x31F26F80
//#define     USA_NAME_ADDR                       0x31F2C5C8

#define     USA_TOWN_FRUIT                      0x31F891BA
#define     USA_GRASS_TYPE                      0x31F7A401
#define     USA_PWP_ADDRESS                     0x31F772B0
#define     USA_PERMIT_ADDRESS                  0x31F2C738
#define     USA_TREE_SIZE                       0x31F72E06

#define     USA_GAME_SPEED                      0x54DDB4
#define     EUR_GAME_SPEED                      0x54CDFC //Same as WA
#define     JAP_GAME_SPEED                      0x54C6E8 //Same as WA
#define     USA_WA_GAME_SPEED                   0x54D30C



#define     USA_ITEM_FORM                       0x3307778C

#define     USA_KEYBOARD                        0xAD7630
#define     EUR_KEYBOARD                        0xAD6630
#define     JAP_KEYBOARD                        0xAD0630
#define     USA_WA_KEYBOARD                     0xAD6630
#define     EUR_WA_KEYBOARD                     0xAD6630
#define     JAP_WA_KEYBOARD                     0xACF630

#define     USA_AMIIBO_WISP                     0x95EECC
#define     EUR_AMIIBO_WISP                     0x95DEC4
#define     JAP_AMIIBO_WISP                     0x957EC4
#define     USA_WA_AMIIBO_WISP                  0x95DEAC
#define     EUR_WA_AMIIBO_WISP                  0x95DEC4
#define     JAP_WA_AMIIBO_WISP                  0x956EC4

#define     USA_AMIIBO_DIE                      0x3308E8CC

#define     USA_BOTTOM_ADDR                     0x950D1F
#define     EUR_BOTTOM_ADDR                     0x94FD1F
#define     JAP_BOTTOM_ADDR                     0x949D1F
#define     USA_WA_BOTTOM_ADDR                  0x94FD0F
#define     EUR_WA_BOTTOM_ADDR                  0x94FD1F
#define     JAP_WA_BOTTOM_ADDR                  0x948D1F

#define     USA_FAINT_ADDR                      0x33077533

#define     USA_TEXT_KEYBOARD                   0x95F11C
#define     EUR_TEXT_KEYBOARD                   0x95E114
#define     JAP_TEXT_KEYBOARD                   0x958114
#define     USA_WA_TEXT_KEYBOARD                0x95E10C
#define     EUR_WA_TEXT_KEYBOARD                0x95E114
#define     JAP_WA_TEXT_KEYBOARD                0x957114

#define     USA_ENTER_BOOL                      0xAD7253
#define     EUR_ENTER_BOOL                      0xAD6253
#define     JAP_ENTER_BOOL                      0xAD0253
#define     USA_WA_ENTER_BOOL                   0xAD6253
#define     EUR_WA_ENTER_BOOL                   0xAD6253
#define     JAP_WA_ENTER_BOOL                   0xACF253

#define     USA_VISIBILITY_ADDR                 0x654594
#define     EUR_VISIBILITY_ADDR                 0x6535CC
#define     JAP_VISIBILITY_ADDR                 0x65308C
#define     USA_WA_VISIBILITY_ADDR              0x653ABC
#define     EUR_WA_VISIBILITY_ADDR              0x6535CC
#define     JAP_WA_VISIBILITY_ADDR              0x65308C

#define     USA_CATALOG_ITEM                    0x95033C
#define     EUR_CATALOG_ITEM                    0x94F33C
#define     JAP_CATALOG_ITEM                    0x94933C
#define		USA_WA_CATALOG_ITEM					0x94F32C
#define		EUR_WA_CATALOG_ITEM					0x94F33C
#define		JAP_WA_CATALOG_ITEM					0x94833C

#define     USA_MAP_BOOL                        0x950C30
#define     EUR_MAP_BOOL                        0x94FC30
#define     JAP_MAP_BOOL                        0x949C30  
#define     USA_WA_MAP_BOOL                     0x94FC20
#define     EUR_WA_MAP_BOOL                     0x94FC30
#define     JAP_WA_MAP_BOOL                     0x948C30

#define     USA_TOURS                           0x95D734
#define     EUR_TOURS                           0x95C730
#define     JAP_TOURS                           0x955730
#define     USA_WA_TOURS                        0x95C724
#define     EUR_WA_TOURS                        0x95E114
#define     JAP_WA_TOURS                        0x954730

#define     USA_EMOTE                           0x25E054
#define     EUR_EMOTE                           0x25E050
#define     JAP_EMOTE                           0x25DF70
#define     USA_WA_EMOTE                        0x25DA98
#define     EUR_WA_EMOTE                        0x25E050
#define     JAP_WA_EMOTE                        0x25DF70

#define     USA_PATTERNEDIT                     0x2FEC44
#define     EUR_PATTERNEDIT                     0x2FECCC
#define     JAP_PATTERNEDIT                     0x2FEC78
#define     USA_WA_PATTERNEDIT                  0x2FE9C0
#define     EUR_WA_PATTERNEDIT                  0x2FECCC
#define     JAP_WA_PATTERNEDIT                  0x2FEC78

#define     USA_NOBREAKFLOWERS                  0x597F58
#define     EUR_NOBREAKFLOWERS                  0x596FA0
#define     JAP_NOBREAKFLOWERS                  0x596890
#define     USA_WA_NOBREAKFLOWERS               0x597470
#define     EUR_WA_NOBREAKFLOWERS               0x596FA0
#define     JAP_WA_NOBREAKFLOWERS               0x596890

#define     USA_COUNTRY                         0x350B18
#define     EUR_COUNTRY                         0x34FC60
#define     JAP_COUNTRY                         0x34F8F8
#define     USA_WA_COUNTRY                      0x35052C
#define     EUR_WA_COUNTRY                      0x34FC60
#define     JAP_WA_COUNTRY                      0x34F8F8

#define     USA_WEATHER                         0x62FC30
#define     EUR_WEATHER                         0x62EC68
#define     JAP_WEATHER                         0x62E728
#define     USA_WA_WEATHER                      0x62F158
#define     EUR_WA_WEATHER                      0x62EC68
#define     JAP_WA_WEATHER                      0x62E728

#define     USA_CONFETTI                        0x266CDC
#define     EUR_CONFETTI                        0x266CD8
#define     JAP_CONFETTI                        0x266BF8
#define     USA_WA_CONFETTI                     0x266720
#define     EUR_WA_CONFETTI                     0x266CD8
#define     JAP_WA_CONFETTI                     0x266BF8

#define     USA_CHERRYBLOSSOM                   0x296A64
#define     EUR_CHERRYBLOSSOM                   0x296A60
#define     JAP_CHERRYBLOSSOM                   0x296960
#define     USA_WA_CHERRYBLOSSOM                0x2964A8
#define     EUR_WA_CHERRYBLOSSOM                0x296A60
#define     JAP_WA_CHERRYBLOSSOM                0x296960

#define     USA_ALWAYSOPEN_RETAIL               0x309348
#define     EUR_ALWAYSOPEN_RETAIL               0x309344
#define     JAP_ALWAYSOPEN_RETAIL               0x3093BC
#define     USA_WA_ALWAYSOPEN_RETAIL            0x309430
#define     EUR_WA_ALWAYSOPEN_RETAIL            0x309344
#define     JAP_WA_ALWAYSOPEN_RETAIL            0x3093BC

#define     USA_ALWAYSOPEN_NOOKLING             0x711B14
#define     EUR_ALWAYSOPEN_NOOKLING             0x710B1C
#define     JAP_ALWAYSOPEN_NOOKLING             0x7102C8
#define     USA_WA_ALWAYSOPEN_NOOKLING          0x710FC4
#define     EUR_WA_ALWAYSOPEN_NOOKLING          0x710AF4
#define     JAP_WA_ALWAYSOPEN_NOOKLING          0x7102A0

#define     USA_ALWAYSOPEN_GARDEN               0x711BCC
#define     EUR_ALWAYSOPEN_GARDEN               0x710BD4
#define     JAP_ALWAYSOPEN_GARDEN               0x710380
#define     USA_WA_ALWAYSOPEN_GARDEN            0x71107C
#define     EUR_WA_ALWAYSOPEN_GARDEN            0x710BAC
#define     JAP_WA_ALWAYSOPEN_GARDEN            0x710358

#define     USA_ALWAYSOPEN_ABLES                0x713EB0
#define     EUR_ALWAYSOPEN_ABLES                0x712EB8
#define     JAP_ALWAYSOPEN_ABLES                0x712664
#define     USA_WA_ALWAYSOPEN_ABLES             0x713360
#define     EUR_WA_ALWAYSOPEN_ABLES             0x712E90
#define     JAP_WA_ALWAYSOPEN_ABLES             0x71263C

#define     USA_ALWAYSOPEN_SHAMPOODLE           0x71D42C
#define     EUR_ALWAYSOPEN_SHAMPOODLE           0x71C434
#define     JAP_ALWAYSOPEN_SHAMPOODLE           0x71BBE0
#define     USA_WA_ALWAYSOPEN_SHAMPOODLE        0x71C774
#define     EUR_WA_ALWAYSOPEN_SHAMPOODLE        0x71C40C
#define     JAP_WA_ALWAYSOPEN_SHAMPOODLE        0x71BBB8

#define     USA_ALWAYSOPEN_KICKS                0x71184C
#define     EUR_ALWAYSOPEN_KICKS                0x710854
#define     JAP_ALWAYSOPEN_KICKS                0x710000
#define     USA_WA_ALWAYSOPEN_KICKS             0x710CFC
#define     EUR_WA_ALWAYSOPEN_KICKS             0x71082C
#define     JAP_WA_ALWAYSOPEN_KICKS             0x70FFD8

#define     USA_ALWAYSOPEN_NOOKS                0x71F654
#define     EUR_ALWAYSOPEN_NOOKS                0x71E65C
#define     JAP_ALWAYSOPEN_NOOKS                0x71DE08
#define     USA_WA_ALWAYSOPEN_NOOKS             0x71E99C
#define     EUR_WA_ALWAYSOPEN_NOOKS             0x71E634
#define     JAP_WA_ALWAYSOPEN_NOOKS             0x71DDE0

#define     USA_ALWAYSOPEN_KATRINA              0x718098
#define     EUR_ALWAYSOPEN_KATRINA              0x7170A0
#define     JAP_ALWAYSOPEN_KATRINA              0x71684C
#define     USA_WA_ALWAYSOPEN_KATRINA           0x717548
#define     EUR_WA_ALWAYSOPEN_KATRINA           0x717078
#define     JAP_WA_ALWAYSOPEN_KATRINA           0x716824

#define     USA_ALWAYSOPEN_REDD                 0x718444
#define     EUR_ALWAYSOPEN_REDD                 0x71744C
#define     JAP_ALWAYSOPEN_REDD                 0x716BF8
#define     USA_WA_ALWAYSOPEN_REDD              0x7178F4
#define     EUR_WA_ALWAYSOPEN_REDD              0x717424
#define     JAP_WA_ALWAYSOPEN_REDD              0x716BD0

#define     USA_FURN_FIX                        0x6A6EE0
#define     EUR_FURN_FIX                        0x6A5F18
#define     JAP_FURN_FIX                        0x6A59B0
#define     USA_WA_FURN_FIX                     0x6A6408
#define     EUR_WA_FURN_FIX                     0x6A5F18
#define     JAP_WA_FURN_FIX                     0x6A59B0

#define     USA_FISH_CANT_BE_SCARED             0x1EAB14
#define     EUR_FISH_CANT_BE_SCARED             0x1EAB34 //Same as WA
#define     JAP_FISH_CANT_BE_SCARED             0x1EAA70 //Same as WA
#define     USA_WA_FISH_CANT_BE_SCARED          0x1EA558

#define     USA_FISH_BITE_RIGHT_AWAY            0x1EA844
#define     EUR_FISH_BITE_RIGHT_AWAY            0x1EA864 //Same as WA
#define     JAP_FISH_BITE_RIGHT_AWAY            0x1EA7A0 //Same as WA
#define     USA_WA_FISH_BITE_RIGHT_AWAY         0x1EA288

#define     USA_FISH_SET_FISH_ID                0x2545CC
#define     EUR_FISH_SET_FISH_ID                0x2545C8 //Same as WA
#define     JAP_FISH_SET_FISH_ID                0x2544E8 //Same as WA
#define     USA_WA_FISH_SET_FISH_ID             0x254010

#define     USA_GAMEMODE_PTR                    0x954648
#define     EUR_GAMEMODE_PTR                    0x953644
#define     JAP_GAMEMODE_PTR                    0x94D644
#define     USA_WA_GAMEMODE_PTR                 0x95362C
#define     EUR_WA_GAMEMODE_PTR                 0x953644
#define     JAP_WA_GAMEMODE_PTR                 0x94C644

#define     USA_INSTANTTEXT                     0x5FC6B0
#define     EUR_INSTANTTEXT                     0x5FB6E8 //Also EUR WA
#define     JAP_INSTANTTEXT                     0x5FAF68 //Also JPN WA
#define     USA_WA_INSTANTTEXT                  0x5FBBE0

#define     USA_ECHOTHEMUSIC                    0x1B1270
#define     EUR_ECHOTHEMUSIC                    0x1B1290 //Also EUR WA
#define     JAP_ECHOTHEMUSIC                    0x1B11CC //Also JPN WA
#define     USA_WA_ECHOTHEMUSIC                 0x1B0CB4

#endif
