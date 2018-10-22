// Homework 4
// Anja Sheppard AMS180001

#ifndef H_LinkedListType
#define H_LinkedListType
   
#include <iostream>
#include <cassert>
#include"LinkedListIterator.h"
 
using namespace std;

template <class Type>
class LinkedListType
{
    public:
        LinkedListType (); 
        LinkedListType (const LinkedListType<Type>& otherList); 
        ~LinkedListType ();   
        void initializeList (); 
        bool isEmptyList () const;
        void print () const;
        int length () const;
        void destroyList ();
        Type front () const; 
        Type back () const; 
        bool search (const Type& searchItem) const;
        void insertFirst (const Type& newItem);
        void insertLast (const Type& newItem);
        void deleteNode (const Type& deleteItem);
        LinkedListIterator<Type> begin ();
        LinkedListIterator<Type> end ();
        const LinkedListType<Type>& operator= (const LinkedListType<Type>&);  
        Type& operator[] (const int&);  
        const LinkedListType<Type>& operator-= (int);  
    protected:
        int count;   //variable to store the number of 
                 //elements in the list
        nodeType<Type> *first; //pointer to the first node of the list
        nodeType<Type> *last;  //pointer to the last node of the list
    private: 
        void copyList (const LinkedListType<Type>& otherList); 
};

#endif
