#pragma once

#include <vector>

#include "BattleEngine/battle/Action.hpp"
#include "BattleEngine/pokemon/Pokemon.hpp"
#include "BattleEngine/trainer/ActionSelection.hpp"

namespace pokegym::engine::trainer {

using pokegym::engine::battle::Action;
using pokegym::engine::pokemon::Pokemon;

class Trainer {
   public:
    explicit Trainer(const std::string& name, std::vector<Pokemon>& team,
                     ActionSelector* action_selector);
    ~Trainer() = default;

    auto getName() const -> const std::string&;
    auto getTeam() -> std::vector<Pokemon>&;
    auto chooseAction(Action::TrainerType trainer_type) -> Action;
    auto setActivePokemon(Pokemon* pokemon) -> void;
    auto getActivePokemon() const -> Pokemon*;

   private:
    std::string name_;
    std::vector<Pokemon> team_;
    Pokemon* active_pokemon_;

    ActionSelector* action_selector_;
};

}  // namespace pokegym::engine::trainer
