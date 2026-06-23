#include "pokegym/trainer/RandomActionSelector.hpp"

namespace pokegym::trainer {

auto RandomActionSelector::selectAction(const Pokemon& pokemon) -> Action {
    return Action{Action::TrainerType::Opponent, Action::Type::Attack, 0};
}

}  // namespace pokegym::trainer
