//
// Created by Tetiana PIVEN on 2019-01-27.
//

#pragma once

#include <chrono>
#include "header.h"

class Interface {
public:
    Interface() noexcept;
    ~Interface();
    void initInterface();
    void changeTimeAndScore();
    void setScore(int plus);
    void restart();
private:
    int score;
    int time;
    std::chrono::time_point<std::chrono::system_clock> start;


};