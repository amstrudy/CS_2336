// Project 1: Disneyland Dining Rewards
// Name: Anja Sheppard
// NetID: AMS180001

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <typeinfo>
#include "Customer.h"
#include "PreferredCustomerGold.h"
#include "PreferredCustomerPlatinum.h"

#define FILENAME_REG "customer4.dat"
#define FILENAME_PREF "preferred4.dat"
#define FILENAME_ORDERS "orders4.dat"
#define PI 3.142

using namespace std;

enum customerType {REGULAR, GOLD, PLATINUM};

struct OrderData
{
    string customerID;
    customerType cType;
    char sizeC;
    string drinkType;
    float squareInchPrice;
    int quantity;
    bool valid;
};

void parseCustomerInformation (Customer ** &, size_t &);
void parsePreferredCustomerInformation (Customer ** &, size_t &);
void parseOrders (Customer ** &, Customer ** &, size_t &, size_t &);
void removeRegular (Customer ** &, Customer *, size_t);
void removeGold (Customer ** &, Customer *, size_t);
void addRegular (Customer ** &, Customer *, size_t);
void addGold (Customer ** &, PreferredCustomerGold *, size_t);
void addPlatinum (Customer ** &, PreferredCustomerPlatinum *, size_t);
OrderData validData (string, Customer ** &, Customer ** &, size_t, size_t);
float amountSpent (string, char, float, int);
void writeToFile (Customer ** &, Customer ** &, size_t, size_t);

int main()
{
    Customer **regularCustomers = new Customer*[0];
    Customer **preferredCustomers;
    size_t regLength = 0;
    size_t preferredLength = 0;
    parseCustomerInformation(regularCustomers, regLength);
    parsePreferredCustomerInformation(preferredCustomers, preferredLength);

    parseOrders(regularCustomers, preferredCustomers, regLength, preferredLength);

    writeToFile(regularCustomers, preferredCustomers, regLength, preferredLength);

    delete [] regularCustomers;

    return 0;
}

void parseCustomerInformation (Customer ** & regularCustomers, size_t &regLength)
{
    ifstream regularCustomerFile(FILENAME_REG);

    if (regularCustomerFile) // ensure file exists
    {
        string lineStr;

        while (getline(regularCustomerFile, lineStr)) // read in each line and add to array
        {
            if (lineStr.length() < 5) // probably a newline at the end, so exit
                return;
            string guestID, fName, lName;
            float amountSpent;
            istringstream iss(lineStr);
            iss >> guestID >> fName >> lName >> amountSpent;
            Customer *regularCustomer = new Customer;
            regularCustomer->setFName(fName);
            regularCustomer->setLName(lName);
            regularCustomer->setGuestID(guestID);
            regularCustomer->setAmountSpent(amountSpent);
            addRegular(regularCustomers, regularCustomer, regLength);
            regLength++;
        }
        regularCustomerFile.close();
    }
    else
    {
        cerr << "There was an error reading the regular file." << endl;
    }
}

void parsePreferredCustomerInformation (Customer ** & preferredCustomers, size_t &preferredLength)
{
    ifstream preferredCustomerFile(FILENAME_PREF);

    if (preferredCustomerFile) // ensure file exists
    {
        string lineStr;
        getline(preferredCustomerFile, lineStr);
        if (lineStr.length() < 5) // make sure file isn't empty
            return;
        preferredCustomers = new Customer*[0];
        do // get data from line and create gold or platinum customer depending on % sign
        {
            if (lineStr.length() < 5) // probably a newline at the end, so exit
                return;
            string guestID, fName, lName, extra;
            float amountSpent;
            istringstream iss(lineStr);
            iss >> guestID >> fName >> lName >> amountSpent >> extra;
            if (extra.back() == '%')
            {
                extra.pop_back();
                float discount = stof(extra);
                PreferredCustomerGold *preferredCustomer = new PreferredCustomerGold;
                preferredCustomer->setFName(fName);
                preferredCustomer->setLName(lName);
                preferredCustomer->setGuestID(guestID);
                preferredCustomer->setAmountSpent(amountSpent);
                preferredCustomer->setExtra(discount);
                addGold(preferredCustomers, preferredCustomer, preferredLength);
                preferredLength++;
            }
            else
            {
                float bucks = stof(extra);
                PreferredCustomerPlatinum *preferredCustomer = new PreferredCustomerPlatinum;
                preferredCustomer->setFName(fName);
                preferredCustomer->setLName(lName);
                preferredCustomer->setGuestID(guestID);
                preferredCustomer->setAmountSpent(amountSpent);
                preferredCustomer->setExtra(bucks);
                addPlatinum(preferredCustomers, preferredCustomer, preferredLength);
                preferredLength++;
            }
        } while (getline(preferredCustomerFile, lineStr));
        preferredCustomerFile.close();
    }
    else
    {
        cerr << "There was an error reading the preferred file." << endl;
    }
}

