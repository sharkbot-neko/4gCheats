#include "Cheats/Groups.hpp"

namespace CTRPluginFramework
{
    void AntiJoin(MenuEntry* entry) {
        Process::Write8(0x0830EA58, 0x01);
        Process::Write8(0x0830EB58, 0x01);
        Process::Write8(0x0830EC58, 0x01);
        Process::Write8(0x0830ED58, 0x01);
    }
}