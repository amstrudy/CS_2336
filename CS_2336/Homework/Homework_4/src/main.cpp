// Homework 4
// Anja Sheppard AMS180001

#include <iostream>
#include "LinkedListType.h"
#include "LinkedListType.cpp"

using namespace std;

int main ()
{
    LinkedListType<int> *ll = new LinkedListType<int>();
    ll->insertFirst(0);
    ll->insertFirst(3);
    ll->insertFirst(4);
    cout << (*ll)[0] << endl;
    cout << (*ll)[1] << endl;
    cout << (*ll)[2] << endl;
    (*ll)-= 0;
    cout << (*ll)[0] << endl;
    cout << (*ll)[3] << endl;
    return 0;
}
