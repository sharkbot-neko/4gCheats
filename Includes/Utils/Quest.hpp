#pragma once
#ifndef QUEST_HPP
#define QUEST_HPP

#include <string>
#include <vector>
#include <iostream>

class Quest {
public:
    uint32_t GetQuestAddress();
    bool InQuest();
};

#endif // MYCLASS_HPP