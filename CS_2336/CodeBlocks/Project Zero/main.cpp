// Project 1 Disneyland Dining Rewards
// Author: Anja Sheppard
// NetID: AMS180001
// Description: This is a system to keep track of customers and their various levels of discount for different food items bought at Disneyland.

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <cmath>
#include <ctype.h>
#define FILENAME "A1base.txt"

using namespace std;

void parseFile (char ***, unsigned int *, unsigned int *);
void reserve (char ***, unsigned int *, unsigned int *);
void userPrint (char ***, unsigned int *, unsigned int *);
bool isAvailable (char **, int, char, unsigned int);
int bestAvailable (char **, unsigned int, int, unsigned int);
void writeOutput (char **, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

int main ()
{
    char **seatingChart;
    unsigned int numRows = 1;
    unsigned int numCols = 0;
    parseFile(&seatingChart, &numRows, &numCols);
    reserve(&seatingChart, &numRows, &numCols);
    free(seatingChart);
    return 0;
}

void parseFile (char ***seatingChart, unsigned int *numRows, unsigned int *numCols)
{
    ifstream theater;
    theater.exceptions(ifstream::badbit);

    try
    {
        theater.open(FILENAME);
        string lineStr;
        getline(theater, lineStr);

         // get length of rows and cols
        for (size_t i = 0; lineStr[i] != '\0'; ++i)
            ++(*numCols);

        while (getline(theater, lineStr))
        {
            if (lineStr.length() >= 4) // make sure there isn't a new line character at the end
                ++(*numRows);
        }

        *seatingChart = (char**) malloc(sizeof(char *) * (*numRows)); // init 2d array

        for (size_t i = 0; i < *numRows; ++i)
        {
            (*seatingChart)[i] = (char (*)) malloc(sizeof(char) * (*numCols));
        }

        theater.clear(); // clear eof and reset pointer to beginning
        theater.seekg(0);
        unsigned int rowOn = 0;

        // now that lengths are known, read data into 2D array
        while (getline(theater, lineStr))
        {
            for (size_t i = 0; lineStr[i] != '\0'; ++i)
            {
                (*seatingChart)[rowOn][i] = lineStr[i];
            }
            rowOn++;
        }
    }
    catch (const ifstream::failure e)
    {
        cerr << "There was an error reading the file." << endl;
    }

    theater.close();
}

void reserve (char ***seatingChart, unsigned int *numRows, unsigned int *numCols)
{
    int menuSelection, rowNum, numA, numC, numS;
    int totalA = 0, totalC = 0, totalS = 0;
    char startingSeatLetter;

    while (true) // loop until quit (2) is selected, then write file
    {
        cout << "Welcome to the seat reservation program for The Avengers 4!\n1. Reserve Seats\n2. Exit\nPlease select a menu option.\n" << endl;
        cin >> menuSelection;

        if (menuSelection == 2) break;
        else if (menuSelection == 1)
        {
            // get user input on seat choices
            cout << "Please see the seating map below. Available seats are marked with \".\".\n" << endl;
            userPrint(seatingChart, numRows, numCols);
            cout << endl;

            cout << "Please decide on your row number, starting seat letter, number of adult tickets, number of child tickets, and number of senior tickets and enter them below.\n" << endl;
            while (true)
            {
                cout << "Enter desired row number: " << flush;
                cin >> rowNum;
                if ((rowNum-1) < 0 || (rowNum-1) >= (int)(*numRows))
                {
                    cout << "Your row number is out of bounds.\n" << endl;
                }
                else break;
            }
            while (true)
            {
                cout << "Enter desired starting seat letter: " << flush;
                cin >> startingSeatLetter;
                if ((startingSeatLetter < 'A') || (startingSeatLetter >= 'A'+(int)*numCols && startingSeatLetter < 'a') || (startingSeatLetter >= 'a'+(int)*numCols))
                {
                    cout << "Your starting seat letter is out of bounds.\n" << endl;
                }
                else break;
            }
            while (true)
            {
                cout << "Enter desired number of adult tickets: " << flush;
                cin >> numA;
                if (numA < 0 || numA > (int)(*numCols))
                {
                    cout << "The number of tickets you requested is invalid.\n" << endl;
                }
                else break;
            }
            while (true)
            {
                cout << "Enter desired number of child tickets: " << flush;
                cin >> numC;
                if (numC < 0 || (numC+numA) > (int)(*numCols))
                {
                    cout << "The number of tickets you requested is invalid.\n" << endl;
                }
                else break;
            }
            while (true)
            {
                cout << "Enter desired number of senior tickets: " << flush;
                cin >> numS;
                if (numS < 0 || (numS+numC+numA) > (int)(*numCols) || (numS+numC+numA) <= 0)
                {
                    cout << "The number of tickets you requested is invalid.\n" << endl;
                }
                else break;
            }

            // decide best possible seat arrangement
            if (isAvailable(*seatingChart, rowNum, startingSeatLetter, (unsigned int)(numA + numC + numS)))
            {
                cout << "Congratulations! The seat choice you made is available. Enter \"Y\" if you want to confirm your reservation, and \"N\" if you want to cancel." << endl;
                char reserveConfirm;
                cin >> reserveConfirm;
                if (reserveConfirm == 89 || reserveConfirm == 121) // confirmed yes, so now reservation is written to 2D array
                    {
                        for (size_t i = 0; (int)i < numA; ++i) // write adults
                        {
                            (*seatingChart)[rowNum-1][((int)toupper(startingSeatLetter)-65)+i] = 'A';
                        }
                        for (size_t i = 0; (int)i < numC; ++i) // write children
                        {
                            (*seatingChart)[rowNum-1][((int)toupper(startingSeatLetter)-65)+numA+i] = 'C';
                        }
                        for (size_t i = 0; (int)i < numS; ++i) // write seniors
                        {
                            (*seatingChart)[rowNum-1][((int)toupper(startingSeatLetter)-65)+numA+numC+i] = 'S';
                        }

                        totalA += numA; // keep track of total number of tickets sold
                        totalC += numC;
                        totalS += numS;

                        cout << "\nYour reservation was successful. Thank you!\n\n" << endl;
                    }
                    else if (reserveConfirm == 78 || reserveConfirm == 110)
                    {
                        cout << "You have decided to cancel and will be taken back to the menu.\n" << endl;
                    }
                    else
                    {
                        cout << "You have entered an invalid input. Your reservation will now restart.\n" << endl;
                    }
            }
            else
            {
                // present alternative if seat is filled
                cout << "The seat choice you requested is not available.\n" << endl;
                int bA = bestAvailable(*seatingChart, *numCols, rowNum, (unsigned int)(numA + numC + numS));
                if (bA >= 0)
                {
                    cout << "Luckily there is another option on the row you selected.\n" << endl;
                    cout << "Your optimal seating arrangement for " << numA << " adult(s), " << numC << " child(ren), and " << numS << " senior(s) on row " << rowNum << " starts on seat " << (char)(65+bA) << ".\n" << endl;
                    char reserveConfirm;
                    cout << "Enter \"Y\" if you would like to confirm this reservation, and \"N\" if you want to cancel." << endl;
                    cin >> reserveConfirm;
                    if (reserveConfirm == 89 || reserveConfirm == 121) // confirmed yes, so now reservation is written to 2D array
                    {
                        for (size_t i = 0; (int)i < numA; ++i) // write adults
                        {
                            (*seatingChart)[rowNum-1][bA+i] = 'A';
                        }
                        for (size_t i = 0; (int)i < numC; ++i) // write children
                        {
                            (*seatingChart)[rowNum-1][bA+numA+i] = 'C';
                        }
                        for (size_t i = 0; (int)i < numS; ++i) // write seniors
                        {
                            (*seatingChart)[rowNum-1][bA+numA+numC+i] = 'S';
                        }

                        totalA += numA;
                        totalC += numC;
                        totalS += numS;

                        cout << "\nYour reservation was successful. Thank you!\n\n" << endl;
                    }
                    else if (reserveConfirm == 78 || reserveConfirm == 110)
                    {
                        cout << "You have decided to cancel and will be taken back to the menu.\n" << endl;
                    }
                    else
                    {
                        cout << "You have entered an invalid input. Your reservation will now restart.\n" << endl;
                    }
                }
            }
        }
        else
        {
            cout << "Your menu selection entry was invalid. Please try again.\n" << endl;
        }
    }
    // now the loop has ended, so file is written and output is printed
    writeOutput((*seatingChart), *numRows, *numCols, totalA, totalC, totalS);
}

void userPrint (char *** seatingChart, unsigned int *numRows, unsigned int *numCols) // prints theater with # for user
{
    cout << "  " << flush;

    for (size_t i = 0; i < *numCols; ++i)
    {
        cout << (char)(65+i) << flush;
    }

    cout << endl;

    for (size_t i = 0; i < *numRows; ++i)
    {
        cout << i+1 << " " << flush;
        for (size_t j = 0; j < *numCols; ++j)
        {
            if ((*seatingChart)[i][j] == '.')
            {
                cout << (*seatingChart)[i][j] << flush;
            }
            else // don't display A, C, S
            {
                cout << "#" << flush;
            }
        }
        cout << endl;
    }
}

bool isAvailable (char ** seatingChart, int rowNum, char startingSeatLetter, unsigned int numSeats) // checks whether the preferred seating arrangement is possible
{
    for (size_t i = 0; i < numSeats; ++i)
    {
        if (seatingChart[rowNum-1][(toupper(startingSeatLetter)-65)+i] != '.')
        {
            return false;
        }
    }
    return true;
}

int bestAvailable (char ** seatingChart, unsigned int numCols, int rowNum, unsigned int numSeats) // returns best starting seat, if none possible returns -1
{
    int minDist = numCols, minSeatNum = -1, dist;
    bool broken = false;
    size_t i;
    for (i = 0; i < numCols; ++i) // repeat until minDist is found
    {
        if (numCols - i >= numSeats) // make sure there are enough seats left in the row
        {
            for (size_t j = 0; j < numSeats; ++j) // run through seats to ensure they are empty
            {
                if (seatingChart[rowNum-1][j+i] != '.')
                {
                    broken = true;
                }
            }
            if (broken == false)
            {
                dist = (((double)numCols + 1.0) / 2.0) - ((double)i + ((double)numSeats / 2.0));
                if (dist < 0) dist *= -1; // absolute value
                if (dist <= minDist) // if there are two possible options, then the rightmost option is shown
                {
                    minDist = dist;
                    minSeatNum = (int)i;
                }

                if (minDist == 0) return (int) i;
            }
            broken = false;
        }
    }
    return minSeatNum; // if minSeatNum is still -1, then no solution was found
}

void writeOutput (char ** seatingChart, unsigned int numRows, unsigned int numCols, unsigned int numA, unsigned int numC, unsigned int numS)
{
    // write output to file
    ofstream theater;
    theater.open(FILENAME, ofstream::out);

    for (size_t i = 0; i < numRows; ++i)
    {
        for (size_t j = 0; j < numCols; ++j)
        {
            theater << seatingChart[i][j];
        }
        theater << "\n";
    }
    theater.close();

    // write output to command line
    string s1 = "Total Seats in Auditorium:";
    string s2 = "Total Tickets Sold:";
    string s3 = "Adult Tickets Sold:";
    string s4 = "Child Tickets Sold:";
    string s5 = "Senior Tickets Sold:";
    string s6 = "Total Ticket Sales:";
    double totalSales = (numA*10.) + (numC*5.) + (numS*7.5);
    cout << left << "AUDITORIUM FINAL REPORT\n" << endl;
    cout << s1 << right << setw(50 - (int)s1.length()) << numRows * numCols << endl;
    cout << s2 << right << setw(50 - (int)s2.length()) << numA + numC + numS << endl;
    cout << s3 << right << setw(50 - (int)s3.length()) << numA << endl;
    cout << s4 << right << setw(50 - (int)s4.length()) << numC << endl;
    cout << s5 << right << setw(50 - (int)s5.length()) << numS << endl;
    cout << s6 << flush;
    for (size_t i = 0; i < (50 - s6.length() - (to_string(totalSales)).length() + 3); ++i) cout << " " << flush;
    cout << "$" << fixed << setprecision(2) << totalSales << "\n\n\n" << endl;
}
