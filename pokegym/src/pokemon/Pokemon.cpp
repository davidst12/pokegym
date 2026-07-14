#include "pokegym/pokemon/Pokemon.hpp"

namespace pokegym::pokemon {

Pokemon::Pokemon(const std::string& name, int velocity, int attack, int defense, int hp,
                 std::vector<Move>& moves)
    : name_(name),
      velocity_(velocity),
      attack_(attack),
      defense_(defense),
      hp_(hp),
      current_hp_(hp),
      moves_(std::move(moves)) {}

auto Pokemon::getName() const -> const std::string& {
    return name_;
}
auto Pokemon::getVelocity() const -> int {
    return velocity_;
}
auto Pokemon::getAttack() const -> int {
    return attack_;
}
auto Pokemon::getDefense() const -> int {
    return defense_;
}
auto Pokemon::getHp() const -> int {
    return hp_;
}

auto Pokemon::getCurrentHp() const -> int {
    return current_hp_;
}

auto Pokemon::takeDamage(int damage) -> void {
    current_hp_ = std::max(current_hp_ - damage, 0);
}

auto Pokemon::getMoves() const -> const std::vector<Move>& {
    return moves_;
}

auto Pokemon::getMovesNames() const -> const std::vector<std::string> {
    std::vector<std::string> moves_names;
    for (const auto& move : moves_) {
        moves_names.push_back(move.getName());
    }
    return moves_names;
}

}  // namespace pokegym::pokemon
