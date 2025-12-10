#pragma once
#ifndef QUEST_HPP
#define QUEST_HPP

#include "Structs/Player.hpp"
#include <string>
#include <vector>
#include <iostream>

#include "CTRPluginFramework.hpp"

class Quest {
public:
    uint32_t GetQuestAddress();
    CTRPluginFramework::PlayerBodyWork* GetPBWStructs();
    bool InQuest();

    inline uint32_t GetBaseAddress() {
        using Func = uint32_t(*)();
        Func func = reinterpret_cast<Func>(0x0013f380);
        u32 read_address;
        CTRPluginFramework::Process::Read32(func(), read_address);
        return read_address;
    }
};

#endif // MYCLASS_HPP