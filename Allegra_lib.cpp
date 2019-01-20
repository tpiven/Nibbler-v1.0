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

ALLEGRO_DISPLAY *display = NULL;

Allegra_lib::Allegra_lib() {}
Allegra_lib::~Allegra_lib() {}
Allegra_lib& Allegra_lib::getInstance() {
    static Allegra_lib instance;
    return instance;
}

void Allegra_lib::init() {
    display = al_create_display(g_weight, g_height + HEIGHT_SCOREBOARD);
    this->_eventQueue = al_create_event_queue();
    al_register_event_source(this->_eventQueue, al_get_display_event_source(this->_display));
    al_register_event_source(this->_eventQueue, al_get_keyboard_event_source());



}

int Allegra_lib::catchHook(){
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                std::cout << "rtuut" << std::endl;
                return -1;
            case ALLEGRO_KEY_W:
                std::cout << "w" << std::endl;
                return 'w';
            case ALLEGRO_KEY_S:
                std::cout << "s" << std::endl;
                return 's';
            case sALLEGRO_KEY_D:
                std::cout << "d" << std::endl;
                return 'd';
            case ALLEGRO_KEY_A:
                std::cout << "a" << std::endl;
                return 'a';
            case ALLEGRO_KEY_SPACE:
                return ' ';
            case ALLEGRO_KEY_UP:
                return 126;
            case ALLEGRO_KEY_DOWN:
                return 125;
            case ALLEGRO_KEY_LEFT:
                return 123;
            case ALLEGRO_KEY_RIGHT:
                return 124;
            default:
                return 0;
    }


    return 0;
}

uint32_t Allegra_lib::getTicks() {
    return 0;

}

void Allegra_lib::delay(int time) {

}

void Allegra_lib::render() {

}


void Allegra_lib::drawMap() {
    }

void Allegra_lib::drawSnake(void* rect, int b_block) {//b_block - wich texture render: tail, body, head

}

void Allegra_lib::drawFood(void* rect) {

}

void Allegra_lib::cleanWindow() {




}

