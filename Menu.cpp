//
// Created by Kostiantyn MYKHAILENKO on 2019-01-19.
//

#include "Menu.hpp"
#include "global.h"

Menu::Menu() noexcept {
    _size_block = g_height / 2;
    _rect.w = _rect.h = _size_block;
    _numButton = 1;
    _select = true;
}

void Menu::changebutton() {
    if (_key == 36){//enter, which mean that player chosed number of players
        _select = false;
        return;
    }

}

bool Menu::runningMenu() const { return _select;}
void Menu::setKey(int key) {_key = key;}

Menu::~Menu() {}