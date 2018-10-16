#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "TheaterSeat.h"
#include "Auditorium.h"

#define FILENAME "A1.txt"

struct Best
{
    unsigned int rowNum;
    unsigned char startingSeat;
};

Auditorium::Auditorium()
{
    std::ifstream theater(FILENAME);
    if (theater)
    {
        std::string lineStr;
        unsigned int numCols = 0, numRows = 0;
        getline(theater, lineStr);

         // get length of rows and cols
        for (size_t i = 0; lineStr[i] != '\0'; ++i)
            ++numCols;

        while (getline(theater, lineStr))
        {
            if (lineStr.length() >= 4) // make sure there isn't a new line character at the end
                ++numRows;
        }

        theater.clear(); // clear eof and reset pointer to beginning
        theater.seekg(0);
        unsigned int rowOn = 0;

        // now that lengths are known, connect up pointers
        TheaterSeat *up = nullptr, *left = nullptr, *prevFirst = nullptr;
        while (getline(theater, lineStr))
        {
            for (size_t i = 0; lineStr[i] != '\0'; ++i)
            {
                TheaterSeat *ts = new TheaterSeat(rowOn, ('A' + i), lineStr[i] != '.', lineStr[i]);
                if (i == 0)
                {
                    left = nullptr;
                    up = prevFirst;
                    prevFirst = ts;
                }
                std::cout << i << std::endl;
                if (ts->getLeft() != nullptr)
                    std::cout << ts->getLeft()->getSeat() << std::endl;
                if (left != nullptr)
                    std::cout << left->getSeat() << std::endl;
                if (i == 0 && rowOn == 0)
                {
                    this->first = ts;
                    left = ts;
                    continue;
                }
                if (rowOn == 0)
                    ts->setUp(nullptr);
                else if (rowOn == numRows-1)
                    ts->setDown(nullptr);
                else if (i == 0)
                    ts->setLeft(nullptr);
                else if (i == numCols-1)
                    ts->setRight(nullptr);
                if (up != nullptr)
                {
                    ts->setUp(up);
                    up->setDown(ts);
                    up = up->getRight();
                }
                else
                    ts->setUp(nullptr);
                if (left != nullptr)
                {
                    ts->setLeft(left);
                    left->setRight(ts);
                }
                else
                    ts->setLeft(nullptr);
                if (i == 0)
                    left = ts;
                else
                    left = left->getRight();
            }
            rowOn++;
        }
        this->height = numRows;
        this->length = numCols;
        theater.close();
    }
    else
    {
        std::cerr << "The file does not exist." << std::endl;
    } 
}

Auditorium::~Auditorium ()
{
    //dtor
}

void Auditorium::print ()
{
    TheaterSeat *curr = this->first;
    TheaterSeat *lineFirst = this->first; // keep track of beginning of line to loop around to
    while (curr != nullptr)
    {
        std::cout << curr->getTicketType();
        if (curr->getRight() == nullptr)
        {
           curr = lineFirst->getDown();
           lineFirst = curr;
           std::cout << std::endl;
        }
        else
            curr = curr->getRight();
    }
}

void Auditorium::userPrint ()
{
    TheaterSeat *curr = this->first;
    TheaterSeat *lineFirst = this->first; // keep track of beginning of line to loop around to
    while (curr != nullptr)
    {
        if (curr->getReserved())
            std::cout << "#";
        else
            std::cout << ".";
        if (curr->getRight() == nullptr)
        {
           curr = lineFirst->getDown();
           lineFirst = curr;
           std::cout << std::endl;
        }
        else
            curr = curr->getRight();
    }
}

int * Auditorium::bestAvailable (unsigned int rowNum, unsigned int numSeats)
{
    bool broken = false;
    int minDist = pow(pow(this->height, 2), pow(this->length, 2), 0.5), rowDist, colDist; // rowDist is distance from middle of row
    int min[2] = {-1, -1};
    for (size_t i = 0; i < this->height; ++i) // test each row
    {
        for (size_t j = 0; j < this->length; ++j) // test each combo on each row
        {
            if (this->length - j >= this->numSeats) // ensure there are enough seats left
            {
                for (size_t k = 0; k < numSeats; ++k) // check that seats are free after starting seat
                {
                    if (a->goTo(i, j+k) != '.')
                        broken = true;
                }
                if (broken == false) // seat combo exists
                {
                    dist = pow(pow(abs(((this->length + 1.0) / 2.0) - (j + (numSeats / 2.0))), 2) + pow(abs((this->height / 2.0) - i), 2), 0.5); // distance formula
                    if (dist < minDist)
                    {
                        minDist = dist;
                        min[0] = i;
                        min[1] = j;
                    }
                }
                broken = false;
            }
        }
    }
    return min; // if still -1, then no solution found
}

bool isAvailable (unsigned int rowNum, char startingSeatLetter, unsigned int numSeats)
{
    for (size_t i = 0; i < numSeats; ++i)
    {
        if (this->goTo(rowNum-1, startingSeatLetter-65+i)->isReserved())
            return false;
    }
    return true;
}

TheaterSeat * Auditorium::goTo (unsigned int row, unsigned int column)
{
    TheaterSeat *curr = this->first, *lineFirst = this->first;
    if (row >= this->length || column >= this->height)
        return nullptr; // error!
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < column; ++j)
        {
            if (curr->getRight() == nullptr)
            {
                curr = lineFirst->getDown();
                lineFirst = curr;
            }
            else
                curr = curr->getRight();
        }
    }
}

void Auditorium::writeOutput (unsigned int numA, unsigned int numC, unsigned int numS)
{
    // write output to file
    ofstream theater;
    theater.open(FILNAME, ofstream::out);

    for (size_t i = 0; i < a->height, ++i)
    {
        for (size_t j = 0; j < a->length, ++j)
        {
            theater << a->goTo(i, j)->getTicketType();
        }
        theater << '\n';
    }
    theater.close();

    // write output to command line
    string s1 = "Total Seats in Auditorium:";
    string s2 = "Total Tickets Sold:";
    string s3 = "Adult Tickets Sold:";
    string s4 = "Child Tickets Sold:";
    string s5 = "Senior Tickets Sold:";
    string s6 = "Total Ticket Sales:";
    double totalSales = (numA*10.) + (numC*5.) + (numS*7.5);
    cout << left << "AUDITORIUM FINAL REPORT\n" << endl;
    cout << s1 << right << setw(50 - (int)s1.length()) << a->height * a->length << endl;
    cout << s2 << right << setw(50 - (int)s2.length()) << numA + numC + numS << endl;
    cout << s3 << right << setw(50 - (int)s3.length()) << numA << endl;
    cout << s4 << right << setw(50 - (int)s4.length()) << numC << endl;
    cout << s5 << right << setw(50 - (int)s5.length()) << numS << endl;
    cout << s6 << flush;
    for (size_t i = 0; i < (50 - s6.length() - (to_string(totalSales)).length() + 3); ++i) cout << " " << flush;
    cout << "$" << fixed << setprecision(2) << totalSales << "\n\n\n" << endl;
}
