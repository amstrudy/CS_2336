// In Class Assignment 3
// Anja Sheppard AMS180001
// Kyle Custodio KYC180000

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>
#include <fstream>
#include <string>

class Document
{
    public:
        Document ();
        Document (std::string s) { text = s; }
        virtual ~Document () {}
        std::string getText() { return text; }
        void setText(std::string val) { text = val; }
        friend std::ostream& operator<< (std::ostream&, const Document);
    protected:
        std::string text;
    private:
};

#endif // DOCUMENT_H
