//
// Created by Таня on 15.01.2019.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "../AView.hpp"
#include <map>


class SFML_lib: public AView{
public:
    SFML_lib();
    SFML_lib(int g_weight, int g_height);
    virtual ~SFML_lib();

void    init() override;
int     catchHook() override;
void    render() override;
void    drawMap() override;
void    drawMenu(void*, void*, int) override;
void    drawSnake(void*, int) override;
uint32_t getTicks() override;
void    delay(int) override;
void    cleanWindow() override;
void    drawFood(void*) override;
void    drawInterface(std::string, int) override;
void    drawTimeBigFood(int) override;
void    renderClear() override;
void    drawGameOver(int) override;

private:
    static sf::RenderWindow *_window;
    sf::Event _event;
    sf::Clock _clock;
    sf::Texture _textureMap;
    sf::Texture  _textureFood;
    sf::Texture _textureArrow;
    sf::Texture timeBigFood;
    sf::Texture _gameOver;
    sf::Sprite GameOver;
    std::map<int, sf::Texture> _snakeTexture;
    std::map<int, sf::Texture> _buttonTexture;
    sf::Font font;
    sf::Text text;
    sf::Text over;
    int weight;
    int height;
    int height_scoreboard;
    int sizeFont;
    bool _isInit;


};

