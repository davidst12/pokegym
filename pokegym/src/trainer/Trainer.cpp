#include "pokegym/trainer/Trainer.hpp"

#include <utility>

namespace pokegym::trainer {

Trainer::Trainer(const std::string& name, std::vector<pokegym::pokemon::Pokemon>& team)
    : name_(name), team_(std::move(team)), active_pokemon_(team_.data()) {}

auto Trainer::chooseAction() -> Action {
    Action action;
    action.type = Action::Type::Attack;
    action.index = 0;  // Always choose the first move for now
    return action;
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
