#pragma once

#include "BattleEngine/battle/BattleEvent.hpp"
#include "BattleEngine/battle/BattleObserver.hpp"

namespace pokegym::renderer {

using pokegym::engine::battle::BattleEvent;
using pokegym::engine::battle::BattleObserver;

class ConsoleBattleRenderer : public pokegym::engine::battle::BattleObserver {
   public:
    ConsoleBattleRenderer() = default;
    ~ConsoleBattleRenderer() = default;

    auto onBattleEvent(const pokegym::engine::battle::BattleEvent& event) -> void override;

    auto processEvent(const pokegym::engine::battle::BattleStartsEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::PokemonSentOutEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::ActionRequestEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::MoveUsedEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::DamageEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::PokemonFaintedEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::NewPokemonRequestEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::BattleWinEvent& event) -> void;
};

}  // namespace pokegym::renderer
