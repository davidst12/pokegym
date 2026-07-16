#include "BattleRenderer/sdl/SdlBattleRenderer.hpp"

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <thread>

namespace pokegym::renderer {

SdlBattleRenderer::SdlBattleRenderer(SdlActionSelector& action_selector)
    : width_(800),
      height_(600),
      window_(nullptr),
      renderer_(nullptr),
      font_medium_(nullptr),
      font_small_(nullptr),
      action_selector_(action_selector) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error inicializando SDL: " << SDL_GetError() << "\n";
        return;
    }

    if (TTF_Init() != 0) {
        std::cerr << "Error inicializando SDL_ttf: " << TTF_GetError() << "\n";
        SDL_Quit();
        return;
    }

    window_ = SDL_CreateWindow("Pokegym", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_,
                               height_, SDL_WINDOW_SHOWN);

    if (window_ == nullptr) {
        std::cerr << "Error creando ventana: " << SDL_GetError() << "\n";

        TTF_Quit();
        SDL_Quit();
        return;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

    if (renderer_ == nullptr) {
        std::cerr << "Error creando renderer: " << SDL_GetError() << "\n";

        SDL_DestroyWindow(window_);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // Fuente (necesitas un .ttf)
    font_medium_ = TTF_OpenFont("assets/fonts/pkmn_font.ttf", 28);
    font_small_ = TTF_OpenFont("assets/fonts/pkmn_font.ttf", 22);

    if (font_small_ == nullptr || font_medium_ == nullptr) {
        std::cerr << "Error cargando fuente: " << TTF_GetError() << "\n";
    }

    texture_manager_ = std::make_unique<TextureManager>(renderer_);
}

SdlBattleRenderer::~SdlBattleRenderer() {
    TTF_CloseFont(font_medium_);
    TTF_CloseFont(font_small_);

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    TTF_Quit();
    SDL_Quit();
}

auto SdlBattleRenderer::run() -> void {
    running_ = true;

    while (running_) {
        if (event_queue_.empty() && !action_animation_.is_action_requested) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        if (!action_animation_.is_action_requested) {
            auto event = event_queue_.front();
            event_queue_.pop();
            std::visit([&](auto&& event) { processEvent(event); }, event);
        }

        // Fondo
        SDL_RenderClear(renderer_);
        SDL_SetRenderDrawColor(renderer_, 30, 80, 120, 255);

        drawBackground(renderer_, "assets/battle/battle_blank_template.jpg");
        drawDialogTextBox(renderer_);
        drawPlayertPokemon(renderer_);
        drawOpponentPokemon(renderer_);

        SDL_RenderPresent(renderer_);

        // std::this_thread::sleep_for(std::chrono::seconds(2));

        bool exit = waitInput();
        if (exit) {
            running_ = false;
        }
    }
}

auto SdlBattleRenderer::drawBackground(SDL_Renderer* renderer, const char* path) -> void {
    SDL_Surface* battle_template_surface = IMG_Load(path);

    if (!battle_template_surface)
        return;

    SDL_Texture* battle_template_texture =
        SDL_CreateTextureFromSurface(renderer, battle_template_surface);

    SDL_FreeSurface(battle_template_surface);

    SDL_Rect battle_template_box;
    battle_template_box.x = 0;
    battle_template_box.y = 0;
    battle_template_box.w = 800;
    battle_template_box.h = 600;

    SDL_RenderCopy(renderer, battle_template_texture, nullptr, &battle_template_box);
}

auto SdlBattleRenderer::drawDialogTextBox(SDL_Renderer* renderer) -> void {
    if (action_animation_.is_action_requested &&
        action_animation_.state == ActionRequestAnimation::State::ShowActions) {
        std::vector<SDL_Rect> action_text_boxes{
            {50, 455, 0, 0}, {width_ / 2, 455, 0, 0}, {50, 515, 0, 0}, {width_ / 2, 515, 0, 0}};
        for (int i = 0; i < action_animation_.actions_prompt.size(); ++i) {
            SDL_Color white{255, 255, 255, 255};
            SDL_Surface* action_text_surface = TTF_RenderText_Solid(
                font_medium_, action_animation_.actions_prompt[i].c_str(), white);
            SDL_Texture* action_text_texture =
                SDL_CreateTextureFromSurface(renderer, action_text_surface);

            action_text_boxes[i].w = action_text_surface->w;
            action_text_boxes[i].h = action_text_surface->h;

            SDL_RenderCopy(renderer, action_text_texture, nullptr, &action_text_boxes[i]);
        }
    } else if (action_animation_.is_action_requested &&
               action_animation_.state == ActionRequestAnimation::State::ShowMoves) {
        std::vector<SDL_Rect> action_text_boxes{
            {50, 455, 0, 0}, {width_ / 2, 455, 0, 0}, {50, 515, 0, 0}, {width_ / 2, 515, 0, 0}};
        for (int i = 0; i < action_animation_.moves_prompt.size(); ++i) {
            SDL_Color white{255, 255, 255, 255};
            SDL_Surface* action_text_surface = TTF_RenderText_Solid(
                font_medium_, action_animation_.moves_prompt[i].c_str(), white);
            SDL_Texture* action_text_texture =
                SDL_CreateTextureFromSurface(renderer, action_text_surface);

            action_text_boxes[i].w = action_text_surface->w;
            action_text_boxes[i].h = action_text_surface->h;

            SDL_RenderCopy(renderer, action_text_texture, nullptr, &action_text_boxes[i]);
        }
    } else {
        SDL_Color white{255, 255, 255, 255};
        SDL_Surface* dialog_text_surface =
            TTF_RenderText_Solid(font_medium_, dialog_text_.c_str(), white);
        SDL_Texture* dialog_text_texture =
            SDL_CreateTextureFromSurface(renderer, dialog_text_surface);

        SDL_Rect dialog_text_dst;
        dialog_text_dst.x = 50;
        dialog_text_dst.y = 455;
        dialog_text_dst.w = dialog_text_surface->w;
        dialog_text_dst.h = dialog_text_surface->h;

        SDL_RenderCopy(renderer, dialog_text_texture, nullptr, &dialog_text_dst);
    }
}

auto SdlBattleRenderer::drawPlayertPokemon(SDL_Renderer* renderer) -> void {
    if (!player_pokemon_.has_value()) {
        return;
    }

    if (player_pokemon_.value().texture == nullptr) {
        player_pokemon_.value().texture =
            texture_manager_->getTexture(player_pokemon_.value().name, false);
    }

    SDL_Rect player_pokemon_rect;
    player_pokemon_rect.x = 150;
    player_pokemon_rect.y = 237;
    player_pokemon_rect.w = 180;
    player_pokemon_rect.h = 180;

    SDL_RenderCopy(renderer, player_pokemon_.value().texture, nullptr, &player_pokemon_rect);

    SDL_Color black{0, 0, 0, 0};
    std::string hp_text = player_pokemon_.value().name + "     " +
                          std::to_string(player_pokemon_.value().current_hp) + "/" +
                          std::to_string(player_pokemon_.value().max_hp);

    SDL_Surface* ply_pk_name_surface = TTF_RenderText_Solid(font_small_, hp_text.c_str(), black);
    SDL_Texture* ply_pk_name_texture = SDL_CreateTextureFromSurface(renderer, ply_pk_name_surface);

    SDL_Rect ply_pk_name_box;
    ply_pk_name_box.x = 470;
    ply_pk_name_box.y = 296;
    ply_pk_name_box.w = 260;
    ply_pk_name_box.h = ply_pk_name_surface->h;

    SDL_RenderCopy(renderer, ply_pk_name_texture, nullptr, &ply_pk_name_box);
}

auto SdlBattleRenderer::drawOpponentPokemon(SDL_Renderer* renderer) -> void {
    if (!opponent_pokemon_.has_value()) {
        return;
    }

    if (opponent_pokemon_.value().texture == nullptr) {
        opponent_pokemon_.value().texture =
            texture_manager_->getTexture(opponent_pokemon_.value().name, true);
    }

    SDL_Rect opponent_pokemon_rect;
    opponent_pokemon_rect.x = 500;
    opponent_pokemon_rect.y = 90;
    opponent_pokemon_rect.w = 180;
    opponent_pokemon_rect.h = 180;

    SDL_RenderCopy(renderer, opponent_pokemon_.value().texture, nullptr, &opponent_pokemon_rect);

    SDL_Color black{0, 0, 0, 0};
    std::string hp_text = opponent_pokemon_.value().name + "     " +
                          std::to_string(opponent_pokemon_.value().current_hp) + "/" +
                          std::to_string(opponent_pokemon_.value().max_hp);

    SDL_Surface* opp_pk_name_surface = TTF_RenderText_Solid(font_small_, hp_text.c_str(), black);
    SDL_Texture* opp_pk_name_texture = SDL_CreateTextureFromSurface(renderer, opp_pk_name_surface);

    SDL_Rect opp_pk_name_box;
    opp_pk_name_box.x = 65;
    opp_pk_name_box.y = 82;
    opp_pk_name_box.w = 260;
    opp_pk_name_box.h = opp_pk_name_surface->h;

    SDL_RenderCopy(renderer, opp_pk_name_texture, nullptr, &opp_pk_name_box);
}

auto SdlBattleRenderer::onBattleEvent(const pokegym::engine::battle::BattleEvent& event) -> void {
    event_queue_.push(event);
}

auto SdlBattleRenderer::waitInput() -> bool {
    SDL_Event event;

    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        } else if (action_animation_.is_action_requested && event.type == SDL_KEYDOWN) {
            int selection = -1;
            switch (event.key.keysym.sym) {
                case SDLK_1:
                    selection = 1;
                    break;
                case SDLK_2:
                    selection = 2;
                    break;
                case SDLK_3:
                    selection = 3;
                    break;
                case SDLK_4:
                    selection = 4;
                    break;
                default:
                    selection = -1;
            }
            processActionInput(selection);
            break;
        } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            break;
    }
    return false;
}

