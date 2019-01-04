//
// Created by kmykhailenko on 31.12.18.
//
#pragma once
#include <iostream>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include "SDL.h"
#include "SDL_image.h"

class Game_Obj {
public:
    static Game_Obj* getInstance();
    void    init();
    void    handleEvent();
    void    update();
    void    render();
private:
    static Game_Obj *_inst;
    Game_Obj();
    ~Game_Obj();
    Game_Obj(Game_Obj &&) = delete;
    Game_Obj(const Game_Obj &) = delete;
    Game_Obj& operator=(const Game_Obj &) = delete;
    Game_Obj& operator=(Game_Obj&&) = delete;
};
