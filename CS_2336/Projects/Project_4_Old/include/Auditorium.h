// Project 2
// Anja Sheppard AMS180001

#pragma once

#include "TheaterSeat.h"

class Auditorium
{
    public:
        Auditorium ();
        Auditorium (std::string);
        ~Auditorium ();
        TheaterSeat * getFirst () { return first; }
        void setFirst (TheaterSeat *val) { first = val; }
        unsigned int getHeight () { return height; }
        void setHeight (unsigned int val) { height = val; }
        unsigned int getLength () { return length; }
        void setLength (unsigned int val) {length = val; }
        unsigned int getNumOpenSeats () { return this->numOpenSeats; }
        void setNumOpenSeats (unsigned int var) { this->numOpenSeats = var; }
        unsigned int getNumReservedSeats () { return this->numReservedSeats; }
        void setNumReservedSeats (unsigned int var) { this->numReservedSeats = var; }
        unsigned int getTotalA () { return totalA; };
        void setTotalA (unsigned int val) { totalA = val; }
        unsigned int getTotalC () { return totalC; };
        void setTotalC (unsigned int val) { totalC = val; }
        unsigned int getTotalS () { return totalS; };
        void setTotalS (unsigned int val) { totalS = val; }
        void print ();
        void userPrint ();
        int * bestAvailable (unsigned int);
        bool isAvailable (unsigned int, char, unsigned int);
        TheaterSeat * goTo (unsigned int, unsigned int);
        void writeOutput ();
    protected:
    private:
        std::string IN_FILE;
        TheaterSeat *first;
        unsigned int height;
        unsigned int length;
        unsigned int numOpenSeats;
        unsigned int numReservedSeats;
        unsigned int totalA;
        unsigned int totalC;
        unsigned int totalS;
};
