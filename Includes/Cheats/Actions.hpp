#ifndef ACTIONS_H
#define ACTIONS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void ExecuteAction(MenuEntry *entry);
    void ExecuteEmotion(MenuEntry* entry);
}
#endif