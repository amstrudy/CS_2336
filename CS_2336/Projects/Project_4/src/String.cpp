// Project 4
// Anja Sheppard AMS180001

#include "String.h"

String::String ()
{
    this->datum = "";
}

String::String (std::string s)
{
    this->datum = s;
}

String::~String () {}

unsigned int String::hash ()
{
    unsigned int hash = 7;
    for (size_t i = 0; i < this->datum.length(); ++i)
    {
        hash += hash * 31 + this->datum[i];
    }
    return hash;
}
