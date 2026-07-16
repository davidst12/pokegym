#include "BattleRenderer/sdl/TextureManager.hpp"

TextureManager::TextureManager(SDL_Renderer* r) : renderer(r) {}

SDL_Texture* TextureManager::getTexture(const std::string& pokemon_name, bool is_opponent) {
    if (active_textures.find(pokemon_name) != active_textures.end()) {
        return active_textures[pokemon_name];
    }

    std::string side = is_opponent ? "front" : "back";
    std::string path = "assets/pokemon/images/" + pokemon_name + "/" + side + ".png";
    // SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());

    SDL_Surface* player_pokemon_surface = IMG_Load(path.c_str());
    if (!player_pokemon_surface)
        return nullptr;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, player_pokemon_surface);

    SDL_FreeSurface(player_pokemon_surface);

    if (texture) {
        active_textures[pokemon_name] = texture;
    }
    return texture;
}

void TextureManager::clearUnusedTextures() {
    for (auto& [id, texture] : active_textures) {
        SDL_DestroyTexture(texture);
    }
    active_textures.clear();
}