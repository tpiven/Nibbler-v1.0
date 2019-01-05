//
// Created by kmykhailenko on 02.01.19.
//

#include "SDL_lib.hpp"
#include "global.h"
#include <unistd.h>
#include "Mmap.hpp"

const char tail_path[] = "/Picture/dirt.png";//TODO create many picture like: tail_16x16, tail_8x8
const char body_path[] = "/Picture/grass_bloc_mod.png";
const char head_path[] = "/Picture/dirt_1.png";

SDL_lib* SDL_lib::_inst = nullptr;
SDL_Renderer* SDL_lib::renderer = nullptr;
SDL_Window*     SDL_lib::_window = nullptr;
SDL_Texture*    SDL_lib::_texture_map = nullptr;

SDL_lib::SDL_lib() {}
SDL_lib::~SDL_lib() {}
SDL_lib& SDL_lib::getInstance() {
    static SDL_lib instance;
    return instance;
}

void SDL_lib::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Trouble with init SDL" << std::endl;
        exit(-1);
    }
    _window = SDL_CreateWindow(
            "Jörmungandr",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            g_weight,
            g_height,
            SDL_WINDOW_SHOWN
            );
    if (!_window){
        std::cout << "Error Window: " << &SDL_Error << std::endl;
        exit(-1);
    }
    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Trouble wih render" << std::endl;
        return;
    }
    //SDL_SetRenderDrawColor(renderer, 80, 80, 253, 0);//BAG NOT WORKING
    char path[4096];
    _dir = getwd(path);
    size_t  n = _dir.rfind('/');
    _dir.resize(n);
    _texture_map = SDL_CreateTextureFromSurface(renderer, IMG_Load("/Users/kmykhail/Desktop/qw.png"));
    _snakeTexture[0] = SDL_CreateTextureFromSurface(renderer, IMG_Load((_dir + tail_path).c_str()));
    _snakeTexture[1] = SDL_CreateTextureFromSurface(renderer, IMG_Load((_dir + body_path).c_str()));
    _snakeTexture[2] = SDL_CreateTextureFromSurface(renderer, IMG_Load((_dir + head_path).c_str()));
}

int SDL_lib::catchHook(){
    SDL_PollEvent(&_event);
    if (_event.type == SDL_QUIT){
        return -1;
    }
    if (_event.type == SDL_KEYDOWN){
        switch (_event.key.keysym.sym){
            case SDLK_ESCAPE:
                return -1;
            case SDLK_w:
                return 'w';
            case SDLK_s:
                return 's';
            case SDLK_d:
                return 'd';
            case SDLK_a:
                return 'a';
            case SDLK_SPACE:
                return ' ';
            case SDLK_UP:
                return 126;
            case SDLK_DOWN:
                return 125;
            case SDLK_LEFT:
                return 123;
            case SDLK_RIGHT:
                return 124;
            default:
                return 0;
        }
    }
    return 0;
}

uint32_t SDL_lib::getTicks() {
    return SDL_GetTicks();
}

void SDL_lib::delay(int time) {
//    std::this_thread::sleep_for(std::chrono::milliseconds(time));
//    SDL_
}

void SDL_lib::render() {
    SDL_RenderPresent(renderer);
}

void SDL_lib::drawMap() {
    _scrR.y = HEIGHT_SCOREBOARD;
    _scrR.x = WEIGHT_SCOREBOARD;
    _scrR.w = g_weight;
    _scrR.h = g_height;
    SDL_RenderCopy(renderer, _texture_map, nullptr, &_scrR);
}

void SDL_lib::drawSnake(void* rect, int b_block) {//b_block - wich texture render: tail, body, head
    _scrR = *reinterpret_cast<SDL_Rect*>(rect);
    SDL_RenderCopy(renderer, _snakeTexture[b_block], nullptr, &_scrR);
}

void SDL_lib::cleanWindow() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}