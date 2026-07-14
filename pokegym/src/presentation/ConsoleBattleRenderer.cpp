#include "pokegym/presentation/ConsoleBattleRenderer.hpp"

#include <iostream>

namespace pokegym::presentation {

auto ConsoleBattleRenderer::onBattleEvent(const pokegym::battle::BattleEvent& event) -> void {
    std::visit([&](auto&& event) { processEvent(event); }, event);
}

auto ConsoleBattleRenderer::processEvent(const pokegym::battle::BattleStartsEvent& event) -> void {
    std::cout << "You are challenged by Rival " << event.opponent_name << "!" << std::endl;
}

auto ConsoleBattleRenderer::processEvent(const pokegym::battle::PokemonSentOutEvent& event)
    -> void {
    if (event.side == pokegym::battle::Side::Player) {
        std::cout << "Go! " << event.pokemon.getName() << "!" << std::endl;
    } else {
        std::cout << "Rival sent out " << event.pokemon.getName() << "!" << std::endl;
    }
}

auto ConsoleBattleRenderer::processEvent(const pokegym::battle::ActionRequestEvent& event) -> void {
}

auto ConsoleBattleRenderer::processEvent(const pokegym::battle::MoveUsedEvent& event) -> void {
    if (event.side == pokegym::battle::Side::Player) {
        std::cout << "Used " << event.move_name << "!" << std::endl;
    } else {
        std::cout << "Rival used " << event.move_name << "!" << std::endl;
    }
}

auto ConsoleBattleRenderer::processEvent(const pokegym::battle::DamageEvent& event) -> void {
    if (event.side == pokegym::battle::Side::Player) {
        std::cout << "Player pokemon has " << event.new_hp << " HP left." << std::endl;
    } else {
        std::cout << "Rival pokemon has " << event.new_hp << " HP left." << std::endl;
    }
}

auto ConsoleBattleRenderer::processEvent(const pokegym::battle::PokemonFaintedEvent& event)
    -> void {
    if (event.side == pokegym::battle::Side::Player) {
        std::cout << "Player pokemon has fainted!" << std::endl;
    } else {
        std::cout << "Rival pokemon has fainted!" << std::endl;
    }
}

auto ConsoleBattleRenderer::processEvent(const pokegym::battle::BattleWinEvent& event) -> void {
    if (event.side == pokegym::battle::Side::Player) {
        std::cout << "Player wins the battle!" << std::endl;
    } else {
        std::cout << "Rival wins the battle!" << std::endl;
    }
}

}  // namespace pokegym::presentation
