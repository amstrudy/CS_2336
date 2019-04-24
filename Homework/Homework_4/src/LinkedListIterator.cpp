// Homework 4
// Anja Sheppard AMS180001

#include <iostream>
#include "LinkedListIterator.h"

template <class Type>
LinkedListIterator<Type>::LinkedListIterator ()
{
    current = nullptr;
}

template <class Type>
LinkedListIterator<Type>::LinkedListIterator (nodeType<Type> *ptr)
{
    current = ptr;
}

template <class Type>
Type LinkedListIterator<Type>::operator* ()
{
    return current->info;
}

template <class Type>
LinkedListIterator<Type> LinkedListIterator<Type>::operator++ ()   
{
    current = current->link;

    return *this;
}

template <class Type>
bool LinkedListIterator<Type>::operator== (const LinkedListIterator<Type>& right) const
{
    return (current == right.current);
}

template <class Type>
bool LinkedListIterator<Type>::operator!= (const LinkedListIterator<Type>& right) const
{    
    return (current != right.current);
}
