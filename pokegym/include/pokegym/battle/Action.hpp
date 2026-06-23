#pragma once

namespace pokegym::battle {

struct Action {
    enum class TrainerType { Player, Opponent };
    enum class Type {
        Attack,
        // UseItem,
        // SwitchPokemon
    };

    TrainerType trainer_type;
    Type type;
    int index;  // Index of move in the Pokémon's move list (for Attack type)
};

}  // namespace pokegym::battle