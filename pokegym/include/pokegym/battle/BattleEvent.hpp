#pragma once

#include "pokegym/battle/Battle.hpp"

namespace pokegym::battle {

using pokegym::battle::Battle;

enum class BattleEventType {
    BattleStarts,
    PlayerNewPokemon,
    OpponentNewPokemon,
    PlayerSelectsAction,
    OpponentSelectsAction,
    PlayerSelectsMove,
    OpponentSelectsMove,
    PlayerAttacks,
    OpponentAttacks,
    PlayerPokemonNewHp,
    OpponentPokemonNewHp,
    PlayerPokemonFainted,
    OpponentPokemonFainted,
    PlayerWins,
    OpponentWins,
};

struct BattleEvent {
    BattleEventType type;
    const Battle* battle;
    const std::string move_name;
};

}  // namespace pokegym::battle
