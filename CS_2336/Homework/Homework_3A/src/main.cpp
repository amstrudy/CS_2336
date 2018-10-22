// Homework 3A
// Anja Sheppard AMS180001

#include "MyArray.h"
#include "MyArray.cpp"

using namespace std;

int main ()
{
    MyArray<int>a(1);
    a[0] = 3;
    cout << a[0] << endl;
    MyArray<char>b(-3, -1);
    b[-1] = 'a';
    b[-2] = 'b';
    b[-3] = 'c';
    cout << b[-3] << endl;
    cout << b[-2] << endl;
    cout << b[-1] << endl;
    b[0] = 'd';
    return 0;
}
