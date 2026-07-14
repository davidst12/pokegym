#pragma once

#include "BattleEngine/battle/Action.hpp"
#include "BattleEngine/pokemon/Pokemon.hpp"

namespace pokegym::engine::trainer {

using pokegym::engine::battle::Action;
using pokegym::engine::pokemon::Pokemon;

class ActionSelector {
   public:
    virtual ~ActionSelector() = default;

    virtual auto selectAction(const Pokemon& pokemon) -> Action = 0;
};

}  // namespace pokegym::engine::trainer
