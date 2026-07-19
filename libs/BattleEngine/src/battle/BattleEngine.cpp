#include "BattleEngine/battle/BattleEngine.hpp"

#include <algorithm>
#include <iostream>

#include "BattleEngine/battle/DamageCalculator.hpp"
#include "BattleEngine/pokemon/Pokemon.hpp"

namespace pokegym {
namespace engine {
namespace battle {

using pokegym::engine::pokemon::Pokemon;

BattleEngine::BattleEngine() = default;

auto BattleEngine::run(Battle& battle) -> Result {
    notifyObservers(BattleStartsEvent{battle.getOpponent()->getName()});
    notifyObservers(PokemonSentOutEvent{Side::Opponent, *battle.getOpponent()->getActivePokemon()});
    notifyObservers(PokemonSentOutEvent{Side::Player, *battle.getPlayer()->getActivePokemon()});
    while (battle.getResult() == Result::Undefined) {
        executeTurn(battle);
        processTurnResult(battle);
        checkBattleFinished(battle);
    }

    return battle.getResult();
}

auto BattleEngine::executeTurn(Battle& battle) -> void {
    battle.incrementTurn();
    auto actions = requestActions(battle);

    // 2. Determine the order of actions based on Pokémon speed
    determineActionOrder(battle, actions);

    // 3. Execute actions in order
    for (auto action : actions) {
        bool execute_next = executeAction(battle, action);
        if (!execute_next)
            break;
    }
}

auto BattleEngine::requestActions(Battle& battle) -> std::vector<Action> {
    notifyObservers(ActionRequestEvent{Action::actionTypesToStringList(),
                                       battle.getPlayer()->getActivePokemon()->getMovesNames(),
                                       battle.getPlayer()->getTeam()});
    // 1. Get actions from both trainers (player and opponent)
    Action player_action = battle.getPlayer()->chooseAction(Action::TrainerType::Player);
    Action opponent_action = battle.getOpponent()->chooseAction(Action::TrainerType::Opponent);

    return {player_action, opponent_action};
}

auto BattleEngine::determineActionOrder(Battle& battle, std::vector<Action>& actions) -> void {
    if (actions.at(0).type == Action::Type::SwitchPokemon) {
        return;
    } else if (actions.at(1).type == Action::Type::SwitchPokemon) {
        std::swap(actions[0], actions[1]);
    } else {
        if (battle.getOpponent()->getActivePokemon()->getVelocity() >
            battle.getPlayer()->getActivePokemon()->getVelocity()) {
            std::swap(actions[0], actions[1]);
        }
    }
}

auto BattleEngine::executeAction(Battle& battle, Action action) -> bool {
    if (action.type == Action::Type::Attack) {
        Side side;
        Pokemon* attacker;
        Pokemon* defender;
        if (action.trainer_type == Action::TrainerType::Player) {
            side = Side::Player;
            attacker = battle.getPlayer()->getActivePokemon();
            defender = battle.getOpponent()->getActivePokemon();
        } else {
            side = Side::Opponent;
            attacker = battle.getOpponent()->getActivePokemon();
            defender = battle.getPlayer()->getActivePokemon();
        }
        notifyObservers(MoveUsedEvent{side, attacker->getMoves()[action.index].getName()});
        int damage = DamageCalculator::calculateDamage(*attacker, *defender,
                                                       attacker->getMoves()[action.index]);
        defender->takeDamage(damage);

        side = (action.trainer_type == Action::TrainerType::Player) ? Side::Opponent : Side::Player;

        notifyObservers(DamageEvent{side, defender->getCurrentHp()});

        if (defender->getCurrentHp() == 0) {
            notifyObservers(PokemonFaintedEvent{side});
            return false;
        }
    } else if (action.type == Action::Type::SwitchPokemon) {
        if (action.trainer_type == Action::TrainerType::Player) {
            battle.getPlayer()->setActivePokemon(action.index);
            notifyObservers(
                PokemonSentOutEvent{Side::Player, *battle.getPlayer()->getActivePokemon()});
        } else {
            auto team = battle.getOpponent()->getTeam();
            battle.getOpponent()->setActivePokemon(&team[action.index]);
            notifyObservers(
                PokemonSentOutEvent{Side::Opponent, *battle.getOpponent()->getActivePokemon()});
        }
    }
    return true;
}

auto BattleEngine::processTurnResult(Battle& battle) -> void {
    if (battle.getPlayer()->getActivePokemon()->getCurrentHp() <= 0 &&
        battle.getPlayer()->hasPokemonsAlive()) {
        notifyObservers(NewPokemonRequestEvent{battle.getPlayer()->getTeam()});
        auto action = battle.getPlayer()->chooseAction(Action::TrainerType::Player);
        battle.getPlayer()->setActivePokemon(action.index);
        notifyObservers(PokemonSentOutEvent{Side::Player, *battle.getPlayer()->getActivePokemon()});
    } else if (battle.getOpponent()->getActivePokemon()->getCurrentHp() <= 0 &&
               battle.getOpponent()->hasPokemonsAlive()) {
        auto action = battle.getOpponent()->chooseAction(Action::TrainerType::Opponent);
        battle.getOpponent()->setActivePokemon(action.index);
        notifyObservers(
            PokemonSentOutEvent{Side::Opponent, *battle.getOpponent()->getActivePokemon()});
    }
}

auto BattleEngine::checkBattleFinished(Battle& battle) -> void {
    if (!battle.getPlayer()->hasPokemonsAlive()) {
        battle.setResult(Result::OpponentWin);
        notifyObservers(BattleWinEvent{Side::Opponent});
    } else if (!battle.getOpponent()->hasPokemonsAlive()) {
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
}  // namespace engine
}  // namespace pokegym
