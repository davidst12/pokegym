#pragma once

#include <vector>

namespace pokegym::engine::battle {

struct Action {
    enum class TrainerType { Player, Opponent };
    enum class Type { Attack, SwitchPokemon, UseItem };

    static auto actionTypesToStringList() -> std::vector<std::string> {
        std::vector<std::string> actions;
        actions.push_back("Attack");
        actions.push_back("Switch Pokemon");
        actions.push_back("Use Item");
        return actions;
    }

    TrainerType trainer_type;
    Type type;
    int index;  // Index of move in the Pokémon's move list (for Attack type)
};

}  // namespace pokegym::engine::battle