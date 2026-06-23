#include "pokegym/presentation/ConsoleActionSelector.hpp"

#include <iostream>

namespace pokegym::presentation {

auto ConsoleActionSelector::selectAction(const Pokemon& pokemon) -> Action {
    std::cout << "Elige ataque\n";

    for (size_t i = 0; i < pokemon.getMoves().size(); i++) {
        std::cout << i << ": " << pokemon.getMoves()[i].getName() << std::endl;
    }

    int choice = 0;
    std::cin >> choice;

    return Action{Action::TrainerType::Player, Action::Type::Attack, choice};
}

}  // namespace pokegym::presentation