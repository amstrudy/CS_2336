// In Class Assignment 3
// Anja Sheppard AMS180001
// Kyle Custodio KYC180000

#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>
#include <fstream>
#include "Document.h"

class File : public Document
{
    public:
        File ();
        File (std::string, std::string, std::string);
        std::string getPathName () { return pathName; }
        void setPathName (std::string val) { pathName = val; }
        std::string getFileName () { return fileName; }
        void setFileName (std::string val) { fileName = val; }
        friend std::ostream& operator<< (std::ostream&, const File);
    protected:
    private:
        std::string pathName;
        std::string fileName;
};

#endif // FILE_H