auto SdlBattleRenderer::processEvent(const pokegym::engine::battle::BattleStartsEvent& event)
    -> void {
    dialog_text_ = "You are challenged by Rival " + event.opponent_name + "!";
}

auto SdlBattleRenderer::processEvent(const pokegym::engine::battle::PokemonSentOutEvent& event)
    -> void {
    if (event.side == pokegym::engine::battle::Side::Player) {
        dialog_text_ = "Go! " + event.pokemon.getName() + "!";
        player_pokemon_ = PokemonVisualization{.name = event.pokemon.getName(),
                                               .current_hp = event.pokemon.getCurrentHp(),
                                               .max_hp = event.pokemon.getHp(),
                                               .texture = nullptr};
    } else {
        dialog_text_ = "Rival sent out " + event.pokemon.getName() + "!";
        opponent_pokemon_ = PokemonVisualization{.name = event.pokemon.getName(),
                                                 .current_hp = event.pokemon.getCurrentHp(),
                                                 .max_hp = event.pokemon.getHp(),
                                                 .texture = nullptr};
    }
}

auto SdlBattleRenderer::processEvent(const pokegym::engine::battle::ActionRequestEvent& event)
    -> void {
    action_animation_.is_action_requested = true;
    action_animation_.state = ActionRequestAnimation::State::ShowQuestion;
    dialog_text_ = "Player, choose your action!";
    int index = 1;
    for (const auto& action_name : event.action_names_list) {
        action_animation_.actions_prompt.push_back(std::to_string(index++) + ". " + action_name);
    }
    index = 1;
    for (const auto& move_name : event.move_names_list) {
        action_animation_.moves_prompt.push_back(std::to_string(index++) + ". " + move_name);
    }
}

