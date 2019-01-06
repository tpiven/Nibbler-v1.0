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
private:
    void    mandatoryFood();
    void    surpriseFood();
    t_scr _rectLil;//struct for render texture
    t_coor _coors;
    int _size_block;
};

