#include "Utils/Player.hpp"

#include "CallFuncWrapper.hpp"
#include "Function.hpp"

void Player::SetPlayerName(std::string player_name) {
    CTRPluginFramework::Process::WriteString(0x08330278, player_name, CTRPluginFramework::StringFormat::Utf16);
}

void Player::SetHunterRank(int hunter_rank) {
    CTRPluginFramework::Process::Write16(0x083302A4, hunter_rank);
}