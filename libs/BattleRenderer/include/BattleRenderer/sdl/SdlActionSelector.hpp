#pragma once

#include "BattleEngine/battle/Action.hpp"
#include "BattleEngine/pokemon/Pokemon.hpp"
#include "BattleEngine/trainer/ActionSelection.hpp"

namespace pokegym::renderer {

using pokegym::engine::battle::Action;
using pokegym::engine::pokemon::Pokemon;
using pokegym::engine::trainer::ActionSelector;

class SdlActionSelector : public ActionSelector {
   public:
    SdlActionSelector() = default;
    ~SdlActionSelector() = default;

    auto selectAction(const Pokemon& pokemon) -> Action override;
    auto selectPokemon(const std::vector<Pokemon>& team) -> Action override;
    auto setAction(const Action& action) -> void;

   private:
    Action selected_action_;
    bool action_selected_ = false;
    std::condition_variable action_selected_cv_;
    std::mutex action_selected_mutex_;
};

}  // namespace pokegym::renderer
