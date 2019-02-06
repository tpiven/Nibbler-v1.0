//
// Created by Tetiana PIVEN on 2019-01-19.
//

#define ALLEGRO_STATICLINK

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
ALLEGRO_EVENT_QUEUE *Allegra_lib::event_queue = NULL;

Allegra_lib::Allegra_lib() {}
Allegra_lib::~Allegra_lib() {}
Allegra_lib& Allegra_lib::getInstance() {
    static Allegra_lib instance;
    return instance;
}

void Allegra_lib::init() {
    g_weight *= 2;
    g_height *= 2;
    HEIGHT_SCOREBOARD = g_weight / 14;
    SizeFont = HEIGHT_SCOREBOARD / 4;
    al_init();
    al_init_image_addon();
    display = al_create_display(g_weight, g_height + HEIGHT_SCOREBOARD);
    al_install_keyboard();
    this->event_queue = al_create_event_queue();
    al_register_event_source(this->event_queue, al_get_display_event_source(this->display));
    al_register_event_source(this->event_queue, al_get_keyboard_event_source());
    _map = al_load_bitmap("Picture/map_1.png");
    _snakeTexture[0]= al_load_bitmap("Picture/dirt.png");
    _snakeTexture[1]= al_load_bitmap("Picture/grass_bloc_mod.png");
    _snakeTexture[2]= al_load_bitmap("Picture/dirt_1.png");
    food = al_load_bitmap("Picture/solid.png");
    arrow = al_load_bitmap("Picture/arrow_path.png");
    button1 = al_load_bitmap("Picture/button1.png");
    button2 = al_load_bitmap("Picture/button2.png");
    _isInit = true;
}

int Allegra_lib::catchHook() {
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    if ( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return -1;
    if ( ev.type == ALLEGRO_EVENT_KEY_DOWN)
   {
       switch (ev.keyboard.keycode) {
           case ALLEGRO_KEY_ESCAPE:
               return -1;
           case ALLEGRO_KEY_W:
                return 'w';
           case ALLEGRO_KEY_S:
                return 's';
           case ALLEGRO_KEY_D:
                return 'd';
           case ALLEGRO_KEY_A:
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
    }
    return 0;
}

uint32_t Allegra_lib::getTicks() {
       return (u_int32_t)al_get_time() * 1000;

}

void Allegra_lib::delay(int time) {
    al_rest(double(time / 100));
}

void Allegra_lib::render() {
    al_flip_display();
}

void Allegra_lib::drawMenu(void* rectA, void* rectB, int typeMenu) {

void Allegra_lib::drawMap() {
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(_map, WEIGHT_SCOREBOARD, HEIGHT_SCOREBOARD, 0);

    }

void Allegra_lib::drawSnake(void* rect, int b_block) {//b_block - wich texture render: tail, body, head
    t_scr _fcrR = *reinterpret_cast<t_scr*>(rect);
    al_draw_bitmap(_snakeTexture[b_block], _fcrR.x, _fcrR.y, 0);
}

void Allegra_lib::drawFood(void* rect) {
    t_scr _fcrR = *reinterpret_cast<t_scr*>(rect);
    al_draw_bitmap(food, _fcrR.x, _fcrR.y, 0);


void Allegra_lib::drawMap() {


}
void Allegra_lib::drawMenu(void* rectA, void* rectB, int b_block) {
    t_scr A = *reinterpret_cast<t_scr*>(rectA);
    al_draw_bitmap(arrow, A.x, A.y, 0);
    t_scr B = *reinterpret_cast<t_scr*>(rectB);
    al_draw_bitmap(button1, B.x, B.y, 0);
    al_draw_bitmap(button2,B.x, (B.y + B.h + 10), 0);
}

void Allegra_lib::drawFood(void* rect) {

}

void Allegra_lib::drawInterface(std::string clock, int score) {

}

void Allegra_lib::hideWindow() {}
void Allegra_lib::showWindow() {}

}

void Allegra_lib::renderClear() {
    al_clear_to_color(al_map_rgb(0,0,0));

}
void Allegra_lib::cleanWindow() {

}
