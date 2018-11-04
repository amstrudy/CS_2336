// Project 3
// Anja Sheppard AMS180001

#include <iostream>
#include "Node.h"
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"

using namespace std;

int addDVD (BinarySearchTree<T>& kiosk, T *newNode);
int removeDVD (BinarySearchTree<T>& kiosk, T *newNode);
int rentDVD (BinarySearchTree<T>& kiosk, T *newNode);
int returnDVD (BinarySearchTree<T>& kiosk, T *newNode);

int main ()
{
    BinarySearchTree<Node> *bst = new BinarySearchTree<Node>();
    bst->insertBST(new Node("Deadpool", 1, 0));
    bst->insertBST(new Node("Now You See Me", 2, 0));
    bst->insertBST(new Node("Harry Potter", 2, 0));
    bst->insertBST(new Node("Spiderman", 2, 0));
    bst->insertBST(new Node("Thor: Ragnorak", 2, 0));
    bst->insertBST(new Node("Spaceballs", 2, 0));
    bst->insertBST(new Node("Lord of the Rings", 2, 0));
    bst->insertBST(new Node("Minority Report", 2, 0));
    bst->insertBST(new Node("Avatar", 2, 0));
    bst->insertBST(new Node("Dr. Strangelove", 2, 0));
    bst->insertBST(new Node("Atomic Blonde", 2, 0));
    bst->printBST();
    cout << "\n" << endl;
    bst->deleteBST(new Node("Dr. Strangelove", 1, 0));
    bst->printBST();
    cout << "\n" << endl;
    bst->deleteBST(new Node("Dr. Strangelove", 1, 0));
    bst->printBST();
    cout << "\n" << endl;
    bst->deleteBST(new Node("Dr. Strangelove", 1, 0));
    //bst->deleteBST(new Node("Deadpool", 2, 0));
    //bst->deleteBST(new Node("Harry Potter 3", 2, 0));
    //bst->deleteBST(new Node("Dr. Strangelove", 2, 0));
    bst->printBST();
    cout << "\n" << endl;
    return 0;
}

int addDVD (BinarySearchTree<T>& kiosk, T *newNode)
{
    T *found = kiosk.searchBST(newNode);
    if (found == nullptr) return -1; // -1: not in the tree (aka fails)
    if (found->getAvailable() == 0) // 0: delete from tree
    {
        bst.deleteBST(newNode);
        return 0;
    }
    else // 1: decrement number available
    {
        found->setAvailable(found->getAvailable() - 1);
        return -1;
    }
}

int removeDVD (BinarySearchTree<T>& kiosk, T *newNode)
{
    T *found = kiosk.searchBST(newNode);
    if (found == nullptr) //  0: insert into tree
    {
        bst.insertBST(newNode);
        return 0;
    }
    else // 1: increment number available
    {
        found->setAvailable(found->getAvailable() + 1);
        return 1;
    }
}

int rentDVD (BinarySearchTree<T>& kiosk, T *newNode)
{
    T *found = kiosk.searchBST(newNode);
    if (found == nullptr) return -1; // -1: doesn't exist
    if (found.getAvailable() == 0) return 0; // 0: none available
    else // 1: successful rent
    {
        found->setAvailable(found->getAvailable() - 1);
        found->setRented(found->getRented() + 1);
        return 1;
    }
}

int returnDVD (BinarySearchTree<T>& kiosk, T *newNode)
{
    T *found = kiosk.searchBST(newNode);
    if (found == nullptr) return -1; // -1: doesn't exist
    if (found.getRented() == 0) return 0; // 0: none rented
    else // 1: successful return
    {
        found->setAvailable(found->getAvailable() + 1);
        found->setRented(found->getRented() - 1);
        return 1;
    }
}
