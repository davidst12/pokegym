#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <unordered_map>

#include "BattleEngine/pokemon/Pokemon.hpp"

namespace pokegym::engine::manager {

using json = nlohmann::json;

class PokemonManager {
   public:
    PokemonManager() = default;
    ~PokemonManager() = default;

    auto loadPokemonData() -> bool;
    auto getPokemonByName(const std::string& name) -> std::optional<pokemon::Pokemon>;

   private:
    std::unordered_map<std::string, json> pokemon_db_by_name_;
    std::unordered_map<std::string, json> moves_db_by_name_;
    bool data_loaded_ = false;
};

}  // namespace pokegym::engine::manager
