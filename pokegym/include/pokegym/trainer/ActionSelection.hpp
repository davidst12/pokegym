#pragma once

#include "pokegym/battle/Action.hpp"
#include "pokegym/pokemon/Pokemon.hpp"

namespace pokegym::trainer {

using pokegym::battle::Action;
using pokegym::pokemon::Pokemon;

class ActionSelector {
   public:
    virtual ~ActionSelector() = default;

    virtual auto selectAction(const Pokemon& pokemon) -> Action = 0;
};

}  // namespace pokegym::trainer
