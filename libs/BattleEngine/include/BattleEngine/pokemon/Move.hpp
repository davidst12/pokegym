#pragma once

#include <string>

#include "BattleEngine/pokemon/Types.hpp"

namespace pokegym::engine::pokemon {

class Move {
   public:
    explicit Move(const std::string& name, Type type, int power);
    ~Move() = default;

    auto getName() const -> std::string;
    auto getType() const -> Type;
    auto getPower() const -> int;

   private:
    std::string name_;
    Type type_;
    int power_;
};

}  // namespace pokegym::engine::pokemon
