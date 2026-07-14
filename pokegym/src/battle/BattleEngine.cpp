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
    notifyObservers(BattleStartsEvent{battle.getOpponent()->getName()});
    notifyObservers(PokemonSentOutEvent{Side::Opponent, *battle.getOpponent()->getActivePokemon()});
    notifyObservers(PokemonSentOutEvent{Side::Player, *battle.getPlayer()->getActivePokemon()});
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
            auto side = (action.trainer_type == Action::TrainerType::Player) ? Side::Opponent
                                                                             : Side::Player;
            notifyObservers(PokemonFaintedEvent{side});
            break;
        }
    }
}

auto BattleEngine::requestActions(Battle& battle)
    -> std::vector<std::tuple<Pokemon*, Action, Pokemon*>> {
    notifyObservers(ActionRequestEvent{Action::actionTypesToStringList(),
                                       battle.getPlayer()->getActivePokemon()->getMovesNames()});
    // 1. Get actions from both trainers (player and opponent)
    Action player_action = battle.getPlayer()->chooseAction(Action::TrainerType::Player);
    // notifyObservers(BattleEvent{BattleEventType::OpponentSelectsAction, &battle});
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
        auto side =
            (action.trainer_type == Action::TrainerType::Player) ? Side::Player : Side::Opponent;
        notifyObservers(MoveUsedEvent{side, pokemon->getMoves()[action.index].getName()});
        int damage =
            DamageCalculator::calculateDamage(*pokemon, *target, pokemon->getMoves()[action.index]);
        target->takeDamage(damage);

        side = (action.trainer_type == Action::TrainerType::Player) ? Side::Opponent : Side::Player;

        notifyObservers(DamageEvent{side, target->getCurrentHp()});
    }
}

auto BattleEngine::checkBattleFinished(Battle& battle) -> void {
    if (battle.getPlayer()->getActivePokemon()->getCurrentHp() <= 0) {
        battle.setResult(Result::OpponentWin);
        notifyObservers(BattleWinEvent{Side::Opponent});
    } else if (battle.getOpponent()->getActivePokemon()->getCurrentHp() <= 0) {
        battle.setResult(Result::PlayerWin);
        notifyObservers(BattleWinEvent{Side::Player});
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
