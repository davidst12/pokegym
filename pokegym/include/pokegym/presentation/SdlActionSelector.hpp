#pragma once

#include "pokegym/battle/Action.hpp"
#include "pokegym/pokemon/Pokemon.hpp"
#include "pokegym/trainer/ActionSelection.hpp"

namespace pokegym::presentation {

using pokegym::battle::Action;
using pokegym::pokemon::Pokemon;
using pokegym::trainer::ActionSelector;

class SdlActionSelector : public ActionSelector {
   public:
    SdlActionSelector() = default;
    ~SdlActionSelector() = default;

    auto selectAction(const Pokemon& pokemon) -> Action override;
    auto setAction(const Action& action) -> void;

   private:
    Action selected_action_;
    bool action_selected_ = false;
    std::condition_variable action_selected_cv_;
    std::mutex action_selected_mutex_;
};

}  // namespace pokegym::presentation
