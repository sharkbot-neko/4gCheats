#include "Utils/Quest.hpp"
#include "Structs/Player.hpp"

#include "CallFuncWrapper.hpp"

uint32_t Quest::GetQuestAddress() {
    uint32_t address;
    CTRPluginFramework::Process::Read32(0x01062ED4, address);
    return address;
}

CTRPluginFramework::PlayerBodyWork* Quest::GetPBWStructs() {
    uint32_t base;
    
    CTRPluginFramework::Process::Read32(0x01062ED4, base);

    uintptr_t addr = static_cast<uintptr_t>(base) + 0xE30;

    // CTRPluginFramework::MessageBox(CTRPluginFramework::Utils::Format("%x", addr))();

    return reinterpret_cast<CTRPluginFramework::PlayerBodyWork*>(addr);
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