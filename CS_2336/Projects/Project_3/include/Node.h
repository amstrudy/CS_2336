// Project 3
// Anja Sheppard AMS180001

#pragma once

#include <string>

class Node
{
    public:
        Node ();
        Node (std::string, int, int);
        Node (Node&);
        ~Node ();
        std::string getTitle () { return this->title; }
        void setTitle (std::string var) { this->title = var; }
        int getAvailable () { return this->available; }
        void setAvailable (int var) { this->available = var; }
        int getRented () { return this->rented; }
        void setRented (int var) { this->rented = var; }
        Node * getLeft () { if (this->left == nullptr) return nullptr; return this->left; }
        void setLeft (Node *var) { this->left = var; }
        Node * getRight () { if (this->right == nullptr) return nullptr; return this->right; }
        void setRight (Node *var) { this->right = var; }
        Node ** getLeftPtr () { return &(this->left); }
        Node ** getRightPtr () { return &(this->right); }
    protected:
        Node *left;
        Node *right;
    private:
        std::string title;
        int available;
        int rented;
};
