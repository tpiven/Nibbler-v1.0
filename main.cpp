//#include "Game_sdl.hpp"
//
//void    obj_staff(Game_sdl &obj){
//    obj.handleEvent();
//    obj.update();
//    obj.render();
//}
//
//int main(int argc, char* argv[]) {
//    int const FPS = 60;
//    int const frameDealy = 500 / FPS;
//
//    uint32_t  frameStart;
//    int frameTime;
//
//    Game_sdl obj;
//    obj.init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 1072, 0);
//    while(!obj.running()){
//
//        frameStart = SDL_GetTicks();
//        obj_staff(obj);
//        frameTime = SDL_GetTicks() - frameStart;
//        if (frameDealy > frameTime)
//            SDL_Delay(frameDealy - frameTime);
//    }
//    obj.clean();
//    return 0;
//}
//
#include <regex>
#include "Game_Obj.hpp"
#include "global.h"
int g_weight;
int g_height;
int g_lib;

int main(int ac, char *av[]){
    std::regex check("[\\s]*?\\d{3,4}[\\s]*?$");
    if (ac != 4){//TODO must change on exception
        std::cout << "usage: ???" << std::endl;
        return -1;
    }
    for (int i = 1; i < ac; ++i) {
        if (!std::regex_match(*(av + i), (i != 3) ? check : std::regex("[\\s]*?\\d{1}[\\s]*?$"))){
            std::cout << "usage: ???" << std::endl;//TODO must change on exception
            return -1;
        }
        if (i == 1) {
            g_weight = std::stoi(*(av + i));
        }
        else if (i == 2){
            g_height = std::stoi(*(av + i));
        }
        else if (i == 3){
            g_lib = std::stoi(*(av + i));
        }
    }
    Game_Obj *obj = Game_Obj::getInstance();
    obj->init();
    return 0;
}