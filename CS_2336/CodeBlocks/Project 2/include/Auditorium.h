#ifndef AUDITORIUM_H
#define AUDITORIUM_H

#include <TheaterSeat.h>

class Auditorium
{
    public:
        Auditorium();
        ~Auditorium();
        Auditorium(const Auditorium& other);
        TheaterSeat Getfirst() { return first; }
        void Setfirst(TheaterSeat val) { first = val; }
    protected:
    private:
        TheaterSeat first;
};

#endif // AUDITORIUM_H
