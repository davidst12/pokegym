#pragma once

#include "pokegym/battle/Result.hpp"
#include "pokegym/trainer/Trainer.hpp"

namespace pokegym::battle {

using pokegym::battle::Result;
using pokegym::trainer::Trainer;

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

}  // namespace pokegym::battle
