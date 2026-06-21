#pragma once

#include <string>

namespace pokegym::pokemon {

class Move {
   public:
    explicit Move(const std::string& name, int power);
    ~Move() = default;

    auto getName() const -> std::string;
    auto getPower() const -> int;

   private:
    std::string name_;
    int power_;
};

}  // namespace pokegym::pokemon