auto SdlBattleRenderer::processEvent(const pokegym::engine::battle::MoveUsedEvent& event) -> void {
    if (event.side == pokegym::engine::battle::Side::Player) {
        dialog_text_ = "Used " + event.move_name + "!";
    } else {
        dialog_text_ = "Rival used " + event.move_name + "!";
    }
}

auto SdlBattleRenderer::processEvent(const pokegym::engine::battle::DamageEvent& event) -> void {
    if (event.side == pokegym::engine::battle::Side::Player) {
        dialog_text_ = "Player pokemon has " + std::to_string(event.new_hp) + " HP left.";
        if (player_pokemon_.has_value()) {
            player_pokemon_.value().current_hp = event.new_hp;
        }
    } else {
        dialog_text_ = "Rival pokemon has " + std::to_string(event.new_hp) + " HP left.";
        if (opponent_pokemon_.has_value()) {
            opponent_pokemon_.value().current_hp = event.new_hp;
        }
    }
}

auto SdlBattleRenderer::processEvent(const pokegym::engine::battle::PokemonFaintedEvent& event)
    -> void {
    if (event.side == pokegym::engine::battle::Side::Player) {
        dialog_text_ = "Player pokemon has fainted!";
        player_pokemon_.reset();
    } else {
        dialog_text_ = "Rival pokemon has fainted!";
        opponent_pokemon_.reset();
    }
}

auto SdlBattleRenderer::processEvent(const pokegym::engine::battle::BattleWinEvent& event) -> void {
    if (event.side == pokegym::engine::battle::Side::Player) {
        dialog_text_ = "Player wins the battle!";
    } else {
        dialog_text_ = "Rival wins the battle!";
    }
    running_ = false;
}

auto SdlBattleRenderer::processActionInput(int selection) -> void {
    switch (action_animation_.state) {
        case ActionRequestAnimation::State::ShowQuestion:
            action_animation_.state = ActionRequestAnimation::State::ShowActions;
            break;
        case ActionRequestAnimation::State::ShowActions:
            if (selection >= 1 && selection <= 3) {
                action_animation_.state = ActionRequestAnimation::State::ShowMoves;
            }
            break;

        case ActionRequestAnimation::State::ShowMoves:
            if (selection >= 1 && selection <= 4) {
                Action action{.trainer_type = engine::battle::Action::TrainerType::Player,
                              .type = engine::battle::Action::Type::Attack,
                              .index = selection - 1};
                action_selector_.setAction(action);
                action_animation_.state = ActionRequestAnimation::State::Idle;
                action_animation_.is_action_requested = false;
                action_animation_.actions_prompt.clear();
                action_animation_.moves_prompt.clear();
            }
            break;

        case ActionRequestAnimation::State::Idle:
            break;
    }
}

}  // namespace pokegym::renderer
