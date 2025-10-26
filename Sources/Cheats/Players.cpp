#include "Cheats/Players.hpp"
#include "CTRPluginFramework.hpp"

using namespace CTRPluginFramework;

static Hook moneyHook;

namespace CTRPluginFramework {

    void MoneyChange(MenuEntry* entry) {
        u32 count;

        std::string now_money = Utils::Format("金額を入力");

        Keyboard keyboard(now_money);
        keyboard.IsHexadecimal(false);
    
        if (keyboard.Open(count) == 0) {
            Process::Write32(0x083302AC, count);
        }
    }

    void MoneyWhenUsingCheck(u32 address, int money)
    {
        bool check = MessageBox("お金を使いますか？", DialogType::DialogYesNo)();

        if (check) {
            int money_player;

            u32 m;
            Process::Read32(0x083302AC, m);
            Process::Write32(0x083302AC, m + money);
        }
    }

    void MoneyWhenUsingTrampoline(int address, int money)
    {
        MoneyWhenUsingCheck(address, money);

        return;
    }

    void MoneyWhenUsing(MenuEntry* entry)
    {
        moneyHook.Initialize(0x00c0c678, reinterpret_cast<u32>(MoneyWhenUsingTrampoline));

        const std::vector<std::string> enable_or_disable = {
            "はい",   // 有効
            "いいえ"  // 無効
        };

        Keyboard keyboard("お金を使う際に確認するか", enable_or_disable);

        int index = keyboard.Open();
        if (index < 0)
            return;

        switch (index) {
            default:
                break;

            case 0: {
                moneyHook.Enable();
                Process::Patch(0x00c0c67c, 0xE12FFF1E);
                break;
            }

            case 1: {
                moneyHook.Disable();
                Process::Patch(0x00c0c67c, 0xE5820034);
                break;
            }
        }
    }

    void GenderChnage(MenuEntry* entry)
    {
        const std::vector<std::string> options = {
            "男",
            "女"
        };

        Keyboard keyboard("性別を入力してください。", options);

        int index = keyboard.Open();
        if (index < 0)
            return;

        switch (index) {
            default:
                break;

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

    // スピードハック（即書き込み）
    void SpeedHack(MenuEntry* entry)
    {
        Process::Write32(0x00B057BC, 0x40200000);
        Process::Write32(0x00AFD8FC, 0x40000000);
    }

} // namespace CTRPluginFramework