#include "Cheats/AntiCheats.hpp"

namespace CTRPluginFramework
{

    void Anti_Gender_Crash(MenuEntry* entry) {
        Process::Write32(0x00AF2840, 0xEB0BE807);
        Process::Patch(0x00DEC864, 0xE5D11000);
        Process::Patch(0x00DEC868, 0xE3510002);
        Process::Patch(0x00DEC86C, 0xA8BD81F0);
        Process::Patch(0x00DEC870, 0xE12FFF1E);
    }
}