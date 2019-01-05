//
// Created by kmykhailenko on 31.12.18.
//

//class INibDisplay{
//public:
//    virtual void init() = 0;//инициализация Любой либы
//    virtual void getEvent() = 0;//ловим хуки от клавиш
//    virtual void updateGameDate() = 0;//обновляем дату по хукам
//    virtual void refreshDisplay() = 0;//перерисовка
//    virtual void stop() = 0;//конец игры ???
//};

#pragma once
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <iostream>

class AView {
public:
    ~AView(){}
    virtual void    init() = 0;//инит окна и прочего
    virtual int     catchHook() = 0; //ловим хуки от клавиш
    virtual void    render() = 0;//рисуем
    virtual void    drawMap() = 0;
    virtual void    drawSnake(void*, int) = 0;
    virtual uint32_t     getTicks() = 0;
    virtual void    delay(int) = 0;
    virtual void    cleanWindow() = 0;
};
