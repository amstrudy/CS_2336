// Project 4
// Anja Sheppard AMS180001

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "User.h"
#include "Order.h"
#include "String.h"
#include "Auditorium.h"

enum auditorium {A_ONE, A_TWO, A_THREE};

class Customer: public User
{
    public:
        Customer ();
        Customer (std::string, std::string);
        ~Customer ();
        void addOrder (auditorium, Order *newOrder);
        friend std::ostream& operator<< (std::ostream& out, const Customer& c);
        void reserve (Auditorium *, Auditorium *, Auditorium *);
        void view ();
        void update (Auditorium *, Auditorium *, Auditorium *);
        void display ();
    protected:
    private:
        Order **ordersList1;
        Order **ordersList2;
        Order **ordersList3;
        unsigned int ordersList1Length;
        unsigned int ordersList2Length;
        unsigned int ordersList3Length;
};
