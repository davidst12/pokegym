#include "BattleEngine/manager/PokemonManager.hpp"

#include <fstream>
#include <iostream>

namespace pokegym::engine::manager {

auto PokemonManager::loadPokemonData() -> bool {
    std::ifstream pokemon_file("assets/pokemon/stats/statistics.json");
    if (!pokemon_file.is_open()) {
        return false;
    }

    json pokemon_data;
    pokemon_file >> pokemon_data;
    pokemon_file.close();

    for (const auto& poke : pokemon_data) {
        pokemon_db_by_name_[poke["name"]] = poke;
    }

    std::ifstream moves_file("assets/pokemon/stats/moves.json");
    if (!moves_file.is_open()) {
        return false;
    }

    json moves_data;
    moves_file >> moves_data;
    moves_file.close();

    for (const auto& move : moves_data) {
        moves_db_by_name_[move["move"]] = move;
    }
    data_loaded_ = true;
    return data_loaded_;
}

auto PokemonManager::getPokemonByName(const std::string& name) -> std::optional<pokemon::Pokemon> {
    if (!data_loaded_) {
        return std::nullopt;
    }

    if (pokemon_db_by_name_.count(name)) {
        const auto& poke = pokemon_db_by_name_[name];

        std::vector<pokemon::Move> moves{};
        for (const auto& move_name : poke["moves"]) {
            if (moves_db_by_name_.count(move_name)) {
                const auto& move_data = moves_db_by_name_[move_name];
                moves.emplace_back(move_data["move"], move_data["power"]);
            }
        }

        pokemon::Pokemon pokemon(poke["id"], poke["name"], poke["stats"]["speed"],
                                 poke["stats"]["attack"], poke["stats"]["defense"],
                                 poke["stats"]["hp"], moves);
        return pokemon;
    }

    return std::nullopt;
}

}  // namespace pokegym::engine::manager
