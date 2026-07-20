#include "BattleEngine/battle/DamageCalculator.hpp"

#include "BattleEngine/battle/TypeEffectiveness.hpp"

namespace pokegym::engine::battle {
DamageCalculator::DamageCalculator() = default;

auto DamageCalculator::calculateDamage(const Pokemon& attacker, const Pokemon& defender,
                                       const Move& move) -> int {
    float multiplier = TypeEffectiveness::GetMultiplier(move.getType(), defender.getType());
    float damage = std::max(attacker.getAttack() + move.getPower() - defender.getDefense(), 1);

    return static_cast<int>(damage * multiplier);
}
}  // namespace pokegym::engine::battle
