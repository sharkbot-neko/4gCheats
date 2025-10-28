#include "Cheats/Debugs.hpp"
#include "CTRPluginFramework.hpp"

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
            quest.GetQuestAddress(),
            home.GetHomeAddress()
        ))();
    }
}