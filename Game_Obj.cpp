//
// Created by kmykhailenko on 31.12.18.
//

#include "Game_Obj.hpp"
#include "Logic.hpp"
#include "Mmap.hpp"
#include <ctime>
#include <thread>
#include <chrono>
#include "SDL_lib.hpp"
#include "SFML_lib.hpp"
#include "Allegra_lib.hpp"
#include <vector>
#include "global.h"
#include <ctime>
//#include <unistd.h>
#include <unistd.h>
#include <mutex>

int const FPS = 60;
uint32_t  frameStart;
int frameTime;

Game_Obj::Game_Obj() {}

Game_Obj::~Game_Obj() {
    std::cout << "!!!" << std::endl;
    delete _inst;
}

Game_Obj* Game_Obj::_inst = nullptr;

bool Game_Obj::menu(AView* lib) {//draw menu for select map, and number of player
    _menu.initMenu();
    int const frameDealy = 3000 / FPS;
    while(_menu.runningMenu()){
        frameStart = _libs[g_lib - 1]->getTicks();
        if (handleEvent(lib) == -1){
            return false;
        }
        _menu.changebutton();
        frameTime = _libs[g_lib - 1]->getTicks() - frameStart;
        if (frameDealy > frameTime){
            _libs[g_lib - 1]->delay(frameDealy - frameTime);
        }
        render(lib);
    }
    return true;
}

Game_Obj* Game_Obj::getInstance() {
    if (!_inst){
        _inst = new Game_Obj;
    }
    return _inst;
}

void Game_Obj::init() {
    _libs = {&SDL_lib::getInstance(), &SFML_lib::getInstance()};//, SFML_lib::getInstance, ALLEGRO_lib::
    _libs[g_lib - 1]->init();//draw map, load picture
    if (!menu(_libs[g_lib - 1])){
        clean(_libs[g_lib - 1]);
        return;
    }
    _libs[g_lib - 1]->drawMap();
    _logic.init(1);
    _food.updateFood();
    render(_libs[g_lib - 1]);//pre drawning before moving
    std::cout << "g_Lib: " << g_lib << std::endl;
    main_loop();
}

void Game_Obj::main_loop() {
    int const frameDealy = 6000 / FPS;
    while(_logic.runningGame()){
        frameStart = _libs[g_lib - 1]->getTicks();
        if (!action(_libs[g_lib - 1])){
                break;
        }
        frameTime = _libs[g_lib - 1]->getTicks() - frameStart;
        if (frameDealy > frameTime){
            _libs[g_lib - 1]->delay(frameDealy - frameTime);
        }
    }
    clean(_libs[g_lib - 1]);
}

bool Game_Obj::action(AView *lib) {
    if (handleEvent(lib) == -1){
        return false;
    }
    update(lib);
    render(lib);
    if (handleEvent(lib) == -1){
        return false;
    }
    return true;
}

void Game_Obj::clean(AView * lib) {
    lib->cleanWindow();
}

int Game_Obj::handleEvent(AView* lib) {
    int symb = lib->catchHook();
    if (symb == -1) {
        return symb;
    }
    if (symb != 0) {
        (!_menu.runningMenu()) ? _logic.setKey(symb) : _menu.setKey(symb);
    }
    return symb;
}

void Game_Obj::update(AView* lib) {
    lib->drawMap();
    _logic.move();
    _food.updateFood();
}

void Game_Obj::render(AView* lib) {
    lib->render();
//    Mmap::getInstance().printMmap();
}