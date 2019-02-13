////
//// Created by Tetiana PIVEN on 2019-01-19.
////
//
#pragma once


#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"

#include "../AView.hpp"
#include <map>


class Allegra_lib: public AView{
public:
    Allegra_lib();
    Allegra_lib(int, int);
    ~Allegra_lib();
    void    init() override;
    int     catchHook() override;
    void    render() override;
    void    drawMenu(void*, void*, int) override;
    void    drawMap() override;
    void    drawSnake(void*, int) override;
    void    renderClear() override;
    uint32_t getTicks() override;
    void    delay(int) override;
    void    cleanWindow() override;
    void    drawFood(void*) override;
    void    drawInterface(std::string, int) override;
    void    drawTimeBigFood(int) override;
    void    hideWindow() override;
    void    showWindow() override;

private:
    ALLEGRO_DISPLAY             *display;
    ALLEGRO_EVENT_QUEUE         *event_queue;
    ALLEGRO_BITMAP        		*_map;
    ALLEGRO_BITMAP              *food;
    ALLEGRO_BITMAP              *arrow;
    ALLEGRO_BITMAP              *button1;
    ALLEGRO_BITMAP              *button2;
   std::map<int, ALLEGRO_BITMAP*> _snakeTexture;
    int weight;
    int height;
    int height_scoreboard;
    int sizeFont;




    Allegra_lib(const Allegra_lib&) = delete;
    Allegra_lib(Allegra_lib&&) = delete;
    Allegra_lib &operator=(const Allegra_lib &) = delete;
    Allegra_lib &operator=(Allegra_lib&&) = delete;
};


