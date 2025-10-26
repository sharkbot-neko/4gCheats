#include "Utils/Home.hpp"

#include "CallFuncWrapper.hpp"

uint32_t Home::GetGroupAddress() {
    uint32_t address;
    CTRPluginFramework::Process::Read32(0x0107CAC0, address);
    return address;
}