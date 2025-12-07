#pragma once
#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>
#include <vector>
#include <iostream>

class Network {
public:
    uint sendLocalPacket(
        uint* sessionHandle,   // param_1
        uint targetNodeId,     // param_2
        uint16_t port,         // param_3
        uint8_t flag1,         // param_4
        void* buffer,          // param_5
        int size,              // param_6
        uint settings,         // param_7
        uint8_t flag2          // param_8
    );
};

#endif