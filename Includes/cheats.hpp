#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

#include "Cheats/Actions.hpp"
#include "Cheats/AntiCheats.hpp"
#include "Cheats/Appearances.hpp"
#include "Cheats/Debugs.hpp"
#include "Cheats/Exploits.hpp"
#include "Cheats/Groups.hpp"
#include "Cheats/Players.hpp"
#include "Cheats/Quests.hpp"
#include "Cheats/Items.hpp"
#include "Cheats/Homes.hpp"

#include "Structs/Player.hpp"
#include "Utils/Home.hpp"
#include "Utils/Quest.hpp"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void ProcessFrameCallback();
    bool DrawMiniMenu(const Screen &screen);
    bool OverlayCallback(const Screen &scr);
}
#endif
