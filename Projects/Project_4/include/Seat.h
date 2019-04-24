// Project 4
// Anja Sheppard AMS180001

#pragma once

#include "TheaterSeat.h"

class Seat
{
    public:
        Seat ();
        Seat (TheaterSeat *);
        ~Seat ();
        TheaterSeat * getTheaterSeat () { return this->theaterSeat; }
    protected:
    private:
        TheaterSeat *theaterSeat;
};
