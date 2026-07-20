#include "BattleEngine/battle/TypeEffectiveness.hpp"

namespace pokegym::engine::battle {

auto TypeEffectiveness::GetMultiplier(pokemon::Type attack, pokemon::Type defense) -> float {
    return type_chart_[static_cast<size_t>(attack)][static_cast<size_t>(defense)];
}

}  // namespace pokegym::engine::battle
