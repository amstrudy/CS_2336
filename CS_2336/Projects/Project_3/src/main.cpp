// Project 3
// Anja Sheppard AMS180001

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include "Node.h"
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"

#define INVENTORY_FILE_NAME "inventory.dat"
#define TRANSACTION_LOG_NAME "transaction.log"
#define ERROR_LOG_NAME "error.log"
#define OUTPUT_FILE_NAME "redbox_kiosk.txt"

using namespace std;

int addDVD (BinarySearchTree<Node>& kiosk, Node *newNode);
int removeDVD (BinarySearchTree<Node>& kiosk, Node *newNode);
int rentDVD (BinarySearchTree<Node>& kiosk, Node *newNode);
int returnDVD (BinarySearchTree<Node>& kiosk, Node *newNode);
void parseInventory (BinarySearchTree<Node>& kiosk);
void parseTransactions (BinarySearchTree<Node>& kiosk);
void writeError (bool&, ofstream&, string);
void writeOutput (BinarySearchTree<Node>&);
void inOrder (Node *, ofstream&);

int main ()
{
    BinarySearchTree<Node> *bst = new BinarySearchTree<Node>();
    parseInventory(*bst);
    parseTransactions(*bst);
    writeOutput(*bst);
    bst->clearBST(); // be a responsible memory manager
    delete bst;
    return 0;
}

int addDVD (BinarySearchTree<Node>& kiosk, Node *newNode)
{
    Node *found = kiosk.searchBST(newNode);
    if (found == nullptr) //  0: insert into tree
    {
        kiosk.insertBST(newNode);
        return 0;
    }
    else // 1: increment number available
    {
        found->setAvailable(found->getAvailable() + newNode->getAvailable()); // available in newNode is the number to add
        return 1;
    }
}

int removeDVD (BinarySearchTree<Node>& kiosk, Node *newNode)
{
    Node *found = kiosk.searchBST(newNode);
    if (found == nullptr) return -1; // -1: not in the tree (aka fails)
    int r;
    if (found->getAvailable() > 0) // 1: decrement number available
    {
        if (found->getAvailable() < newNode->getAvailable()) // make sure this isn't negative
            found->setAvailable(0);
        else
            found->setAvailable(found->getAvailable() - newNode->getAvailable()); // available in newNode is the number to remove
        r = 1;
    }
    if (found->getAvailable()+found->getRented() <= 0) // 0: delete from tree
    {
        kiosk.deleteBST(newNode);
        r = 0;
    }
    return r;
}

int rentDVD (BinarySearchTree<Node>& kiosk, Node *newNode)
{
    Node *found = kiosk.searchBST(newNode);
    if (found == nullptr) return -1; // -1: doesn't exist
    if (found->getAvailable() == 0) return 0; // 0: none available
    else // 1: successful rent
    {
        found->setAvailable(found->getAvailable() - 1);
        found->setRented(found->getRented() + 1);
        return 1;
    }
}

int returnDVD (BinarySearchTree<Node>& kiosk, Node *newNode)
{
    Node *found = kiosk.searchBST(newNode);
    if (found == nullptr) return -1; // -1: doesn't exist
    if (found->getRented() == 0) return 0; // 0: none rented
    else // 1: successful return
    {
        found->setAvailable(found->getAvailable() + 1);
        found->setRented(found->getRented() - 1);
        return 1;
    }
}

void parseInventory (BinarySearchTree<Node>& kiosk)
{
    ifstream inventory(INVENTORY_FILE_NAME);
    if (inventory)
    {
        string lineStr;
        while (getline(inventory, lineStr))
        {
            if (lineStr.length() < 4) continue;
            string title;
            unsigned int available, rented;
            size_t i;
            for (i = 1; i < lineStr.length(); ++i) // skip first char which is a "
            {
                if (lineStr[i] == '"') // find title according to quotes
                {
                    title = lineStr.substr(1, i-1);
                    ++i;
                    break;
                }
            }
            lineStr.erase(0, i+1);
            for (size_t j = 0; j < lineStr.length(); ++j) // parse num available and num rented
            {
                if (lineStr[j] == ',')
                {
                    available = stoi(lineStr.substr(0, j));
                    rented = stoi(lineStr.substr(j+1, lineStr.length()-j));
                    break;
                }
            }
            addDVD(kiosk, new Node(title, available, rented));
        }
    }
    else
    {
        cerr << "The file does not exist." << endl;
    }
    inventory.close();
}

