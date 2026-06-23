#include "pokegym/trainer/Trainer.hpp"

#include <utility>

namespace pokegym::trainer {

Trainer::Trainer(const std::string& name, std::vector<pokegym::pokemon::Pokemon>& team,
                 ActionSelector* action_selector)
    : name_(name),
      team_(std::move(team)),
      active_pokemon_(team_.data()),
      action_selector_(action_selector) {}

auto Trainer::chooseAction(Action::TrainerType trainer_type) -> Action {
    return action_selector_->selectAction(*active_pokemon_);
}

auto Trainer::getActivePokemon() const -> Pokemon* {
    return active_pokemon_;
}

auto Trainer::setActivePokemon(Pokemon* pokemon) -> void {
    active_pokemon_ = pokemon;
}

auto Trainer::getName() const -> const std::string& {
    return name_;
}

auto Trainer::getTeam() -> std::vector<Pokemon>& {
    return team_;
}

}  // namespace pokegym::trainer
