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
    void    drawMenu(void*, void*, int) override;
    void    drawMap() override;
    void    drawSnake(void*, int) override;
    void    renderClear() override;
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
    ALLEGRO_BITMAP              *arrow;
    ALLEGRO_BITMAP              *button1;
    ALLEGRO_BITMAP              *button2;
   std::map<int, ALLEGRO_BITMAP*> _snakeTexture;


    Allegra_lib();
    ~Allegra_lib();
    Allegra_lib(const Allegra_lib&) = delete;
    Allegra_lib(Allegra_lib&&) = delete;
    Allegra_lib &operator=(const Allegra_lib &) = delete;
    Allegra_lib &operator=(Allegra_lib&&) = delete;
};



//#include "Allegro.hh"
//
//Allegro::Allegro() : _display(NULL), _eventQueue(NULL), _timer(NULL), _bouncer(NULL)
//{
//
//}
//
//Allegro::~Allegro()
//{
//
//}
//
//void					Allegro::playSound() {
//
//}
//
//bool					Allegro::initDisplay(int width, int height)
//{
//    int bouncerWidthSize  = (int) (SCREEN_W / width);
//    int bouncerHeightSize = (int) (SCREEN_H / height);
//    this->_bouncerSize = (bouncerHeightSize < bouncerWidthSize) ? bouncerHeightSize : bouncerWidthSize;
//    if (!al_init())
//        return (false);
//    if (!al_init_image_addon())
//        return (false);
//    if (!al_install_keyboard())
//        return (false);
//    this->_display = al_create_display(SCREEN_W, SCREEN_H);
//    if (!this->_display)
//        return (false);
//    /* On crée une file d'évenements pour le clavier*/
//    this->_eventQueue = al_create_event_queue();
//    if (!this->_eventQueue)
//        return (false);
//    /* Puis une pour le timer */
//    this->_eventTimerQueue = al_create_event_queue();
//    if (!this->_eventTimerQueue)
//        return (false);
//    /* On crée un timer sur 0.1 seconde (Il sera mis au wait) */
//    this->_timer = al_create_timer(0.1);
//    if (!this->_timer)
//        return (false);
//    /* On enregistre les sources d'evenements clavier + fenetre */
//    al_register_event_source(this->_eventQueue, al_get_display_event_source(this->_display));
//    al_register_event_source(this->_eventQueue, al_get_keyboard_event_source());
//    /* On enregistre la source d'evenement timer */
//    al_register_event_source(this->_eventTimerQueue, al_get_timer_event_source(this->_timer));
//
//    this->_wallBouncer = this->createSprite("ressources/wall.png", 145, 145, 145);
//    this->_foodBouncer = this->createSprite("ressources/apple.png", 58, 199, 69);
//    this->_starBouncer = this->createSprite("ressources/star.png", 255, 255, 115);
//    this->_randomBouncer = this->createSprite("ressources/random.png", 145, 0, 161);
//    this->_speedUpBouncer = this->createSprite("ressources/speedup.png", 89, 239, 247);
//
//    /* TMP */
//    this->_bouncer = al_create_bitmap(40, 40);
//    if (!this->_bouncer)
//        return (false);
//    al_set_target_bitmap(this->_bouncer);
//    al_clear_to_color(al_map_rgb(6, 162, 209));
//    /* ENDTMP */
//
//    /* On clean l'écran une premiere fois */
//    al_set_target_bitmap(al_get_backbuffer(this->_display));
//    al_clear_to_color(al_map_rgb(0,0,0));
//
//    /* On démarre le timer */
//    al_start_timer(this->_timer);
//
//
//
//    return (true);
//}
//
//ALLEGRO_BITMAP			*Allegro::createSprite(const std::string &path, int r, int g, int b) {
//    ALLEGRO_BITMAP		*tmp;
//
//    tmp = al_load_bitmap(path.c_str());
//    if (tmp == NULL) {
//        tmp = al_create_bitmap(40, 40);
//        if (tmp) {
//            al_set_target_bitmap(tmp);
//            al_clear_to_color(al_map_rgb(r, g, b));
//            return (tmp);
//        } else {
//            throw new NibblerException("Cannot load Allegro Bitmap.");
//        }
//    }
//    return (tmp);
//}
//
//void					Allegro::closeDisplay()
//{
//
//}
//
//bool					Allegro::isRunning()
//{
//    return (true);
//}
//
//void					Allegro::getEvent(std::queue<Key> &events)
//{
//    ALLEGRO_EVENT 		ev;
//
//    while (!al_is_event_queue_empty(this->_eventQueue)) {
//        bool isEvent = al_get_next_event(this->_eventQueue, &ev);
//        if (isEvent && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
//            events.push(ESCAPE);
//        else if (isEvent && ev.type == ALLEGRO_EVENT_KEY_DOWN) {
//            switch(ev.keyboard.keycode) {
//                case ALLEGRO_KEY_UP:
//                    events.push(UP);
//                    break;
//
//                case ALLEGRO_KEY_DOWN:
//                    events.push(DOWN);
//                    break;
//
//                case ALLEGRO_KEY_LEFT:
//                    events.push(LEFT);
//                    break;
//
//                case ALLEGRO_KEY_RIGHT:
//                    events.push(RIGHT);
//                    break;
//
//                case ALLEGRO_KEY_ESCAPE:
//                    events.push(ESCAPE);
//                    break;
//            }
//        }
//    }
//}
//
//void					Allegro::display(Snake *snake, std::list<IItem *> obj, int score)
//{
//    std::list<IParts *> tmp = snake->getParts();
//    (void) score;
//    /* On clear le backbuffer */
//    al_set_target_bitmap(al_get_backbuffer(this->_display));
//    al_clear_to_color(al_map_rgb(0,0,0));
//
//    /* On dessine le snake */
//    for (std::list<IParts *>::iterator it = tmp.begin(); it != tmp.end(); it++)
//    {
//        al_draw_scaled_bitmap(this->_bouncer, 0, 0, 40, 40, (*it)->getX() * this->_bouncerSize, (*it)->getY() * this->_bouncerSize, this->_bouncerSize, this->_bouncerSize, 0);
//    }
//
//    /* On dessine les objets */
//    for (std::list<IItem *>::iterator it = obj.begin(); it != obj.end(); ++it)
//    {
//        ALLEGRO_BITMAP *toDisplay;
//
//        if ((*it)->getType() == WALL)
//            toDisplay = this->_wallBouncer;
//        else if ((*it)->getType() == FOOD)
//            toDisplay = this->_foodBouncer;
//        else if ((*it)->getType() == RANDOM)
//            toDisplay = this->_randomBouncer;
//        else if ((*it)->getType() == STAR)
//            toDisplay = this->_starBouncer;
//        else if ((*it)->getType() == SPEEDUP)
//            toDisplay = this->_speedUpBouncer;
//        else
//            toDisplay = this->_bouncer;
//
//        al_draw_scaled_bitmap(toDisplay, 0, 0, 40, 40, (*it)->getX() * this->_bouncerSize, (*it)->getY() * this->_bouncerSize, this->_bouncerSize, this->_bouncerSize, 0);
//    }
//
//    /* On flip entre le buffer et le backbuffer */
////    al_flip_display();
//}
//
//void					Allegro::wait(int time)
//{
//    al_set_timer_speed(this->_timer, ALLEGRO_USECS_TO_SECS(time));
//    ALLEGRO_EVENT ev;
//    al_wait_for_event(this->_eventTimerQueue, &ev);
//}
//
//extern "C"
//{
//IDisplay *make_display()
//{
//    return (new Allegro);
//}
//}


