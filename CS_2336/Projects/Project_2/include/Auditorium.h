#pragma once

#include <TheaterSeat.h>

class Auditorium
{
    public:
        Auditorium ();
        ~Auditorium ();
        TheaterSeat * getFirst () { return first; }
        void setFirst (TheaterSeat *val) { first = val; }
        unsigned int getHeight () { return height; }
        void setHeight (unsigned int val) { height = val; }
        unsigned int getLength () { return length; }
        void setLength (unsigned int val) {length = val; }
        unsigned int getTotalA () { return totalA; };
        void setTotalA (unsigned int val) { totalA = val; }
        unsigned int getTotalC () { return totalC; };
        void setTotalC (unsigned int val) { totalC = val; }
        unsigned int getTotalS () { return totalS; };
        void setTotalS (unsigned int val) { totalS = val; }
        void print ();
        void userPrint ();
        int * bestAvailable (unsigned int, unsigned int);
        bool isAvailable (unsigned int, char, unsigned int);
        TheaterSeat * goTo (unsigned int, unsigned int);
        void writeOutput (unsigned int, unsigned int, unsigned int);
    protected:
    private:
        TheaterSeat *first;
        unsigned int height;
        unsigned int length;
        unsigned int totalA;
        unsigned int totalC;
        unsigned int totalS;
};
