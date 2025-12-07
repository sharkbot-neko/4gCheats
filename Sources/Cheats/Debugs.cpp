#include "Cheats/Debugs.hpp"
#include "CTRPluginFramework.hpp"
#include "CallFuncWrapper.hpp"

#include "Utils/Quest.hpp"
#include "Utils/Home.hpp"
#include "Utils/Network.hpp"

#include "Function.hpp"

using namespace CTRPluginFramework;

Hook record;

#include <CTRPluginFramework.hpp>
#include <deque>
using namespace CTRPluginFramework;

static std::deque<std::string> g_Packets;
static Mutex g_Lock;

static bool DrawPacketsCallback(const Screen &screen)
{
    if (!screen.IsTop)return true;

    g_Lock.Lock();

    int y = 10;
    int index = 0;

    for (auto it = g_Packets.rbegin(); it != g_Packets.rend(); ++it)
    {
        if (index++ >= 10)
            break;

        screen.Draw(*it, 10, y, Color::Yellow);
        y += 12;
    }

    g_Lock.Unlock();
    return true;
}

extern "C" uint recorder(
    uint* sessionHandle,
    uint  targetNodeId,
    uint16_t port,
    uint8_t flag1,
    void* buffer,
    int   size,
    uint  settings,
    uint8_t flag2
)
{
    const int previewLen = (size > 32 ? 32 : size);

    std::string hexPreview;
    hexPreview.reserve(previewLen * 3);

    u8 *buf = reinterpret_cast<u8*>(buffer);
    for (int i = 0; i < previewLen; i++)
        hexPreview += Utils::Format("%02X ", buf[i]);

    std::string line = Utils::Format(
        "N:%u P:%u Size:%d %s%s",
        targetNodeId,
        port,
        size,
        hexPreview.c_str(),
        (size > 32 ? "..." : "")
    );

    g_Lock.Lock();

    g_Packets.push_back(line);
    if (g_Packets.size() > 10)
        g_Packets.pop_front();

    g_Lock.Unlock();

    auto &ctx = CTRPluginFramework::HookContext::GetCurrent();

    return ctx.OriginalFunction<
        uint,                      // TResult
        uint*, uint, uint16_t,     // Args...
        uint8_t, void*, int, uint, uint8_t
    >(
        sessionHandle,
        targetNodeId,
        port,
        flag1,
        buffer,
        size,
        settings,
        flag2
    );
}

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

        char local_68[24];   // テキストバッファ
        int local_6c = 0;
        char auStack_50;  // 補助用（多分カラーテーブルとか）
        char auStack_48[36]; // レイアウトバッファ
        char local_b8[128];  // テキスト出力領域（0x80バイト）
        char auStack_138[16];

        int local_1d8 [30];

        local_1d8[3] = 6;
        local_1d8[1] = 0;
        local_1d8[2] = 4;

        Function<void>(0x00bc4000)("testnow", 0xFFFFFFFF, auStack_48, 0x80, &auStack_50);

        uint uver3 = Function<char>(0x005a382c)(0x00f976b4, 0xFFFFFFFF);

        uint* puVar2 = Function<uint*>(0x00bf3ebc)(0x01037ea0, uver3, 0x00fec49c);

        Function<void>(0x00acbc48)(local_1d8);

        Function<void>(0x00acdd50)(puVar2, 0x0107c2ec, auStack_48, auStack_50, local_1d8);
        // Function<void>(0x005c15d4)(0x00595a8c, 0xEDAC28AC, 0x70055e9d, auStack_50);
    }

    void packetRecord(MenuEntry* entry) {
        record.InitializeForMitm(0x00551a3c, reinterpret_cast<u32>(recorder));

        std::vector<std::string> options = {
            "はい（有効）",
            "いいえ（無効）"
        };

        Keyboard kb("パケットを記録しますか？", options);
        int res = kb.Open();

        if (res < 0)
            return;

        switch (res) {
            case 0:
                record.Enable();
                MessageBox("パケット記録を有効化しました\nOSDを使って表示されます")();
                OSD::Run(DrawPacketsCallback);
                break;

            case 1:
                record.Disable();
                MessageBox("パケット記録を無効化しました")();
                OSD::Stop(DrawPacketsCallback);
                break;
        }
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
                    } else {
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