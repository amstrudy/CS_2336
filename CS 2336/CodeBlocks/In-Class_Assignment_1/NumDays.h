#include <iostream>

#ifndef NUM_DAYS
#define NUM_DAYS

class NumDays
{
private:
    float hours;
    float days;
public:
    NumDays () {hours = 0; days = 0;}
    NumDays (float h) {hours = h; days = h/8;}
    NumDays (const NumDays &nd) {hours = nd.hours; days = nd.days;};
    float getHours () {return hours;}
    float getDays () {return days;}
    void setHours (float h) {hours = h; days = h/8;}
    void setDays (float d) {hours = d * 8; days = d;}
    float operator+ (NumDays nd) {return hours + nd.hours;}
    float operator- (NumDays nd) {return hours - nd.hours;}
    NumDays operator++ () {hours++; days = hours/8; return *this;} // prefix
    NumDays operator++ (int) {NumDays temp = *this; hours++; days = hours/8; return temp;} // postfix
    bool operator< (NumDays nd) {return hours < nd.hours;}
    bool operator> (NumDays nd) {return hours > nd.hours;}
    friend std::ostream & operator<< (std::ostream &out, const NumDays &nd);// {out << "Hours: " << nd.hours << " "; out << "Days: " << nd.days << std::endl; return out;}
};

#endif
