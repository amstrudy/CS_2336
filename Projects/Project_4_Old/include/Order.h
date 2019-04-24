// Project 4
// Anja Sheppard AMS180001

#pragma once

#include <iostream>
#include "Seat.h"

class Order
{
    public:
        Order();
        Order (unsigned int);
        ~Order();
        unsigned int getAuditorium () { return this->auditorium; }
        void setAuditorium (unsigned int var) { this->auditorium = var; }
        Seat ** getSeats () { return this->seats; }
        void setSeats (Seat **var) { this->seats = var; }
        unsigned int getNumSeats () { return this->numSeats; }
        void setNumSeats (unsigned int var) { this->numSeats = var; }
        unsigned int getNumAdultTickets () { return this->numAdultTickets; }
        void setNumAdultTickets (unsigned int var) { this->numAdultTickets = var; }
        unsigned int getNumChildTickets () { return this->numChildTickets; }
        void setNumChildTickets (unsigned int var) { this->numChildTickets = var; }
        unsigned int getNumSeniorTickets () { return this->numSeniorTickets; }
        void setNumSeniorTickets (unsigned int var) { this->numSeniorTickets = var; }
        Seat *** getSeatsPtr () { return &(this->seats); }
        friend std::ostream& operator<< (std::ostream&, const Order&);
        void appendSeat (Seat *);
        void deleteSeat (Seat *);
    protected:
    private:
        unsigned int auditorium;
        Seat **seats;
        unsigned int numSeats;
        unsigned int numAdultTickets;
        unsigned int numChildTickets;
        unsigned int numSeniorTickets;
};
