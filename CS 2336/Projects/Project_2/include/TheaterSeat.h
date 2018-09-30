#ifndef THEATERSEAT_H
#define THEATERSEAT_H

#include <Node.h>


class TheaterSeat : public Node
{
    public:
        TheaterSeat();
        ~TheaterSeat();
        TheaterSeat Get*up() { return *up; }
        void Set*up(TheaterSeat val) { *up = val; }
        TheaterSeat Get*down() { return *down; }
        void Set*down(TheaterSeat val) { *down = val; }
        TheaterSeat Get*left() { return *left; }
        void Set*left(TheaterSeat val) { *left = val; }
        TheaterSeat Get*right() { return *right; }
        void Set*right(TheaterSeat val) { *right = val; }
    protected:
    private:
        TheaterSeat *up;
        TheaterSeat *down;
        TheaterSeat *left;
        TheaterSeat *right;
};

#endif // THEATERSEAT_H
