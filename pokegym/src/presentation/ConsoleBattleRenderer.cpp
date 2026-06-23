#include "pokegym/presentation/ConsoleBattleRenderer.hpp"

#include <iostream>

namespace pokegym::presentation {

auto ConsoleBattleRenderer::onBattleEvent(const pokegym::battle::BattleEvent& event) -> void {
    switch (event.type) {
        case pokegym::battle::BattleEventType::BattleStarts:
            std::cout << "You are challenged by Rival " << event.battle->getOpponent()->getName()
                      << "!" << std::endl;
            break;
        case pokegym::battle::BattleEventType::PlayerNewPokemon:
            std::cout << "Go! " << event.battle->getPlayer()->getActivePokemon()->getName() << "!"
                      << std::endl;
            break;
        case pokegym::battle::BattleEventType::OpponentNewPokemon:
            std::cout << "Rival " << event.battle->getOpponent()->getName() << " sent out "
                      << event.battle->getOpponent()->getActivePokemon()->getName() << "!"
                      << std::endl;
            break;
        case pokegym::battle::BattleEventType::PlayerSelectsAction:
            std::cout << "What will " << event.battle->getPlayer()->getActivePokemon()->getName()
                      << " do?" << std::endl;
            break;
        case pokegym::battle::BattleEventType::OpponentSelectsAction:
            std::cout << "Opponent selected an action." << std::endl;
            break;
        case pokegym::battle::BattleEventType::PlayerSelectsMove:
            std::cout << "Player selected a move." << std::endl;
            break;
        case pokegym::battle::BattleEventType::OpponentSelectsMove:
            std::cout << "Opponent selected a move." << std::endl;
            break;
        case pokegym::battle::BattleEventType::PlayerAttacks:
            std::cout << event.battle->getPlayer()->getActivePokemon()->getName() << " used "
                      << event.move_name << "!" << std::endl;
            break;
        case pokegym::battle::BattleEventType::OpponentAttacks:
            std::cout << "The foe's " << event.battle->getOpponent()->getActivePokemon()->getName()
                      << " used " << event.move_name << "!" << std::endl;
            break;
        case pokegym::battle::BattleEventType::PlayerPokemonNewHp:
            std::cout << event.battle->getPlayer()->getActivePokemon()->getName() << " has "
                      << event.battle->getPlayer()->getActivePokemon()->getCurrentHp()
                      << " HP left." << std::endl;
            break;
        case pokegym::battle::BattleEventType::OpponentPokemonNewHp:
            std::cout << event.battle->getOpponent()->getActivePokemon()->getName() << " has "
                      << event.battle->getOpponent()->getActivePokemon()->getCurrentHp()
                      << " HP left." << std::endl;
            break;
        case pokegym::battle::BattleEventType::PlayerPokemonFainted:
            std::cout << event.battle->getPlayer()->getActivePokemon()->getName() << " fainted!"
                      << std::endl;
            break;
        case pokegym::battle::BattleEventType::OpponentPokemonFainted:  // Fixed the typo here
            std::cout << "The foe's " << event.battle->getOpponent()->getActivePokemon()->getName()
                      << " fainted!" << std::endl;
            break;
        case pokegym::battle::BattleEventType::PlayerWins:
            std::cout << event.battle->getPlayer()->getName() << " wins the battle!" << std::endl;
            break;
        case pokegym::battle::BattleEventType::OpponentWins:
            std::cout << event.battle->getOpponent()->getName() << " wins the battle!" << std::endl;
            break;
        default:
            std::cout << "Unknown battle event." << std::endl;
            break;
    }
}

}  // namespace pokegym::presentation
