#include "Utils/Action.hpp"

#include "CallFuncWrapper.hpp"

void Action::RunAction(uint32_t quest_address,uint32_t id_1, uint32_t id_2, uint32_t id_3) {
    (CTRPluginFramework::CallFuncWrapper(0x00b0ca30))(quest_address, id_1, id_2, id_3);
}

void Action::RunEmotion(uint32_t quest_address,uint32_t id) {
    (CTRPluginFramework::CallFuncWrapper(0x00b0ca30))(quest_address, 0x0000000B, id);
}