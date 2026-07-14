#include <iostream>

#include "BattleEngine/battle/Battle.hpp"
#include "BattleEngine/battle/BattleEngine.hpp"
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
    const std::string pikachu_name = "Pikachu";
    const std::string geodude_name = "Geodude";
    const std::string brook_name = "Brook";
    const std::string player_name = "David";
    Move thunderbolt("Thunderbolt", 90);
    Move quick_attack("Quick Attack", 40);
    std::vector<Move> pikachu_moves{thunderbolt, quick_attack};
    std::vector<Move> geodude_moves{thunderbolt, quick_attack};

    Pokemon pikachu(pikachu_name, 90, 55, 400, 35, pikachu_moves);
    Pokemon geodude(geodude_name, 20, 80, 100, 50, geodude_moves);

    std::vector<Pokemon> brook_team{geodude};
    std::vector<Pokemon> player_team{pikachu};

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