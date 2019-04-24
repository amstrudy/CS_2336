// Homework 3B
// Anja Sheppard
// AMS180001

#pragma once

#include <iostream>
#include <fstream>

class FileFilter
{
    public:
        virtual void doFilter(std::ifstream &in, std::ofstream &out) = 0;
    protected:
    private:
};
