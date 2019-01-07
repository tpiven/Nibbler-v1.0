//
// Created by kmykhailenko on 31.12.18.
//
#pragma once
#include <map>
#include <list>
#include <tuple>
#include "header.h"

using lst = std::list<t_coor>;

class Logic {
public:
    explicit Logic() noexcept;
    explicit Logic(int players) noexcept;
    ~Logic();
    void    move();
    bool    running() const;
    void    setKey(int key);
    void    init(int);
private:
    void    updateHead(t_coor&);
    lst _cors;
    int _pl;
    char _key;//w,a,s,d
    int _size_block;
    t_scr _rect;//struct for render texture
    bool _play;//flag for finish game
    void    crash();
    void    grow();
    int    getNumberSprite(int itr);
};

