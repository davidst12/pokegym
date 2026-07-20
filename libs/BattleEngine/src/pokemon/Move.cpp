#include "BattleEngine/pokemon/Move.hpp"

namespace pokegym::engine::pokemon {

Move::Move(const std::string& name, Type type, int power)
    : name_(name), type_(type), power_(power) {}

auto Move::getName() const -> std::string {
    return name_;
}

auto Move::getType() const -> Type {
    return type_;
}

auto Move::getPower() const -> int {
    return power_;
}

}  // namespace pokegym::engine::pokemon
