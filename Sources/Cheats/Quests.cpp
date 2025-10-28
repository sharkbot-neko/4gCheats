#include "Cheats/Quests.hpp"
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
}