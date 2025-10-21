#include "Cheats/Players.hpp"

namespace CTRPluginFramework
{

    void MoneyChange(MenuEntry* entry) {
        u32 count;

        std::string now_money = Utils::Format("金額を入力");

        Keyboard keyboard(now_money);
        keyboard.IsHexadecimal(false);
    
        if (keyboard.Open(count) == 0) {
            Process::Write32(0x083302AC, count);
        }
    }

    void SpeedHack(MenuEntry* entry) {
        Process::Write32(0x00B057BC, 0x40200000);
        Process::Write32(0x00AFD8FC, 0x40000000);
    }
}