//
// Created by kmykhailenko on 14.03.19.
//

#include "GL_lib.hpp"
#include <thread>
#include <string.h>

#define CREATE_TEXTURE(str) SOIL_load_OGL_texture(str, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT)

const char tail_path[] = "/Picture/snake_tails.png";
const char body_path[] = "/Picture/snake_body.png";
const char head_path[] = "/Picture/snake_head.png";
const char map_1[] = "/Picture/map_1.png";
const char map_2[] = "/Picture/map_2.png";
const char lilFood[] = "/Picture/lilfood.png";
const char bigFood[] = "/Picture/bigfood.png";
const char buttonSingle_path[] = "/Picture/button1.png";
const char buttonMulti_path[] = "/Picture/button2.png";
const char lineFood_path[] = "/Picture/lineTimeFood.png";
extern const char buttonOption_path[] = "/Picture/options.png";
extern const char buttonContinue_path[] = "/Picture/continue.png";
extern const char buttonExit_path[] = "/Picture/exit.png";
const char arrow_path[] = "/Picture/arrow_path.png";
const char font_path[] = "/Picture/ArialItalic.ttf";
const char gameOver_path[] = "/Picture/gameOver.png";

typedef struct {
    GLfloat positionCoors[3];
    GLfloat textureCoors[2];
}           VertexData;

int GL_lib::_buttonStatus = 0;
//TTF_Font GL_lib::*_font = nullptr;

static  TTF_Font* _font = nullptr;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS){
        switch (key){
            case GLFW_KEY_ESCAPE:
                std::cout << "PAUSE" << std::endl;
                GL_lib::_buttonStatus = ' ';
                return;
            case GLFW_KEY_W:
                std::cout << "w" << std::endl;
                GL_lib::_buttonStatus = 'w';
                return;
            case GLFW_KEY_S:
                std::cout << "s" << std::endl;
                GL_lib::_buttonStatus= 's';
                return;
            case GLFW_KEY_D:
                std::cout << "d" << std::endl;
                GL_lib::_buttonStatus= 'd';
                return;
            case GLFW_KEY_A:
                std::cout << "a" << std::endl;
                GL_lib::_buttonStatus= 'a';
                return;
            case GLFW_KEY_SPACE:
                std::cout << "space" << std::endl;
                GL_lib::_buttonStatus= ' ';
                return;
            case GLFW_KEY_UP:
                GL_lib::_buttonStatus= 126;
                return;
            case GLFW_KEY_DOWN:
                GL_lib::_buttonStatus= 125;
                return;
            case GLFW_KEY_LEFT:
                GL_lib::_buttonStatus = 123;
                return;
            case GLFW_KEY_RIGHT:
                GL_lib::_buttonStatus = 124;
                return;
            case GLFW_KEY_ENTER:
                GL_lib::_buttonStatus = 36;
                return;//enter
            case GLFW_KEY_1://change current lib on SDL
                GL_lib::_buttonStatus = 1;
                return;
            case GLFW_KEY_2://change current lib on SFML
                GL_lib::_buttonStatus = 2;
                return;
            case GLFW_KEY_3://change current lib on ALLEGRO
                GL_lib::_buttonStatus = 3;
                return;
            default:
                GL_lib::_buttonStatus = 0;
                return;
        }
    }
}

GL_lib::GL_lib() {}

GL_lib::GL_lib(int weight, int height) {
    g_weight = weight;
    g_height = height;
    HEIGHT_SCOREBOARD = g_weight / 14;
    SizeFont = HEIGHT_SCOREBOARD / 4;
    _size_block = (g_weight / 90);
}

GL_lib::~GL_lib() {

}