void addRegular (Customer ** & regulars, Customer *regular, size_t length) // TODO: delete??
{
    Customer **regulars2 = new Customer*[length+1]; // new enlarged array
    for (size_t i = 0; i < length; ++i)
    {
        regulars2[i] = new Customer;
        regulars2[i]->setFName(regulars[i]->getFName());
        regulars2[i]->setLName(regulars[i]->getLName());
        regulars2[i]->setGuestID(regulars[i]->getGuestID());
        regulars2[i]->setAmountSpent(regulars[i]->getAmountSpent());
    }
    regulars2[length] = regular;
    delete [] regulars; // no memory leaks!
    regulars = regulars2;
}

void addGold (Customer **  & preferreds, PreferredCustomerGold *gold, size_t length)
{
    if (length == 0) // if preferred array doesn't exist yet, allocate memory
    {
        preferreds = new Customer*[0];
    }
    Customer **preferreds2 = new Customer*[length+1];
    for (size_t i = 0; i < length; ++i) // transfer all data
    {
        preferreds2[i] = new Customer;
        preferreds2[i]->setFName(preferreds[i]->getFName());
        preferreds2[i]->setLName(preferreds[i]->getLName());
        preferreds2[i]->setGuestID(preferreds[i]->getGuestID());
        preferreds2[i]->setAmountSpent(preferreds[i]->getAmountSpent());
        preferreds2[i]->setExtra(preferreds[i]->getExtra());

    }
    preferreds2[length] = gold;

    delete [] preferreds;
    preferreds = preferreds2;
}

void addPlatinum (Customer ** & preferreds, PreferredCustomerPlatinum *platinum, size_t length)
{
    if (length == 0) // if preferred array doesn't exist yet, allocate memory
    {
        preferreds = new Customer*[0];
    }
    Customer **preferreds2 = new Customer*[length+1];
    for (size_t i = 0; i < length; ++i)
    {
        preferreds2[i] = new Customer;
        preferreds2[i]->setFName(preferreds[i]->getFName());
        preferreds2[i]->setLName(preferreds[i]->getLName());
        preferreds2[i]->setGuestID(preferreds[i]->getGuestID());
        preferreds2[i]->setAmountSpent(preferreds[i]->getAmountSpent());
        preferreds2[i]->setExtra(preferreds[i]->getExtra());
    }
    preferreds2[length] = platinum;
    delete [] preferreds;
    preferreds = preferreds2;
}

void removeRegular (Customer ** & regulars, Customer *regular, size_t length)
{
    if (length == 0)
    {
        cerr << "Can't remove something from an empty array. Nice try." << endl;
        return;
    }
    Customer **regulars2 = new Customer*[length-1];
    int index = -1; // marker if item isn't found

    for (size_t i = 0; i < length; ++i)
    {
        if (regulars[i]->getGuestID() == regular->getGuestID())
            index = (int)i;
    }
    if (index == -1)
    {
        cerr << "The object wasn't found while trying to remove it." << endl;
        return;
    }

    for (int i = 0; i < (int)length; ++i)
    {
        if (i != index) // skip over index we want to remove
        {
            if (index == -1)
            {
                regulars2[i-1] = new Customer;
                regulars2[i-1]->setFName(regulars[i]->getFName());
                regulars2[i-1]->setLName(regulars[i]->getLName());
                regulars2[i-1]->setGuestID(regulars[i]->getGuestID());
                regulars2[i-1]->setAmountSpent(regulars[i]->getAmountSpent());
            }
            else
            {
                regulars2[i] = new Customer;
                regulars2[i]->setFName(regulars[i]->getFName());
                regulars2[i]->setLName(regulars[i]->getLName());
                regulars2[i]->setGuestID(regulars[i]->getGuestID());
                regulars2[i]->setAmountSpent(regulars[i]->getAmountSpent());
            }
        }
        else
        {
            index = -1; // void now
        }
    }

    delete [] regulars;
    regulars = regulars2;
}

