// Project 2
// Anja Sheppard AMS180001

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>
#include "TheaterSeat.h"
#include "Auditorium.h"

Auditorium::Auditorium ()
{
    this->first = nullptr;
}

Auditorium::Auditorium(std::string FILENAME)
{
    this->IN_FILE = FILENAME;
    std::ifstream theater(this->IN_FILE);
    if (theater) // ensure file exists
    {
        std::string lineStr;
        unsigned int numCols = 0, numRows = 1;
        getline(theater, lineStr);
        if (lineStr.length() < 2) // make sure file isn't empty
        {
            std::cout << "The file is empty." << std::endl;
            exit(0);
        }

        // get length of rows and cols
        for (size_t i = 0; i < lineStr.length(); ++i)
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
                TheaterSeat *ts = new TheaterSeat(rowOn, (static_cast<char>(static_cast<unsigned int>('A') + i)), lineStr[i] != '.', lineStr[i]);
                if (i == 0)
                {
                    left = nullptr;
                    up = prevFirst;
                    prevFirst = ts;
                }
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
    TheaterSeat *curr = this->first, *hold = curr;
    TheaterSeat *lineFirst = this->first; // keep track of beginning of line to loop around to
    while (curr != nullptr)
    {
        if (curr->getRight() == nullptr)
        {
           curr = lineFirst->getDown();
           lineFirst = curr;
        }
        else
        {
            hold = curr; // traverse while deleting each node
            curr = curr->getRight();
            delete hold;
        }
    }
    
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
    int row = 1;
    bool first = true;
    std::cout << "  " << std::flush;
    for (size_t i = 0; i < this->getLength(); ++i)
    {
        std::cout << static_cast<char>(65 + i);
    }
    std::cout << std::endl;
    while (curr != nullptr)
    {
        if (first)
        {
            std::cout << row << " " << std::flush;
            first = false;
        }
        if (curr->getReserved())
            std::cout << "#";
        else
            std::cout << ".";
        if (curr->getRight() == nullptr)
        {
           curr = lineFirst->getDown();
           lineFirst = curr;
           std::cout << std::endl;
           first = true;
           row++;
        }
        else
            curr = curr->getRight();
    }
}

int * Auditorium::bestAvailable (unsigned int numSeats)
{
    bool broken = false;
    double minDist = pow((pow(this->height, 2.0) + pow(this->length, 2.0)), 0.5), dist; // rowDist is distance from middle of row
    int *min = new int[2];
    min[0] = -1;
    min[1] = -1;
    for (size_t i = 0; i < this->height; ++i) // test each row
    {
        for (size_t j = 0; j < this->length; ++j) // test each combo on each row
        {
            if (this->length - j >= numSeats) // ensure there are enough seats left
            {
                for (size_t k = 0; k < numSeats; ++k) // check that seats are free after starting seat
                {
                    if (this->goTo(static_cast<unsigned int>(i), static_cast<unsigned int>(j+k))->getReserved())
                    {
                        broken = true;
                    }
                }
                if (broken == false) // seat combo exists
                {
                    double goalx = (this->length - 1) / 2.0 , goaly = (this->height - 1) / 2.0;
                    double currx = j + ((numSeats - 1) / 2.0) , curry = i;

                    dist = pow((pow(abs(goalx - currx), 2.0) + pow(abs(goaly - curry), 2.0)), 0.5); // distance formula
                    if (dist == 0)
                    {
                        minDist = 0;
                        min[0] = static_cast<int>(i);
                        min[1] = static_cast<int>(j);
                        return min;
                    }
                    if (dist < minDist)
                    {
                        minDist = dist;
                        min[0] = static_cast<int>(i);
                        min[1] = static_cast<int>(j);
                    }
                }
                broken = false;
            }
        }
    }
    return min; // if still -1, then no solution found
}

bool Auditorium::isAvailable (unsigned int rowNum, char startingSeatLetter, unsigned int numSeats)
{
    if (startingSeatLetter - 65 + numSeats > this->length)
    {
        return false;
    }
    for (size_t i = 0; i < numSeats; ++i)
    {
        if (this->goTo(rowNum-1, startingSeatLetter-65+static_cast<unsigned int>(i))->getReserved())
            return false;
    }
    return true;
}

TheaterSeat * Auditorium::goTo (unsigned int row, unsigned int column)
{
    TheaterSeat *curr = this->first;
    TheaterSeat *lineFirst = this->first; // keep track of beginning of line to loop around to
    unsigned int rowF = 0, colF = 0;
    while (curr != nullptr)
    {
        if (rowF == row && colF == column)
            return curr;
        if (curr->getRight() == nullptr)
        {
           curr = lineFirst->getDown();
           lineFirst = curr;
           ++rowF;
           colF = 0;
        }
        else
        {
            curr = curr->getRight();
            ++colF;
        }
    }
    return curr;
}

void Auditorium::writeOutput ()
{
    // write output to file
    std::ofstream theater;
    theater.open(this->IN_FILE, std::ofstream::out);

    TheaterSeat *curr = this->first;
    TheaterSeat *lineFirst = this->first; // keep track of beginning of line to loop around to
    while (curr != nullptr)
    {
        theater << curr->getTicketType();
        if (curr->getRight() == nullptr)
        {
           curr = lineFirst->getDown();
           lineFirst = curr;
           theater << '\n';
        }
        else
            curr = curr->getRight();
    }
    theater.close();
}
