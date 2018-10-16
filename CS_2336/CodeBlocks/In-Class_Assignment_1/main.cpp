#include <iostream>
#include "NumDays.h"

using namespace std;

int main()
{
    NumDays nd(10); // init with 10 hours
    NumDays nd2(nd);
    nd.setDays(2);
    cout << "Addition: " << (nd + nd2) << endl;
    cout << "Subtraction: " << (nd - nd2) << endl;
    cout << "Prefix: " << ++nd;
    cout << "Postfix: " << nd++ << nd;
    cout << "Less than? " << (nd < nd2) << endl;
    cout << "Greater than? " << (nd > nd2) << endl;
    cout << "Days of obj1: " << nd.getDays() << endl;
    cout << "Days of obj2: " << nd2.getDays() << endl;

    return 0;
}
