#include <gtest/gtest.h>

#include "pokegym/battle/Battle.hpp"
#include "pokegym/battle/BattleEngine.hpp"
#include "pokegym/pokemon/Move.hpp"
#include "pokegym/pokemon/Pokemon.hpp"
#include "pokegym/trainer/Trainer.hpp"

using pokegym::battle::Battle;
using pokegym::battle::BattleEngine;
using pokegym::pokemon::Move;
using pokegym::pokemon::Pokemon;
using pokegym::trainer::Trainer;

TEST(PokemonTest, Constructor) {
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

    Trainer brook(brook_name, brook_team);
    Trainer player(player_name, player_team);

    Battle battle(&player, &brook);

    BattleEngine battle_engine;
    battle_engine.run(battle);

    EXPECT_EQ(2 + 2, 5);
}
