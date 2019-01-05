//
// Created by kmykhailenko on 02.01.19.
//
#pragma once

#include "AView.hpp"
#include <map>

class SDL_lib : public AView{
public:
    static SDL_lib & getInstance();
    void    init() override;
    int     catchHook() override;
    void    render() override;
    void    drawMap() override;
    void    drawSnake(void*, int) override;
    uint32_t getTicks() override;
    void    delay(int) override;
    void    cleanWindow() override;
private:
    static SDL_lib *_inst;
    static SDL_Renderer * renderer;
    static SDL_Window *_window;
    SDL_Event   _event;
    static SDL_Texture *_texture_map;
    SDL_Rect    _scrR;
    std::string _dir;
    std::map<int, SDL_Texture*> _snakeTexture;
    SDL_lib();
    ~SDL_lib();
    SDL_lib(const SDL_lib&) = delete;
    SDL_lib(SDL_lib&&) = delete;
    SDL_lib &operator=(const SDL_lib &) = delete;
    SDL_lib &operator=(SDL_lib&&) = delete;
};
