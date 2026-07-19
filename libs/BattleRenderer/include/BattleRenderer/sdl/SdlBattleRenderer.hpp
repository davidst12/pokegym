#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include <optional>
#include <queue>
#include <string>
#include <thread>

#include "BattleEngine/battle/BattleEvent.hpp"
#include "BattleEngine/battle/BattleObserver.hpp"
#include "BattleEngine/pokemon/Pokemon.hpp"
#include "BattleRenderer/sdl/SdlActionSelector.hpp"
#include "BattleRenderer/sdl/TextureManager.hpp"

namespace pokegym::renderer {

using pokegym::engine::battle::BattleEvent;
using pokegym::engine::battle::BattleObserver;

struct PokemonVisualization {
    std::string name = "";
    int current_hp = 0;
    int max_hp = 0;
    SDL_Texture* texture = nullptr;
    bool is_drawn = false;
};

struct ActionRequestAnimation {
    enum class State {
        ShowQuestion,
        ShowActions,
        ShowMoves,
        ShowPokemons,
        Idle
    } state = State::Idle;
    bool is_action_requested = false;
    std::vector<std::string> actions_prompt = {};
    std::vector<std::string> moves_prompt = {};
    std::vector<std::string> pokemon_prompt = {};
};

class SdlBattleRenderer : public pokegym::engine::battle::BattleObserver {
   public:
    SdlBattleRenderer(SdlActionSelector& action_selector);
    ~SdlBattleRenderer();

    auto run() -> void;
    auto onBattleEvent(const pokegym::engine::battle::BattleEvent& event) -> void override;

   private:
    auto drawOpponentPokemon(SDL_Renderer* renderer) -> void;
    auto drawPlayertPokemon(SDL_Renderer* renderer) -> void;
    auto drawDialogTextBox(SDL_Renderer* renderer) -> void;
    auto drawBackground(SDL_Renderer* renderer, const char* path) -> void;

    auto waitInput() -> bool;

    auto processEvent(const pokegym::engine::battle::BattleStartsEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::PokemonSentOutEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::ActionRequestEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::MoveUsedEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::DamageEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::PokemonFaintedEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::NewPokemonRequestEvent& event) -> void;
    auto processEvent(const pokegym::engine::battle::BattleWinEvent& event) -> void;

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

    std::unique_ptr<TextureManager> texture_manager_ = nullptr;
};

}  // namespace pokegym::renderer
