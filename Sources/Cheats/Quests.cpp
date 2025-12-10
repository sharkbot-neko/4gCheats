#include "Cheats/Quests.hpp"
#include "Structs/Player.hpp"
#include "CTRPluginFramework.hpp"

#include "Utils/Quest.hpp"
#include "Utils/Home.hpp"

using namespace CTRPluginFramework;

namespace CTRPluginFramework
{
    void WallBreak(MenuEntry* entry) {
        Quest quest;
        if (!quest.InQuest()) return;

        if(Controller::IsKeyPressed(DPadUp))
        {
            Process::Write32(0x00B04C34, 0xEA000018);
            OSD::Notify("WallBreak Enabled!");
        }
        if(Controller::IsKeyPressed(DPadDown))
        {
            Process::Write32(0x00B04C34, 0x00000000);
            OSD::Notify("WallBreak Disabled!");
        }
    }

    void CoordMove(MenuEntry* entry) {
        Quest quest;
        if (!quest.InQuest()) return;

        Player* player = quest.GetPlayerStructs();
        PlayerBodyWork* pbw = player->playerbodywork;
        if(Controller::IsKeysDown(DPadUp | X))
        {
            pbw->vec_z += 30; 
        }
        if(Controller::IsKeysDown(DPadDown | X))
        {
            pbw->vec_z -= 30;
        }
        if(Controller::IsKeysDown(DPadRight | X))
        {
            pbw->vec_x += 30; 
        }
        if(Controller::IsKeysDown(DPadLeft | X))
        {
            pbw->vec_x -= 30;
        }
    }
}