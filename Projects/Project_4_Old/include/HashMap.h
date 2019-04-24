// Project 4
// Anja Sheppard AMS180001

#pragma once

template <class K, class V>
class HashMap
{
    public:
        HashMap ();
        HashMap (unsigned int);
        ~HashMap ();
        unsigned int put (K *, V *);
        void rehash ();
        void print ();
        void clear ();
        bool isEmpty ();
        V * get(K *);
    protected:
    private:
        unsigned int size;
        int filled;
        V **map;
        const double LOAD_FACTOR = 0.5;
};
