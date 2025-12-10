#include "Utils/Home.hpp"
#include "Structs/Player.hpp"

#include "CallFuncWrapper.hpp"

uint32_t Home::GetHomeAddress() {
    uint32_t address;
    CTRPluginFramework::Process::Read32(0x0107CAC0, address);
    return address;
}

CTRPluginFramework::PlayerBodyWork* Home::GetPBWStructs() {
    uint32_t address;
    CTRPluginFramework::Process::Read32(0x0107CAC0, address);
    uintptr_t addr = static_cast<uintptr_t>(address) + 0xE30;
    return reinterpret_cast<CTRPluginFramework::PlayerBodyWork*>(addr);
}

bool Home::InHome() {
    Home home;
    uint32_t quest_ = home.GetHomeAddress();
    if (quest_ != 0x00000000) {
        return true;
    } else {
        return false;
    }
}