// Project 4
// Anja Sheppard AMS180001

#include <iostream>
#include "HashMap.h"
#include "Customer.h"

template <typename K, typename V>
HashMap<K, V>::HashMap ()
{
    this->size = 10;
    this->filled = 0;
    this->map = new V *[this->size];
    for (size_t i = 0; i < this->size; ++i)
    {
        this->map[i] = nullptr;
    }
}

template <typename K, typename V>
HashMap<K, V>::HashMap (unsigned int s)
{
    if (s == 0)
        this->size = 10;
    else
        this->size = s;
    this->filled = 0;
    this->map = new V *[this->size];
    for (size_t i = 0; i < this->size; ++i)
    {
        this->map[i] = nullptr;
    }
}

template <typename K, typename V>
HashMap<K, V>::~HashMap ()
{
    delete [] this->map;
}

template <typename K, typename V>
unsigned int HashMap<K, V>::put (K *key, V *value)
{
    if (this->size == 0 || static_cast<double>(this->filled) / this->size >= this->LOAD_FACTOR)
    {
        this->rehash();
    }
    unsigned int hash = key->hash() % this->size;
    if (this->map[hash] == nullptr) // empty slot, insert here
    {
        this->map[hash] = value;
        this->filled++;
    }
    else // linear probe to find a new location
    {
        for (size_t i = 1; ; ++i)
        {
            if (this->map[(hash+i) % this->size] == nullptr) // found empty, insert here
            {
                this->map[(hash+i) % this->size] = value;
                this->filled++;
                break;
            }
        }
    }
    return hash;
}

template <typename K, typename V>
void HashMap<K, V>::rehash ()
{
    HashMap<K, V> *tmp = new HashMap<K, V>(this->size * 2);
    tmp->size = this->size * 2;
    for (size_t i = 0; i < static_cast<unsigned int>(this->size); ++i)
    {
        if (this->map[i] != nullptr)
        {
            unsigned int hash = this->map[i]->getKey()->hash() % tmp->size;
            if (tmp->map[hash] == nullptr) // empty slot, reinstert here
            {
                tmp->map[hash] = this->map[i];
                tmp->filled++;
            }
            else
            {
                for (size_t j = 1; ; ++j) // linear probe
                {
                    if (tmp->map[(hash+j) % tmp->size] == nullptr) // found empty, insert here
                    {
                        tmp->map[(hash+j) % tmp->size] = this->map[i];
                        tmp->filled++;
                        break;
                    }
                }
            }
        }
    }
    this->map = tmp->map; // copy tmp over to this so rehashed array is saved
    this->size = tmp->size;
    this->filled = tmp->filled;
}

template <typename K, typename V>
void HashMap<K, V>::print ()
{
    for (size_t i = 0; i < this->size; ++i)
    {
        if (this->map[i] != nullptr)
            std::cout << this->map[i]->getKey()->getDatum() << " | " << std::flush;
        else
            std::cout << "--- | " <<std::flush;
    }
    std::cout << std::endl;
}

template <typename K, typename V>
void HashMap<K, V>::clear ()
{
    for (size_t i = 0; i < this->size; ++i)
    {
        V *tmp = this->map[i];
        this->map[i] = nullptr;
        delete tmp;
    }
}

template <typename K, typename V>
bool HashMap<K, V>::isEmpty ()
{
    return (this->size == 0);
}

template <typename K, typename V>
V * HashMap<K, V>::get(K *key)
{
    unsigned int hash = key->hash() % this->size;
    if (this->map[hash] == nullptr) // not found!
    {
        return nullptr;
    }
    if (this->map[hash]->getKey()->getDatum() == key->getDatum())
        return this->map[hash];
    else // linear probe
    {
        for (size_t i = 0; ; ++i)
        {
            if (this->map[(hash + i) % this->size] == nullptr) // not found!
                return nullptr;
            if (this->map[(hash + i) % this->size]->getKey()->getDatum() == key->getDatum())
                return this->map[hash];
        }
    }
}
