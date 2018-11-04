// Project 4
// Anja Sheppard AMS180001

#pragma once

#include "Node.h"

template <class T>
class BinarySearchTree
{
    public:
        BinarySearchTree ();
        T * getRoot () { if (this->root == nullptr) return nullptr; return this->root; }
        void setRoot (T *var) { this->root = var; }
        int insertBST (T *);
        T * searchBST (T *);
        int deleteBST (T *);
        void printBST ();
        T * min ();
    protected:
    private:
        T *root;
        //int insertNode (T *, T *);
        //int searchNode (T *, T *);
        //int deleteNode (T *, T *);
        //void printNode (T *);
};
