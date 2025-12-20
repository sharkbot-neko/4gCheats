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

uint32_t Item::GetItemOffset() {
    uint32_t value;
    CTRPluginFramework::Process::Read32(0x00fb02a8, value);
    return value;
}

uint Item::FindItemIndex(uint32_t base_address, uint32_t item_id) {
    return Function<uint>(0x00af96f0)(base_address, item_id);
}

void Item::AddItem(uint32_t base_address, uint16_t item_id, int count) {
    uint32_t address = GetItemOffset();
    Function<void>(0x00c021cc)(address, item_id, count,*(int *)(base_address + 0xe30) + 0x256,0x20,1,0);
}