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
    bool    runningGame() const;
    void    setKey(int key);
    int     getkey() const;
    void    init(int);
    void    restart();
private:
    lst _cors;
    lst _corsCopy;
    int _pl;
    char _key;//w,a,s,d
    int _size_block;
    t_scr _rect;//struct for render texture
    t_scr _rectCopy;
    bool _playGame;//flag for finish game
    void    updateHead(t_coor&);
    void    crash();
    void    grow();
    int    getNumberSprite(int itr);
};

