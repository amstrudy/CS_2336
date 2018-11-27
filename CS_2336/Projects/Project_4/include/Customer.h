// Project 4
// Anja Sheppard AMS180001

#include <string>
#include "User.h"
#include "Order.h"

enum auditorium {A_ONE, A_TWO, A_THREE};

class Customer: public User
{
    public:
        Customer ();
        Customer ();
        ~Customer ();
        void addOrder (auditorium, Order *newOrder);
    protected:
    private:
        Orders *ordersList1;
        Orders *ordersList2;
        Orders *ordersList3;
};
