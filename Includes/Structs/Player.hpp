#pragma once
#ifndef PLAYER_STRUCT_HPP
#define PLAYER_STRUCT_HPP

#include <string>
#include <vector>
#include <iostream>

namespace CTRPluginFramework {
    typedef struct PlayerBodyWork {
        char pad_0000[0x0010];
        float vec_x;
        float vec_y;
        float vec_z;
        char pad_0084[0x04];
    } PlayerBodyWork;

    typedef struct Player {
        char pad_0000[0x60];
        float playerWidthX;
        float playerWidthY;
        float playerWidthZ;
        char pad_0001[0xDC4];
        PlayerBodyWork* playerbodywork;
    } Player;
}

#endif 