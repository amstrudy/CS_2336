// Homework 8
// Anja Sheppard AMS180001

#pragma once

#include "Node.h"

class Graph
{
    public:
        Graph ();
        Graph (unsigned int);
        ~Graph ();
        bool isEmpty ();
        void createGraph ();
        bool isConnected ();
        void appendG (Node *);
    protected:
    private:
        Node **nodes;
        unsigned int currSize;
        unsigned int maxSize;
};
