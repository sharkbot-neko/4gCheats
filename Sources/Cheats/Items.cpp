#include "Cheats/Items.hpp"
#include "Utils/Item.hpp"
#include "Utils/Quest.hpp"
#include "Utils/Home.hpp"

using namespace CTRPluginFramework;

namespace CTRPluginFramework
{
    void IsHaveItem(MenuEntry* entry) {
        Item item;

        Keyboard itemid_key("アイテムID");
        u32 itemID;

        Home home;
        if (home.InHome()) {
            if (itemid_key.Open(itemID) == 0) {
                uint item_ = item.FindItemIndex(home.GetHomeAddress(), itemID);
                if (item_ == 0xffff) {
                    MessageBox(Utils::Format("そのアイテムは持っていません。"))();
                    return;
                }
                MessageBox(Utils::Format("結果: %x", item_))();
            }
            return;
        };

        Quest quest;
        if (quest.InQuest()) {
            if (itemid_key.Open(itemID) == 0) {
                uint item_ = item.FindItemIndex(quest.GetQuestAddress(), itemID);
                if (item_ == 0xffff) {
                    MessageBox(Utils::Format("そのアイテムは持っていません。"))();
                    return;
                }
                MessageBox(Utils::Format("結果: %x", item_))();
            }
            return;
        };
    }

    void AddItems(MenuEntry* entry) {
        Item item;

        u16 itemID;
        u32 count;
        Keyboard itemid_key("アイテムID");
        Keyboard count_key("カウント");
        count_key.IsHexadecimal(false);

        Home home;
        if (home.InHome()) {
            return;
            // if (itemid_key.Open(itemID) == 0) {
            //     if (count_key.Open(count) == 0) {
            //         item.AddItem(home.GetHomeAddress(), itemID, count);
            //     }
            // }
            // return;
        };

        Quest quest;
        if (quest.InQuest()) {
            if (itemid_key.Open(itemID) == 0) {
                if (count_key.Open(count) == 0) {
                    item.AddItem(quest.GetBaseAddress(), itemID, count);
                }
            }
            return;
        };

    }
}