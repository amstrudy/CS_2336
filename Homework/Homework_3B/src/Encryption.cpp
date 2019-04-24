// Homework 3B
// Anja Sheppard
// AMS180001

#include <iostream>
#include <fstream>
#include "Encryption.h"

#define INFILE "in.txt"
#define OUTFILE "outEncryption.txt"

void Encryption::doFilter (std::ifstream &in, std::ofstream &out)
{
    in.open(INFILE);
    out.open(OUTFILE);
    if (in && out)
    {
        int c; // deals with values over 126
        char a;
        while (!in.eof())
        {
            in.get(a);
            c = static_cast<int>(a);
            if (c < 32)
                break;
            c += key;
            while (c > 126)
            {
                c -= 95;
            }
            while (c < 32)
            {
                c += 95;
            }
            char d = static_cast<char>(c);
            out.write(&d, 1);
        }
        in.close();
        out.close();
    }
    else
    {
        std::cerr << "There was a problem reading the files." << std::endl;
    }
}
