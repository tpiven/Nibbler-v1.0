////
//// Created by Tetiana PIVEN on 2019-01-19.
////
//
#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

#include "AView.hpp"
#include <map>


class Allegra_lib: public AView{
public:
    static Allegra_lib & getInstance();
    void    init() override;
    int     catchHook() override;
    void    render() override;
    void    drawMap() override;
    void    drawSnake(void*, int) override;
    uint32_t getTicks() override;
    void    delay(int) override;
    void    cleanWindow() override;
    void    drawFood(void*) override;
private:
    ALLEGRO_DISPLAY             *display;
    ALLEGRO_EVENT_QUEUE         *event_queue;
    ALLEGRO_EVENT_QUEUE   		*_eventTimerQueue;
    ALLEGRO_TIMER         		*_timer;
    ALLEGRO_BITMAP        		*_map;
    ALLEGRO_BITMAP              *food;
    std::map<int, ALLEGRO_BITMAP*> _snakeTexture;


    Allegra_lib();
    ~Allegra_lib();
    Allegra_lib(const Allegra_lib&) = delete;
    Allegra_lib(Allegra_lib&&) = delete;
    Allegra_lib &operator=(const Allegra_lib &) = delete;
    Allegra_lib &operator=(Allegra_lib&&) = delete;
};

