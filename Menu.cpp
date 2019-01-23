//
// Created by Kostiantyn MYKHAILENKO on 2019-01-19.
//

#include "Menu.hpp"
#include "global.h"
#include "SDL_lib.hpp"

Menu::Menu() noexcept {
    _size_block = g_weight / 90 + 20;//50 is scale for arrow
    _rectA.w = _rectA.h = _size_block;//rect for Arrow

    /**********RECT FOR BUTTON********/
    _rectB.h = _size_block;
    _rectB.w = _size_block * 4;

    _numButton = 1;//number of button
    _typeMenu = 1;//flag for 1 is Start_menu, 2 is Escape_Menu, 3 is Pause_menu
    _select = true;//flag for select menu
}

void Menu::initMenu() {
    _rectA.x = g_weight / 2 - (_size_block * 4) - 10;// position of arrow x
    _rectA.y = g_height / 2 - (_size_block * 3) - 10;// position of arrow y

    _rectB.x = g_weight / 2 - (_size_block * 2) - 10;
    _rectB.y = _rectA.y; //button must be on the same level with arrow
    _numButton = 1;
    switch (g_lib){
        case 1:
            SDL_lib::getInstance().drawMenu(&_rectA, &_rectB, _typeMenu);
            SDL_lib::getInstance().render();
            break;
        case 2:
            //TODO call sfml.draw();
            break;
        case 3:
            //TODO call allegro.draw();
            break;
        default:
            break;
    }
}

bool Menu::changebutton() {
    if (_key == 36){//enter, which mean that player chosed number of players
        _key = 0;
        _select = false;
        if ((_typeMenu == 3 && _numButton == 3) || (_typeMenu != 3 && _numButton == 4)){
            return false;
        }
        return true;
    }
    moveArrow();
    switch (g_lib){
        case 1:
            SDL_lib::getInstance().drawMenu(&_rectA, &_rectB, _typeMenu);
            break;
        case 2:
            //TODO call sfml.draw();
            break;
        case 3:
            //TODO call allegro.draw();
            break;
        default:
            break;
    }
    _key = 0;
    return true;
}

void Menu::moveArrow() {
    if (_key == 125 && _numButton != 4){//125 down
        _rectA.y += (_typeMenu == 3 && _numButton == 3) ? 0 :  _rectA.h + 10;
        _numButton += (_typeMenu == 3 && _numButton == 3) ? 0 : 1;
    }
    else if (_key == 126 && _numButton != 1){//126 up
        _rectA.y -=  _rectA.h + 10;
        _numButton--;
    }
}

void Menu::escapeDialog() { _select = true;}
void Menu::pauseDialog() { _select = true;}

bool Menu::runningMenu() const { return _select;}
void Menu::setKey(int key) {_key = key;}

Menu::~Menu() {}