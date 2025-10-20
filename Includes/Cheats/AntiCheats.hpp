#ifndef ANTICHEAT_H
#define ANTICHEAT_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void Anti_Gender_Crash(MenuEntry* entry);
}
#endif