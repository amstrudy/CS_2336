// In Class Assignment 3
// Anja Sheppard AMS180001
// Kyle Custodio KYC180000

#include <iostream>
#include "Document.h"
// In Class Assignment 3
// Anja Sheppard AMS180001
// Kyle Custodio KYC180000

#include "EMail.h"
#include "File.h"

using namespace std;

bool containsKeyword (Document *, string);

int main()
{
    Document *doc = new Document("Hey");
    cout << *doc << endl;
    EMail *mail = new EMail ("Kyle", "Anja", "Hello", "CS");
    cout << *mail << endl;
    File *file = new File ("/bin", "f.txt", "Hello World");
    cout << *file << endl;
    string test = "Hello";
    cout << "Doc contains Hello? " << containsKeyword(doc, test) << endl;
    cout << "EMail contains Hello? " << containsKeyword(mail, test) << endl;
    cout << "File contains Hello? " << containsKeyword(file, test) << endl;

    return 0;
}

bool containsKeyword (Document *doc, string str)
{
    // check if email
    EMail *e = dynamic_cast<EMail*>(doc);
    if (e != nullptr)
    {
        return ((e->getSender()).find(str) != (e->getSender()).npos) || ((e->getRecipient()).find(str) != (e->getRecipient()).npos) ||
                ((e->getTitle()).find(str) != (e->getTitle()).npos) || ((e->getText()).find(str) != (e->getText()).npos);
    }
    // check if file
    File *f = dynamic_cast<File*>(doc);
    if (f != nullptr)
    {
        return ((f->getPathName()).find(str) != (f->getPathName()).npos) || ((f->getPathName()).find(str) != (f->getPathName()).npos) ||
                ((f->getPathName()).find(str) != (f->getPathName()).npos) || ((f->getText()).find(str) != (f->getText()).npos);
    }
    // if doc
    return (doc->getText()).find(str) != (doc->getText()).npos;
}
