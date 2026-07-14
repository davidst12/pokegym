#include "BattleEngine/trainer/RandomActionSelector.hpp"

namespace pokegym::engine::trainer {

auto RandomActionSelector::selectAction(const Pokemon& pokemon) -> Action {
    return Action{Action::TrainerType::Opponent, Action::Type::Attack, 0};
}

}  // namespace pokegym::engine::trainer
