#ifndef ITEMS_H
#define ITEMS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void AddItems(MenuEntry* entry);
    void IsHaveItem(MenuEntry* entry);
}
#endif
