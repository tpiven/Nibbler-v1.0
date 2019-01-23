//
// Created by Таня on 15.01.2019.
//

#include "SFML_lib.hpp"
#include "global.h"
#include <unistd.h>
#include "Mmap.hpp"
#include "header.h"

//const char tail_path[] = "/Picture/dirt.png";//TODO create many picture like: tail_16x16, tail_8x8
////const char body_path[] = "/Picture/grass_bloc_mod.png";
////const char head_path[] = "/Picture/dirt_1.png";
////const char map_1[] = "/Picture/map_1.png";
////const char lilFood[] = "/Picture/solid.png";

//SDL_lib* SDL_lib::_inst = nullptr;
//SDL_Renderer* SDL_lib::renderer = nullptr;
//SDL_Window*     SDL_lib::_window = nullptr;
//SDL_Texture*    SDL_lib::_textureMap = nullptr;
//SDL_Texture*    SDL_lib::_textureFood = nullptr;

sf::RenderWindow* SFML_lib::_window =nullptr;

SFML_lib::SFML_lib() {}
SFML_lib::~SFML_lib() {}
SFML_lib& SFML_lib::getInstance() {
    static SFML_lib instance;
    return instance;
}

void SFML_lib::init() {
    _window = new sf::RenderWindow(sf::VideoMode(g_weight, g_height + HEIGHT_SCOREBOARD, 32), "Nibbler");
    //_window->clear();
    _textureMap.loadFromFile("Picture/map_1.png");
    _snakeTexture[0].loadFromFile("Picture/dirt.png");
    _snakeTexture[1].loadFromFile("Picture/grass_bloc_mod.png");
    _snakeTexture[2].loadFromFile("Picture/dirt_1.png");
    _textureFood.loadFromFile("Picture/small_food.png");

}

int SFML_lib::catchHook(){
    while(_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            std::cout << "EXIT" << std::endl;
            return -1;
        }
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Escape:
                    std::cout << "rtuut" << std::endl;
                    return -1;
                case sf::Keyboard::W:
                    std::cout << "w" << std::endl;
                    return 'w';
                case sf::Keyboard::S:
                    std::cout << "s" << std::endl;
                    return 's';
                case sf::Keyboard::D:
                    std::cout << "d" << std::endl;
                    return 'd';
                case sf::Keyboard::A:
                    std::cout << "a" << std::endl;
                    return 'a';
                case sf::Keyboard::Space:
                    return ' ';
                case sf::Keyboard::Up:
                    return 126;
                case sf::Keyboard::Down:
                    return 125;
                case sf::Keyboard::Left:
                    return 123;
                case sf::Keyboard::Right:
                    return 124;
                default:
                    return 0;
            }
        }
    }
    return 0;
}

uint32_t SFML_lib::getTicks() {
    sf::Time time = _clock.getElapsedTime();
    return static_cast<uint32_t>(time.asMilliseconds());
}

void SFML_lib::delay(int time) {
    sf:: sleep(sf::milliseconds(time));
}

void SFML_lib::render() {
    _window->display();
    //_window->clear();
}

void SFML_lib::drawMenu(void *, void *, int) {

}

void SFML_lib::drawMap() {
    _window->pollEvent(_event);
    _window->clear();
    sf::Sprite map;
    map.setTexture(_textureMap);
    map.setPosition(WEIGHT_SCOREBOARD, HEIGHT_SCOREBOARD);
    auto size = map.getTexture()->getSize();
    map.setScale(float(g_weight)/size.x, float(g_weight)/size.y);
    _window->draw(map);

}

void SFML_lib::drawSnake(void* rect, int b_block) {//b_block - wich texture render: tail, body, head
    sf::Sprite snake;
    t_scr _fcrR = *reinterpret_cast<t_scr*>(rect);
    snake.setTexture(_snakeTexture[b_block]);
    auto size = snake.getTexture()->getSize();
    snake.setScale(float(_fcrR.w)/size.x, float(_fcrR.h)/size.y);
    snake.setPosition(_fcrR.x, _fcrR.y);
    _window->draw(snake);
 }

void SFML_lib::drawFood(void* rect) {
    sf::Sprite food;
    t_scr _fcrR = *reinterpret_cast<t_scr*>(rect);
    food.setTexture(_textureFood);
    auto size = food.getTexture()->getSize();
    food.scale(float(_fcrR.w)/size.x, float(_fcrR.h)/size.y);
    food.setPosition(_fcrR.x, _fcrR.y);
    _window->draw(food);
}

void SFML_lib::renderClear() {

}

void SFML_lib::cleanWindow() {
    _window->clear();
    _window->close();

}


