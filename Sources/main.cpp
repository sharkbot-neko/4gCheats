#include <3ds.h>
#include "csvc.h"
#include <CTRPluginFramework.hpp>
#include "cheats.hpp"
#include "PatternManager.hpp"

#include <vector>

namespace CTRPluginFramework
{
    // This patch the NFC disabling the touchscreen when scanning an amiibo, which prevents ctrpf to be used
    static void    ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Result  res;
        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if(R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
        svcCloseHandle(processHandle);
    }

    // This function is called before main and before the game starts
    // Useful to do code edits safely
    void    PatchProcess(FwkSettings &settings)
    {
        ToggleTouchscreenForceOn();
    }

    // This function is called when the process exits
    // Useful to save settings, undo patchs or clean up things
    void    OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }

    void    InitMenu(PluginMenu &menu)
    {
        // Create your entries here, or elsewhere
        // You can create your entries whenever/wherever you feel like it
        
        // Example entry
        /*menu += new MenuEntry("Test", nullptr, [](MenuEntry *entry)
        {
            std::string body("What's the answer ?\n");

            body += std::to_string(42);

            MessageBox("UA", body)();
        });*/

        MenuFolder *players = new MenuFolder("プレイヤー");
        *players += new MenuEntry("所持金変更", nullptr, MoneyChange);
        *players += new MenuEntry("所持金使用時に確認", nullptr, MoneyWhenUsing);
        *players += new MenuEntry("性別変更", nullptr, GenderChnage);
        *players += new MenuEntry("スピード変更", SpeedHack);

        MenuFolder *appearance = new MenuFolder("見た目");

        *appearance += new MenuEntry("プレイヤーを平らにするか", PlayerFlatten);

        *players += appearance;

        menu += players;

        MenuFolder *items = new MenuFolder("アイテム");
        *items += new MenuEntry("アイテム入手", nullptr, AddItems, "クエスト中のみ使用できます。");
        menu += items;

        MenuFolder *quests = new MenuFolder("クエスト");
        *quests += new MenuEntry("壁抜け", WallBreak, "壁抜けをします。\n↑オン ↓オフ");
        menu += quests;

        MenuFolder *groups = new MenuFolder("集会所");
        *groups += new MenuEntry("集会所参加制限", AntiJoin, "集会所に参加できなくします。\n集会所オーナーが使用してください。\n今のところオフはできません。");
        menu += groups;

        MenuFolder *action_codes = new MenuFolder("アクション");
        *action_codes += new MenuEntry("アクション実行", ExecuteAction, "上キーとLキーでid設定、\n下キーとLキーで実行。");
        *action_codes += new MenuEntry("エモート実行", ExecuteEmotion, "上キーとRキーでid設定、\n下キーとRキーで実行。");
        menu += action_codes;

        MenuFolder *exploits = new MenuFolder("害悪");
        *exploits += new MenuEntry("集会所オーナー変更", nullptr, ChangeOwner);
        // *exploits += new MenuEntry("メンバーキック", nullptr, KickMember);
        menu += exploits;

        MenuFolder *anti_cheat = new MenuFolder("アンチチート");
        *anti_cheat += new MenuEntry("性別クラッシュ無効", nullptr, Anti_Gender_Crash);
        menu += anti_cheat;

        MenuFolder *debug = new MenuFolder("デバッグコード");
        *debug += new MenuEntry("ベースアドレスを取得", nullptr, getBaseAddress);
        *debug += new MenuEntry("アドレス監視", nullptr, AddressViewer);
        *debug += new MenuEntry("文字描画", drawTextTest);
        *debug += new MenuEntry("送信するパケットを記録", nullptr, packetRecord);
        menu += debug;
    }

    int     main(void)
    {
        PluginMenu *menu = new PluginMenu("MonsterHunter 4G", 1, 0, 0,
                                            "モンスターハンター4Gのプラグインです。\n今度はOLD3dsも、New3dsも対応させました。");

        // Synnchronize the menu with frame event
        menu->SynchronizeWithFrame(true);

        menu->ShowWelcomeMessage(false);

        OSD::Notify("Welcome to MonsterHunter 4G Plugin!");

        // Init our menu entries & folders
        InitMenu(*menu);

        // Launch menu and mainloop
        menu->Run();

        delete menu;

        // Exit plugin
        return (0);
    }
}
