// Name: Anja Sheppard
// NetID: AMS180001

#include "Customer.h"
#include "PreferredCustomerGold.h"

#ifndef PREFERREDCUSTOMERPLATINUM_H
#define PREFERREDCUSTOMERPLATINUM_H

class PreferredCustomerPlatinum : public Customer
{
    public:
        PreferredCustomerPlatinum ();
        PreferredCustomerPlatinum (std::string, std::string, std::string, float, float);
        ~PreferredCustomerPlatinum ();
        virtual float getExtra () { return bonusBucks; }
        virtual void setExtra (float val) { bonusBucks = val; }
    protected:
    private:
        float bonusBucks;
};

#endif // PREFERREDCUSTOMERPLATINUM_H
