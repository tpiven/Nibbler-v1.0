//
// Created by kmykhailenko on 31.12.18.
//
#pragma once
#include <iostream>
#include "AView.hpp"
#include "Logic.hpp"
#include "Food.hpp"
#include "Menu.hpp"
#include "Interface.hpp"

class Game_Obj {
public:
    static Game_Obj* getInstance();
    void    init();
    int     handleEvent(AView*);
    void    update(AView*);
    void    render(AView*);
    Interface& getInterface();
private:
    static Game_Obj *_inst;
    bool    menu(AView*);
    void    clean(AView*);
    bool    action(AView*);
    void    main_loop();
    bool    escapeLogic();
    bool    pauseLogic();
    std::vector<AView*> _libs;
    Logic   _logic;
    Menu    _menu;
    Food    _food;
    Interface _interface;
    Game_Obj();
    ~Game_Obj();
    Game_Obj(Game_Obj &&) = delete;
    Game_Obj(const Game_Obj &) = delete;
    Game_Obj& operator=(const Game_Obj &) = delete;
    Game_Obj& operator=(Game_Obj&&) = delete;
};
