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
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    display = al_create_display(g_weight, g_height + HEIGHT_SCOREBOARD);
    this->event_queue = al_create_event_queue();
    this->_eventTimerQueue = al_create_event_queue();
    this->_timer = al_create_timer(0.1);
    al_register_event_source(this->event_queue, al_get_display_event_source(this->display));
    al_register_event_source(this->event_queue, al_get_keyboard_event_source());
    al_register_event_source(this->_eventTimerQueue, al_get_timer_event_source(this->_timer));
    _map = al_load_bitmap("Picture/map_1.png");
    _snakeTexture[0]= al_load_bitmap("Picture/dirt.png");
    _snakeTexture[1]= al_load_bitmap("Picture/grass_bloc_mod.png");
    _snakeTexture[2]= al_load_bitmap("Picture/dirt_1.png");
    food = al_load_bitmap("Picture/solid.png");
    arrow = al_load_bitmap("Picture/arrow_path.png");
    button1 = al_load_bitmap("Picture/button1.png");
    button2 = al_load_bitmap("Picture/button2.png");
}

int Allegra_lib::catchHook() {
    ALLEGRO_EVENT ev;
    while (!al_is_event_queue_empty(this->event_queue)) {
        bool isEvent = al_get_next_event(this->event_queue, &ev);
        if (isEvent && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            return -1;
        else if (isEvent && ev.type == ALLEGRO_EVENT_KEY_DOWN) {
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
                case ALLEGRO_KEY_D:
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
        }
    }
    return 0;
}

uint32_t Allegra_lib::getTicks() {
    return 0;

}

void Allegra_lib::delay(int time) {
}

void Allegra_lib::render() {
    al_flip_display();
}


void Allegra_lib::drawMap() {
    al_draw_bitmap(_map, WEIGHT_SCOREBOARD, HEIGHT_SCOREBOARD, 0);

    }

void Allegra_lib::drawSnake(void* rect, int b_block) {//b_block - wich texture render: tail, body, head
    t_scr _fcrR = *reinterpret_cast<t_scr*>(rect);
    al_draw_bitmap(_snakeTexture[b_block], _fcrR.x, _fcrR.y, 0);
}

void Allegra_lib::drawFood(void* rect) {
    t_scr _fcrR = *reinterpret_cast<t_scr*>(rect);
    al_draw_bitmap(food, _fcrR.x, _fcrR.y, 0);

}

void Allegra_lib::cleanWindow() {
    al_destroy_display(display);


}
void Allegra_lib::drawMenu(void* rectA, void* rectB, int b_block) {
//    al_set_target_bitmap(al_get_backbuffer(this->display));
  //   al_clear_to_color(al_map_rgb(0,0,0));

    t_scr A = *reinterpret_cast<t_scr*>(rectA);
    al_draw_bitmap(arrow, A.x, A.y, 0);
    t_scr B = *reinterpret_cast<t_scr*>(rectB);
   al_draw_bitmap(button1, B.x, B.y, 0);
   al_draw_bitmap(button2,B.x, (B.y + B.h + 10), 0);
  //  al_flip_display();
   // al_clear_to_color(al_map_rgb(0,0,0));


}

void Allegra_lib::renderClear() {

}
