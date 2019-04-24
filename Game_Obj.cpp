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

extern int const FPS = 60;
uint32_t  frameStart;
int frameTime;
unsigned Game_Obj::_frameDelay = 4000 / FPS;

Game_Obj::Game_Obj() {}

Game_Obj::~Game_Obj() {
    void	(*destroy_gui)(AView *);
    void     (*destroy_music)(Music*);
    destroy_gui = (void (*)(AView *))dlsym(dl_lib, "destroy_object");
    destroy_gui(viev);
    if (this->dl_lib != NULL) {
        dlclose(this->dl_lib);
    }
    destroy_music = (void (*)(Music *))dlsym(dl_music, "destroy_object");
    destroy_music(music);
    if (this->dl_music != NULL) {
        dlclose(this->dl_music);
    }
}

void *Game_Obj:: dl_lib = nullptr;
void *Game_Obj:: dl_music = nullptr;
AView*  Game_Obj::viev = nullptr;
Music*  Game_Obj::music = nullptr;



bool Game_Obj::menu() {
    int const frameDealy = 4000 / FPS;
    while(_menu.runningMenu()){
        viev->renderClear();
        frameStart = viev->getTicks();
        if (handleEvent() == -1){
            return false;
        }
        if (!_menu.changebutton()){
            return false;
        }
        frameTime = viev->getTicks() - frameStart;
        if (frameDealy > frameTime && frameTime >= 0){
            viev->delay(frameDealy - frameTime);
        }
        viev->render();
    }
    return true;
}

void Game_Obj::addNewSharedLib() {

    AView*		(*getInstance)(int, int);
    void	(*destroy_gui)(AView *);

    if (this->dl_lib != NULL) {
        destroy_gui = (void (*)(AView *))dlsym(dl_lib, "destroy_object");
        destroy_gui(viev);
        dlclose(dl_lib);
        dl_lib = NULL;

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

void Game_Obj::addMusicLib() {
    Music*		(*getInstance)();

    dl_music = dlopen("../lib_Music.dylib", RTLD_LAZY);
    if (!dl_music)
        throw std::logic_error( dlerror() );


    getInstance = reinterpret_cast<Music*(*)()> (dlsym(dl_music, "getInstance"));
    if (!getInstance) {
        throw std::logic_error( dlerror()) ;
    }
    music = getInstance();
}


void Game_Obj::init() {
    library[0] = "../libSDL.dylib";
    library[1] = "../libSFML.dylib";
    library[2] = "../gl.dylib";
    addNewSharedLib();
    addMusicLib();
    music->init();
    _interface = Interface::getInstance();
    viev->init();
    _menu.initMenu();
    if (!menu()){
        viev->cleanWindow();
        return;
    }
    _interface->initInterface();
    viev->drawMap();
    _logic.init(1);
    _interface->changeTimeAndScore();
    _food.updateFood();
    viev->render();//pre drawning before moving
    main_loop();
}

void Game_Obj::main_loop() {
    music->playMusic();
    while(1){
        viev->renderClear();
        frameStart = viev->getTicks();
        if (!_logic.runningGame()){
            music->stopMusic();
            if (!escapeLogic()){
                break;
            }
        }
        else if (!action()){
                break;
        }
        frameTime = viev->getTicks() - frameStart;
        if (_frameDelay > frameTime && frameTime >= 0){
            viev->delay(_frameDelay - frameTime);
        }
    }
    viev->cleanWindow();
}

bool Game_Obj::escapeLogic() {
    int const frameDealy = 4000 / FPS;
    _menu.escapeDialog();
    _mapInit = false;

    _logic.restart();
    _food.restart();
    music->playGame_over();

    while(handleEvent() != 32 ){
        viev->renderClear();
        viev->drawGameOver(_interface->getScore());
        frameTime = viev->getTicks() - frameStart;
        if (frameDealy > frameTime && frameTime >= 0){
            viev->delay(frameDealy - frameTime);
        }
        viev->render();
    }
    if (!menu()){
        return false;
    }
    _interface->restart();
    music->playMusic();
    return true;
}

bool Game_Obj::pauseLogic() {
    _menu.pauseDialog();
    return menu();
}

bool Game_Obj::action() {
    int key = handleEvent();
    if (key == -1 || (key == ' ' && !pauseLogic())){
        return false;
    }
    update();
    viev->render();
    key = handleEvent();
    if (key == -1 || (key == ' ' && !pauseLogic())){
        return false;
    }
    return true;
}

void Game_Obj::switchLib(int symb) {
    viev->cleanWindow();
    if (symb == 2) {
        g_height *=2;
        g_weight *=2;
        HEIGHT_SCOREBOARD = g_weight / 14;
        _logic.changeSize(1);
        _food.changeSize(1);
        _menu.changeSize();

    }
    if ((symb == 1 || symb == 3) && g_lib == 2)
    {
        g_height /=2;
        g_weight /=2;
        HEIGHT_SCOREBOARD = g_weight / 14;
        _logic.changeSize(-1);
        _food.changeSize(-1);
        _menu.changeSize();
    }
    g_lib = symb;
    addNewSharedLib();
    viev->init();
    if (_mapInit == true) {
        viev->initMap(_numMap);
    }
}


int Game_Obj::handleEvent() {
    int symb = viev->catchHook();
    if (symb == -1) {
        return symb;
    }
    if ((symb == 1 || symb == 2 || symb == 3) && symb != g_lib){
          switchLib(symb);
    }
    else if (symb != 0) {
        (!_menu.runningMenu() && symb != ' ') ? _logic.setKey(symb) : _menu.setKey(symb);
    }

    return symb;
}

void Game_Obj::update() {
    viev->drawMap();
    _logic.move();
   _interface->changeTimeAndScore();
   _food.updateFood();

}
