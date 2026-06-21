#include "pokegym/battle/DamageCalculator.hpp"

namespace pokegym::battle {
DamageCalculator::DamageCalculator() = default;

auto DamageCalculator::calculateDamage(const Pokemon& attacker, const Pokemon& defender,
                                       const Move& move) -> int {
    return std::max(attacker.getAttack() + move.getPower() - defender.getDefense(), 0);
}
}  // namespace pokegym::battle
