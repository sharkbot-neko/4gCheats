#include "Utils/Home.hpp"

#include "CallFuncWrapper.hpp"

uint32_t Home::GetHomeAddress() {
    uint32_t address;
    CTRPluginFramework::Process::Read32(0x0107CAC0, address);
    return address;
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