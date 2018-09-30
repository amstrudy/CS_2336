// Name: Anja Sheppard
// NetID: AMS180001

#include "Customer.h"

Customer::Customer()
{
    //ctor
}

Customer::Customer (std::string f, std::string l, std::string id, float spent) : fName(f), lName(l), guestID(id), amountSpent(spent)
{

}

Customer::~Customer()
{
    //dtor
}

Customer::Customer(const Customer& other)
{
    fName = other.fName;
    lName = other.lName;
    guestID = other.guestID;
    amountSpent = other.amountSpent;
}
