// Name: Anja Sheppard
// NetID: AMS180001

#include "Customer.h"
#include "PreferredCustomerGold.h"

PreferredCustomerGold::PreferredCustomerGold ()
{

}

PreferredCustomerGold::PreferredCustomerGold (std::string f, std::string l, std::string id, float spent, unsigned int percentage)
{
    discountPercentage = percentage;
    Customer(f, l, id, spent);
}

PreferredCustomerGold::~PreferredCustomerGold ()
{

}
