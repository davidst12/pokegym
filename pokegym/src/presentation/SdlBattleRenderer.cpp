#include "pokegym/presentation/SdlBattleRenderer.hpp"

#include <iostream>

namespace pokegym::presentation {

SdlBattleRenderer::SdlBattleRenderer() {}

auto SdlBattleRenderer::onBattleEvent(const pokegym::battle::BattleEvent& event) -> void {
    switch (event.type) {
        case pokegym::battle::BattleEventType::BattleStarts:
            break;
        case pokegym::battle::BattleEventType::PlayerNewPokemon:
            break;
        case pokegym::battle::BattleEventType::OpponentNewPokemon:
            break;
        case pokegym::battle::BattleEventType::PlayerSelectsAction:
            break;
        case pokegym::battle::BattleEventType::OpponentSelectsAction:
            break;
        case pokegym::battle::BattleEventType::PlayerSelectsMove:
            break;
        case pokegym::battle::BattleEventType::OpponentSelectsMove:
            break;
        case pokegym::battle::BattleEventType::PlayerAttacks:
            break;
        case pokegym::battle::BattleEventType::OpponentAttacks:
            break;
        case pokegym::battle::BattleEventType::PlayerPokemonNewHp:
            break;
        case pokegym::battle::BattleEventType::OpponentPokemonNewHp:
            break;
        case pokegym::battle::BattleEventType::PlayerPokemonFainted:
            break;
        case pokegym::battle::BattleEventType::OpponentPokemonFainted:  // Fixed the typo here
            break;
        case pokegym::battle::BattleEventType::PlayerWins:
            break;
        case pokegym::battle::BattleEventType::OpponentWins:
            break;
        default:
            break;
    }
}

}  // namespace pokegym::presentation
