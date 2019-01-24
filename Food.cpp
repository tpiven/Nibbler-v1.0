//
// Created by Kostiantyn MYKHAILENKO on 1/6/19.
//

#include "Food.hpp"
#include "global.h"
#include "Mmap.hpp"
#include "SDL_lib.hpp"
#include "SFML_lib.hpp"
#include <random>
#define GET_VALUE_FROM_MAP(y,x) Mmap::getInstance().getValueFromMap(y, x)
#define SET_VALUE_IN_MAP(v,y,x) Mmap::getInstance().setValueInMap(v,y,x)

static int cntCreateFood = 0;

Food::Food() noexcept {
    _size_block = (g_weight / 90) / 2;
    _rectLil.w = _rectLil.h = _size_block;
    _rectBig.w = _rectBig.h = _size_block * 2;
    _coorLilFood.x_arr = _coorLilFood.y_arr = _coorLilFood.y_dis = _coorLilFood.x_dis = 0;
    _coorBigFood.x_arr = _coorBigFood.y_arr = _coorBigFood.y_dis = _coorBigFood.x_dis = 0;
    _drawBig = false;
}

Food::~Food() {
}

void Food::mandatoryFood() {
    if (GET_VALUE_FROM_MAP(_coorLilFood.y_arr, _coorLilFood.x_arr) != -2){//-2 on array is food
        cntCreateFood++;
        int x = 0;
        int y = 0;
        std::random_device rd;
        std::mt19937 gen(rd());
        do{
            std::uniform_int_distribution<> dis_x(0, 89);
            std::uniform_int_distribution<> dis_y(0, 66);
            x = dis_x(gen);
            y = dis_y(gen);
        }while(GET_VALUE_FROM_MAP(y, x) != 0);
        SET_VALUE_IN_MAP(-2, y, x);
        _coorLilFood.y_arr = y;
        _coorLilFood.x_arr = x;
        _rectLil.y = _coorLilFood.y_dis = (y * g_height / 67) + HEIGHT_SCOREBOARD + _size_block/2;
        _rectLil.x = _coorLilFood.x_dis = (x * g_weight / 90) + _size_block/2;
    }
    switch (g_lib){
        case 1:
            SDL_lib::getInstance().drawFood(&_rectLil);
            break;
        case 2:
            SFML_lib::getInstance().drawFood(&_rectLil);
               break;
        case 3:
            //TODO call allegro.draw();
            break;
        default:
            break;
    }
}

void Food::surpriseFood() {
    if (GET_VALUE_FROM_MAP(_coorBigFood.y_arr, _coorBigFood.x_arr) != -2) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> createFood(0, 1);
        if (cntCreateFood && !(cntCreateFood % 5) && createFood(gen)) {//if true, create New Big Food
            cntCreateFood = 0;
            int x = 0;
            int y = 0;
            _drawBig = true;
            do {
                std::uniform_int_distribution<> dis_x(0, 89);
                std::uniform_int_distribution<> dis_y(0, 66);
                x = dis_x(gen);
                y = dis_y(gen);
            } while (GET_VALUE_FROM_MAP(y, x) != 0);
            SET_VALUE_IN_MAP(-2, _coorBigFood.y_arr, _coorBigFood.x_arr);
            _coorBigFood.y_arr = y;
            _coorBigFood.x_arr = x;
            _rectBig.y = _coorBigFood.y_dis = (_coorBigFood.y_arr * g_height / 67) + HEIGHT_SCOREBOARD + _size_block;
            _rectBig.x = _coorBigFood.x_dis = (_coorBigFood.x_arr * g_weight / 90) + _size_block;
        }
        if (_drawBig){
            switch (g_lib){
                case 1:
                    SDL_lib::getInstance().drawFood(&_rectBig);
                    break;
                case 2:
                    SFML_lib::getInstance().drawFood(&_rectBig);
                    break;
                case 3:
                    //TODO call allegro.draw();
                    break;
                default:
                    break;
            }
        }
    }
}


void Food::updateFood() {
    mandatoryFood();
    surpriseFood();
}

void Food::restart() {
    SET_VALUE_IN_MAP(0, _coorLilFood.y_arr, _coorLilFood.x_arr);
    SET_VALUE_IN_MAP(0, _coorBigFood.y_arr, _coorBigFood.x_arr);
    cntCreateFood = 0;
}