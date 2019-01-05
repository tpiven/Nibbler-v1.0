//
// Created by kmykhailenko on 31.12.18.
//
#pragma once
#include <iostream>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include "SDL.h"
#include "SDL_image.h"
#include "AView.hpp"
#include "Logic.hpp"

class Game_Obj {
public:
    static Game_Obj* getInstance();
    void    init();
    int    handleEvent(Logic&, AView*);
    void    update(Logic&, AView*);
    void    render(AView*);
private:
    static Game_Obj *_inst;
    void    menu(AView*);
    void    clean(AView*);
    Game_Obj();
    ~Game_Obj();
    Game_Obj(Game_Obj &&) = delete;
    Game_Obj(const Game_Obj &) = delete;
    Game_Obj& operator=(const Game_Obj &) = delete;
    Game_Obj& operator=(Game_Obj&&) = delete;
};
