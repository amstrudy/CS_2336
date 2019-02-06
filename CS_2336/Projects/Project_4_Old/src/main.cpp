// Project 4
// Anja Sheppard AMS180001

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "HashMap.h"
#include "HashMap.cpp"
#include "User.h"
#include "String.h"

#define USER_FILE "userdb.dat"
#define FILE_A_1 "A1.txt"
#define FILE_A_2 "A2.txt"
#define FILE_A_3 "A3.txt"

using namespace std;

void parseUsers (HashMap<String, User> *);
User * logIn (HashMap<String, User> *);
void menuSelectionCustomer (User *, Auditorium *, Auditorium *, Auditorium *);
void menuSelectionAdministrator (User *, Auditorium *, Auditorium *, Auditorium *);

int main ()
{
    HashMap<String, User> *h = new HashMap<String, User>();
    parseUsers(h);
    Auditorium *auditorium1 = new Auditorium(FILE_A_1);
    Auditorium *auditorium2 = new Auditorium(FILE_A_2);
    Auditorium *auditorium3 = new Auditorium(FILE_A_3);
    while (true)
    {
        User *u = logIn(h);
        while (u == nullptr)
        {
            cout << "You entered an invalid username/password combination too many times. Please try again." << endl;
            u = logIn(h);
        }
        if (u->getIsAdmin() == false)
        {
            menuSelectionCustomer(u, auditorium1, auditorium2, auditorium3);
        }
        else if (u->getIsAdmin() == true)
        {
            menuSelectionAdministrator(u, auditorium1, auditorium2, auditorium3);
        }
    }
    return 0;
}

void parseUsers (HashMap<String, User> *h)
{
    ifstream in(USER_FILE);
    if (in)
    {
        string lineStr;
        while (getline(in, lineStr))
        {
            if (lineStr.length() > 2) // make sure no newlines
            {
                istringstream iss(lineStr);
                string username, password;
                iss >> username >> password;
                if (username == "admin")
                {
                    User *newUser = new User(username, password, true);
                    h->put(newUser->getKey(), newUser);
                }
                else
                {
                    User *newUser = new User(username, password, false);
                    h->put(newUser->getKey(), newUser);
                }
            }
        }
    }
    else
    {
        std::cerr << "The user file does not exist. The program will now exit." << std::endl;
        exit(1);
    }
}

User * logIn (HashMap<String, User> *h)
{
    bool invalidLogin = true;
    unsigned int numTimesInvalid = 0;
    string username, password;
    User *u;
    
    cout << "Welcome to the Ticket Reservation System for the Avengers 4! Please log in below.\nUsername: " << flush;
    cin >> username;
    while (invalidLogin && numTimesInvalid < 3)
    {
        cout << "Password: " << flush;
        cin >> password;
        String *k = new String(username);
        if (h->get(k) == nullptr)
        {
            cerr << "The username/password combo was not valid. Please try again!" << endl;
            numTimesInvalid++;
            invalidLogin = true;
        }
        else if (h->get(k)->getPassword() == password)
        {
            cout << "Welcome " << username << "!" << endl;
            u = h->get(k);
            invalidLogin = false;
        }
        else
        {
            cerr << "The username/password combo was not valid. Please try again!" << endl;
            numTimesInvalid++;
            invalidLogin = true;
        }
    }
    if (numTimesInvalid >= 3) return nullptr;
    return u;
}

void menuSelectionCustomer (User *customer, Auditorium *auditorium1, Auditorium *auditorium2, Auditorium *auditorium3)
{
    string menuSelectionS;
    unsigned int menuSelection;
    while (true)
    {    
        cout << "\nMAIN MENU\n\n1. Reserve Seats\n2. View Orders\n3. Update Orders\n4. Display Receipt\n5. Log out\n\n" << flush;
        while (true)
        {
            cout << "What would you like to do (1-5)? " << flush;
            cin >> menuSelectionS;
            if (menuSelectionS.length() == 1 && isdigit(menuSelectionS[0]) && (menuSelectionS[0] == '1' || menuSelectionS[0] == '2' || menuSelectionS[0] == '3' || menuSelectionS[0] == '4' || menuSelectionS[0] == '5'))
            {
                menuSelection = stoi(menuSelectionS);
                break;
            }
            else
            {
                cerr << "Invalid choice. Please try again." << endl;
            }
        }
    
        // RESERVE
        if (menuSelection == 1)
        {
            customer->reserve(auditorium1, auditorium2, auditorium3);
        }

        // VIEW ORDERS
        else if (menuSelection == 2)
        {
            customer->view();
        }

        // UPDATE ORDERS
        else if (menuSelection == 3)
        {
            customer->update(auditorium1, auditorium2, auditorium3);
        }

        // DISPLAY RECEIPT
        else if (menuSelection == 4)
        {
            customer->display();
        }

        // LOG OUT
        else if (menuSelection == 5)
        {
            return;
        }
    }
}

void menuSelectionAdministrator (User *administrator, Auditorium *auditorium1, Auditorium *auditorium2, Auditorium *auditorium3)
{
    string menuSelectionS;
    unsigned int menuSelection;
    while (true)
    {    
        cout << "\nMAIN MENU\n\n1. Print Report\n2. Log out\n3. Exit\n\n" << flush;
        while (true)
        {
            cout << "What would you like to do (1-3)? " << flush;
            cin >> menuSelectionS;
            if (menuSelectionS.length() == 1 && isdigit(menuSelectionS[0]) && (menuSelectionS[0] == '1' || menuSelectionS[0] == '2' || menuSelectionS[0] == '3'))
            {
                menuSelection = stoi(menuSelectionS);
                break;
            }
            else
            {
                cerr << "Invalid choice. Please try again." << endl;
            }
        }
    
        // PRINT REPORT
        if (menuSelection == 1)
        {
            administrator->printReport(auditorium1, auditorium2, auditorium3);
        }

        // LOG OUT
        else if (menuSelection == 2)
        {
            return;
        }

        // EXIT
        else if (menuSelection == 3)
        {
            administrator->exitProgram(auditorium1, auditorium2, auditorium3);
        }
    }
}
