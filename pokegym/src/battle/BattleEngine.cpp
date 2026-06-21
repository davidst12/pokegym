#include "pokegym/battle/BattleEngine.hpp"

#include <algorithm>
#include <iostream>

#include "pokegym/battle/DamageCalculator.hpp"
#include "pokegym/pokemon/Pokemon.hpp"

namespace pokegym {
namespace battle {

using pokegym::pokemon::Pokemon;

BattleEngine::BattleEngine() = default;

auto BattleEngine::run(Battle& battle) -> Result {
    while (battle.getResult() == Result::Undefined) {
        executeTurn(battle);

        checkBattleFinished(battle);
    }

    return battle.getResult();
}

auto BattleEngine::executeTurn(Battle& battle) -> void {
    battle.incrementTurn();
    auto actions = requestActions(battle);

    // 2. Determine the order of actions based on Pokémon speed
    determineActionOrder(actions);

    // 3. Execute actions in order
    for (auto [pokemon, action, target] : actions) {
        executeAction(pokemon, action, target);

        // 3.5 Check if pokemon target fainted and if the battle is finished
        if (target->getCurrentHp() <= 0) {
            break;
        }
    }
}

auto BattleEngine::requestActions(Battle& battle)
    -> std::vector<std::tuple<Pokemon*, Action, Pokemon*>> {
    std::cout << " --- Turn " << battle.getCurrentTurn() << " ---" << std::endl;
    // 1. Get actions from both trainers (player and opponent)
    Action player_action = battle.getPlayer()->chooseAction();
    Action opponent_action = battle.getOpponent()->chooseAction();

    std::tuple<Pokemon*, Action, Pokemon*> first_action{battle.getPlayer()->getActivePokemon(),
                                                        player_action,
                                                        battle.getOpponent()->getActivePokemon()};
    std::tuple<Pokemon*, Action, Pokemon*> second_action{battle.getOpponent()->getActivePokemon(),
                                                         opponent_action,
                                                         battle.getPlayer()->getActivePokemon()};
    return {first_action, second_action};
}

auto BattleEngine::determineActionOrder(
    std::vector<std::tuple<Pokemon*, Action, Pokemon*>>& actions) -> void {
    std::sort(actions.begin(), actions.end(), [](const auto& a, const auto& b) {
        return std::get<0>(a)->getVelocity() > std::get<0>(b)->getVelocity();
    });
}

auto BattleEngine::executeAction(Pokemon* pokemon, const Action& action, Pokemon* target) -> void {
    if (action.type == Action::Type::Attack) {
        std::cout << pokemon->getName() << " used " << pokemon->getMoves()[action.index].getName()
                  << "!" << std::endl;
        int damage =
            DamageCalculator::calculateDamage(*pokemon, *target, pokemon->getMoves()[action.index]);
        target->takeDamage(damage);

        std::cout << target->getName() << " took " << damage << " damage!" << std::endl;
        std::cout << target->getName() << " has " << target->getCurrentHp() << " HP left."
                  << std::endl;

        // Check if the target Pokémon fainted
        if (target->getCurrentHp() <= 0) {
            std::cout << target->getName() << " fainted!" << std::endl;
        }
    }
}

auto BattleEngine::checkBattleFinished(Battle& battle) -> void {
    if (battle.getPlayer()->getActivePokemon()->getCurrentHp() <= 0) {
        battle.setResult(Result::OpponentWin);
    } else if (battle.getOpponent()->getActivePokemon()->getCurrentHp() <= 0) {
        battle.setResult(Result::PlayerWin);
    }
}

}  // namespace battle
}  // namespace pokegym
