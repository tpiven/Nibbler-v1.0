//
// Created by kmykhailenko on 31.12.18.
//

#include "Game_Obj.hpp"
#include "Logic.hpp"
#include "Mmap.hpp"
#include "Interface.hpp"
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
#include "global.h"
#include <ctime>
#include <unistd.h>
#include <mutex>

int const FPS = 60;
uint32_t  frameStart;
int frameTime;


Game_Obj::Game_Obj() {}

Game_Obj::~Game_Obj() {
    if (this->dl_lib != NULL) {
        dlclose(this->dl_lib);

    }
    delete _inst;
}

Game_Obj* Game_Obj::_inst = nullptr;
void *Game_Obj:: dl_lib = NULL;
AView*  Game_Obj::viev = nullptr;


bool Game_Obj::menu(AView* lib) {//draw menu for select map, and number of player
    int const frameDealy = 4000 / FPS;
    while(_menu.runningMenu()){
        lib->renderClear();

        frameStart = lib->getTicks();
        if (handleEvent(lib) == -1){
            return false;
        }
        if (!_menu.changebutton()){
            return false;
        }
        frameTime = lib->getTicks() - frameStart;
        if (frameDealy > frameTime){
            lib->delay(frameDealy - frameTime);
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

void Game_Obj::addNewSharedLib() {

    AView*		(*getInstance)(int, int);
    void	(*destroy_gui)(AView *);


    if (this->dl_lib != NULL) {
        destroy_gui = (void (*)(AView *))dlsym(dl_lib, "destroy_object");
        destroy_gui(viev);
        dlclose(this->dl_lib);
        this->dl_lib = NULL;

    }
    this->dl_lib = dlopen(library[g_lib - 1].c_str(), RTLD_LAZY);
    if (!this->dl_lib)
        throw std::logic_error( dlerror() );


    getInstance = reinterpret_cast<AView*(*)(int, int)> (dlsym(this->dl_lib, "getInstance"));
    if (!getInstance) {
        throw std::logic_error( dlerror()) ;
    }
    viev = getInstance(g_weight, g_height);
}

void Game_Obj::init() {
    library[0] = "libSDL.dylib";
    library[1] = "libSFML.dylib";
    library[2] = "libAllegro.so";
   // _libs = {&SDL_lib::getInstance(), &SFML_lib::getInstance(), &Allegra_lib::getInstance()};
    addNewSharedLib();
    _interface = Interface::getInstance();
    viev->init();
    //_libs[g_lib - 1]->init();//draw map, load picture
    _menu.initMenu();
    if (!menu(viev)){
        clean(viev);
        return;
    }
    _interface->initInterface();
    //_libs[g_lib - 1]->drawMap();
    viev->drawMap();
    _logic.init(1);
    _interface->changeTimeAndScore();
    _food.updateFood();
    render(viev);//pre drawning before moving
    main_loop();
}

void Game_Obj::main_loop() {
    int const frameDealy = 6000 / FPS;
    while(1){
        viev->renderClear();
        frameStart = viev->getTicks();
        if (!_logic.runningGame()){
            if (!escapeLogic()){
                break;
            }
        }
        else if (!action(viev)){
                break;
        }

        frameTime = viev->getTicks() - frameStart;
        if (frameDealy > frameTime && frameTime >= 0){
            viev->delay(frameDealy - frameTime);
        }

    }
    clean(viev);
}

bool Game_Obj::escapeLogic() {
    _menu.escapeDialog();
    if (!menu(viev)){
        return false;
    }
    _logic.restart();
    _food.restart();
    _interface->restart();
    return true;
}

bool Game_Obj::pauseLogic() {
    _menu.pauseDialog();
    return menu(viev);
}

bool Game_Obj::action(AView *lib) {
    int key = handleEvent(lib);
    if (key == -1 || (key == ' ' && !pauseLogic())){
        return false;
    }
    update(lib);
    render(lib);
    key = handleEvent(lib);
    if (key == -1 || (key == ' ' && !pauseLogic())){
        return false;
    }
    return true;
}

void Game_Obj::clean(AView * lib) {
    lib->cleanWindow();
}

void Game_Obj::switchLib(int symb, AView*& lib) {
//    std::cout << "G_HEIGHT: " << g_height << std::endl;
//    std::cout << "G_WEIGHT: " << g_weight << std::endl;
//    std::cout << "HEIGHT_BOARD: " << HEIGHT_SCOREBOARD << std::endl;
    viev->hideWindow();
//    if (symb == 2 && g_lib == 1) {
//        g_height *=2;
//        g_weight *=2;
//        HEIGHT_SCOREBOARD = g_weight / 14;
//
//    }
//    if (g_lib == 2 && symb == 1)
//    {
//        g_height /=2;
//        g_weight /=2;
//        HEIGHT_SCOREBOARD = g_weight / 14;
//
//    }
    g_lib = symb;
    addNewSharedLib();
    viev->showWindow();
    //render(viev);
//    std::cout << "-------------------" << std::endl;
//    std::cout << "G_HEIGHT: " << g_height << std::endl;
//    std::cout << "G_WEIGHT: " << g_weight << std::endl;
//    std::cout << "HEIGHT_BOARD: " << HEIGHT_SCOREBOARD << std::endl;

    lib = viev;
}


int Game_Obj::handleEvent(AView*& lib) {
    int symb = lib->catchHook();
    if (symb == -1) {
        return symb;
    }
    if ((symb == 1 || symb == 2 || symb == 3) && symb != g_lib){
        if (g_lib == 2){
            int a = 10;
        }
        switchLib(symb, lib);
    }
    else if (symb != 0) {
        (!_menu.runningMenu() && symb != ' ') ? _logic.setKey(symb) : _menu.setKey(symb);
    }

    return symb;
}

void Game_Obj::update(AView* lib) {

    lib->drawMap();
    _logic.move();
   _interface->changeTimeAndScore();
   _food.updateFood();

}

void Game_Obj::render(AView* lib) {
    lib->render();
}