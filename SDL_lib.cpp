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
SDL_Event*      SDL_lib::_event = nullptr;
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    char path[4096];
    _dir = getwd(path);//get_current_dir_name();//macOs stupid
    //char *cwd_buffer = malloc(sizeof(char) * MAX_PATH_NAME);
    //std::string dir =
    //std::cout << dir << std::endl;
    size_t  n = _dir.rfind('/');
    _dir.resize(n);
    _texture_map = SDL_CreateTextureFromSurface(renderer, IMG_Load("/Users/kmykhail/Desktop/qw.png"));
    drawMap();
    _snakeTexture[0] = SDL_CreateTextureFromSurface(renderer, IMG_Load((_dir + tail_path).c_str()));
    _snakeTexture[1] = SDL_CreateTextureFromSurface(renderer, IMG_Load((_dir + body_path).c_str()));
    _snakeTexture[2] = SDL_CreateTextureFromSurface(renderer, IMG_Load((_dir + head_path).c_str()));
}

void SDL_lib::handleEvent() {}

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
    std::cout << "Y: " << _scrR.y << " X: " << _scrR.x << " W: " <<  _scrR.w << " H: " << _scrR.h << std::endl;
    SDL_RenderCopy(renderer, _snakeTexture[b_block], nullptr, &_scrR);
}