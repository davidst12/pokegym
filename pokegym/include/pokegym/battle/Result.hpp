#pragma once

#include <cstdint>

namespace pokegym::battle {

enum class Result : std::uint8_t { Undefined, PlayerWin, OpponentWin };

}  // namespace pokegym::battle