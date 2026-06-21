#include "pokegym/battle/Battle.hpp"

namespace pokegym::battle {

Battle::Battle(Trainer* player, Trainer* opponent)
    : player_(player), opponent_(opponent), current_turn_(0), result_(Result::Undefined) {}

auto Battle::getPlayer() const -> Trainer* {
    return player_;
}

auto Battle::getOpponent() const -> Trainer* {
    return opponent_;
}

auto Battle::incrementTurn() -> void {
    current_turn_++;
}

auto Battle::getCurrentTurn() const -> int {
    return current_turn_;
}

auto Battle::resetTurn() -> void {
    current_turn_ = 0;
}

auto Battle::setResult(Result result) -> void {
    result_ = result;
}

auto Battle::getResult() const -> Result {
    return result_;
}

}  // namespace pokegym::battle
