#include "Cheats/Items.hpp"
#include "Utils/Item.hpp"
#include "Utils/Quest.hpp"

using namespace CTRPluginFramework;

namespace CTRPluginFramework
{
    void AddItems(MenuEntry* entry) {
        Quest quest;

        if (!quest.InQuest()) {
            MessageBox("クエスト中でのみ使用できます。")();
            return;
        };

        u32 itemID;
        u32 count;
        Keyboard itemid_key("アイテムID");
        Keyboard count_key("カウント");
        count_key.IsHexadecimal(false);

        if (itemid_key.Open(itemID) == 0) {
            if (count_key.Open(count) == 0) {
                Item item;
                item.AddItem(quest.GetQuestAddress(), itemID, count);
            }
        }
    }
}