void removeGold (Customer ** & preferreds, Customer *gold, size_t length)
{
    if (length == 0)
    {
        cerr << "Can't remove something from an empty array. Nice try." << endl;
        return;
    }
    Customer **preferreds2 = new Customer*[length-1];
    int index = -1; // marker if item isn't found
    for (size_t i = 0; i < length; ++i)
    {
        if (preferreds[i]->getGuestID() == gold->getGuestID())
            index = (int)i;
    }
    if (index == -1)
    {
        cerr << "The object wasn't found while trying to remove it." << endl;
        return;
    }
    for (size_t i = 0; i < length; ++i)
    {
        if ((int)i != index) // skip over index we want to remove
        {
            if (index == -1)
            {
                preferreds2[i-1] = new Customer;
                preferreds2[i-1]->setFName(preferreds[i]->getFName());
                preferreds2[i-1]->setLName(preferreds[i]->getLName());
                preferreds2[i-1]->setGuestID(preferreds[i]->getGuestID());
                preferreds2[i-1]->setAmountSpent(preferreds[i]->getAmountSpent());
                preferreds2[i-1]->setExtra(preferreds[i]->getExtra());
            }
            else
            {
                preferreds2[i] = new Customer;
                preferreds2[i]->setFName(preferreds[i]->getFName());
                preferreds2[i]->setLName(preferreds[i]->getLName());
                preferreds2[i]->setGuestID(preferreds[i]->getGuestID());
                preferreds2[i]->setAmountSpent(preferreds[i]->getAmountSpent());
                preferreds2[i]->setExtra(preferreds[i]->getExtra());
            }
        }
        else
        {
            index = -1; // void now
        }
    }
    delete [] preferreds;
    preferreds = preferreds2;
}

