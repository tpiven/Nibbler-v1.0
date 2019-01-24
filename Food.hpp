//
// Created by Kostiantyn MYKHAILENKO on 1/6/19.
//

#pragma once

#include "header.h"

class Food {
public:
    explicit Food() noexcept;
    Food(const Food &) = delete;
    Food(Food &&) = delete;
    Food &operator=(const Food&) = delete;
    Food &operator=(Food&&) = delete;
    ~Food();
    void    updateFood();
    void    restart();
private:
    void    mandatoryFood();
    void    surpriseFood();
    t_scr _rectLil;//struct for render texture smallFood
    t_scr _rectBig;//struct for render texture bigFood
    t_coor _coorLilFood;
    t_coor _coorBigFood;
    int _size_block;
//    int _cntCreateFood;
    bool _drawBig;
};

