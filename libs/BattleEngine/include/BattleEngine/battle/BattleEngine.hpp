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
    auto requestActions(Battle& battle) -> std::vector<Action>;
    auto determineActionOrder(Battle& battle, std::vector<Action>& actions) -> void;
    auto executeAction(Battle& battle, Action action) -> bool;
    auto checkBattleFinished(Battle& battle) -> void;
    auto notifyObservers(const BattleEvent& event) -> void;
    auto processTurnResult(Battle& battle) -> void;

    std::vector<BattleObserver*> observers_;
};

}  // namespace pokegym::engine::battle
