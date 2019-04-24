// In Class Assignment 3
// Anja Sheppard AMS180001
// Kyle Custodio KYC180000

#include "File.h"
#include <string>
#include <iostream>
#include <fstream>

File::File (std::string p, std::string f, std::string t) : Document (t)
{
    pathName = p;
    fileName = f;
}

std::ostream& operator<< (std::ostream& osObject, const File file)
{
    osObject << file.text << std::endl;
    return osObject;
}
