#include "TheaterSeat.h"

TheaterSeat::TheaterSeat ()
{
    //ctor
}

TheaterSeat::TheaterSeat (unsigned int rowL, unsigned char seatL, bool reservedL, unsigned char ticketTypeL)
{
    this->setRow(rowL);
    this->setSeat(seatL);
    this->setReserved(reservedL);
    this->setTicketType(ticketTypeL);
}

TheaterSeat::~TheaterSeat ()
{
    //dtor
}
