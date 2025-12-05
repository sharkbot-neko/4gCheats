#include "Utils/Network.hpp"

#include "CallFuncWrapper.hpp"
#include "Function.hpp"

uint Network::sendLocalPacket(
    uint* sessionHandle,   // param_1
    uint targetNodeId,     // param_2
    uint16_t port,         // param_3
    uint8_t flag1,         // param_4
    void* buffer,          // param_5
    int size,              // param_6
    uint settings,         // param_7
    uint8_t flag2          // param_8
) {
    return Function<uint>(0x00551a3c)(sessionHandle, targetNodeId, port, flag1, buffer, size, settings, flag2);
};