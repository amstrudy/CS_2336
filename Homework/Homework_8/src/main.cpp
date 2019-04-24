// Homework 8
// Anja Sheppard AMS180001

#include <iostream>
#include <fstream>
#include "Graph.h"

#define IN_FILE "input.txt"

using namespace std;

int main ()
{
    Graph *g;
    ifstream in(IN_FILE);
    if (in)
    {
        string lineStr;
        getline(in, lineStr);
        g = new Graph(static_cast<unsigned int>(stoi(lineStr)));
        in.close();
    }
    else
    {
        cout << "The file does not exist." << endl;
        exit(1);
    }

    g->createGraph();
    if (g->isEmpty())
    {
        cout << "The graph is empty." << endl;
    }
    else
    {
        cout << "The graph is not empty." << endl;
    }
    if (g->isConnected())
    {
        cout << "The graph is connected." << endl;
    }
    else
    {
        cout << "The graph is not connected." << endl;
    }
    
    return 0;
}
