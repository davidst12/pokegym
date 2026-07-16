#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <string>
#include <unordered_map>

class TextureManager {
   private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> active_textures;

   public:
    TextureManager(SDL_Renderer* r);

    SDL_Texture* getTexture(const std::string& pokemon_name, bool is_opponent);
    void clearUnusedTextures();
};