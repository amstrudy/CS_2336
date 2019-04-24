
#include "NumDays.h"

std::ostream& operator<<(std::ostream& out, const NumDays& obj)
{
    out << obj.hours << " " << obj.days << std::endl;
    return out;
}
