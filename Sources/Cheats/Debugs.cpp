#include "Cheats/Debugs.hpp"
#include "CTRPluginFramework.hpp"
#include "CallFuncWrapper.hpp"

#include "Utils/Quest.hpp"
#include "Utils/Home.hpp"

using namespace CTRPluginFramework;

namespace CTRPluginFramework
{
    void getBaseAddress(MenuEntry* entry) {
        Quest quest;
        Home home;
        
        MessageBox(Utils::Format(
            "ベースアドレス一覧\n\nクエストのベースアドレス: %x\n拠点のベースアドレス: %x", 
            quest.GetBaseAddress(),
            home.GetHomeAddress()
        ))();
    }

    void drawTextTest(MenuEntry* entry) {
        char local_68[24] = {0};   // テキストバッファ
        char auStack_50[4] = {0};  // 補助用（多分カラーテーブルとか）
        char auStack_48[36] = {0}; // レイアウトバッファ
        char local_b8[128] = {0};  // テキスト出力領域（0x80バイト）

        // 関数ポインタの定義
        typedef void (*Func_00100130)(char* out, int fontId, const char* text, void* context);
        typedef uint (*Func_00bc4000)(const char* in, uint color, char* outBuf, uint maxLen, const char* extra);
        typedef uint (*Func_00bc40fc)(char* dst, const char* src, uint maxLen);
        typedef void (*Func_005c15d4)(uint param1, uint param2, uint param3, int param4);

        Func_00100130 makeText = (Func_00100130)0x00100130;
        Func_00bc4000 layoutText = (Func_00bc4000)0x00bc4000;
        Func_00bc40fc copyText = (Func_00bc40fc)0x00bc40fc;
        Func_005c15d4 drawText  = (Func_005c15d4)0x005c15d4;

        // "testNow" という文字列を作る
        makeText(local_68, 0xF, "testNow", NULL);

        // テキストをレイアウトに変換
        layoutText(local_68, 0xFFFFFFFF, auStack_48, 0x20, auStack_50);

        // コピーして描画用バッファに入れる
        copyText(local_b8, auStack_48, 0x80);

        // 実際に描画命令を登録（3Dオブジェクトならparam_3にID）
        drawText((uint)entry, 0x12345678, 0x70055E9D, (int)auStack_48);
    }

    static std::vector<u32> g_addresses;   // 監視対象アドレス
    static bool g_isMonitoring = false;    // 監視ON/OFFフラグ

    bool AddressOSDCallback(const Screen &screen)
    {
        if (!g_isMonitoring || g_addresses.empty())
            return true;

        if (!screen.IsTop) return true;

        int y = 20;
        for (u32 addr : g_addresses)
        {
            u32 value = *(u32*)addr;
            std::string text = Utils::Format("0x%08X : 0x%08X", addr, value);
            screen.Draw(text, 20, y, Color::White);
            y += 12;
        }

        return true;
    }

    void AddressViewer(MenuEntry* entry)
    {
        while (true)
        {
            std::vector<std::string> options;
            options.push_back(g_isMonitoring ? "監視を停止" : "監視を開始");
            options.push_back("アドレスを追加");
            options.push_back("アドレスを削除");
            options.push_back("全削除");
            options.push_back("戻る");

            Keyboard menu("アドレスモニター");
            menu.Populate(options);
            int index = menu.Open();

            if (index < 0 || index == 4)
                return;

            switch (index)
            {
                case 0:
                    g_isMonitoring = !g_isMonitoring;
                    if (g_isMonitoring)
                    {
                        OSD::Run(AddressOSDCallback);
                    }
                    else
                    {
                        OSD::Stop(AddressOSDCallback);
                    }
                    break;

                case 1:
                {
                    Keyboard addressKeyboard("アドレスを16進数で入力 (例: 00100000)");
                    std::string input;
                    if (addressKeyboard.Open(input) == 0)
                    {
                        u32 address = strtoul(input.c_str(), nullptr, 16);
                        g_addresses.push_back(address);
                        MessageBox("追加完了", Utils::Format("0x%08X を追加しました。", address))();
                    }
                    break;
                }

                case 2:
                {
                    if (g_addresses.empty())
                    {
                        MessageBox("削除できるアドレスがありません。")();
                        break;
                    }

                    std::vector<std::string> list;
                    for (u32 addr : g_addresses)
                        list.push_back(Utils::Format("0x%08X", addr));

                    Keyboard deleteMenu("削除するアドレスを選択");
                    deleteMenu.Populate(list);
                    int delIndex = deleteMenu.Open();
                    if (delIndex >= 0)
                    {
                        MessageBox("削除完了", Utils::Format("0x%08X を削除しました。", g_addresses[delIndex]))();
                        g_addresses.erase(g_addresses.begin() + delIndex);
                    }
                    break;
                }

                case 3:
                    g_addresses.clear();
                    MessageBox("全削除完了", "すべてのアドレスを削除しました。")();
                    break;
            }
        }
    }
}