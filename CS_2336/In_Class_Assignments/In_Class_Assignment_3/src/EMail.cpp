// In Class Assignment 3
// Anja Sheppard AMS180001
// Kyle Custodio KYC180000

#include "EMail.h"
#include <string>
#include <iostream>
#include <fstream>

EMail::EMail (std::string s, std::string r, std::string t, std::string text) : Document (text)
{
    sender = s;
    recipient = r;
    title = t;
}

std::ostream& operator<< (std::ostream& osObject, const EMail mail)
{
    osObject << mail.sender << "\n" << mail.recipient << "\n" << mail.title << std::endl;
    osObject << mail.text << std::endl;
    return osObject;
}
