#pragma once

#include "BattleEngine/battle/Action.hpp"
#include "BattleEngine/pokemon/Pokemon.hpp"
#include "BattleEngine/trainer/ActionSelection.hpp"

namespace pokegym::renderer {

using pokegym::engine::battle::Action;
using pokegym::engine::pokemon::Pokemon;
using pokegym::engine::trainer::ActionSelector;

class ConsoleActionSelector : public ActionSelector {
   public:
    ConsoleActionSelector() = default;
    ~ConsoleActionSelector() = default;

    auto selectAction(const Pokemon& pokemon) -> Action override;
    auto selectPokemon(const std::vector<Pokemon>& team) -> Action override;
};

}  // namespace pokegym::renderer
