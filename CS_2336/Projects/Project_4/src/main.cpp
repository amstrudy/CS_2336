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
#include "Customer.h"
#include "Administrator.h"
#include "String.h"

#define USER_FILE "userdb.dat"
#define FILE_A_1 "A1.txt"
#define FILE_A_2 "A2.txt"
#define FILE_A_3 "A3.txt"

using namespace std;

void parseUsers (HashMap<String, User> *);
User * logIn (HashMap<String, User> *);
void menuSelectionCustomer (Customer *, Auditorium *, Auditorium *, Auditorium *);

int main ()
{
    HashMap<String, User> *h = new HashMap<String, User>();
    parseUsers(h);
    Auditorium *auditorium1 = new Auditorium(FILE_A_1);
    Auditorium *auditorium2 = new Auditorium(FILE_A_2);
    Auditorium *auditorium3 = new Auditorium(FILE_A_3);
    while (true)
    {
        User *user = logIn(h);
        while (user == nullptr)
        {
            cout << "You entered an invalid username/password combo too many times. Please try again." << endl;
            user = logIn(h);
        }
        if (user->getUserType() == CUSTOMER)
        {
            menuSelectionCustomer(dynamic_cast<Customer *>(user), auditorium1, auditorium2, auditorium3);
        }
        if (user->getUserType() == ADMIN)
        {
            break;
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
                User *newUser;
                if (username == "admin")
                {
                    newUser = new Administrator(username, password);
                }
                else
                {
                    newUser = new Customer(username, password);
                }
                h->put(newUser->getKey(), newUser);
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
    User *check;
    
    cout << "Welcome to the Ticket Reservation System for the Avengers 4! Please log in below.\nUsername: " << flush;
    cin >> username;
    while (invalidLogin && numTimesInvalid < 3)
    {
        cout << "Password: " << flush;
        cin >> password;
        if (username == "admin")
        {
            check = new Administrator(username, password);
            check->setUserType(ADMIN);
        }
        else
        {
            check = new Customer (username, password);
            check->setUserType(CUSTOMER);
        }
        if (h->get(check->getKey()) == nullptr)
        {
            cerr << "The username/password combo was not valid. Please try again!" << endl;
            numTimesInvalid++;
            invalidLogin = true;
        }
        else if (h->get(check->getKey())->getPassword() == password)
        {
            cout << "Welcome " << username << "!" << endl;
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
    return check;
}

void menuSelectionCustomer (Customer *customer, Auditorium *auditorium1, Auditorium *auditorium2, Auditorium *auditorium3)
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
