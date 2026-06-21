#include "pokegym/pokemon/Move.hpp"

namespace pokegym::pokemon {

Move::Move(const std::string& name, int power) : name_(name), power_(power) {}

auto Move::getName() const -> std::string {
    return name_;
}

auto Move::getPower() const -> int {
    return power_;
}

}  // namespace pokegym::pokemon
