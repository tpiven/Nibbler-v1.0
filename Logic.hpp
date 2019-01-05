//
// Created by kmykhailenko on 31.12.18.
//
#pragma once
#include <map>
#include <list>
#include <tuple>

typedef struct s_coor{
    int y_dis;
    int x_dis;
    int y_arr;
    int x_arr;
}            t_coor;

typedef struct s_scr{
    int x;
    int y;
    int w;
    int h;
} t_scr;

using lst = std::list<t_coor>;

class Logic {
public:
    explicit Logic() noexcept;
    explicit Logic(int players) noexcept;
    ~Logic();
    void    move();
    bool    running() const;
    void    hook();
    void    setKey(int key);
    char    getkey() const;
private:
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

