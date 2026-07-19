#pragma once

#include "BattleEngine/battle/Action.hpp"
#include "BattleEngine/pokemon/Pokemon.hpp"
#include "BattleEngine/trainer/ActionSelection.hpp"

namespace pokegym::engine::trainer {

using pokegym::engine::battle::Action;
using pokegym::engine::pokemon::Pokemon;
using pokegym::engine::trainer::ActionSelector;

class RandomActionSelector : public ActionSelector {
   public:
    RandomActionSelector() = default;
    ~RandomActionSelector() = default;

    auto selectAction(const Pokemon& pokemon) -> Action override;
    auto selectPokemon(const std::vector<Pokemon>& team) -> Action override;
};

}  // namespace pokegym::engine::trainer
