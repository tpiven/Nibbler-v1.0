//
// Created by kmykhailenko on 23.01.19.
//

/*******************ONLY FOR SDL************************/
#include "TextureManager.hpp"

TextureManager::TextureManager() {}
TextureManager::~TextureManager() {}

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

SDL_Texture* TextureManager::LoadTexture(const char *filename) {
//    std::cout << "Filename: " << filename << std::endl;
    SDL_Surface *tmp_surface = IMG_Load(filename);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(SDL_lib::renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
    return  texture;
}
/*******************ONLY FOR SDL************************/