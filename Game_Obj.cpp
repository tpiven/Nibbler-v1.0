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
#include <vector>
#include "global.h"
#include <ctime>
#include <unistd.h>

Game_Obj::Game_Obj() {}

Game_Obj::~Game_Obj() {
    std::cout << "!!!" << std::endl;
    delete _inst;
}

Game_Obj* Game_Obj::_inst = nullptr;

void Game_Obj::menu(AView* lib_ptr) {//draw menu for select map, and number of player
    //TODO create the main menu, think about design
    //lib_ptr->drawMenu();
    //lib_ptr->render();
}

Game_Obj* Game_Obj::getInstance() {
    if (!_inst){
        _inst = new Game_Obj;
    }
    return _inst;
}

clock_t current_ticks, delta_ticks;
clock_t fps = 0;
//while(true)// your main loop. could also be the idle() function in glut or whatever
//{
//    current_ticks = clock();
//
//    render();
//
//    delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
//    if(delta_ticks > 0)
//        fps = CLOCKS_PER_SEC / delta_ticks;
//    cout << fps << endl;
//}


void Game_Obj::init() {
    int const FPS = 60;
    int const frameDealy = 1000 / FPS;
    uint32_t  frameStart;
    int frameTime;


    std::vector<AView*> lib_ptr = {&SDL_lib::getInstance()};//, SFML_lib::getInstance, ALLEGRO_lib::
    menu(lib_ptr[g_lib - 1]);
    lib_ptr[g_lib - 1]->init();//draw map, load picture
    Logic logic(1);
    render(lib_ptr[g_lib - 1]);
    while(logic.running()){
        //frameStart = SDL_GetTicks();

        if (handleEvent(logic, lib_ptr[g_lib - 1]) == -1){
            break;
        }
        update(logic, lib_ptr[g_lib - 1]);
        render(lib_ptr[g_lib - 1]);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    clean(lib_ptr[g_lib]);
}

void Game_Obj::clean(AView * lib) {
    lib->cleanWindow();
}

int Game_Obj::handleEvent(Logic& logic, AView* lib) {
    int symb = lib->catchHook();
    if (symb == -1)
        return symb;
    if (symb != 0) {
        logic.setKey(symb);
    }
    return symb;
}
void Game_Obj::update(Logic& logic, AView* lib) {
    lib->drawMap();
    logic.move();
}
void Game_Obj::render(AView* lib) {
    lib->render();
}