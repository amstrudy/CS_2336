// Project 4
// Anja Sheppard AMS180001

#include <string>

class User
{
    public:
        virtual User () = 0;
        virtual ~User ();
        string getUsername () { return this->username; }
        void setUsername (string val) { this->username = val; }
        string getPassword () { return this->password; }
        void setPassword (string val) { this->password = val; }
    protected:
        string username;
        string password;
    private:
};
