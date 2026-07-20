#include <iostream>

#include "BattleEngine/battle/Battle.hpp"
#include "BattleEngine/battle/BattleEngine.hpp"
#include "BattleEngine/manager/PokemonManager.hpp"
#include "BattleEngine/pokemon/Move.hpp"
#include "BattleEngine/pokemon/Pokemon.hpp"
#include "BattleEngine/trainer/RandomActionSelector.hpp"
#include "BattleEngine/trainer/Trainer.hpp"
#include "BattleRenderer/console/ConsoleActionSelector.hpp"
#include "BattleRenderer/console/ConsoleBattleRenderer.hpp"
#include "BattleRenderer/sdl/SdlActionSelector.hpp"
#include "BattleRenderer/sdl/SdlBattleRenderer.hpp"

using pokegym::engine::battle::Battle;
using pokegym::engine::battle::BattleEngine;
using pokegym::engine::pokemon::Move;
using pokegym::engine::pokemon::Pokemon;
using pokegym::engine::trainer::RandomActionSelector;
using pokegym::engine::trainer::Trainer;
using pokegym::renderer::ConsoleActionSelector;
using pokegym::renderer::SdlActionSelector;
using pokegym::renderer::SdlBattleRenderer;

int main() {
    const std::string player_pk_name = "Charizard";
    const std::string player_pk_name2 = "Venusaur";
    const std::string opponent_pk_name = "Squirtle";
    const std::string opponent_pk_name2 = "Blastoise";
    const std::string brook_name = "Brook";
    const std::string player_name = "David";

    pokegym::engine::manager::PokemonManager pokemon_manager;
    pokemon_manager.loadPokemonData();

    auto player_pk_opt = pokemon_manager.getPokemonByName(player_pk_name);
    auto player_pk_opt2 = pokemon_manager.getPokemonByName(player_pk_name2);
    auto opponent_pk_opt = pokemon_manager.getPokemonByName(opponent_pk_name);
    auto opponent_pk_opt2 = pokemon_manager.getPokemonByName(opponent_pk_name2);

    std::vector<Pokemon> brook_team{opponent_pk_opt.value(), opponent_pk_opt2.value()};
    std::vector<Pokemon> player_team{player_pk_opt.value(), player_pk_opt2.value()};

    RandomActionSelector random_selector;
    SdlActionSelector sdl_selector;

    Trainer brook(brook_name, brook_team, &random_selector);
    Trainer player(player_name, player_team, &sdl_selector);

    Battle battle(&player, &brook);

    BattleEngine battle_engine;
    pokegym::renderer::ConsoleBattleRenderer console_renderer;
    SdlBattleRenderer sdl_render(sdl_selector);
    battle_engine.addObserver(&console_renderer);
    battle_engine.addObserver(&sdl_render);

    std::thread render_loop =
        std::thread([&battle_engine, &battle]() -> void { battle_engine.run(battle); });
    sdl_render.run();
    render_loop.join();

    return 0;
}