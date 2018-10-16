// Homework 3B
// Anja Sheppard
// AMS180001

#include <iostream>
#include <fstream>
#include "Encryption.h"
#include "Uppercase.h"
#include "Copy.h"

using namespace std;

int main ()
{
    ifstream in;
    ofstream out;
    Encryption *e = new Encryption();
    e->doFilter(in, out);
    Uppercase *u = new Uppercase();
    u->doFilter(in, out);
    Copy *c = new Copy();
    c->doFilter(in, out);
    
    return 0;
}
