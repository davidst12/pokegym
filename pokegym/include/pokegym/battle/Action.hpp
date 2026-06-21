#pragma once

namespace pokegym::battle {

struct Action {
    enum class Type {
        Attack,
        // UseItem,
        // SwitchPokemon
    };

    Type type;
    int index;  // Index of move in the Pokémon's move list (for Attack type)
};

}  // namespace pokegym::battle