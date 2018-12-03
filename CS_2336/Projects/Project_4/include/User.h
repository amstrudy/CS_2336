// Project 4
// Anja Sheppard AMS180001

#pragma once

#include <string>
#include "String.h"

enum userType {CUSTOMER, ADMIN};

class User
{
    public:
        User ();
        User (std::string, std::string);
        virtual ~User ();
        std::string getUsername () { return this->username; }
        void setUsername (std::string var) { this->username = var; this->key = new String(this->username); }
        std::string getPassword () { return this->password; }
        void setPassword (std::string val) { this->password = val; }
        String * getKey () { return this->key; }
        userType getUserType () { return this->USER_TYPE; }
        void setUserType (userType val) { this->USER_TYPE = val; }
    protected:
        std::string username;
        std::string password;
        String *key;
        userType USER_TYPE;
    private:
};
