#pragma once

namespace pokegym::battle {

class BattleObserver {
   public:
    BattleObserver() = default;
    virtual ~BattleObserver() = default;

    virtual auto onBattleEvent(const BattleEvent& event) -> void = 0;
};

}  // namespace pokegym::battle
