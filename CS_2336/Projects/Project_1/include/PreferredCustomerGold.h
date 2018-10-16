// Name: Anja Sheppard
// NetID: AMS180001

#include "Customer.h"

#ifndef PREFERREDCUSTOMERGOLD_H
#define PREFERREDCUSTOMERGOLD_H


class PreferredCustomerGold : public Customer
{
    public:
        PreferredCustomerGold ();
        PreferredCustomerGold (std::string, std::string, std::string, float, unsigned int);
        virtual ~PreferredCustomerGold ();
        virtual float getExtra () { return discountPercentage; }
        virtual void setExtra (float val) { discountPercentage = val; }
    protected:
    private:
        float discountPercentage;
};

#endif // PREFERREDCUSTOMERGOLD_H
