//
// Created by kmykhailenko on 14.03.19.
//

#ifndef GLFW_GAMEWINDOW_HPP
#define GLFW_GAMEWINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../AView.hpp"
#ifdef __APPLE__
    #include <GLUT/glut.h>
#endif

#ifdef __linux__
    #include <GL/glut.h>
#endif

#include <iostream>
#include <SOIL.h>
#include <fstream>
#include <string>
#include <map>
#include <unistd.h>


#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#pragma once
//#include "SDL2/SDL.h"
//#include "SDL2/SDL_image.h"
//#include "SDL2/SDL_ttf.h"
//#include "../AView.hpp"
//#include <map>
//#include "TextureManager.hpp"
//
//class SDL_lib : public AView{
//public:
//    SDL_lib();
//    SDL_lib(int weight, int height);
//    virtual ~SDL_lib();
//    void    init() override;
//    int     catchHook() override;
//    void    render() override;
//    void    drawMenu(void*, void*, int) override;
//    void    drawMap() override;
//    void    drawSnake(void*, int) override;
//    void    renderClear() override;
//    uint32_t getTicks() override;
//    void    delay(int) override;
//    void    cleanWindow() override;
//    void    drawFood(void*) override;
//    void    drawInterface(std::string, int) override;
//    void    drawTimeBigFood(int) override;
//    void    drawGameOver(int) override;
//private:
//    friend class TextureManager;
//    static SDL_Renderer * renderer;
//    static SDL_Window *_window;
//    SDL_Event   _event;
//    static SDL_Texture *_textureMap;
//    static SDL_Texture *_textureFood;
//    static SDL_Texture  *_textureArrow;
//    static SDL_Texture  *_textureLine;
//
//    static SDL_Texture  *_textureText;
//    static TTF_Font     *_font;
//    SDL_Color           _textColor;
//    SDL_Rect    _mcrR;//menu
//    SDL_Rect    _scrR;//snake
//    SDL_Rect    _fcrR;//food
//    SDL_Rect    _tcrR;//text
//    SDL_Rect    _lcrR;
//    bool        _isInit;
//    int g_weight;
//    int g_height;
//    int HEIGHT_SCOREBOARD;
//    int SizeFont;
//
//    std::string _dir;
//    std::map<int, SDL_Texture*> _snakeTexture;
//    std::map<std::string, SDL_Texture*> _buttonTexture;
//
//    SDL_lib(const SDL_lib&) = delete;
//    SDL_lib(SDL_lib&&) = delete;
//    SDL_lib &operator=(const SDL_lib &) = delete;
//    SDL_lib &operator=(SDL_lib&&) = delete;

struct Vertex{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texcoord;
};

typedef struct s_glScr{
    int x;
    int y;
    int w;
    int h;
}               t_glScr;

class GL_lib : public AView{
private:
    GLFWwindow*     _window;
    std::string     _dir;
    int             g_weight;
    int             g_height;
    int             HEIGHT_SCOREBOARD;
    int             SizeFont;


    GLuint          _textureMap1;
    GLuint          _textureMap2;
    GLuint          _textureFood;
    GLuint          _textureBigFood;
    GLuint          _textureArrow;
    GLuint          _textureLine;
    std::map<std::string, GLuint>   _textureButton;
    std::map<int, GLuint > _textureSnake;

    t_glScr           _scrR;//snake
    t_glScr           _fcrR;//food
    t_glScr           _lcrR;//line time
    t_glScr           _mcrR;//menu
    t_glScr           _gcrR;//target map

    void LoadImage();
    void DrawEveryThing(t_glScr glScr, GLuint& drawThis);
    void ScaleCoors(t_glScr&);
public:
    GL_lib();
    GL_lib(int weight, int height);
    ~GL_lib();
    void    init() override;
    void    initMap(int) override;
    int     catchHook() override;
    void    render() override;
    void    drawMenu(void*, void*, int) override;
    void    drawMap() override;
    void    drawSnake(void*, int) override;
    void    renderClear() override;
    uint32_t getTicks() override;
    void    delay(int) override;
    void    cleanWindow() override;
    void    drawFood(void* rect) override;
    void    drawBigFood(void*) override;
    void    drawInterface(std::string clock, int score) override;
    void    drawTimeBigFood(int time) override;
    void    drawGameOver(int) override;
    void    drawChangeMap(int)   override;

    int     CloseWindow() const;
    void    Update();
    void    DestroyWindow();
    void    updateInput();

    static int  _buttonStatus;
};


#endif //GLFW_GAMEWINDOW_HPP

