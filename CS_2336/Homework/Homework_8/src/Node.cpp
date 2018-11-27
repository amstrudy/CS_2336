// Homework 8
// Anja Sheppard AMS180001

#include "Node.h"

Node::Node () {}

Node::Node (int d)
{
    this->datum = d;
    this->numNeighbors = 0;
    this->neighbors = new Node*[0];
}

Node::~Node ()
{
    delete [] this->neighbors;
}

void Node::append (Node *add)
{
    this->numNeighbors++;
    Node **newA = new Node*[this->numNeighbors];
    for (size_t i = 0; i < this->numNeighbors-1; ++i)
    {
        newA[i] = this->neighbors[i];
    }
    newA[this->numNeighbors-1] = add;
    Node **tmp = this->neighbors;
    this->neighbors = newA;
    delete [] tmp;
}
