// Project 3
// Anja Sheppard AMS180001

#include <string>
#include "Node.h"

Node::Node ()
{
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node (std::string title, int available, int rented)
{
    this->title = title;
    this->available = available;
    this->rented = rented;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node (Node& copy)
{
    this->title = copy.getTitle();
    this->available = copy.getAvailable();
    this->rented = copy.getRented();
    this->left = copy.left;
    this->right = copy.left;
}

Node::~Node () {}
