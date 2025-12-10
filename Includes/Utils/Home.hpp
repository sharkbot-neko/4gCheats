#pragma once
#ifndef HOME_HPP
#define HOME_HPP

#include "Structs/Player.hpp"
#include <string>
#include <vector>
#include <iostream>

class Home {
public:
    uint32_t GetHomeAddress();
    CTRPluginFramework::PlayerBodyWork* GetPBWStructs();
    CTRPluginFramework::Player* GetPlayerStructs();
    bool InHome();
};

#endif // MYCLASS_HPP