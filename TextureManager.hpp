//
// Created by kmykhailenko on 23.01.19.
//

/*******************ONLY FOR SDL************************/

#pragma once
#include "SDL_lib.hpp"

class TextureManager {
public:
    static TextureManager & getInstance();
    SDL_Texture* LoadTexture(const char *filename);
private:
    TextureManager();
    ~TextureManager();
    TextureManager(const TextureManager &) = delete;
    TextureManager(TextureManager&&) = delete;
    TextureManager &operator=(const TextureManager&) = delete;
    TextureManager &operator=(TextureManager&&) = delete;
};
/*******************ONLY FOR SDL************************/