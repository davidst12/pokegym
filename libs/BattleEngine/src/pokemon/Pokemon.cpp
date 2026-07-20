#include "BattleEngine/pokemon/Pokemon.hpp"

namespace pokegym::engine::pokemon {

Pokemon::Pokemon(const std::string& id, const std::string& name, Type type, int velocity,
                 int attack, int defense, int hp, std::vector<Move>& moves)
    : id_(id),
      name_(name),
      type_(type),
      velocity_(velocity),
      attack_(attack),
      defense_(defense),
      hp_(hp),
      current_hp_(hp),
      moves_(std::move(moves)) {}

auto Pokemon::getId() const -> const std::string& {
    return id_;
}

auto Pokemon::getName() const -> const std::string& {
    return name_;
}

auto Pokemon::getType() const -> const Type {
    return type_;
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

}  // namespace pokegym::engine::pokemon
