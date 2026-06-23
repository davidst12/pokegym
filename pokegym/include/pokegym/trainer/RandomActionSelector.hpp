#pragma once

#include "pokegym/battle/Action.hpp"
#include "pokegym/pokemon/Pokemon.hpp"
#include "pokegym/trainer/ActionSelection.hpp"

namespace pokegym::trainer {

using pokegym::battle::Action;
using pokegym::pokemon::Pokemon;
using pokegym::trainer::ActionSelector;

class RandomActionSelector : public ActionSelector {
   public:
    RandomActionSelector() = default;
    ~RandomActionSelector() = default;

    auto selectAction(const Pokemon& pokemon) -> Action override;
};

}  // namespace pokegym::trainer
