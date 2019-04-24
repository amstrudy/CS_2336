// Homework 8
// Anja Sheppard AMS180001

#pragma once

#include <iostream>

class Node
{
    public:
        Node ();
        Node (int);
        ~Node ();
        int getDatum () { return this->datum; }
        void setDatum (int var) { this->datum = var; }
        unsigned int getNumNeighbors () { return this->numNeighbors; }
        void setNumNeighbors (unsigned int var) { this->numNeighbors = var; }
        Node ** getNeighbors () { return this->neighbors; }
        void append (Node *);
    protected:
    private:
        int datum;
        unsigned int numNeighbors;
        Node **neighbors;
};
