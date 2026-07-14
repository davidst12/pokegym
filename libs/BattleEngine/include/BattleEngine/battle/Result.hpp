#pragma once

#include <cstdint>

namespace pokegym::engine::battle {

enum class Result : std::uint8_t { Undefined, PlayerWin, OpponentWin };

}  // namespace pokegym::engine::battle