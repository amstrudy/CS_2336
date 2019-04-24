// Homework 7
// Anja Sheppard AMS180001

#include <iostream>
#include <math.h>
#include "HashMap.h"

HashMap::HashMap ()
{
    this->size = 0;
    this->filled = 0;
    this->array = nullptr;
}

HashMap::HashMap (int s)
{
    if (s < 0)
    {
        std::cerr << "Not a valid size." << std::endl;
        exit(1);
    }
    this->size = s;
    this->filled = 0;
    this->array = new int[this->size];
    for (size_t i = 0; i < static_cast<unsigned int>(this->size); ++i)
    {
        this->array[i] = 0;
    }
}

HashMap::~HashMap ()
{
    delete this->array;
}

int HashMap::insert (int key)
{
    if (static_cast<double>(this->filled) / this->size >= this->LOAD_FACTOR)
        this->rehash();
    size_t hash = key % this->size;
    if (this->array[hash] == 0) // empty slot, insert here
    {
        this->array[hash] = key;
        this->filled++;
    }
    else // quadratic probing to find new location
    {
        int p = 2;
        for (size_t i = 0; ; ++i)
        {
            if (this->array[hash + static_cast<int>(pow(i, p))] == 0)
            {
                this->array[hash + static_cast<int>(pow(i, p))] = key;
                this->filled++;
                break;
            }
            if (i > static_cast<unsigned int>(this->size * 3))
            {
                p = 1; // revert to linear
            }
        }
    }
    return static_cast<int>(hash);
}

void HashMap::print ()
{
    for (size_t i = 0; i < static_cast<unsigned int>(this->size); ++i)
    {
        std::cout << this->array[i] << " " << std::flush;
    }
    std::cout << std::endl;
}

void HashMap::rehash ()
{
    HashMap *tmp = new HashMap(this->size * 2);
    for (size_t i = 0; i < static_cast<unsigned int>(this->size); ++i)
    {
        if (this->array[i] != 0)
        {    
            size_t hash = this->array[i] % tmp->size;
            if (tmp->array[hash] == 0) // empty slot, insert here
            {
                tmp->array[hash] = this->array[i];
                tmp->filled++;
            }
            else // quadratic probing to find new location
            {
                int p = 2;
                for (size_t i = 0; ; ++i)
                {
                    if (tmp->array[hash + static_cast<int>(pow(i, p))] == 0)
                    {
                        tmp->array[hash + static_cast<int>(pow(i, p))] = this->array[i];
                        tmp->filled++;
                        break;
                    }
                    if (i > static_cast<unsigned int>(tmp->size * 3))
                    {
                        p = 1; // revert to linear
                    }
                }
            }
        }
    }
    this->array = tmp->array; // copy tmp over to this so rehashed array is saved
    this->size = tmp->size;
    this->filled = tmp->filled;
}
