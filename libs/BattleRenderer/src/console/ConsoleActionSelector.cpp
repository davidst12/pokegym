#include "BattleRenderer/console/ConsoleActionSelector.hpp"

#include <iostream>

namespace pokegym::renderer {

auto ConsoleActionSelector::selectAction(const Pokemon& pokemon) -> Action {
    std::cout << "Elige ataque\n";

    for (size_t i = 0; i < pokemon.getMoves().size(); i++) {
        std::cout << i << ": " << pokemon.getMoves()[i].getName() << std::endl;
    }

    int choice = 0;
    std::cin >> choice;

    return Action{Action::TrainerType::Player, Action::Type::Attack, choice};
}

auto ConsoleActionSelector::selectPokemon(const std::vector<Pokemon>& team) -> Action {
    std::cout << "Elige ataque\n";

    for (size_t i = 0; i < team.size(); i++) {
        std::cout << i << ": " << team[i].getName() << std::endl;
    }

    int choice = 0;
    std::cin >> choice;

    return Action{Action::TrainerType::Player, Action::Type::Attack, choice};
}

}  // namespace pokegym::renderer