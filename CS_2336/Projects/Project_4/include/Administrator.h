// Project 4
// Anja Sheppard AMS180001

#pragma once

#include <string>
#include "User.h"
#include "Auditorium.h"

class Administrator : public User
{
    public:
        Administrator ();
        Administrator (std::string, std::string);
        ~Administrator ();
        void printReport (Auditorium **);
        void exit ();
    protected:
    private:
};
