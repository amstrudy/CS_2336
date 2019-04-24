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

class User
{
    public:
        User ();
        User (std::string, std::string, bool);
        ~User ();
        void addOrder (auditorium, Order *newOrder);
        friend std::ostream& operator<< (std::ostream& out, const User& c);
        void reserve (Auditorium *, Auditorium *, Auditorium *);
        void view ();
        void update (Auditorium *, Auditorium *, Auditorium *);
        void display ();
        void printReport (Auditorium *, Auditorium *, Auditorium *);
        void exitProgram (Auditorium *, Auditorium *, Auditorium *);
        void append (unsigned int listNum, Order *newOrder);
        void setOrdersList1Length (unsigned int var) { this->ordersList1Length = var; }
        unsigned int getOrdersList1Length () { return this->ordersList1Length; }
        std::string getUsername () { return this->username; }
        void setUsername (std::string var) { this->username = var; this->key = new String(this->username); }
        std::string getPassword () { return this->password; }
        void setPassword (std::string val) { this->password = val; }
        String * getKey () { return this->key; }
        void setIsAdmin (bool var) { this->isAdmin = var; }
        bool getIsAdmin () { return this->isAdmin; }
    protected:
    private:
        std::string username;
        std::string password;
        String *key;
        Order **ordersList1;
        Order **ordersList2;
        Order **ordersList3;
        unsigned int ordersList1Length;
        unsigned int ordersList2Length;
        unsigned int ordersList3Length;
        bool isAdmin;
};
