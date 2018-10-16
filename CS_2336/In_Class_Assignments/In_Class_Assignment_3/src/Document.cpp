// In Class Assignment 3
// Anja Sheppard AMS180001
// Kyle Custodio KYC180000

#include "Document.h"
#include <iostream>
#include <fstream>

std::ostream& operator<< (std::ostream& osObject, const Document doc)
{
    osObject << doc.text << std::endl;
    return osObject;
}
