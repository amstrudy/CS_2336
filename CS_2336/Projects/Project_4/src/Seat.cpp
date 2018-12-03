// Project 4
// Anja Sheppard AMS180001

#include "Seat.h"

Seat::Seat ()
{
    this->theaterSeat = nullptr;
}

Seat::Seat (TheaterSeat *ts)
{
    this->theaterSeat = ts;
}

Seat::~Seat ()
{

}
