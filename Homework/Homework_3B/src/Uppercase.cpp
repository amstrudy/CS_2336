// Homework 3B
// Anja Sheppard
// AMS180001

#include <iostream>
#include <fstream>
#include "Uppercase.h"

#define INFILE "in.txt"
#define OUTFILE "outUppercase.txt"

void Uppercase::doFilter (std::ifstream &in, std::ofstream &out)
{
    in.open(INFILE);
    out.open(OUTFILE);
    if (in && out)
    {
        char c;
        while (!in.eof())
        {
            in.get(c);
            c = transform(c);
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

char Uppercase::transform (char c)
{
    if (c > 96 && c < 122)
    {
        c = static_cast<char>(static_cast<int>(c) - 32);
    }
    return c;
}
