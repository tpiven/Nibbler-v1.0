//
// Created by Tetiana PIVEN on 2019-01-27.
//

#include "Interface.hpp"
#include "global.h"
#include "header.h"
#include <iostream>
//#include "SDL_lib.hpp"
//#include "SFML_lib.hpp"
//#include "Allegra_lib.hpp"

Interface:: Interface() {
    score = 0;
    time = 0;
}

Interface:: ~Interface() {
    delete _inst;
}

Interface *Interface::_inst  = nullptr;

Interface * Interface::getInstance() {
    if (!_inst){
        _inst = new Interface;
    }
    return _inst;
}


void Interface::setScore(int plus) {
    score = score + plus;
}

void Interface:: initInterface() {
    start = std::chrono::system_clock::now();
}

void Interface::changeTimeAndScore() {
    auto t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
    time = static_cast<int>(t.count() / 1000);
    std::string clock;
    int minutes = time/60;
    int seconds = time - minutes * 60;
    if (minutes == 0) {
        clock = "00:";
    }
    else if (minutes < 10) {
        clock = "0" + std::to_string(minutes) + ":";
    }
    else {
        clock = std::to_string(minutes) + ":";
    }
    if (seconds == 0){
        clock = clock + "00";
    }
    else if (seconds < 10) {
        clock = clock + "0" + std::to_string(seconds);
    }
    else {
        clock = clock + std::to_string(seconds);
    }
//    switch (g_lib){
//        case 1:
//            SDL_lib::getInstance().drawInterface(clock, score);
//            break;
//        case 2:
//            SFML_lib::getInstance().drawInterface(clock, score);
//            break;
//        case 3:
//            Allegra_lib::getInstance().drawInterface(clock, score);
//            break;
//        default:
//            break;
//    }
}

void Interface::restart() {
    time = 0;
    score = 0;
    start = std::chrono::system_clock::now();
}


