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
    void        setMap(int n);
    void    printMmap() const;
private:
    Mmap();
    Mmap(const Mmap &) = delete;
    Mmap(Mmap &&) = delete;
    Mmap &operator=(const Mmap &) = delete;
    Mmap &operator=(Mmap &&) = delete;
    ~Mmap();
//    static  int **& (_mmap);//[67] - height, [90]- weight
//    int** _mmap;
    int (*_mmap)[67][90];

};