// In Class Assignment 3
// Anja Sheppard AMS180001
// Kyle Custodio KYC180000

#ifndef EMAIL_H
#define EMAIL_H

#include <string>
#include <iostream>
#include <fstream>
#include "Document.h"

class EMail : public Document
{
    public:
        EMail ();
        EMail (std::string, std::string, std::string, std::string);
        std::string getSender() { return sender; }
        void setSender(std::string val) { sender = val; }
        std::string getRecipient() { return recipient; }
        void setRecipient(std::string val) { recipient = val; }
        std::string getTitle() { return title; }
        void setTitle(std::string val) { title = val; }
        friend std::ostream& operator<< (std::ostream&, const EMail);
    protected:
    private:
        std::string sender;
        std::string recipient;
        std::string title;
};

#endif // EMAIL_H
