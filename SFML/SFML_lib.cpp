//
// Created by Таня on 15.01.2019.
//

#include "SFML_lib.hpp"
#include "../global.h"
#include <unistd.h>
#include "../Mmap.hpp"
#include "../header.h"

//const char tail_path[] = "/Picture/dirt.png";//TODO create many picture like: tail_16x16, tail_8x8
//const char body_path[] = "/Picture/grass_bloc_mod.png";
//const char head_path[] = "/Picture/dirt_1.png";
//const char map_1[] = "/Picture/map_1.png";
//const char lilFood[] = "/Picture/solid.png";


sf::RenderWindow* SFML_lib::_window = nullptr;

SFML_lib::SFML_lib() {

}

SFML_lib::SFML_lib(int g_weight, int g_height) {
    weight = g_weight;
    height = g_height;
    height_scoreboard = g_weight / 14;
    sizeFont = height_scoreboard / 4;

}

SFML_lib::~SFML_lib() {}

void SFML_lib::init() {
    _window = new sf::RenderWindow(sf::VideoMode(weight, height + height_scoreboard, 32), "Nibbler");
     _textureMap.loadFromFile("Picture/map_1.png");
    _snakeTexture[0].loadFromFile("Picture/dirt_1.png");
    _snakeTexture[1].loadFromFile("Picture/grass_bloc_mod.png");
    _snakeTexture[2].loadFromFile("Picture/dirt_1.png");
    _textureFood.loadFromFile("Picture/solid.png");
    _textureArrow.loadFromFile("Picture/arrow_path.png");
    _buttonTexture[0].loadFromFile("Picture/button1.png");
    _buttonTexture[1].loadFromFile("Picture/button2.png");
    _buttonTexture[2].loadFromFile("Picture/options.png");
    _buttonTexture[3].loadFromFile("Picture/continue.png");
    _buttonTexture[4].loadFromFile("Picture/exit.png");
    _gameOver.loadFromFile("Picture/gameOver.png");
    GameOver.setTexture(_gameOver);
    font.loadFromFile("Picture/ArialItalic.ttf");
    text.setFont(font);
    text.setCharacterSize(sizeFont);
    text.setFillColor(sf::Color::Red);
    over.setFont(font);
    over.setCharacterSize(height_scoreboard / 3);
    over.setFillColor(sf::Color::Green);
    timeBigFood.loadFromFile("Picture/map_1.png", sf::IntRect(10, 10, 5, sizeFont - 10));
    _isInit = true;
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
                    return ' ';
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
                case sf::Keyboard::Return:
                    return 36;
                case sf::Keyboard::Num1:
                    return 1;
                case sf::Keyboard::Num2:
                    return 2;
                case sf::Keyboard::Num3:
                    return 3;
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

}

void SFML_lib::drawMenu(void* rectA, void* rectB, int typeMenu) {
    _window->pollEvent(_event);
    _window->clear();
    sf::Sprite arrow;
    t_scr A = *reinterpret_cast<t_scr*>(rectA);
    t_scr B = *reinterpret_cast<t_scr*>(rectB);
    arrow.setTexture(_textureArrow);
    arrow.setPosition(A.x, A.y);
    auto size = arrow.getTexture()->getSize();
    arrow.setScale(float(A.w)/size.x, float(A.h)/size.y);
    _window->draw(arrow);
    if (typeMenu == 3) {
        sf::Sprite button;
        button.setTexture(_buttonTexture[3]);
        size = button.getTexture()->getSize();
        button.setScale(float(B.w) / size.x, float(B.h) / size.y);
        button.setPosition(B.x, B.y);
        _window->draw(button);
        button.setTexture(_buttonTexture[2]);
        size = button.getTexture()->getSize();
        button.setScale(float(B.w) / size.x, float(B.h) / size.y);
        B.y += B.h + 10;
        button.setPosition(B.x, B.y);
        _window->draw(button);
        button.setTexture(_buttonTexture[4]);
        size = button.getTexture()->getSize();
        button.setScale(float(B.w) / size.x, float(B.h) / size.y);
        B.y += B.h + 10;
        button.setPosition(B.x, B.y);
        _window->draw(button);
    }

    else {
            sf::Sprite button;
            button.setTexture(_buttonTexture[0]);
            size = button.getTexture()->getSize();
            button.setScale(float(B.w)/size.x, float(B.h)/size.y);
            button.setPosition(B.x, B.y);
            _window->draw(button);
            button.setTexture(_buttonTexture[1]);
            size = button.getTexture()->getSize();
            button.setScale(float(B.w)/size.x, float(B.h)/size.y);
            B.y += B.h + 10;
            button.setPosition(B.x, B.y);
            _window->draw(button);
            button.setTexture(_buttonTexture[2]);
            size = button.getTexture()->getSize();
            button.setScale(float(B.w)/size.x, float(B.h)/size.y);
            B.y += B.h + 10;
            button.setPosition(B.x, B.y);
            _window->draw(button);
            button.setTexture(_buttonTexture[4]);
            size = button.getTexture()->getSize();
            button.setScale(float(B.w)/size.x, float(B.h)/size.y);
            B.y += B.h + 10;
            button.setPosition(B.x, B.y);
            _window->draw(button);
    }
}



void SFML_lib::drawMap() {
    _window->pollEvent(_event);
    _window->clear();
    sf::Sprite map;
    map.setTexture(_textureMap);
    map.setPosition(0, height_scoreboard);
    auto size = map.getTexture()->getSize();
    map.setScale(float(weight)/size.x, float(height)/size.y);

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

void SFML_lib::drawInterface(std::string clock, int score) {

    text.setString(clock);
    text.setPosition(50, height_scoreboard / 2);
    _window->draw(text);
    text.setString("Score:   " + std::to_string(score));
    text.setPosition(weight / 3, height_scoreboard / 2);
    _window->draw(text);
}

void SFML_lib::drawTimeBigFood(int time) {
    sf::Sprite sprite;
    sprite.setTexture(timeBigFood);
    sprite.setColor(sf::Color::Green);
    for (int i = 0; i < time; i++) {
        sprite.setPosition((weight / 3) * 2 + (3 * i), height_scoreboard / 2);
        _window->draw(sprite);
    }
}

void SFML_lib::renderClear() {

}

void SFML_lib::cleanWindow() {
    _window->clear();
    _window->close();

}

void SFML_lib::drawGameOver(int score) {
    _window->pollEvent(_event);
    _window->clear();
    auto size = GameOver.getTexture()->getSize();
    GameOver.setScale((weight/3)/size.x, (height/3)/size.y);
    GameOver.setPosition((weight / 3) , (height / 3));
    _window->draw(GameOver);
    over.setString("SCORE:    " + std::to_string(score));
    over.setPosition( (weight / 2) - height_scoreboard , (height / 3) * 2);
    _window->draw(over);
    over.setString("Please, press space key");
    over.setPosition((weight / 2 - height_scoreboard * 2), (height - height_scoreboard));
    _window->draw(over);
}

extern "C"  AView* getInstance(int weight, int height) {
    return new SFML_lib(weight, height);
}

extern "C" void		destroy_object(SFML_lib *gui) {
    delete gui;
}
