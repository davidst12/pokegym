#pragma once

#include "pokegym/battle/Battle.hpp"
#include "pokegym/battle/BattleEvent.hpp"
#include "pokegym/battle/BattleObserver.hpp"
#include "pokegym/battle/Result.hpp"
#include "pokegym/pokemon/Pokemon.hpp"

namespace pokegym::battle {

using pokegym::battle::Battle;
using pokegym::battle::BattleObserver;
using pokegym::battle::Result;
using pokegym::pokemon::Pokemon;

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

}  // namespace pokegym::battle
