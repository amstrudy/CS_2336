// Project 2
// Anja Sheppard AMS180001

#include "TheaterSeat.h"

TheaterSeat::TheaterSeat ()
{
    //ctor
}

TheaterSeat::TheaterSeat (unsigned int rowL, char seatL, bool reservedL, char ticketTypeL)
{
    this->setRow(rowL);
    this->setSeat(seatL);
    this->setReserved(reservedL);
    this->setTicketType(ticketTypeL);
}

TheaterSeat::~TheaterSeat ()
{
    delete this;
}
