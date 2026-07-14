#pragma once

#include "BattleEngine/pokemon/Move.hpp"
#include "BattleEngine/pokemon/Pokemon.hpp"

namespace pokegym::engine::battle {

using pokegym::engine::pokemon::Move;
using pokegym::engine::pokemon::Pokemon;

class DamageCalculator {
   public:
    DamageCalculator();
    ~DamageCalculator() = default;

    // Method to calculate damage based on attacker's attack, defender's defense, and move power
    static auto calculateDamage(const Pokemon& attacker, const Pokemon& defender, const Move& move)
        -> int;
};

}  // namespace pokegym::engine::battle
