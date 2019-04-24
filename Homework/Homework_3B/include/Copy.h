// Homework 3B
// Anja Sheppard
// AMS180001

#pragma once

#include <iostream>
#include <fstream>
#include "FileFilter.h"

class Copy : FileFilter
{
    public:
        virtual void doFilter (std::ifstream &in, std::ofstream &out);
    protected:
    private:
};
