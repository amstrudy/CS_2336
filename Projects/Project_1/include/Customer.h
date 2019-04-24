// Name: Anja Sheppard
// NetID: AMS180001

#include <iostream>

#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer
{
    public:
        Customer ();
        Customer (std::string, std::string, std::string, float);
        ~Customer ();
        Customer (const Customer& other);
        std::string getFName () { return fName; }
        void setFName (std::string val) { fName = val; }
        std::string getLName () { return lName; }
        void setLName (std::string val) { lName = val; }
        std::string getGuestID () { return guestID; }
        void setGuestID (std::string val) { guestID = val; }
        float getAmountSpent () { return amountSpent; }
        void setAmountSpent (float val) { amountSpent = val; }
        virtual float getExtra () { return extra; }
        virtual void setExtra (float val) { extra = val; }
    protected:
    private:
        std::string fName;
        std::string lName;
        std::string guestID;
        float amountSpent;
        float extra;
};

#endif // CUSTOMER_H
