// Homework 3B
// Anja Sheppard
// AMS180001

#pragma once

#include <iostream>
#include <fstream>
#include "FileFilter.h"

class Encryption : FileFilter
{
    public:
        Encryption () { key = 5; } // default is 5
        Encryption (int k) { key = k; }
        virtual void doFilter (std::ifstream &in, std::ofstream &out);
        int getKey () { return key; }
    protected:
    private:
        int key; // modifies asci value of char
};
