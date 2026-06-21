#pragma once

#include <vector>

#include "pokegym/battle/Action.hpp"
#include "pokegym/pokemon/Pokemon.hpp"

namespace pokegym::trainer {

using pokegym::battle::Action;
using pokegym::pokemon::Pokemon;

class Trainer {
   public:
    explicit Trainer(const std::string& name, std::vector<Pokemon>& team);
    ~Trainer() = default;

    auto getName() const -> const std::string&;
    auto getTeam() -> std::vector<Pokemon>&;
    auto chooseAction() -> Action;
    auto setActivePokemon(Pokemon* pokemon) -> void;
    auto getActivePokemon() const -> Pokemon*;

   private:
    std::string name_;
    std::vector<Pokemon> team_;
    Pokemon* active_pokemon_;
};

}  // namespace pokegym::trainer
