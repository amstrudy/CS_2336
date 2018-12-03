// Project 4
// Anja Sheppard AMS180001

#pragma once

#include <string>

class String
{
    public:
        String ();
        String (std::string);
        ~String ();
        std::string getDatum () { return this->datum; };
        void setDatum (std::string var) { this->datum = var; }
        unsigned int hash ();
    protected:
    private:
        std::string datum;
};
