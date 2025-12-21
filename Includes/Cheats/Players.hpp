#ifndef PLAYERS_H
#define PLAYERS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void MoneyChange(MenuEntry* entry);
    void MoneyWhenUsing(MenuEntry* entry);
    
    void GenderChnage(MenuEntry* entry);
    
    void SpeedHack(MenuEntry* entry);

    void NameChange(MenuEntry* entry);
}
#endif
