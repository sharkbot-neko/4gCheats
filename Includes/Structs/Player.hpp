#pragma once
#ifndef PLAYER_STRUCT_HPP
#define PLAYER_STRUCT_HPP

#include <string>
#include <vector>
#include <iostream>

namespace CTRPluginFramework {
    typedef struct PlayerWork {
        uint32_t mJobFlag;          // 0x00

        char pad_0004[0x38 - 0x04]; // 0x04〜0x37

        int mTimer;                 // 0x38

        char pad_003C[0x4C - 0x3C]; // 0x3C〜0x4B

        int mActionTimer;           // 0x4C
        int mDashTimer;             // 0x50

        char pad_0054[0xC0 - 0x54]; // 0x54〜0xBF

        float mNowMotSpeed;         // 0xC0

        // まだこの先も何かある
    } PlayerWork;

    typedef struct PlayerSubData {
        char pad_0000[0x34C];   // 未解析の領域

        uint16_t hp_vital;          // 0x34C
        uint16_t max_hp_vital;      // 0x34E

        char pad_0350[0x354 - 0x350];

        int dash_vital;             // 0x354
        int max_dash_vital;         // 0x358
        int heal_vital;             // 0x35C
        int heal_vital_timer;       // 0x360
        int dash_vital_time;        // 0x364

        char pad_xxx[0x6FB - 0x368];

        uint8_t chat_act_flag;      // 0x6FB

        // この後もデータが続くはず
    } PlayerSubData;
        
    // プレイヤーの位置など
    typedef struct PlayerBodyWork {
        char pad_0000[0x0018];
        float vec_x;
        float vec_y;
        float vec_z;

        char pad_002C[0x0005];
        unsigned char pl_type;

        char pad_0032[0x033E];
        int  pl_st;
    } PBW;

    // 00b14168で登録
    typedef struct Player {
        char pad_0x000[0xCC];
        int mRegupTimer3;       // offset 0xCC
        char pad_0xD0[0x58];    // offset 0x128 までの空白領域 
        int mRegupValue3;       // offset 0x128
        int mAttackTimer;       // offset 0x12C
        int mBleedingTimer;     // offset 0x130

        char pad_unknown[0xA29C - 0x134];

        PlayerWork* mPlayerWork;      // 0xA29C
    } Player;
}

#endif 