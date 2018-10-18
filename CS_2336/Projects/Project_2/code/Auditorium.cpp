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

#define FILENAME "A1.txt"

Auditorium::Auditorium()
{
    std::ifstream theater(FILENAME);
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
                TheaterSeat *ts = new TheaterSeat(rowOn, (static_cast<unsigned int>('A') + i), lineStr[i] != '.', lineStr[i]);
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
                        broken = true;
                }
                if (broken == false) // seat combo exists
                {
                    dist = pow((pow(abs((this->length / 2.0) - (static_cast<double>(j) + (numSeats / 2.0))), 2.0) + pow(abs((this->height / 2.0) - i), 2.0)), 0.5); // distance formula
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
    theater.open(FILENAME, std::ofstream::out);

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

    // write output to command line
    std::string s1 = "Total Seats in Auditorium:";
    std::string s2 = "Total Tickets Sold:";
    std::string s3 = "Adult Tickets Sold:";
    std::string s4 = "Child Tickets Sold:";
    std::string s5 = "Senior Tickets Sold:";
    std::string s6 = "Total Ticket Sales:";
    double totalSales = (this->getTotalA()*10.) + (this->getTotalC()*5.) + (this->getTotalS()*7.5);
    std::cout << std::left << "AUDITORIUM FINAL REPORT\n" << std::endl;
    std::cout << s1 << std::right << std::setw(50 - (int)s1.length()) << this->height * this->length << std::endl;
    std::cout << s2 << std::right << std::setw(50 - (int)s2.length()) << this->getTotalA() + this->getTotalC() + this->getTotalS() << std::endl;
    std::cout << s3 << std::right << std::setw(50 - (int)s3.length()) << this->getTotalA() << std::endl;
    std::cout << s4 << std::right << std::setw(50 - (int)s4.length()) << this->getTotalC() << std::endl;
    std::cout << s5 << std::right << std::setw(50 - (int)s5.length()) << this->getTotalS() << std::endl;
    std::cout << s6 << std::flush;
    for (size_t i = 0; i < (50 - s6.length() - (std::to_string(totalSales)).length() + 3); ++i) std::cout << " " << std::flush;
    std::cout << "$" << std::fixed << std::setprecision(2) << totalSales << "\n\n\n" << std::endl;
}
