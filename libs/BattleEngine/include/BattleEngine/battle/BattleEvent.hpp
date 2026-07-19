#pragma once

#include "BattleEngine/battle/Battle.hpp"

namespace pokegym::engine::battle {

using pokegym::engine::battle::Battle;
using pokegym::engine::pokemon::Pokemon;

enum class Side {
    Player,
    Opponent,
};

struct BattleStartsEvent {
    std::string opponent_name;
};

struct PokemonSentOutEvent {
    Side side;
    const Pokemon pokemon;
};

struct ActionRequestEvent {
    std::vector<std::string> action_names_list;
    std::vector<std::string> move_names_list;
    std::vector<Pokemon> pokemons_alive_list;
};

struct MoveUsedEvent {
    Side side;
    std::string move_name;
};

struct DamageEvent {
    Side side;
    int new_hp;
};

struct PokemonFaintedEvent {
    Side side;
};

struct NewPokemonRequestEvent {
    std::vector<Pokemon> pokemons_alive_list;
};

struct BattleWinEvent {
    Side side;
};

using BattleEvent =
    std::variant<BattleStartsEvent, PokemonSentOutEvent, ActionRequestEvent, MoveUsedEvent,
                 DamageEvent, PokemonFaintedEvent, NewPokemonRequestEvent, BattleWinEvent>;

}  // namespace pokegym::engine::battle
