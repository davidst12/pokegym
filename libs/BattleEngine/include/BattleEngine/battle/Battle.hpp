#pragma once

#include "BattleEngine/battle/Result.hpp"
#include "BattleEngine/trainer/Trainer.hpp"

namespace pokegym::engine::battle {

using pokegym::engine::battle::Result;
using pokegym::engine::trainer::Trainer;

class Battle {
   public:
    Battle(Trainer* player, Trainer* opponent);
    ~Battle() = default;

    auto getPlayer() const -> Trainer*;
    auto getOpponent() const -> Trainer*;

    auto incrementTurn() -> void;
    auto getCurrentTurn() const -> int;
    auto resetTurn() -> void;

    auto setResult(Result result) -> void;
    auto getResult() const -> Result;

   private:
    Trainer* player_;
    Trainer* opponent_;

    int current_turn_;

    Result result_;
};

}  // namespace pokegym::engine::battle
