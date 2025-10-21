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

    void GenderChnage(MenuEntry* entry) {
        const std::vector<std::string> enable_or_disable = {
            "男",
            "女"
        };

        Keyboard keyboard("性別を入力してください。", enable_or_disable);

		int index = keyboard.Open();
		if(index < 0)
			return;

		switch (index) {
			default: break;

            case 0: {
                Process::Write32(0x08330290, 0x00000000);
                break;
            }

            case 1: {
                Process::Write32(0x08330290, 0x00000001);
                break;
            }
        }
    }

    void SpeedHack(MenuEntry* entry) {
        Process::Write32(0x00B057BC, 0x40200000);
        Process::Write32(0x00AFD8FC, 0x40000000);
    }
}