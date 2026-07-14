#pragma once

#include "pokegym/battle/BattleEvent.hpp"
#include "pokegym/battle/BattleObserver.hpp"

namespace pokegym::presentation {

using pokegym::battle::BattleEvent;
using pokegym::battle::BattleObserver;

class ConsoleBattleRenderer : public pokegym::battle::BattleObserver {
   public:
    ConsoleBattleRenderer() = default;
    ~ConsoleBattleRenderer() = default;

    auto onBattleEvent(const pokegym::battle::BattleEvent& event) -> void override;

    auto processEvent(const pokegym::battle::BattleStartsEvent& event) -> void;
    auto processEvent(const pokegym::battle::PokemonSentOutEvent& event) -> void;
    auto processEvent(const pokegym::battle::ActionRequestEvent& event) -> void;
    auto processEvent(const pokegym::battle::MoveUsedEvent& event) -> void;
    auto processEvent(const pokegym::battle::DamageEvent& event) -> void;
    auto processEvent(const pokegym::battle::PokemonFaintedEvent& event) -> void;
    auto processEvent(const pokegym::battle::BattleWinEvent& event) -> void;
};

}  // namespace pokegym::presentation