void parseOrders (Customer ** & regularCustomers, Customer ** & preferredCustomers, size_t &regLength, size_t &preferredLength)
{
    ifstream ordersFile(FILENAME_ORDERS);

    if (ordersFile)
    {
        string lineStr;

        while (getline(ordersFile, lineStr))
        {
            OrderData order = validData(lineStr, regularCustomers, preferredCustomers, regLength, preferredLength);
            if (order.valid == true)
            {
                // find customer from ID (this is done this way to ensure the object type is specific)
                Customer *customer;
                if (order.cType == REGULAR)
                {
                    for (size_t i = 0; i < regLength; ++i)
                    {
                        if (regularCustomers[i]->getGuestID() == order.customerID)
                            customer = regularCustomers[i];
                    }
                }
                else if (order.cType == GOLD)
                {
                    for (size_t i = 0; i < preferredLength; ++i)
                    {
                        if (preferredCustomers[i]->getGuestID() == order.customerID)
                            customer = preferredCustomers[i];
                    }
                }
                else
                {
                    for (size_t i = 0; i < preferredLength; ++i)
                    {
                        if (preferredCustomers[i]->getGuestID() == order.customerID)
                            customer = preferredCustomers[i];
                    }
                }

                float justSpent = amountSpent(order.drinkType, order.sizeC, order.squareInchPrice, order.quantity);
                double totalSpent = customer->getAmountSpent() + justSpent;
                // REGULAR
                if (order.cType == REGULAR)
                {
                    if (totalSpent < 50) // regular
                    {
                        customer->setAmountSpent(customer->getAmountSpent() + justSpent);
                    }
                    else if (totalSpent >= 50)
                    {
                        float discount; // %
                        if (totalSpent >= 50)  // qualifies for gold
                        {
                            discount = 5;
                            totalSpent = customer->getAmountSpent() + (justSpent * ((100-discount)/100.0));
                            if (totalSpent >= 100)
                            {
                                discount = 10;
                                totalSpent = customer->getAmountSpent() + (justSpent * ((100-discount)/100.0));
                                if (totalSpent >= 150)
                                {
                                    discount = 15;
                                    totalSpent = customer->getAmountSpent() + (justSpent * ((100-discount)/100.0));
                                }
                            }
                        }

                        PreferredCustomerGold *newGold = new PreferredCustomerGold; // upgrade regular to gold
                        newGold->setFName(customer->getFName());
                        newGold->setLName(customer->getLName());
                        newGold->setGuestID(customer->getGuestID());
                        newGold->setAmountSpent((float)totalSpent);
                        customer->setAmountSpent((float)totalSpent);
                        newGold->setExtra(discount);
                        addGold(preferredCustomers, newGold, preferredLength);
                        preferredLength++;
                        removeRegular(regularCustomers, customer, regLength);
                        regLength--;
                    }
                    if (totalSpent >= 200) // qualifies for platinum
                    {
                        float bucks = (float)(int)(totalSpent - 200) / 10;
                        PreferredCustomerPlatinum *newPlatinum = new PreferredCustomerPlatinum; // upgrade regular->gold to platinum
                        newPlatinum->setFName(customer->getFName());
                        newPlatinum->setLName(customer->getLName());
                        newPlatinum->setGuestID(customer->getGuestID());
                        newPlatinum->setAmountSpent((float)totalSpent);
                        customer->setAmountSpent((float)totalSpent);
                        newPlatinum->setExtra(bucks);
                        removeGold(preferredCustomers, customer, preferredLength);
                        preferredLength--;
                        addPlatinum(preferredCustomers, newPlatinum, preferredLength);
                        preferredLength++;
                    }
                }
                // GOLD
                else if (order.cType == GOLD)
                {
                    if (totalSpent < 100)
                    {
                        customer->setAmountSpent((float)totalSpent);
                    }
                    else if (totalSpent >= 100) // apply discounts and check qualifications
                    {
                        unsigned int discount;
                        if (totalSpent >= 100)
                        {
                            discount = 10;
                            totalSpent = customer->getAmountSpent() + (justSpent * ((100-discount)/100.0));
                            if (totalSpent >= 150)
                            {
                                discount = 15;
                                totalSpent = customer->getAmountSpent() + (justSpent * ((100-discount)/100.0));
                            }
                            customer->setExtra((float)discount);
                        }
                        if (totalSpent < 200)
                            customer->setAmountSpent((float)totalSpent);
                    }
                    if (totalSpent >= 200) // qualifies for platinum
                    {
                        float bucks = (float)((int)totalSpent - 200) / 10;
                        PreferredCustomerPlatinum *newPlatinum = new PreferredCustomerPlatinum;
                        newPlatinum->setFName(customer->getFName());
                        newPlatinum->setLName(customer->getLName());
                        newPlatinum->setGuestID(customer->getGuestID());
                        newPlatinum->setAmountSpent((float)totalSpent);
                        customer->setAmountSpent((float)totalSpent);
                        newPlatinum->setExtra(bucks);
                        removeGold(preferredCustomers, customer, preferredLength); // switch gold for platinum
                        preferredLength--;
                        addPlatinum(preferredCustomers, newPlatinum, preferredLength);
                        preferredLength++;
                    }
                }
                // PLATINUM
                else
                {
                    if (justSpent < customer->getExtra()) // if there are more bonus bucks available than needed
                    {
                        totalSpent -= (int)justSpent;
                        customer->setAmountSpent((float)totalSpent);
                        customer->setExtra(customer->getExtra() - (int)justSpent);
                    }
                    else // otherwise spend all bonus bucks and re-calculate
                    {
                        totalSpent -= customer->getExtra();
                        customer->setAmountSpent((float)totalSpent);
                        customer->setExtra((float)(((int)totalSpent - 200) / 10));
                    }
                }
            }
        }
    }
    else
    {
        cerr << "There was an error reading the orders file." << endl;
    }
}

