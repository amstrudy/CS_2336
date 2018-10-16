// Homework 3B
// Anja Sheppard
// AMS180001

#include <iostream>
#include <fstream>
#include "Copy.h"

#define INFILE "in.txt"
#define OUTFILE "outCopy.txt"

void Copy::doFilter (std::ifstream &in, std::ofstream &out)
{
    in.open(INFILE);
    out.open(OUTFILE);
    if (in && out)
    {
        char c;
        while (!in.eof())
        {
            in.get(c);
            out.write(&c, 1);
        }
        in.close();
        out.close();
    }
    else
    {
        std::cerr << "There was a problem reading the files." << std::endl;
    }
}
