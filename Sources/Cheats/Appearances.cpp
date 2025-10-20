#include "Cheats/Appearances.hpp"
#include "Utils/Quest.hpp"

namespace CTRPluginFramework
{

    void PlayerFlatten(MenuEntry* entry) {
        Quest quest;

        if (!quest.InQuest()) {
            return;
        }

        Process::Write32(quest.GetQuestAddress() + 0x63, 0x00000000);
    }
}