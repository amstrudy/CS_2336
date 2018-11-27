//Homework 8
// Anja Sheppard AMS180001

#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

#define IN_FILE "input.txt"

void dfs (Node *root, bool visited[]);

Graph::Graph ()
{
    this->nodes = new Node*[0];
    this->currSize = 0;
    this->maxSize = 10;
}

Graph::Graph (unsigned int size)
{
    this->nodes = new Node*[0];
    this->currSize = 0;
    this->maxSize = size;
}

Graph::~Graph ()
{
    delete [] this->nodes;
}

bool Graph::isEmpty ()
{
    return (this->currSize == 0);
}

void Graph::createGraph ()
{
    std::ifstream in(IN_FILE);
    std::string lineStr;
    if (in)
    {
        getline(in, lineStr); // get first line which has size of graph
        for (size_t i = 0; i < static_cast<unsigned int>(stoi(lineStr)); ++i)
        {
            Node *t = new Node(static_cast<int>(i + 1));
            this->appendG(t);
        }
        for (size_t i = 0; i < this->currSize; ++i)
        {
            getline(in, lineStr);
            std::istringstream iss(lineStr);
            int index;
            iss >> index; // first number is the node
            int otherNode;
            for (size_t j = 0; iss.rdbuf()->in_avail() != 0; ++j) // get the nodes in the adjacency list
            {
                iss >> otherNode;
                this->nodes[i]->append(this->nodes[otherNode - 1]); // add node to adjacency list
            }
        }
        in.close();
    }
    else
    {
        std::cout << "The file does not exist." << std::endl;
        exit(1);
    }
}

void Graph::appendG (Node *add)
{
    this->currSize++;
    Node **newA = new Node*[this->currSize];
    for (size_t i = 0; i < this->currSize-1; ++i)
    {
        newA[i] = this->nodes[i];
       
    }
    newA[this->currSize-1] = add;
    Node **tmp = this->nodes;
    this->nodes = newA;
    delete [] tmp;
}

bool Graph::isConnected ()
{
    bool *visited = new bool[this->currSize];
    dfs(this->nodes[0], visited);
    unsigned int numVisited = 0;
    for (size_t i = 0; i < this->currSize; ++i)
    {
        if (visited[i] == true)
            ++numVisited;
    }
    return (numVisited == this->currSize);
}

void dfs (Node *root, bool visited[]) // isConnected helper
{
    visited[root->getDatum() - 1] = true;
    for (size_t i = 0; i < root->getNumNeighbors(); ++i)
    {
        if (visited[root->getNeighbors()[i]->getDatum() - 1] == false)
        {
            dfs(root->getNeighbors()[i], visited);
        }
    }
}
