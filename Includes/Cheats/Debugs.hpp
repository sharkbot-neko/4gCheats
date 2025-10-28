#ifndef DEBUG_H
#define DEBUG_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void getBaseAddress(MenuEntry* entry);
}
#endif
