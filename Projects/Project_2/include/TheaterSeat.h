// Project 2
// Anja Sheppard AMS180001

#pragma once

#include <Node.h>

class TheaterSeat : public Node
{
    public:
        TheaterSeat ();
        TheaterSeat (unsigned int, char, bool, char);
        ~TheaterSeat ();
        TheaterSeat * getUp () { return up; }
        void setUp (TheaterSeat *val) { up = val; }
        TheaterSeat * getDown () { return down; }
        void setDown (TheaterSeat *val) { down = val; }
        TheaterSeat * getLeft () { return left; }
        void setLeft (TheaterSeat *val) { left = val; }
        TheaterSeat * getRight () { return right; }
        void setRight (TheaterSeat *val) { right = val; }
    protected:
    private:
        TheaterSeat *up;
        TheaterSeat *down;
        TheaterSeat *left;
        TheaterSeat *right;
};
