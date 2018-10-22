// Homework 3A
// Anja Sheppard AMS180001

#pragma once

#include <iostream>

template <class T>
class MyArray
{
    public:
        MyArray ();
        MyArray (unsigned int);
        MyArray (int, int);
        ~MyArray ();
        T& operator[] (int);
        const T& operator[] (int) const;
    protected:
    private:
        T *array;
        int indexStart = 0;
        unsigned int size;
};