//#ifndef 				__ALLEGRO_HH__
//#define 				__ALLEGRO_HH__
//
//#include 				<iostream>
//#include 				<string>
//#include				<queue>
//#include        "NibblerException.hpp"
//#include 				"IDisplay.hh"
//#include        <allegro.h>
//#include 				<allegro_image.h>
//
//const int       SCREEN_W    = 1280.0;
//const int       SCREEN_H    = 1024.0;
//
//class 							        Allegro : public IDisplay
//{
//private:
//    ALLEGRO_DISPLAY       		*_display;
//    ALLEGRO_EVENT_QUEUE   		*_eventQueue;
//    ALLEGRO_EVENT_QUEUE   		*_eventTimerQueue;
//    ALLEGRO_TIMER         		*_timer;
//    ALLEGRO_BITMAP        		*_bouncer;
//    ALLEGRO_BITMAP				    *_wallBouncer;
//    ALLEGRO_BITMAP				    *_foodBouncer;
//    ALLEGRO_BITMAP				    *_randomBouncer;
//    ALLEGRO_BITMAP            *_starBouncer;
//    ALLEGRO_BITMAP				    *_speedUpBouncer;
//    int 							        _bouncerSize;
//
//public:
//    Allegro();
//    virtual ~Allegro();
//    virtual bool				initDisplay(int, int);
//    virtual void				closeDisplay();
//    virtual bool				isRunning();
//    virtual void				getEvent(std::queue<Key> &);
//    virtual void				display(Snake *, std::list<IItem *>, int score);
//    virtual void				wait(int);
//    virtual void        playSound();
//    ALLEGRO_BITMAP      *createSprite(const std::string &path, int r, int g, int b);
//};