void GL_lib::init()
{
    if (!glfwInit()){
        std::cerr << "Error Init" << std::endl;
        exit(1);
    }

    if (!(_window = glfwCreateWindow(g_weight, g_height + HEIGHT_SCOREBOARD, "Snake", nullptr, nullptr))){
        std::cerr <<  "Error Create Window" << std::endl;
        exit(1);
    }

    glfwSetKeyCallback(_window, keyCallback);

    glfwMakeContextCurrent(_window);
//    glViewport(0.0f, 0.0f, g_weight, g_height + HEIGHT_SCOREBOARD);

    if (!glfwGetCurrentContext()){
        std::cerr << "Couldn't create OpenGL context" << std::endl;
        exit(1);
    }

    GLenum err = glewInit();
    if (GLEW_OK != err){
        std::cerr << glewGetErrorString(err) <<std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    glClearColor(57.0f/255.0f, 200.0f/255.0f, 12.0f/255.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    LoadImage();

}

void GL_lib::LoadImage()
{
    char path[4096];
    _dir = getwd(path);
     size_t  n = _dir.rfind('/');
    _dir.resize(n);

    /*************LOAD MAP TEXTURE*************/
    if (! (_textureMap1 = CREATE_TEXTURE((_dir + map_1).c_str()))) {
        std::cerr << "Not load texture map" << std::endl;
        exit(1);
    }
    if (! (_textureMap2 = CREATE_TEXTURE((_dir + map_2).c_str()))) {
        std::cerr << "Not load texture map" << std::endl;
        exit(1);
    }
    /*************LOAD SNAKE TEXTURE*************/
    _textureSnake = {
                        {0, CREATE_TEXTURE((_dir + tail_path).c_str())},
                        {1, CREATE_TEXTURE((_dir + body_path).c_str())},
                        {2, CREATE_TEXTURE((_dir + head_path).c_str())}
                    };
    if (_textureSnake.empty()){
        std::cerr << "Not load texture snake" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR FOOD************/
    _textureFood = CREATE_TEXTURE((_dir + lilFood).c_str());
    if (!_textureFood){
        std::cerr << "textuteFood not exist" << std::endl;
        exit(1);
    }

    _textureBigFood = CREATE_TEXTURE((_dir + bigFood).c_str());
    if (!_textureBigFood){
        std::cerr << "textuteBigFood not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR LINE TIME OF SURP FOOD************/
    _textureLine = CREATE_TEXTURE((_dir + lineFood_path).c_str());
    if (!_textureLine){
        std::cerr << "textureLine not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR BUTTON***********/
    _textureButton = {{"single", CREATE_TEXTURE((_dir + buttonSingle_path).c_str())}, {"multi", CREATE_TEXTURE((_dir + buttonMulti_path).c_str())},
                      {"continue", CREATE_TEXTURE((_dir + buttonContinue_path).c_str())}, {"option", CREATE_TEXTURE((_dir + buttonOption_path).c_str())},
                      {"exit", CREATE_TEXTURE((_dir + buttonExit_path).c_str())}};
    if (_textureButton.empty()){
        std::cerr << "textureButton not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR ARROW************/
    _textureArrow = CREATE_TEXTURE((_dir + arrow_path).c_str());
    if (!_textureArrow){
        std::cerr << "textureArrow not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE GAME OVER************/
    _textureGameOver = CREATE_TEXTURE((_dir + gameOver_path).c_str());
    if (!_textureGameOver){
        std::cerr << "textureGameOver not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE GAME OVER************/
    //TODO
    /************INIT TEXTURE FOR FONT************/
    //TODO
    if (TTF_Init() < 0){
        std::cerr << TTF_GetError() << std::endl;
        exit(-1);
    }
    if (!(_font = TTF_OpenFont((_dir + font_path).c_str(), (HEIGHT_SCOREBOARD / 3)))){
        std::cerr << "text Game Over not exist" << std::endl;
        exit(1);
    }
    _tColor = {107,142,35, 0};

    glBindTexture(GL_TEXTURE_2D, _textureMap1);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glfwPollEvents();
}

void GL_lib::drawMap() {
    glfwMakeContextCurrent(_window);
    glViewport(0, 0, g_weight * 2, g_height * 2);
    glClearColor(0.f, 0.f, 0.f, 1.0f);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureMap1);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBegin(GL_QUADS);

    glTexCoord2f(0.f, 0.f);
    glVertex2f(-1.f, -1.f);

    glTexCoord2f(1.f, 0.f);
    glVertex2f(1.f, -1.f);

    glTexCoord2f(1.f, 1.f);
    glVertex2f(1.f, 1.f);

    glTexCoord2f(0.f, 1.f);
    glVertex2f(-1.f, 1.f);

    glEnd();
}

void GL_lib::initMap(int) {

}

int GL_lib::catchHook() {
    glfwPollEvents();
    int sym = _buttonStatus;
    _buttonStatus = 0;
    return sym;
}

uint32_t GL_lib::getTicks() {
    return glfwGetTime();
}

void GL_lib::delay(int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void GL_lib::render()
{
    glfwSwapBuffers(_window);
}

int GL_lib::CloseWindow() const
{
    return glfwWindowShouldClose(_window);
}

void GL_lib::updateInput()
{
    //FUCTION FOR ESCAPE HOOK
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        #ifdef __APPLE__
            glfwSetWindowShouldClose(_window, GLFW_TRUE);
        #endif

        #ifdef __linux__
            glfwSetWindowShouldClose(_window, 1);
        #endif
    }
}

void GL_lib::Update()
{

}

void GL_lib::ScaleCoors(t_glScr& glScr) {
    glScr.x *= 2;
    glScr.w *= 2;
    glScr.y = g_height - glScr.y;
    glScr.h *= 2;
}

void GL_lib::DrawEveryThing(t_glScr glScr, GLuint &drawThis) {
    glfwMakeContextCurrent(_window);
    glViewport(glScr.x * 2, glScr.y * 2, glScr.w * 2, glScr.h * 2);

    glClearColor(0.f, 0.f, 0.f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (drawThis != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, drawThis);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
    glBegin(GL_QUADS);

    glTexCoord2f(0.f, 0.f);
    glVertex2f(-1.f, -1.f);

    glTexCoord2f(1.f, 0.f);
    glVertex2f(1.f, -1.f);

    glTexCoord2f(1.f, 1.f);
    glVertex2f(1.f, 1.f);

    glTexCoord2f(0.f, 1.f);
    glVertex2f(-1.f, 1.f);

    glEnd();
}

void GL_lib::drawMenu(void* rectA, void* rectB, int typeMenu) {
    if (!rectA || !rectB) {
        std::cerr << "Trouble with rectA or rectB" << std::endl;
        exit(1);
    }
    _mcrR = *reinterpret_cast<t_glScr*>(rectA);
    _mcrR.y =  g_height - _mcrR.y;
    DrawEveryThing(_mcrR, _textureArrow);
    _mcrR = *reinterpret_cast<t_glScr*>(rectB);
    _mcrR.y =  g_height - _mcrR.y;
    if (typeMenu == 3){
        DrawEveryThing(_mcrR, _textureButton["continue"]);
        _mcrR.y += (_mcrR.h + 10) * -1;
        DrawEveryThing(_mcrR, _textureButton["option"]);
        _mcrR.y += (_mcrR.h + 10) * -1;
        DrawEveryThing(_mcrR, _textureButton["exit"]);
    }
    else{
        DrawEveryThing(_mcrR, _textureButton["single"]);
        _mcrR.y += (_mcrR.h + 10) * -1;
        DrawEveryThing(_mcrR, _textureButton["multi"]);
        _mcrR.y += (_mcrR.h + 10) * -1;
        DrawEveryThing(_mcrR, _textureButton["option"]);
        _mcrR.y += (_mcrR.h + 10) * -1;
        DrawEveryThing(_mcrR, _textureButton["exit"]);
    }
}



void GL_lib::drawSnake(void* rect, int b_block) {
    if (!rect){
        std::cout << "Rect is NULL" << std::endl;
        exit(1);
    }

    _scrR = *reinterpret_cast<t_glScr*>(rect);
    _scrR.y = (g_height + HEIGHT_SCOREBOARD) - _scrR.y - _size_block;

    DrawEveryThing(_scrR, _textureSnake[b_block]);
}


void GL_lib::drawFood(void *rect) {
    if (!rect){
        std::cout << "Rect is NULL" << std::endl;
        exit(1);
    }

    _fcrR = *reinterpret_cast<t_glScr*>(rect);
    _fcrR.y = (g_height + HEIGHT_SCOREBOARD) - _fcrR.y - _size_block;
    DrawEveryThing(_fcrR, _textureFood);
}

void    GL_lib::drawBigFood(void *rect) {
    _fcrR = *reinterpret_cast<t_glScr*>(rect);
    _fcrR.y = (g_height + HEIGHT_SCOREBOARD) - _fcrR.y - (_size_block * 2);

    DrawEveryThing(_fcrR, _textureBigFood);
}

//glfwMakeContextCurrent(_window);
//    glViewport(glScr.x * 2, glScr.y * 2, glScr.w * 2, glScr.h * 2);
//
//    glClearColor(0.f, 0.f, 0.f, 1.0f);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    if (drawThis != 0) {
//        glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, drawThis);
//        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    }
//    glBegin(GL_QUADS);
//
//    glTexCoord2f(0.f, 0.f);
//    glVertex2f(-1.f, -1.f);
//
//    glTexCoord2f(1.f, 0.f);
//    glVertex2f(1.f, -1.f);
//
//    glTexCoord2f(1.f, 1.f);
//    glVertex2f(1.f, 1.f);
//
//    glTexCoord2f(0.f, 1.f);
//    glVertex2f(-1.f, 1.f);
//
//    glEnd();

void GL_lib::drawInterface(std::string clock, int score){
    //TODO
//
//    SDL_Surface* surface = TTF_RenderText_Blended(_font, "QQQQQ", _tColor);
//    if (!surface){
//        TTF_CloseFont(_font);
//        std::cerr << TTF_GetError() << std::endl;
//        exit(-1);
//    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    SDL_Surface* sText = TTF_RenderText_Blended(_font, "QQQQ", _tColor);
    if (!sText){
        std::cerr << TTF_GetError() << std::endl;
        exit(-1);
    }
    _area.x = 0;
    _area.y = 0;
    _area.w = sText->w;
    _area.h = sText->h;
//    SDL_Surface* temp = SDL_CreateRGBSurface(0, sText->w, sText->h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0x000000ff);
//    if (!temp){
//        std::cerr << TTF_GetError() << std::endl;
//        exit(-1);
//    }
//    SDL_BlitSurface(sText, &_area, temp, NULL);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sText->w, sText->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS); {
        glTexCoord2d(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2d(1, 0); glVertex3f(0 + sText->w, 0, 0);
        glTexCoord2d(1, 1); glVertex3f(0 + sText->w, 0 + sText->h, 0);
        glTexCoord2d(0, 1); glVertex3f(0, 0 + sText->h, 0);
    } glEnd();
    glDisable(GL_TEXTURE_2D);
    SDL_FreeSurface( sText );
//    SDL_FreeSurface( temp );
}

void GL_lib::drawTimeBigFood(int time) {
    _lcrR = {(g_weight / 3) * 2, (g_height + HEIGHT_SCOREBOARD / 2), time, SizeFont - 10};
    DrawEveryThing(_lcrR, _textureLine);
//    glClearColor(0.f, 0.f, 0.f, 1.0f);
}

void GL_lib::renderClear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void GL_lib::drawGameOver(int score) {
    //TODO
    std::cout << "Game Over" << std::endl;
//    _gcrR = {(g_weight / 3), g_height / 3, g_weight / 3, g_height / 3};
//    SDL_RenderCopy(renderer, _textureGameOver, nullptr, &_gcrR);
//    _textureScore = CREATE_TEXTURETEXT(("SCORE   " + std::to_string(score)).c_str(), _tColor, _tcrR);
//    _tcrR.x = g_weight/2 - (HEIGHT_SCOREBOARD / 3) * 2;
//    _tcrR.y = (g_height / 3) * 2;
//    SDL_RenderCopy(renderer, _textureScore, nullptr, &_tcrR);
//
//    _textureScore = CREATE_TEXTURETEXT("Please, press space key", _tColor, _tcrR);
//    _tcrR.x = g_weight / 2 - (HEIGHT_SCOREBOARD + (HEIGHT_SCOREBOARD / 3));
//    _tcrR.y = g_height - HEIGHT_SCOREBOARD;
//    SDL_RenderCopy(renderer, _textureScore, nullptr, &_tcrR);
}

void GL_lib::drawChangeMap(int n) {
    unsigned int qw = 0;
    _gcrR = {g_weight / 3, g_height / 3, 180, 134};
    DrawEveryThing(_gcrR, _textureMap1);
    _gcrR = {(g_weight / 3) + 180 + HEIGHT_SCOREBOARD, g_height / 3, 180, 134};
    DrawEveryThing(_gcrR, _textureMap2);

    t_glScr square;
    if (n == 1){
        square = {(g_weight / 3)  - 10, (g_height / 3) - 10, 200, 150};
    }
    else if (n == 2) {
        square = {(g_weight / 3) + (90 * 2) + HEIGHT_SCOREBOARD - 10, (g_height / 3) - 10, 200, 150};
    }
    //TODO normal case with switch lib
    DrawEveryThing(square, qw);
}

void GL_lib::cleanWindow() {
    //TODO DELETE THIS CODE
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void GL_lib::DestroyWindow()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}