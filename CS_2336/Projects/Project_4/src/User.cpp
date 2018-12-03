// Project 4
// Anja Sheppard AMS180001

#include "User.h"
#include <iostream>

User::User ()
{
    this->username = "";
    this->password = "";
    this->key = new String(this->username);
}

User::User (std::string username, std::string password)
{
    this->username = username;
    this->password = password;
    this->key = new String(this->username);
}

User::~User ()
{
    delete this->key;
}
