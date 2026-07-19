#include "BattleEngine/trainer/Trainer.hpp"

#include <utility>

namespace pokegym::engine::trainer {

Trainer::Trainer(const std::string& name, std::vector<pokegym::engine::pokemon::Pokemon>& team,
                 ActionSelector* action_selector)
    : name_(name),
      team_(std::move(team)),
      active_pokemon_(team_.data()),
      action_selector_(action_selector) {}

auto Trainer::chooseAction(Action::TrainerType trainer_type) -> Action {
    Action action;
    if (active_pokemon_->getCurrentHp() > 0) {
        action = action_selector_->selectAction(*active_pokemon_);
    } else {
        action = action_selector_->selectPokemon(team_);
    }
    return action;
}

auto Trainer::getActivePokemon() const -> Pokemon* {
    return active_pokemon_;
}

auto Trainer::setActivePokemon(Pokemon* pokemon) -> void {
    active_pokemon_ = pokemon;
}

auto Trainer::setActivePokemon(int index) -> void {
    active_pokemon_ = &team_[index];
}

auto Trainer::getName() const -> const std::string& {
    return name_;
}

auto Trainer::getTeam() -> std::vector<Pokemon>& {
    return team_;
}

auto Trainer::hasPokemonsAlive() -> bool {
    for (auto& pokemon : team_) {
        if (pokemon.getCurrentHp() > 0) {
            return true;
        }
    }
    return false;
}

}  // namespace pokegym::engine::trainer
