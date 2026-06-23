#pragma once

#include <vector>

#include "pokegym/battle/Action.hpp"
#include "pokegym/pokemon/Pokemon.hpp"
#include "pokegym/trainer/ActionSelection.hpp"

namespace pokegym::trainer {

using pokegym::battle::Action;
using pokegym::pokemon::Pokemon;

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

}  // namespace pokegym::trainer
