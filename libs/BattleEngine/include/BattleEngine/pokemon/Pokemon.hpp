#pragma once

#include <string>
#include <vector>

#include "BattleEngine/pokemon/Move.hpp"
#include "BattleEngine/pokemon/Types.hpp"

namespace pokegym::engine::pokemon {

class Pokemon {
   public:
    explicit Pokemon(const std::string& id, const std::string& name, Type type, int velocity,
                     int attack, int defense, int hp, std::vector<Move>& moves);
    ~Pokemon() = default;

    auto getId() const -> const std::string&;
    auto getName() const -> const std::string&;
    auto getType() const -> const Type;
    auto getVelocity() const -> int;
    auto getAttack() const -> int;
    auto getDefense() const -> int;
    auto getHp() const -> int;
    auto getCurrentHp() const -> int;
    auto getMoves() const -> const std::vector<Move>&;
    auto getMovesNames() const -> const std::vector<std::string>;

    auto takeDamage(int damage) -> void;

   private:
    std::string id_;
    std::string name_;
    Type type_;
    int velocity_;
    int attack_;
    int defense_;
    int hp_;
    int current_hp_;
    std::vector<Move> moves_;
};

}  // namespace pokegym::engine::pokemon