void parseTransactions (BinarySearchTree<Node>& kiosk)
{
    ifstream transactions(TRANSACTION_LOG_NAME);
    ofstream error;
    bool errored = false;
    if (transactions)
    { 
        string lineStr, lineStrCopy;
        while (getline(transactions, lineStr))
        {
            lineStrCopy = lineStr;
            if (lineStr.length() < 4)
            {
                //error
                writeError(errored, error, lineStrCopy);
                continue;
            }
            string action;
            size_t i;
            for (i = 0; i < lineStr.length(); ++i) // get action 
            {
                if (lineStr[i] == ' ')
                {
                    action = lineStr.substr(0, i);
                    ++i;
                    break;
                }
            }
            if (!(action == "add" || action == "remove" || action == "rent" || action == "return"))
            {
                //error
                writeError(errored, error, lineStrCopy);
                continue;
            }
            lineStr.erase(0, i); // remove action
            if (lineStr[0] != '"')
            {
                //error
                writeError(errored, error, lineStrCopy);
                continue;
            }
            lineStr.erase(0, 1);
            string title;
            for (size_t j = 0; j < lineStr.length(); ++j) // get title
            {
                if (lineStr[j] == '"') // find title according to quotes
                {
                    title = lineStr.substr(0, j);
                    ++j;
                    break;
                }
            }
            if (kiosk.searchBST(new Node(title, 0, 0)) == nullptr && action != "add")
            {
                //error
                writeError(errored, error, lineStrCopy);
                continue;
            }
            lineStr.erase(0, title.length()+1); // remove title and quotes
            if (action == "rent")
            {
                rentDVD(kiosk, new Node(title, 0, 0));
                continue;
            }
            else if (action == "return")
            {
                returnDVD(kiosk, new Node(title, 0, 0));
                continue;
            }
            if (lineStr[0] != ',')
            {
                //error
                writeError(errored, error, lineStrCopy);
                continue;
            }
            lineStr.erase(0, 1); // remove comma
            bool isntDigit = false;
            for (size_t j = 0; j < lineStr.length(); ++j)
            {
                if (!isdigit(lineStr[j]))
                {
                    //error
                    writeError(errored, error, lineStrCopy);
                    isntDigit = true;
                    break;
                }
            }
            if (isntDigit) continue;
            int num = stoi(lineStr);
            if (num < 0)
            {
                //error
                writeError(errored, error, lineStrCopy);
                continue;
            }
            if (action == "add")
            {
                addDVD(kiosk, new Node(title, num, 0));
            }
            else if (action == "remove")
            {
                removeDVD(kiosk, new Node(title, num, 0));
            }
            else
            {
                //error
                writeError(errored, error, lineStrCopy);
                continue;
            }
        }
    }
    else
    {
        cerr << "The file does not exist." << endl;
    }
    transactions.close();
    if (errored) error.close();
}

void writeError (bool& errored, ofstream& error, string lineStr)
{
    if (errored == false) // check if error file is open
    {
        error.open(ERROR_LOG_NAME);
        errored = true;
    }
    error << lineStr << endl;
}

void writeOutput (BinarySearchTree<Node>& kiosk)
{
    ofstream out(OUTPUT_FILE_NAME); // run recursive inOrder traversal function
    inOrder(kiosk.getRoot(), out);
    out.close();
}

void inOrder (Node *root, ofstream& out)
{
    if (root == nullptr) return; // inOrder traversal
    inOrder(root->getLeft(), out);
    out << root->getTitle() << setw(50 - static_cast<int>(root->getTitle().length())) << root->getAvailable() << "\t\t" << root->getRented() << endl;
    inOrder(root->getRight(), out);
}
