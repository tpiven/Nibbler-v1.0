//
// Created by Kostiantyn MYKHAILENKO on 1/6/19.
//

#pragma once

//typedef std::chrono::duration<float, std::ratio<1>> duration;

typedef struct s_scr{
    int x;
    int y;
    int w;
    int h;
} t_scr;

typedef struct s_coor{
    int y_dis;
    int x_dis;
    int y_arr;
    int x_arr;
    bool inPortal;
}            t_coor;