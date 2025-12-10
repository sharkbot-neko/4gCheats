#include "Cheats/Homes.hpp"
#include "Utils/Home.hpp"

using namespace CTRPluginFramework;

namespace CTRPluginFramework
{
    void CoordMovesHome(MenuEntry* entry) {
        Home home;

        if (!home.InHome()) {
            return;
        };

        PlayerBodyWork* pbw = home.GetPBWStructs();
        if(Controller::IsKeysDown(DPadUp | X))
        {
            pbw->vec_z += 30; 
        }
        if(Controller::IsKeysDown(DPadDown | X))
        {
            pbw->vec_z -= 30;
        }
        if(Controller::IsKeysDown(DPadRight | X))
        {
            pbw->vec_x += 30; 
        }
        if(Controller::IsKeysDown(DPadLeft | X))
        {
            pbw->vec_x -= 30;
        }
    }
}