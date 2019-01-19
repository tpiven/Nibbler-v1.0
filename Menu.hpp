//
// Created by Kostiantyn MYKHAILENKO on 2019-01-19.
//

#pragma once

#include "header.h"

class Menu {
public:
    Menu() noexcept;
    ~Menu();
//    void    initMenu();
    void    setKey(int key);
    bool    runningMenu() const;
    void    changebutton();
private:
    int _numButton;
    char _key;//w,a,s,d
    int _size_block;
    t_scr _rect;//struct for render texture
    bool _select;//flag for select menu
};

