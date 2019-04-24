// Homework 4
// Anja Sheppard AMS180001

#pragma once

#include <iostream>
#include <cassert>
 
using namespace std;

//Definition of the node

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type> *link;
};

template <class Type>
class LinkedListIterator
{
    public:
        LinkedListIterator ();
        LinkedListIterator (nodeType<Type> *ptr);
        Type operator* ();
        LinkedListIterator<Type> operator++ ();    
        bool operator== (const LinkedListIterator<Type>& right) const; 
        bool operator!= (const LinkedListIterator<Type>& right) const; 
        nodeType<Type> * getCurrent () {return this->current; }

    private:
        nodeType<Type> *current; //pointer to point to the current
};
