// Homework 4
// Anja Sheppard AMS180001

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "LinkedListIterator.h"
#include "LinkedListIterator.cpp"
#include "LinkedListType.h"

template <class Type>
LinkedListType<Type>::LinkedListType ()
{
    first = nullptr;
    last = nullptr;
    count = 0;
}

template <class Type>
LinkedListType<Type>::LinkedListType (const LinkedListType<Type>& otherList)
{
    first = nullptr;
    copyList(otherList);
}

template <class Type>
LinkedListType<Type>::~LinkedListType () //destructor
{
   destroyList();
}

template <class Type>
void LinkedListType<Type>::initializeList ()
{
	destroyList(); //if the list has any nodes, delete them
}

template <class Type>
bool LinkedListType<Type>::isEmptyList () const
{
    return (first == nullptr);
}

template <class Type>
void LinkedListType<Type>::print () const
{
    nodeType<Type> *current; //pointer to traverse the list

    current = first;    //set current so that it points to 
                        //the first node
    while (current != nullptr) //while more data to print
    {
        cout << current->info << " ";
        current = current->link;
    }
}

template <class Type>
int LinkedListType<Type>::length () const
{
    return count;
}

template <class Type>
void LinkedListType<Type>::destroyList ()
{
    nodeType<Type> *temp;   //pointer to deallocate the memory
                            //occupied by the node
    while (first != nullptr)   //while there are nodes in 
    {                          //the list
        temp = first;        //set temp to the current node
        first = first->link; //advance first to the next node
        delete temp;   //deallocate the memory occupied by temp
    }
    last = nullptr; //initialize last to nullptr; first has 
               //already been set to nullptr by the while loop
    count = 0;
}

template <class Type>
Type LinkedListType<Type>::front () const
{   
    assert(first != nullptr);

    return first->info; //return the info of the first node	
}

template <class Type>
Type LinkedListType<Type>::back () const
{   
    assert(last != nullptr);

    return last->info; //return the info of the last node	
}

template <class Type>
bool LinkedListType<Type>::search (const Type& searchItem) const { return false; }

template <class Type>
void LinkedListType<Type>::insertFirst (const Type& newItem) 
{
    if (this->count == 0)
    {
        nodeType<Type> *n = new nodeType<Type>;
        n->info = newItem;
        n->link = nullptr;
        this->first = this->last = n;
        this->count++;
    }
    else
    {
        nodeType<Type> *tmp = this->first;
        nodeType<Type> *n = new nodeType<Type>;
        n->info = newItem;
        n->link = tmp;
        this->first = n;
        this->count++;
    }
}

template <class Type>
void LinkedListType<Type>::insertLast (const Type& newItem) {}

template <class Type>
void deleteNode (const Type& deleteItem) {}

template <class Type>
LinkedListIterator<Type> LinkedListType<Type>::begin ()
{
    LinkedListIterator<Type> temp(first);

    return temp;
}

template <class Type>
LinkedListIterator<Type> LinkedListType<Type>::end ()
{
    LinkedListIterator<Type> temp(nullptr);

    return temp;
}

template <class Type>
const LinkedListType<Type>& LinkedListType<Type>::operator= (const LinkedListType<Type>& otherList)
{ 
    if (this != &otherList) //avoid self-copy
    {
        copyList(otherList);
    }

     return *this; 
}

template <class Type>
Type& LinkedListType<Type>::operator[] (const int& index)
{
    nodeType<Type> *curr = this->first;
    if (index < 0 || index >= this->count) // ensure in bounds
    {
        std::cerr << "Index out of bounds." << std::endl;
        exit(1);
    }
    for (size_t i = 0; static_cast<int>(i) < index; ++i) // traverse
    {
        curr = curr->link;
    }
    return curr->info;
}

template <class Type>
const LinkedListType<Type>& LinkedListType<Type>::operator-= (int k)
{
    if (k < 0 || k >= this->count) // ensure in bounds
    {
        std::cerr << "k out of bounds." << std::endl;
        return *this;
    }
    if (this->count == 1)
    {
        delete this->first;
        this->first = this->last = nullptr;
        this->count = 0;
        return *this;
    }
    else
    {
        if (k == 0)
        {
            nodeType<Type> *tmp = this->first;
            this->first = this->first->link;
            this->count--;
            delete tmp;
        }
        else if (k == this->count-1)
        {
            nodeType<Type> *tmp = this->last;
            nodeType<Type> *curr = this->first;
            for (size_t i = 0; static_cast<int>(i) < this->count-2; ++i)
            {
                curr = curr->link;
            }
            this->last = curr;
            this->last->link = nullptr;
            this->count--;
            delete tmp;
        }
        else
        {
            nodeType<Type> *curr = this->first;
            for (size_t i = 0; static_cast<int>(i) < k-1; ++i)
            {
                curr = curr->link;
            }
            nodeType<Type>*tmp = curr->link;
            curr->link = curr->link->link;
            this->count--;
            delete tmp;
        }
    }
    return *this;
}

template <class Type>
void LinkedListType<Type>::copyList (const LinkedListType<Type>& otherList) 
{
    nodeType<Type> *newNode; //pointer to create a node
    nodeType<Type> *current; //pointer to traverse the list

    if (first != nullptr) //if the list is nonempty, make it empty
       destroyList();

    if (otherList.first == nullptr) //otherList is empty
    {
        first = nullptr;
        last = nullptr;
        count = 0;
    }
    else
    {
        current = otherList.first; //current points to the 
                                   //list to be copied
        count = otherList.count;

            //copy the first node
        first = new nodeType<Type>;  //create the node

        first->info = current->info; //copy the info
        first->link = nullptr;        //set the link field of 
                                   //the node to nullptr
        last = first;              //make last point to the
                                   //first node
        current = current->link;     //make current point to
                                     //the next node

           //copy the remaining list
        while (current != nullptr)
        {
            newNode = new nodeType<Type>;  //create a node
            newNode->info = current->info; //copy the info
            newNode->link = nullptr;       //set the link of 
                                        //newNode to nullptr
            last->link = newNode;  //attach newNode after last
            last = newNode;        //make last point to
                                   //the actual last node
            current = current->link;   //make current point 
                                       //to the next node
        }
    }
}
