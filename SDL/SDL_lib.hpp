//
// Created by kmykhailenko on 02.01.19.
//
#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "../AView.hpp"
#include <map>
#include "TextureManager.hpp"

class SDL_lib : public AView{
public:
    SDL_lib();
    SDL_lib(int weight, int height);
    virtual ~SDL_lib();
    void    init() override;
    int     catchHook() override;
    void    render() override;
    void    drawMenu(void*, void*, int) override;
    void    drawMap() override;
    void    drawSnake(void*, int) override;
    void    renderClear() override;
    uint32_t getTicks() override;
    void    delay(int) override;
    void    cleanWindow() override;
    void    drawFood(void*) override;
    void    drawInterface(std::string, int) override;
    void    drawTimeBigFood(int) override;
    void    hideWindow() override;
    void    showWindow() override;
private:
    friend class TextureManager;
    static SDL_Renderer * renderer;
    static SDL_Window *_window;
    SDL_Event   _event;
    static SDL_Texture *_textureMap;
    static SDL_Texture *_textureFood;
    static SDL_Texture  *_textureArrow;

    static SDL_Texture  *_textureText;
    static TTF_Font     *_font;
    SDL_Color           _textColor;
    SDL_Rect    _mcrR;//menu
    SDL_Rect    _scrR;//snake
    SDL_Rect    _fcrR;//food
    SDL_Rect    _tcrR;//text
    bool        _isInit;
    int g_weight;
    int g_height;
    int HEIGHT_SCOREBOARD;
    int SizeFont;

    std::string _dir;
    std::map<int, SDL_Texture*> _snakeTexture;
    std::map<std::string, SDL_Texture*> _buttonTexture;

    SDL_lib(const SDL_lib&) = delete;
    SDL_lib(SDL_lib&&) = delete;
    SDL_lib &operator=(const SDL_lib &) = delete;
    SDL_lib &operator=(SDL_lib&&) = delete;
};
