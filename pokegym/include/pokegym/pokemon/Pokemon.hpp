#pragma once

#include <string>
#include <vector>

#include "pokegym/pokemon/Move.hpp"

namespace pokegym::pokemon {

class Pokemon {
   public:
    explicit Pokemon(const std::string& name, int velocity, int attack, int defense, int hp,
                     std::vector<Move>& moves);
    ~Pokemon() = default;

    auto getName() const -> const std::string&;
    auto getVelocity() const -> int;
    auto getAttack() const -> int;
    auto getDefense() const -> int;
    auto getHp() const -> int;
    auto getCurrentHp() const -> int;
    auto getMoves() const -> const std::vector<Move>&;
    auto getMovesNames() const -> const std::vector<std::string>;

    auto takeDamage(int damage) -> void;

   private:
    std::string name_;
    int velocity_;
    int attack_;
    int defense_;
    int hp_;
    int current_hp_;
    std::vector<Move> moves_;
};

}  // namespace pokegym::pokemon
