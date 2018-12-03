// Project 4
// Anja Sheppard

#include "Order.h"

Order::Order ()
{
    this->auditorium = 0;
    this->seats = nullptr;
    this->numSeats = 0;
    this->numAdultTickets = 0;
    this->numChildTickets = 0;
    this->numSeniorTickets = 0;
}

Order::Order (unsigned int a)
{
    this->auditorium = a;
    this->seats = new Seat*[0];
    this->numSeats = 0;
    this->numAdultTickets = 0;
    this->numChildTickets = 0;
    this->numSeniorTickets = 0;
}

Order::~Order ()
{
    delete this->seats;
}

std::ostream& operator<< (std::ostream& out, const Order& o)
{
    out << o.auditorium << "\t\t" << o.numAdultTickets << "\t" << o.numChildTickets << "\t" << o.numSeniorTickets << "\t\t";
    for (size_t i = 0; i < o.numSeats; ++i)
    {
        out << o.seats[i]->getTheaterSeat()->getRow()+1 << o.seats[i]->getTheaterSeat()->getSeat() << "(" << o.seats[i]->getTheaterSeat()->getTicketType() << ")  ";
    }
    out << std::endl;
    return out;
}

void Order::appendSeat (Seat *newSeat)
{
    Seat ** newSeats = new Seat*[this->numSeats+1];
    for (size_t i = 0; i < this->numSeats; ++i)
    {
        newSeats[i] = this->seats[i];
    }
    newSeats[this->numSeats] = newSeat;
    this->numSeats++;
    delete this->seats;
    this->seats = newSeats;
}

void s (Seat ** & a, Seat ** & b)
{
    a = b;
}

void Order::deleteSeat (Seat *deleteSeat)
{
    Seat ** newSeats = new Seat*[this->numSeats-1];
    Seat *** newSeatsPtr = &newSeats;
    std::cout << deleteSeat->getTheaterSeat()->getRow() << std::endl;
    for (size_t i = 0, j = 0; i < this->numSeats; ++i)
    {
        if (this->seats[i]->getTheaterSeat()->getRow() == deleteSeat->getTheaterSeat()->getRow() && this->seats[i]->getTheaterSeat()->getSeat() == deleteSeat->getTheaterSeat()->getSeat())
        {
            // skip this seat
            deleteSeat->getTheaterSeat()->setReserved(false);
            deleteSeat->getTheaterSeat()->setTicketType('.');
            j--;
            //delete deleteSeat;
        }
        else
            newSeats[j] = this->seats[i];
    }
    this->numSeats--;
    delete this->seats;
    s(this->seats, newSeats);
}
