#pragma once

#include "pokegym/battle/BattleEvent.hpp"
#include "pokegym/battle/BattleObserver.hpp"

namespace pokegym::presentation {

using pokegym::battle::BattleEvent;
using pokegym::battle::BattleObserver;

class SdlBattleRenderer : public pokegym::battle::BattleObserver {
   public:
    SdlBattleRenderer();
    ~SdlBattleRenderer() = default;

    auto onBattleEvent(const pokegym::battle::BattleEvent& event) -> void override;
};

}  // namespace pokegym::presentation
