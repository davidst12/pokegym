#pragma once

#include "pokegym/battle/Action.hpp"
#include "pokegym/pokemon/Pokemon.hpp"
#include "pokegym/trainer/ActionSelection.hpp"

namespace pokegym::presentation {

using pokegym::battle::Action;
using pokegym::pokemon::Pokemon;
using pokegym::trainer::ActionSelector;

class ConsoleActionSelector : public ActionSelector {
   public:
    ConsoleActionSelector() = default;
    ~ConsoleActionSelector() = default;

    auto selectAction(const Pokemon& pokemon) -> Action override;
};

}  // namespace pokegym::presentation
