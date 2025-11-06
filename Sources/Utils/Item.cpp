#include "Utils/Item.hpp"

#include "CallFuncWrapper.hpp"

uint8_t Item::GetNowSelect() {
    u8 value;
    CTRPluginFramework::Process::Read8(0x0106C236, value);
    return value;
}

bool Item::IsSelected() {
    u8 value;
    CTRPluginFramework::Process::Read8(0x0106C234, value);
    if (value == 0x4) {
        return true;
    } else {
        return false;
    }
}

void Item::AddItem(uint32_t base_address, uint16_t item_id, int count) {
    CTRPluginFramework::CallFuncWrapper(0x00b561a4)(base_address, item_id, count);
}