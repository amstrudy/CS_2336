// Homework 7
// Anja Sheppard AMS180001

#include <string>
#include <math.h>
#include <iostream>
#include "HashMap.h"

using namespace std;

int main ()
{
    HashMap *hm = new HashMap(9);

    hm->insert(184);
    hm->insert(243);
    hm->insert(123);
    hm->insert(985);
    hm->insert(345);
    hm->insert(666);
    hm->insert(677);
    hm->insert(434);
    hm->insert(334);
    hm->insert(998);
    hm->print();
    
    return 0;
}
