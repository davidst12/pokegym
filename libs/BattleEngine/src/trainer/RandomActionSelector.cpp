#include "BattleEngine/trainer/RandomActionSelector.hpp"

namespace pokegym::engine::trainer {

auto RandomActionSelector::selectAction(const Pokemon& pokemon) -> Action {
    return Action{Action::TrainerType::Opponent, Action::Type::Attack, 0};
}

auto RandomActionSelector::selectPokemon(const std::vector<Pokemon>& team) -> Action {
    int index = 0;
    for (const auto& pokemon : team) {
        if (pokemon.getCurrentHp() > 0) {
            return Action{Action::TrainerType::Opponent, Action::Type::SwitchPokemon, index};
        }
        index++;
    }
    return Action{Action::TrainerType::Opponent, Action::Type::SwitchPokemon, 99};
}

}  // namespace pokegym::engine::trainer
