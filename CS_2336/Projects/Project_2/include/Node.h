#pragma once

class Node
{
    public:
        Node ();
        virtual ~Node ();
        unsigned int getRow () { return row; }
        void setRow (unsigned int val) { row = val; }
        unsigned char getSeat () { return seat; }
        void setSeat (unsigned char val) { seat = val; }
        bool getReserved () { return reserved; }
        void setReserved (bool val) { reserved = val; }
        unsigned char getTicketType () { return ticketType; }
        void setTicketType (unsigned char val) { ticketType = val; }
    protected:
    private:
        unsigned int row;
        unsigned char seat;
        bool reserved;
        unsigned char ticketType;
};
