#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <iostream>

class Player {
public:
    void SetPlayerName(std::string player_name);
    void SetHunterRank(int hunter_rank);
};

#endif