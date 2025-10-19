#include "Utils/Action.hpp"
#include "Utils/Quest.hpp"
#include "Cheats/Actions.hpp"

namespace CTRPluginFramework
{
    u32 actionID;
    u32 actionID2;
    u32 actionID3;

    void ExecuteAction(MenuEntry* entry) {
        Quest quest;
        Action action;

        if (!quest.InQuest()) {
            return;
        }

        if (Controller::IsKeysPressed(L | DPadUp)) {
            u32 _actionid = 0;
            Keyboard keyboard("アクションid(1)を入力");
            if (keyboard.Open(_actionid) == 0) {
                actionID = _actionid;
            }

            u32 _actionid2 = 0;
            Keyboard keyboard2("アクションid(2)を入力");
            if (keyboard2.Open(_actionid2) == 0) {
                actionID2 = _actionid2;
            }

            u32 _actionid3 = 0;
            Keyboard keyboard3("アクションid(3)を入力");
            if (keyboard3.Open(_actionid3) == 0) {
                actionID3 = _actionid3;
            }
        }

        if (Controller::IsKeysPressed(L | DPadDown)) {
            action.RunAction(quest.GetQuestAddress(), actionID, actionID2, actionID3);
        }
    }
}