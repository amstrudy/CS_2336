// Project 3
// Anja Sheppard AMS180001

#include <iostream>
#include "BinarySearchTree.h"

template <typename T>
int insertNode (T *root, T *newNode)
{
    if (root->getTitle() > newNode->getTitle())
    {
        if (!root->getLeft())
            root->setLeft(newNode);
        else
            return 1 + insertNode(root->getLeft(), newNode);
    }
    else
    {
        if (!root->getRight())
            root->setRight(newNode);
        else
            return 1 + insertNode(root->getRight(), newNode);
    }
    return 0;
}

template <typename T>
T * searchNode (T *root, T *newNode)
{
    if (root == nullptr)
        return nullptr;
    if (newNode->getTitle() == root->getTitle())
        return root;
    if (newNode->getTitle() < root->getTitle())
        searchNode(root->getLeft(), newNode);
    else
        searchNode(root->getRight(), newNode);
}

template <typename T>
int deleteNode (T **root, T *newNode)
{
    T * tmp = *root;
    if (tmp == nullptr) return -1; // doesn't exist in tree
    if (newNode->getTitle() < tmp->getTitle())
    {
        int depth = deleteNode(tmp->getLeftPtr(), newNode);
        return depth == -1 ? -1 : 1 + depth;
    }
    if (newNode->getTitle() > tmp->getTitle())
    {
        int depth = deleteNode(tmp->getRightPtr(), newNode);
        return depth == -1 ? -1 : 1 + depth;
    }
    if (tmp->getLeft() && tmp->getRight())
    {
        T *next = min(tmp->getRight());
        tmp->setTitle(next->getTitle());
        tmp->setAvailable(next->getAvailable());
        tmp->setRented(next->getRented());
        deleteNode(tmp->getRightPtr(), next);
        return 0;
    }
    if (tmp->getLeft() == nullptr)
    {
        *root = tmp->getRight();
    }
    else
        *root = tmp->getLeft();
    delete tmp;
    return 0;
}

template <typename T>
T * min (T *root)
{
    if (root->getLeft() == nullptr)
        return root;
    return min(root->getLeft());
}

template <typename T>
void printNode (T *root)
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

template <typename T>
BinarySearchTree<T>::BinarySearchTree () {}

template <typename T>
int BinarySearchTree<T>::insertBST (T *newNode)
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
    /*T * foundNode = this->searchBST(newNode);
    if (foundNode->getAvailable() == 0)
        return deleteNode(&(this->root), newNode);
    else
    {
        foundNode->setAvailable(foundNode->getAvailable() - 1);
        return 0;
    }*/
    return deleteNode(&(this->root), newNode);
}

template <typename T>
void BinarySearchTree<T>::printBST ()
{
    printNode(this->root);
    std::cout << std::endl;
}

