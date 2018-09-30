#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        Node();
        virtual ~Node();
        unsigned int Getrow() { return row; }
        void Setrow(unsigned int val) { row = val; }
        unsigned char Getseat() { return seat; }
        void Setseat(unsigned char val) { seat = val; }
        bool Getreserved() { return reserved; }
        void Setreserved(bool val) { reserved = val; }
        unsigned char GetticketType() { return ticketType; }
        void SetticketType(unsigned char val) { ticketType = val; }
    protected:
    private:
        unsigned int row;
        unsigned char seat;
        bool reserved;
        unsigned char ticketType;
};

#endif // NODE_H
