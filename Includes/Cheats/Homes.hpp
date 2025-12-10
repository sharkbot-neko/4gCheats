#ifndef HOMES_H
#define HOMES_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void CoordMovesHome(MenuEntry* entry);
}
#endif