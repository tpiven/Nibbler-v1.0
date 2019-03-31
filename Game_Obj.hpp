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
    void    DeleteStaticGame();
    void    init();
    int     handleEvent();
    void    update();
    static AView * viev;

private:
    static Game_Obj *_inst;
    bool    menu();
    bool    action();
    void    main_loop();
    void    addNewSharedLib();
    void    switchLib(int);
    bool    escapeLogic();
    bool    pauseLogic();

  std::string library[3];

    Logic   _logic;
    Menu    _menu;
    Food    _food;
    Interface  *_interface;
   static void *dl_lib;

    friend class Logic;
    friend class Menu;
    friend class Food;
    friend class Interface;
    Game_Obj();
    ~Game_Obj();
    Game_Obj(Game_Obj &&) = delete;
    Game_Obj(const Game_Obj &) = delete;
    Game_Obj& operator=(const Game_Obj &) = delete;
    Game_Obj& operator=(Game_Obj&&) = delete;

};
