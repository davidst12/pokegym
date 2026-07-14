#pragma once

#include "BattleEngine/battle/Battle.hpp"
#include "BattleEngine/battle/BattleEvent.hpp"
#include "BattleEngine/battle/BattleObserver.hpp"
#include "BattleEngine/battle/Result.hpp"
#include "BattleEngine/pokemon/Pokemon.hpp"

namespace pokegym::engine::battle {

using pokegym::engine::battle::Battle;
using pokegym::engine::battle::BattleObserver;
using pokegym::engine::battle::Result;
using pokegym::engine::pokemon::Pokemon;

class BattleEngine {
   public:
    BattleEngine();
    ~BattleEngine() = default;

    auto run(Battle& battle) -> Result;

    auto addObserver(BattleObserver* observer) -> void;

   private:
    auto executeTurn(Battle& battle) -> void;
    auto requestActions(Battle& battle) -> std::vector<std::tuple<Pokemon*, Action, Pokemon*>>;
    auto determineActionOrder(std::vector<std::tuple<Pokemon*, Action, Pokemon*>>& actions) -> void;
    auto executeAction(Battle& battle, Pokemon* pokemon, const Action& action, Pokemon* target)
        -> void;
    auto checkBattleFinished(Battle& battle) -> void;
    auto notifyObservers(const BattleEvent& event) -> void;

    std::vector<BattleObserver*> observers_;
};

}  // namespace pokegym::engine::battle
