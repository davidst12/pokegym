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
    notifyObservers(BattleEvent{BattleEventType::BattleStarts, &battle});
    notifyObservers(BattleEvent{BattleEventType::OpponentNewPokemon, &battle});
    notifyObservers(BattleEvent{BattleEventType::PlayerNewPokemon, &battle});
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
        executeAction(battle, pokemon, action, target);

        // 3.5 Check if pokemon target fainted and if the battle is finished
        if (target->getCurrentHp() <= 0) {
            auto event_type = (action.trainer_type == Action::TrainerType::Player)
                                  ? BattleEventType::OpponentPokemonFainted
                                  : BattleEventType::PlayerPokemonFainted;
            notifyObservers(BattleEvent{event_type, &battle});
            break;
        }
    }
}

auto BattleEngine::requestActions(Battle& battle)
    -> std::vector<std::tuple<Pokemon*, Action, Pokemon*>> {
    notifyObservers(BattleEvent{BattleEventType::PlayerSelectsAction, &battle});
    // 1. Get actions from both trainers (player and opponent)
    Action player_action = battle.getPlayer()->chooseAction(Action::TrainerType::Player);
    notifyObservers(BattleEvent{BattleEventType::OpponentSelectsAction, &battle});
    Action opponent_action = battle.getOpponent()->chooseAction(Action::TrainerType::Opponent);

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

auto BattleEngine::executeAction(Battle& battle, Pokemon* pokemon, const Action& action,
                                 Pokemon* target) -> void {
    if (action.type == Action::Type::Attack) {
        auto event_type = (action.trainer_type == Action::TrainerType::Player)
                              ? BattleEventType::PlayerAttacks
                              : BattleEventType::OpponentAttacks;
        notifyObservers(
            BattleEvent{event_type, &battle, pokemon->getMoves()[action.index].getName()});
        int damage =
            DamageCalculator::calculateDamage(*pokemon, *target, pokemon->getMoves()[action.index]);
        target->takeDamage(damage);

        event_type = (action.trainer_type == Action::TrainerType::Player)
                         ? BattleEventType::OpponentPokemonNewHp
                         : BattleEventType::PlayerPokemonNewHp;

        notifyObservers(BattleEvent{event_type, &battle});
    }
}

auto BattleEngine::checkBattleFinished(Battle& battle) -> void {
    if (battle.getPlayer()->getActivePokemon()->getCurrentHp() <= 0) {
        battle.setResult(Result::OpponentWin);
        notifyObservers(BattleEvent{BattleEventType::OpponentWins, &battle});
    } else if (battle.getOpponent()->getActivePokemon()->getCurrentHp() <= 0) {
        battle.setResult(Result::PlayerWin);
        notifyObservers(BattleEvent{BattleEventType::PlayerWins, &battle});
    }
}

auto BattleEngine::addObserver(BattleObserver* observer) -> void {
    observers_.push_back(observer);
}

auto BattleEngine::notifyObservers(const BattleEvent& event) -> void {
    for (auto* observer : observers_) {
        observer->onBattleEvent(event);
    }
}

}  // namespace battle
}  // namespace pokegym
