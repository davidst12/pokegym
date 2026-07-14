#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include <optional>
#include <queue>
#include <string>
#include <thread>

#include "pokegym/battle/BattleEvent.hpp"
#include "pokegym/battle/BattleObserver.hpp"
#include "pokegym/pokemon/Pokemon.hpp"
#include "pokegym/presentation/SdlActionSelector.hpp"

namespace pokegym::presentation {

using pokegym::battle::BattleEvent;
using pokegym::battle::BattleObserver;

struct PokemonVisualization {
    std::string name = "";
    int current_hp = 0;
    int max_hp = 0;
    SDL_Texture* texture = nullptr;
};

struct ActionRequestAnimation {
    enum class State { ShowQuestion, ShowActions, ShowMoves, Idle } state = State::Idle;
    bool is_action_requested = false;
    std::vector<std::string> actions_prompt = {};
    std::vector<std::string> moves_prompt = {};
};

class SdlBattleRenderer : public pokegym::battle::BattleObserver {
   public:
    SdlBattleRenderer(SdlActionSelector& action_selector);
    ~SdlBattleRenderer();

    auto run() -> void;
    auto onBattleEvent(const pokegym::battle::BattleEvent& event) -> void override;

   private:
    auto drawOpponentPokemon(SDL_Renderer* renderer, const char* path) -> void;
    auto drawPlayertPokemon(SDL_Renderer* renderer, const char* path) -> void;
    auto drawDialogTextBox(SDL_Renderer* renderer) -> void;
    auto drawBackground(SDL_Renderer* renderer, const char* path) -> void;

    auto waitInput() -> bool;

    auto processEvent(const pokegym::battle::BattleStartsEvent& event) -> void;
    auto processEvent(const pokegym::battle::PokemonSentOutEvent& event) -> void;
    auto processEvent(const pokegym::battle::ActionRequestEvent& event) -> void;
    auto processEvent(const pokegym::battle::MoveUsedEvent& event) -> void;
    auto processEvent(const pokegym::battle::DamageEvent& event) -> void;
    auto processEvent(const pokegym::battle::PokemonFaintedEvent& event) -> void;
    auto processEvent(const pokegym::battle::BattleWinEvent& event) -> void;

    auto processActionInput(int selection) -> void;

    bool running_ = false;

    int width_;
    int height_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    TTF_Font* font_medium_;
    TTF_Font* font_small_;
    std::thread main_loop_;
    std::queue<BattleEvent> event_queue_;
    SdlActionSelector& action_selector_;
    ActionRequestAnimation action_animation_ = ActionRequestAnimation();

    std::string dialog_text_ = " ";
    std::optional<PokemonVisualization> player_pokemon_ = std::nullopt;
    std::optional<PokemonVisualization> opponent_pokemon_ = std::nullopt;
};

}  // namespace pokegym::presentation
