#pragma once

#include "pokegym/pokemon/Move.hpp"
#include "pokegym/pokemon/Pokemon.hpp"

namespace pokegym::battle {

using pokegym::pokemon::Move;
using pokegym::pokemon::Pokemon;

class DamageCalculator {
   public:
    DamageCalculator();
    ~DamageCalculator() = default;

    // Method to calculate damage based on attacker's attack, defender's defense, and move power
    static auto calculateDamage(const Pokemon& attacker, const Pokemon& defender, const Move& move)
        -> int;
};

}  // namespace pokegym::battle
