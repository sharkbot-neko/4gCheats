#ifndef QUESTS_H
#define QUESTS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void WallBreak(MenuEntry* entry);
    void CoordMove(MenuEntry* entry);

    void BunnyHop(MenuEntry* entry);
}
#endif