//void SDL_lib::init() {
//    /************INIT WINDOW************/
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
//        std::cerr << "Trouble with init SDL" << std::endl;
//        exit(-1);
//    }
//    _window = SDL_CreateWindow(
//            "Jörmungandr",
//            SDL_WINDOWPOS_CENTERED,
//            SDL_WINDOWPOS_CENTERED,
//            g_weight,
//            g_height + HEIGHT_SCOREBOARD,
//            SDL_WINDOW_SHOWN
//    );
//    if (!_window){
//        std::cerr << "Error Window: " << &SDL_Error << std::endl;
//        exit(-1);
//    }
//    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
//    if (!renderer) {
//        std::cerr << "Trouble wih render" << std::endl;
//        return;
//    }
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);//BAG NOT WORKING
//    char path[4096];
//    _dir = getwd(path);
//   // size_t  n = _dir.rfind('/');
//    //_dir.resize(n); //TODO investigate PATH of PICTURES
//    /************INIT TEXTURE FOR BUTTON***********/
//    _buttonTexture = {{"single", CREATE_TEXTURE((_dir + buttonSingle_path).c_str())}, {"multi", CREATE_TEXTURE((_dir + buttonMulti_path).c_str())},
//                      {"continue", CREATE_TEXTURE((_dir + buttonContinue_path).c_str())}, {"option", CREATE_TEXTURE((_dir + buttonOption_path).c_str())},
//                      {"exit", CREATE_TEXTURE((_dir + buttonExit_path).c_str())}};
//    if (_buttonTexture.empty()){
//        std::cerr << "textureButton not exist" << std::endl;
//        exit(1);
//    }
//    /************INIT TEXTURE FOR ARROW************/
//    _textureArrow = CREATE_TEXTURE((_dir + arrow_path).c_str());
//    if (!_textureArrow){
//        std::cerr << "textureArrow not exist" << std::endl;
//        exit(1);
//    }
//    /************INIT TEXTURE FOR MAP**************/
//    _textureMap = CREATE_TEXTURE((_dir + map_1).c_str());
//    if (!_textureMap){
//        std::cerr << "textuteMap not exist" << std::endl;
//        exit(1);
//    }
//    /************INIT TEXTURE FOR SNAKE************/
//    _snakeTexture = {{0, CREATE_TEXTURE((_dir + tail_path).c_str())}, {1, CREATE_TEXTURE((_dir + body_path).c_str())},
//                     {2, CREATE_TEXTURE((_dir + head_path).c_str())}};
//    if (_snakeTexture.empty()){
//        std::cerr << "textureSnake not exist" << std::endl;
//        exit(1);
//    }
//    /************INIT TEXTURE FOR FOOD************/
//    _textureFood = CREATE_TEXTURE((_dir + lilFood).c_str());
//    if (!_textureFood){
//        std::cerr << "textuteFood not exist" << std::endl;
//        exit(1);
//    }
//    /************INIT TEXTURE FOR LINE TIME OF SURP FOOD************/
//    _textureLine = CREATE_TEXTURE((_dir + lineFood_path).c_str());
//    if (!_textureLine){
//        std::cerr << "textureLine not exist" << std::endl;
//        exit(1);
//    }
//    /************INIT TEXTURE FOR FONT************/
//    if (TTF_Init() < 0){
//        std::cout << TTF_GetError() << std::endl;
//        exit(-1);
//    }
//    std::cout << "FONT_PATH: " << _dir + font_path << std::endl;
//
//    if (!(_font = TTF_OpenFont((_dir + font_path).c_str(), SizeFont))){//TODO change size font on variable
//        std::cerr << "textureText not exist" << std::endl;
//        exit(1);
//    }
//    _textColor = {255, 0, 0, 0};//color red
//    _isInit = true;
//}
//
//
//int SDL_lib::catchHook(){
//    SDL_PollEvent(&_event);
//    if (_event.type == SDL_QUIT){
//        std::cout << "EXIT" << std::endl;
//        return -1;
//    }
//    if (_event.type == SDL_KEYDOWN){
//        switch (_event.key.keysym.sym){
//            case SDLK_ESCAPE:
//                std::cout << "PAUSE" << std::endl;
//                return ' ';
//            case SDLK_w:
//                std::cout << "w" << std::endl;
//                return 'w';
//            case SDLK_s:
//                std::cout << "s" << std::endl;
//                return 's';
//            case SDLK_d:
//                std::cout << "d" << std::endl;
//                return 'd';
//            case SDLK_a:
//                std::cout << "a" << std::endl;
//                return 'a';
//            case SDLK_SPACE:
//                return ' ';
//            case SDLK_UP:
//                return 126;
//            case SDLK_DOWN:
//                return 125;
//            case SDLK_LEFT:
//                return 123;
//            case SDLK_RIGHT:
//                return 124;
//            case SDLK_RETURN:
//                return 36;//enter
//            case SDLK_1://change current lib on SDL
//                return 1;
//            case SDLK_2://change current lib on SFML
//                return 2;
//            case SDLK_3://change current lib on ALLEGRO
//                return 3;
//            default:
//                return 0;
//        }
//    }
//    return 0;
//}
//
//uint32_t SDL_lib::getTicks() {
//    return SDL_GetTicks();
//}
//
//void SDL_lib::delay(int time) {
//    SDL_Delay(time);
//}
//
//void SDL_lib::render() {
//    SDL_RenderPresent(renderer);
//}
//
//void SDL_lib::drawMenu(void* rectA, void* rectB, int typeMenu) {
//    _mcrR = *reinterpret_cast<SDL_Rect*>(rectA);
//    /***********ADD ARROW TEXTURE***********/
//    SDL_RenderCopy(renderer, _textureArrow, nullptr, &_mcrR);//render arrow
//    /***********ADD BUTTON TEXTURE***********/
//    _mcrR = *reinterpret_cast<SDL_Rect*>(rectB);
//    if (typeMenu == 3){
//        SDL_RenderCopy(renderer, _buttonTexture["continue"], nullptr, & _mcrR);
//        _mcrR.y += _mcrR.h + 10;// distance between continue and multi option
//        SDL_RenderCopy(renderer, _buttonTexture["option"], nullptr, &_mcrR);
//        _mcrR.y += _mcrR.h + 10;// distance between option and multi exit
//        SDL_RenderCopy(renderer, _buttonTexture["exit"], nullptr, &_mcrR);
//    }
//    else {
//        SDL_RenderCopy(renderer, _buttonTexture["single"], nullptr, &_mcrR);//single player
//        _mcrR.y += _mcrR.h + 10;// distance between single and multi button
//        SDL_RenderCopy(renderer, _buttonTexture["multi"], nullptr, &_mcrR);//multi player
//        _mcrR.y += _mcrR.h + 10;// distance between multi and option
//        SDL_RenderCopy(renderer, _buttonTexture["option"], nullptr, &_mcrR);
//        _mcrR.y += _mcrR.h + 10;// distance between option and exit
//        SDL_RenderCopy(renderer, _buttonTexture["exit"], nullptr, &_mcrR);
//    }
//}
//
//void SDL_lib::drawMap() {
//     _scrR.y = HEIGHT_SCOREBOARD;
//    _scrR.x = 0;
//    _scrR.w = g_weight;
//    _scrR.h = g_height;
//    SDL_RenderCopy(renderer, _textureMap, nullptr, &_scrR);
//}
//
//void SDL_lib::drawSnake(void* rect, int b_block) {//b_block - wich texture render: tail, body, head
//    _scrR = *reinterpret_cast<SDL_Rect*>(rect);
//    SDL_RenderCopy(renderer, _snakeTexture[b_block], nullptr, &_scrR);
//}
//
//void SDL_lib::drawFood(void* rect) {
//    _fcrR = *reinterpret_cast<SDL_Rect*>(rect);
//    SDL_RenderCopy(renderer, _textureFood, nullptr, &_fcrR);
//}
//
//void SDL_lib::drawInterface(std::string clock, int score) {
//    /***************DRAW CLOCK****************/
//    _textureText = CREATE_TEXTURETEXT(clock.c_str(), _textColor, _tcrR);
//    _tcrR.x = 50;
//    _tcrR.y = HEIGHT_SCOREBOARD/2;
//    SDL_RenderCopy(renderer, _textureText, nullptr, &_tcrR);
//    /***************DRAW SCORE****************/
//    _textureText = CREATE_TEXTURETEXT(("Score:   " + std::to_string(score)).c_str(), _textColor, _tcrR);
//    _tcrR.x = g_weight/3;
//    _tcrR.y = HEIGHT_SCOREBOARD/2;
//    SDL_RenderCopy(renderer, _textureText, nullptr, &_tcrR);
//}
//
//void SDL_lib::drawTimeBigFood(int time) {
//    /***************DRAW LINE TIME FOR SURP FOOD****************/
//    _lcrR = {(g_weight / 3) * 2, HEIGHT_SCOREBOARD / 2, time, SizeFont - 10};
//    SDL_RenderCopy(renderer, _textureLine, nullptr, &_lcrR);
//}
//
//void SDL_lib::renderClear() {
//    SDL_RenderClear(renderer);
//}
//
//void SDL_lib::drawGameOver(int) {
//
//}
//
//void SDL_lib::cleanWindow() {
//    SDL_DestroyWindow(_window);
//    SDL_DestroyRenderer(renderer);
//    SDL_Quit();
//}
//
//extern "C"  AView* getInstance(int weight, int height) {
//    return new SDL_lib(weight, height);
//}
//
//extern "C" void         destroy_object(SDL_lib *gui)
//{
//    delete gui;
//}%
