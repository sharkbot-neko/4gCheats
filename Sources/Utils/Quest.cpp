#include "Utils/Quest.hpp"

#include "CallFuncWrapper.hpp"

uint32_t Quest::GetQuestAddress() {
    uint32_t address;
    CTRPluginFramework::Process::Read32(0x01062ED4, address);
    return address;
}

bool Quest::InQuest() {
    Quest quest;
    uint32_t quest_ = quest.GetQuestAddress();
    if (quest_ != 0x00000000) {
        return true;
    } else {
        return false;
    }
}