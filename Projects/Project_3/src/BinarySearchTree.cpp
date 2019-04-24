// Project 3
// Anja Sheppard AMS180001

#include <iostream>
#include "BinarySearchTree.h"

template <typename T>
int insertNode (T *root, T *newNode) // recursive helper function for insertion
{
    if (root->getTitle() > newNode->getTitle()) // go left
    {
        if (!root->getLeft())
            root->setLeft(newNode);
        else
            return 1 + insertNode(root->getLeft(), newNode);
    }
    else // go right
    {
        if (!root->getRight())
            root->setRight(newNode);
        else
            return 1 + insertNode(root->getRight(), newNode);
    }
    return 0;
}

template <typename T>
T * searchNode (T *root, T *newNode) // recurseive helper search function
{
    if (root == nullptr || newNode->getTitle() == root->getTitle())
    {
        return root;
    }
    if (newNode->getTitle() < root->getTitle())
        return searchNode(root->getLeft(), newNode); // search left
    return searchNode(root->getRight(), newNode); // search right
}

template <typename T>
int deleteNode (T **root, T *newNode) // recursive helper delete function
{
    T * tmp = *root;
    if (tmp == nullptr) return -1; // doesn't exist in tree
    if (newNode->getTitle() < tmp->getTitle())
    {
        int depth = deleteNode(tmp->getLeftPtr(), newNode);
        return depth == -1 ? -1 : 1 + depth; // return depth of deleted node
    }
    if (newNode->getTitle() > tmp->getTitle())
    {
        int depth = deleteNode(tmp->getRightPtr(), newNode);
        return depth == -1 ? -1 : 1 + depth;
    }
    if (tmp->getLeft() && tmp->getRight()) // once you've reached the node you want to delete
    {
        T *next = min(tmp->getRight());
        tmp->setTitle(next->getTitle());
        tmp->setAvailable(next->getAvailable());
        tmp->setRented(next->getRented());
        deleteNode(tmp->getRightPtr(), next);
        return 0;
    }
    if (tmp->getLeft() == nullptr) // if it's null, it's easier
    {
        *root = tmp->getRight();
    }
    else
        *root = tmp->getLeft();
    delete tmp;
    return 0;
}

template <typename T>
T * min (T *root) // find leftmost node (the min) recursively
{
    if (root->getLeft() == nullptr)
        return root;
    return min(root->getLeft());
}

template <typename T>
void printNode (T *root) // recursive helper print function, not used in final code
{
    static int depth = 0;
    if (root == nullptr)
        depth = 0;
    else
    {
        int tmp = depth;
        ++depth;
        if (root->getRight() != nullptr)
        {
            printNode(root->getRight());
            for (size_t i = 0; static_cast<int>(i) < tmp+2; ++i)
                std::cout << " " << std::flush;
            std::cout << "|" << std::endl;
        }
        depth = tmp + 1;
        for (size_t k = 0; static_cast<int>(k) < depth; ++k)
            std::cout << " " << std::flush;
        std::cout << "-" << root->getTitle() << " " << root->getAvailable() << " " << root->getRented() << std::endl;
        depth = tmp + 1;
        if (root->getLeft() != nullptr)
        {
            for (size_t i = 0; static_cast<int>(i) < tmp+2; ++i)
            {
                std::cout << " " << std::flush;
            }
            std::cout << "|" << std::endl;
            printNode(root->getLeft());
        }
        depth = tmp;
    }
}

template <class T>
void clearNode (T **root) // recursive helper clear function
{
    T *tmp = *root;
    if (tmp == nullptr)
        return;
    clearNode(tmp->getLeftPtr());
    clearNode(tmp->getRightPtr());
    delete tmp;
    *root = nullptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree ()
{
    this->root = nullptr;
}

template <typename T>
int BinarySearchTree<T>::insertBST (T *newNode) // just calls helper function
{
    if (this->root == nullptr)
    {
        this->root = newNode;
        return 0;
    }
    return insertNode(this->root, newNode);
}

template <typename T>
T * BinarySearchTree<T>::searchBST (T *newNode)
{
    return searchNode (this->root, newNode);
}

template <typename T>
int BinarySearchTree<T>::deleteBST (T *newNode)
{
    return deleteNode(&(this->root), newNode);
}

template <typename T>
void BinarySearchTree<T>::printBST ()
{
    printNode(this->root);
    std::cout << std::endl;
}

template <typename T>
void BinarySearchTree<T>::clearBST () // deletes all nodes in tree
{
    clearNode(&(this->root));
}
