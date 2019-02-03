//
// Created by Tetiana PIVEN on 2019-01-19.
//


#include "Allegra_lib.hpp"
#include "global.h"
#include <unistd.h>
#include "Mmap.hpp"
#include "header.h"

//const char tail_path[] = "/Picture/dirt.png";//TODO create many picture like: tail_16x16, tail_8x8
//const char body_path[] = "/Picture/grass_bloc_mod.png";
//const char head_path[] = "/Picture/dirt_1.png";
//const char map_1[] = "/Picture/map_1.png";
//const char lilFood[] = "/Picture/solid.png";

//ALLEGRO_DISPLAY *Allegra_lib::display = NULL;
//ALLEGRO_BITMAP *ALLEgra_map = NULL;
//ALLEGRO_BITMAP *button1 = NULL;
//ALLEGRO_BITMAP *button2 = NULL;
//ALLEGRO_BITMAP *arrow = NULL;
//ALLEGRO_EVENT_QUEUE *Allegra_lib::event_queue = NULL;

Allegra_lib::Allegra_lib() {}
Allegra_lib::~Allegra_lib() {}
Allegra_lib& Allegra_lib::getInstance() {
    static Allegra_lib instance;
    return instance;
}


void Allegra_lib::init() {
    if(!al_init()) {
        std::cout << "al_init" << std::endl;
        exit (1);
    }
    display = al_create_display(g_weight, g_height + HEIGHT_SCOREBOARD);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_rest(10.0);
    al_destroy_display(display);
}

int Allegra_lib::catchHook(){

    return 0;
}

uint32_t Allegra_lib::getTicks() {

}

void Allegra_lib::delay(int time) {
}

void Allegra_lib::render() {
}

void Allegra_lib::drawMenu(void* rectA, void* rectB, int typeMenu) {

    if (typeMenu == 3) {

    }

    else {

    }
}



void Allegra_lib::drawMap() {


}

void Allegra_lib::drawSnake(void* rect, int b_block) {//b_block - wich texture render: tail, body, head

}

void Allegra_lib::drawFood(void* rect) {

}

void Allegra_lib::drawInterface(std::string clock, int score) {

}

void Allegra_lib::drawTimeBigFood(int time) {

}

void Allegra_lib::renderClear() {

}
void Allegra_lib::cleanWindow() {

}
