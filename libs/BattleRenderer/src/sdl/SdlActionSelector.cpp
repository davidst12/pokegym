#include "BattleRenderer/sdl/SdlActionSelector.hpp"

#include <iostream>

namespace pokegym::renderer {

auto SdlActionSelector::selectAction(const Pokemon& pokemon) -> Action {
    std::unique_lock lock(action_selected_mutex_);

    action_selected_cv_.wait(lock, [&] { return action_selected_; });
    action_selected_ = false;  // Reset the flag for the next action selection

    return selected_action_;
}

auto SdlActionSelector::setAction(const Action& action) -> void {
    selected_action_ = action;
    action_selected_ = true;
    action_selected_cv_.notify_one();
}

}  // namespace pokegym::renderer