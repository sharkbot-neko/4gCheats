#include "Utils/Item.hpp"

#include "CallFuncWrapper.hpp"
#include "Function.hpp"

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

uint Item::FindItemIndex(uint32_t base_address, uint32_t item_id) {
    return Function<uint>(0x00af96f0)(base_address, item_id);
}

void Item::AddItem(uint32_t base_address, uint16_t item_id, int count) {
    Function<void>(0x00b561a4)(base_address, item_id, count);
}