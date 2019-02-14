#include <regex>
#include "Game_Obj.hpp"
#include "global.h"


int g_weight;
int g_height;
int g_lib;
int HEIGHT_SCOREBOARD;
int SizeFont;


int size(int n, int g){
    if (g == 1) {
        if (n % 90 == 0)
            return n;
        else
            return (90 *(n / 90));
    }
    else if (g == 2) {
        return (67 * (g_weight / 90));
    }
    return 0;
}

int main(int argc, char **argv){
    std::regex check("[\\s]*?\\d{3,4}[\\s]*?$");
    if (argc != 4){//TODO must change on exception
        std::cout << "usage: ???" << std::endl;
        return -1;
    }
    for (int i = 1; i < argc; ++i) {
        if (!std::regex_match(*(argv + i), (i != 3) ? check : std::regex("[\\s]*?\\d{1}[\\s]*?$"))){
            std::cout << "usage: ???" << std::endl;//TODO must change on exception
            return -1;
        }
        if (i == 1) {
            g_weight = size(std::stoi(*(argv + i)), 1);
            if (g_weight > 1620 || g_weight < 720) {
                std::cout << "Not valued weight" << std::endl;
                return -1;
            }
        }
        else if (i == 2){
            g_height = size(std::stoi(*(argv + i)), 2);
            if (g_height > 1206 || g_height < 536) {
                std::cout << "Not valued height" << std::endl;
                return -1;
            }
        }
        else if (i == 3){
            g_lib = std::stoi(*(argv + i));
            if (g_lib > 3) {
                {
                    std::cout << "Not valued number of libraries" << std::endl;
                    return -1;
                }
            }
        }
    }
//    if (g_lib == 2){
//        g_weight *= 2;
//        g_height *= 2;
//    }
    HEIGHT_SCOREBOARD = g_weight / 14;
    //SizeFont = HEIGHT_SCOREBOARD / 4;
    Game_Obj *obj = Game_Obj::getInstance();
    obj->init();
    return 0;
}