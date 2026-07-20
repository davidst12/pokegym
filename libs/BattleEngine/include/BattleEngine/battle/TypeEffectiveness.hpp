#pragma once

#include "BattleEngine/pokemon/Types.hpp"

namespace pokegym::engine::battle {

using pokegym::engine::pokemon::Type;

class TypeEffectiveness {
   public:
    static auto GetMultiplier(Type attack, Type defense) -> float;

   private:
    // Row: attacker
    // Column: defender
    static constexpr float type_chart_[static_cast<size_t>(Type::Count)]
                                      [static_cast<size_t>(Type::Count)] = {
                                          //          Fire.  Water Grass Normal
                                          /* Fire  */ {0.5f, 0.5f, 2.0f, 1.0f},
                                          /* Water */ {2.0f, 0.5f, 0.5f, 1.0f},
                                          /* Grass */ {0.5f, 2.0f, 0.5f, 1.0f},
                                          /* Normal*/ {1.0f, 1.0f, 1.0f, 1.0f}};
};

}  // namespace pokegym::engine::battle