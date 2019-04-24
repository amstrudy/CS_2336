// Homework 3B
// Anja Sheppard
// AMS180001

#pragma once

#include <iostream>
#include <fstream>
#include "FileFilter.h"

class Uppercase : FileFilter
{
    public:
        virtual void doFilter (std::ifstream &in, std::ofstream &out);
        char transform (char c);
    protected:
    private:
};
