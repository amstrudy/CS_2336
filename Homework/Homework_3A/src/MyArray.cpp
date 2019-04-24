// Homework 3A
// Anja Sheppard AMS180001

#include "MyArray.h"

template <typename T>
MyArray<T>::MyArray ()
{
    this->size = 0;
    this->array = new T[size];
}

template <typename T>
MyArray<T>::MyArray (unsigned int size)
{
    this->size = size;
    this->array = new T[size];
}

template <typename T>
MyArray<T>::MyArray (int start, int end)
{
    if (end < start)
    {
        std::cerr << "You can't have the end index lower than the start index.\n" << std::endl;
        exit(1);
    }
    this->size = static_cast<unsigned int>(abs(end - start) + 1);
    this->indexStart = start;
    this->array = new T[size];
}

template <typename T>
MyArray<T>::~MyArray ()
{
    if (this->array) delete [] array;
    this->array = nullptr;
}

template <typename T>
T& MyArray<T>::operator[] (int index)
{
    if (index < this->indexStart || index >= static_cast<int>(this->indexStart + size))
    {
        std::cerr << "The index is out of bounds.\n" << std::endl;
        exit(1);
    }
    return this->array[index - this->indexStart];
}

template <typename T>
const T& MyArray<T>::operator[] (int index) const
{
    if (index < this->indexStart || index >= this->indexStart + size)
    {
        std::cerr << "The index is out of bounds.\n" << std::endl;
        exit(1);
    }
    return this->array[index - this->index];
}
