//
// Created by kmykhailenko on 31.12.18.
#pragma once

#include <vector>
#include <iostream>

class Mmap{
public:
    static Mmap & getInstance();
    void        setValueInMap(int val, const int y, const int x);
    int         getValueFromMap(const int y, const int x) const;
    std::pair<int, int>  getYXmap() const;
    void    printMmap() const;
private:
    static int _x_start;//start x on screen
    static int _y_start;//start y on screen
    Mmap();
    Mmap(const Mmap &) = delete;
    Mmap(Mmap &&) = delete;
    Mmap &operator=(const Mmap &) = delete;
    Mmap &operator=(Mmap &&) = delete;
    ~Mmap();
    static int _mmap[67][90];//[67] - height, [90]- weight
};