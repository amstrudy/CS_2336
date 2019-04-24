// Homework 7
// Anja Sheppard AMS180001

#pragma once

class HashMap
{
    public:
        HashMap ();
        HashMap (int);
        ~HashMap ();
        void setSize (int var) { this->size = var; }
        int getSize () { return this->size; }
        void setFilled (int var) { this->filled = var; }
        int getFilled () { return this->filled; }
        void setArray (int *var) { this->array = var; }
        int * getArray () { return this->array; }
        int insert (int);
        void rehash ();
        void print ();
    protected:
    private:
        int size;
        int filled;
        int *array;
        const double LOAD_FACTOR = 0.5;
};
