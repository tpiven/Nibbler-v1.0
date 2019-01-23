//
// Created by kmykhailenko on 02.01.19.
//
#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "AView.hpp"
#include <map>
#include "TextureManager.hpp"

class SDL_lib : public AView{
public:
    static SDL_lib & getInstance();
    void    init() override;
    int     catchHook() override;
    void    render() override;
    void    drawMenu(void*, void*, int) override;
    void    drawMap() override;
    void    drawSnake(void*, int) override;
    uint32_t getTicks() override;
    void    delay(int) override;
    void    cleanWindow() override;
    void    drawFood(void*) override;
private:
    friend class TextureManager;
    static SDL_Renderer * renderer;
    static SDL_Window *_window;
    SDL_Event   _event;
    static SDL_Texture *_textureMap;
    static SDL_Texture *_textureFood;
    static SDL_Texture  *_textureArrow;
    SDL_Rect    _mcrR;//menu
    SDL_Rect    _scrR;//snake
    SDL_Rect    _fcrR;//food
    std::string _dir;
    std::map<int, SDL_Texture*> _snakeTexture;
    std::map<int, SDL_Texture*> _buttonTexture;
    SDL_lib();
    ~SDL_lib();
    SDL_lib(const SDL_lib&) = delete;
    SDL_lib(SDL_lib&&) = delete;
    SDL_lib &operator=(const SDL_lib &) = delete;
    SDL_lib &operator=(SDL_lib&&) = delete;
};