OrderData validData (string lineStr, Customer ** & regularCustomers, Customer ** & preferredCustomers, size_t regLength, size_t preferredLength)
{
    OrderData order;
    order.valid = false;
    string customerID, sizeC, drinkType, squareInchPrice;

    istringstream checkStream(lineStr);
    istringstream stream(lineStr);
    int numWords = (int)distance(istream_iterator<string>(checkStream), istream_iterator<string>()); // count the number of words in lineStr
    if (numWords != 5)
    {
        return order;
    }

    // check that customerID (guestID) is valid
    stream >> customerID;
    bool custExists = false;
    for (size_t i = 0; i < regLength; ++i)
    {
        if (regularCustomers[i]->getGuestID() == customerID)
        {
            custExists = true;
            order.customerID = customerID;
            order.cType = REGULAR;
        }
    }
    if (custExists == false) // customer wasn't found in regularCustomers
    {
        for (size_t i = 0; i < preferredLength; ++i)
        {
            if (preferredCustomers[i]->getGuestID() == customerID)
            {
                custExists = true;
                order.customerID = customerID;
                if (preferredCustomers[i]->getAmountSpent() >= 200)
                    order.cType = PLATINUM;
                else
                    order.cType = GOLD;
            }
        }
    }
    if (custExists == false) // customer not found in either array
    {
        return order;
    }

    // check that size is either S, M, L
    stream >> sizeC;
    if (sizeC == "S" || sizeC == "M" || sizeC == "L")
    {
        order.sizeC = sizeC[0];
    }
    else
    {
        return order;
    }

    // check that the drinkType is either soda, tea, or punch
    stream >> drinkType;
    if (drinkType == "soda" || drinkType == "tea" || drinkType == "punch")
    {
        order.drinkType = drinkType;
    }
    else
    {
        return order;
    }

    // check the square inch price is correct
    string priceStr;
    stream >> priceStr;
    if (!(order.squareInchPrice = stof(priceStr)) || order.squareInchPrice < 0 || (priceStr.length() - priceStr.find_first_of("."))!= 3) // failed because it wasn't a string or was negative or didn't have 2 decimals
    {
        if (order.squareInchPrice != 0) // zero is a valid answer regardless
            return order;
    }

    // check the quantity is valid
    stream >> order.quantity;
    if (stream.fail() || order.quantity < 0)
    {
        return order;
    }

    order.valid = true; // all checks are passed, so data is valid
    return order;
}

float amountSpent (string drinkType, char sizeC, float squareInchPrice, int quantity)
{
    const int SMALL_SIZE = 12; // oz
    const int MEDIUM_SIZE = 20; // oz
    const int LARGE_SIZE = 32; // oz
    const double SODA_PRICE = 0.2; // dollars per oz
    const double TEA_PRICE = 0.12; // dolalrs per oz
    const double PUNCH_PRICE = 0.15; // dollars per oz
    const double SMALL_SA = (PI * 2) * 4.5; // in^2
    const double MEDIUM_SA = (PI * 2.25) * 5.75; // in^2
    const double LARGE_SA = (PI * 2.75) * 7; // in^2

    double price;

    if (drinkType == "soda")
    {
        if (sizeC == 'S')
            price = SMALL_SIZE * SODA_PRICE;
        else if (sizeC == 'M')
            price = MEDIUM_SIZE * SODA_PRICE;
        else
            price = LARGE_SIZE * SODA_PRICE;
    }
    else if (drinkType == "tea")
    {
        if (sizeC == 'S')
            price = SMALL_SIZE * TEA_PRICE;
        else if (sizeC == 'M')
            price = MEDIUM_SIZE * TEA_PRICE;
        else
            price = LARGE_SIZE * TEA_PRICE;
    }
    else
    {
        if (sizeC == 'S')
            price = SMALL_SIZE * PUNCH_PRICE;
        else if (sizeC == 'M')
            price = MEDIUM_SIZE * PUNCH_PRICE;
        else
            price = LARGE_SIZE * PUNCH_PRICE;
    }

    if (squareInchPrice != 0) // add personalization price
    {
        if (sizeC == 'S')
            price += SMALL_SA * squareInchPrice;
        else if (sizeC == 'M')
            price += MEDIUM_SA * squareInchPrice;
        else
            price += LARGE_SA * squareInchPrice;
    }

    price *= quantity;

    return (float)price;
}

void writeToFile (Customer ** & regularCustomers, Customer ** & preferredCustomers, size_t regLength, size_t preferredLength)
{
    ofstream out(FILENAME_REG); // send outputs to respective files in same input format

    if (out)
    {
        for (size_t i = 0; i < regLength; ++i)
        {
            out << regularCustomers[i]->getGuestID() << " " << regularCustomers[i]->getFName() << " " << regularCustomers[i]->getLName() << " " << fixed << setprecision(2) << regularCustomers[i]->getAmountSpent() << endl;
        }

        out.close();
    }

    out.open(FILENAME_PREF);

    if (out)
    {
        for (size_t i = 0; i < preferredLength; ++i)
        {
            out << preferredCustomers[i]->getGuestID() << " " << preferredCustomers[i]->getFName() << " " << preferredCustomers[i]->getLName() << " " << fixed << setprecision(2) << preferredCustomers[i]->getAmountSpent() << setprecision(0) << " " << preferredCustomers[i]->getExtra();
            if (preferredCustomers[i]->getAmountSpent() < 200) //  decide whether to print percent for discount
                out << "%";
            out << endl;
        }

        out.close();
    }
}
