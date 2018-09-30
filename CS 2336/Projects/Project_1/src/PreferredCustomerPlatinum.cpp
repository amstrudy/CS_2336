// Name: Anja Sheppard
// NetID: AMS180001

#include "Customer.h"
#include "PreferredCustomerPlatinum.h"

PreferredCustomerPlatinum::PreferredCustomerPlatinum()
{
    //ctor
}

PreferredCustomerPlatinum::PreferredCustomerPlatinum (std::string f, std::string l, std::string id, float spent, float bucks)
{
    bonusBucks = bucks;
    Customer(f, l, id, spent);
}

PreferredCustomerPlatinum::~PreferredCustomerPlatinum()
{
    //dtor
}
