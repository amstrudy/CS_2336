// Project 2
// Anja Sheppard AMS180001

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <iomanip>
#include "Node.h"
#include "TheaterSeat.h"
#include "Auditorium.h"

using namespace std;

void reserve (Auditorium&);

int main()
{
    Auditorium *a = new Auditorium();
    reserve(*a);

    return 0;
}

void reserve (Auditorium& a)
{
    string menuSelectionS, rowNumS, numAS, numCS, numSS, startingSeatLetterS; // first get all command line inputs as strings to check type
    unsigned int menuSelection, rowNum, numA, numC, numS;
    char startingSeatLetter;

    while (true)
    {
        cout << "Welcome to the seat reservation program for The Avengers 4!\n1. Reserve Seats\n2. Save and exit\nPlease select a menu option.\n" << endl;
        while (true) // continues until valid menu selection
        {
            cin >> menuSelectionS;
            if (menuSelectionS.find_first_not_of("12"))
            {
                menuSelection = stoi(menuSelectionS);
                break;
            }
            else
                cout << "Invalid menu option. Please try again.\n" << endl;
        }
        if (menuSelection == 1)
        {
            cout << "Please see the seating map below. Available seats are marked with \".\"." << endl;
            a.userPrint();
            cout << endl;

            // GET VALID DESIRED ROW AND TICKET INFORMATION

            cout << "Please decide on your row number, starting seat number, number of adult tickets, number of child tickets, and number of senior tickets and enter them below.\n" << endl; 
            cout << "Enter desired row number: " << endl;
            while (true) // get row number and validate
            {
                cin >> rowNumS;
                if (rowNumS.find_first_not_of("1234567890") == string::npos)
                {
                    rowNum = stoi(rowNumS);
                    if (rowNum > 0 && rowNum <= a.getLength())
                        break;
                }
                cout << "Invalid input. Please try again.\n" << endl;
            }
            cout << "Enter desired starting seat letter: " << endl;
            while (true) // get starting seat letter
            {
                cin >> startingSeatLetterS;
                if (startingSeatLetterS.length() == 1)
                {
                    startingSeatLetter = toupper(startingSeatLetterS[0]);
                    if (isalpha(startingSeatLetter))
                    {
                        if (startingSeatLetter - 65 < static_cast<int>(a.getLength()))
                            break;
                    }
                }
                cout << "Invalid input. Please try again.\n" << endl;
            }
            cout << "Enter desired number of adult tickets: " << endl;
            while (true) // get number of adult tickets
            {
                cin >> numAS;
                if (numAS.find_first_not_of("1234567890") == string::npos)
                {
                    numA = stoi(numAS);
                    if (numA < a.getLength())
                        break;
                }
                cout << "Invalid input. Please try again.\n" << endl;
            }
            cout << "Enter desired number of child tickets: " << endl;
            while (true) // get number of child tickets
            {
                cin >> numCS;
                if (numCS.find_first_not_of("1234567890") == string::npos)
                {
                    numC = stoi(numCS);
                    if (numC < a.getLength())
                        break;
                }
                cout << "Invalid input. Please try again.\n" << endl;
            }
            cout << "Enter desired number of senior tickets: " << endl;
            while (true) // get number of senior tickets
            {
                cin >> numSS;
                if (numSS.find_first_not_of("1234567890") == string::npos)
                {
                    numS = stoi(numSS);
                    if (numS < a.getLength())
                        break;
                }
                cout << "Invalid input. Please try again.\n" << endl;
            }

            // FIND BEST POSSIBLE OPTION

            if (a.isAvailable(rowNum, startingSeatLetter, static_cast<unsigned int>(numA+numC+numS))) // chosen configuration is available
            {
                cout << "Congratulations! The seat choice you made is available. Enter \"Y\" if you would like to confirm your reservation and \"N\" if you want to cancel." << endl;
                string reserveConfirmS;
                char reserveConfirm;
                while (true)
                {
                    cin >> reserveConfirmS;
                    if (reserveConfirmS.length() == 1)
                    {
                        reserveConfirm = static_cast<char>(toupper(reserveConfirmS[0]));
                        if (reserveConfirm == 'Y' || reserveConfirm == 'N')
                            break;
                    }
                    else
                        cout << "Invalid input. Please try again.\n" << endl;
                }
                if (reserveConfirm == 'Y')
                {
                    for (size_t i = 0; i < numA; ++i) // write adults
                    {
                        a.goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+i))->setTicketType('A');
                        a.goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+i))->setReserved(true);
                    }
                    for (size_t i = 0; i < numC; ++i) // write children
                    {
                        a.goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+numA+i))->setTicketType('C');
                        a.goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+numA+i))->setReserved(true);
                    }
                    for (size_t i = 0; i < numS; ++i) // write seniors
                    {
                        a.goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+numA+numC+i))->setTicketType('S');
                        a.goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+numA+numC+i))->setReserved(true);
                    }
                    a.setTotalA(a.getTotalA() + numA);
                    a.setTotalC(a.getTotalC() + numC);
                    a.setTotalS(a.getTotalS() + numS);

                    cout << "Your reservation was successful. Thank you!\n\n" << endl;
                }
                else
                {
                    cout << "You have decided to cancel and will be taken back to the main menu.\n\n" << endl;
                }
            }
            else // chosen configuration is not available
            {
                cout << "The seat choice you requested was not available.\n" << endl;
                int *bA = a.bestAvailable(static_cast<unsigned int>(numA+numC+numS));
                if (bA[0] >= 0)
                {
                    cout << "Luckily there is another option in the auditorium." << endl;
                    cout << "You optimal seating arrangement for " << numA << " adult(s), " << numC << " child(ren), and " << numS << " senior(s) is on row " << bA[0]+1 << " and starts on seat " << static_cast<char>(bA[1]+65) << ".\n" << endl;
                    cout << "Enter \"Y\" if you would like to confirm your reservation and \"N\" if you want to decline.\n" << endl;
                    rowNum = bA[0]+1;
                    startingSeatLetter = static_cast<char>(bA[1]+65);
                    string reserveConfirmS;
                    char reserveConfirm;
                    while (true)
                    {
                        cin >> reserveConfirmS;
                        if (reserveConfirmS.length() == 1)
                        {
                            reserveConfirm = static_cast<char>(toupper(reserveConfirmS[0]));
                            if (reserveConfirm == 'Y' || reserveConfirm == 'N')
                                break;
                        }
                        else
                            cout << "Invalid input. Please try again.\n" << endl;
                    }
                    if (reserveConfirm == 'Y')
                    {
                        for (size_t i = 0; i < numA; ++i) // write adults
                        {
                            a.goTo(rowNum-1, startingSeatLetter-65+static_cast<unsigned int>(i))->setTicketType('A');
                            a.goTo(rowNum-1, startingSeatLetter-65+static_cast<unsigned int>(i))->setReserved(true);
                        }
                        for (size_t i = 0; i < numC; ++i) // write children
                        {
                            a.goTo(rowNum-1, startingSeatLetter-65+numA+static_cast<unsigned int>(i))->setTicketType('C');
                            a.goTo(rowNum-1, startingSeatLetter-65+numA+static_cast<unsigned int>(i))->setReserved(true);
                        }
                        for (size_t i = 0; i < numS; ++i) // write seniors
                        {
                            a.goTo(rowNum-1, startingSeatLetter-65+numA+numC+static_cast<unsigned int>(i))->setTicketType('S');
                            a.goTo(rowNum-1, startingSeatLetter-65+numA+numC+static_cast<unsigned int>(i))->setReserved(true);
                        }
                        a.setTotalA(a.getTotalA() + numA);
                        a.setTotalC(a.getTotalC() + numC);
                        a.setTotalS(a.getTotalS() + numS);

                    cout << "Your reservation was successful. Thank you!\n\n" << endl;
                    }
                    else
                    {
                        cout << "You have decided to cancel and will be taken back to the main menu.\n\n" << endl;
                    }
                }
                else
                {
                    cout << "There are no possible configurations of the seats you chose. You will be taken back to the main menu.\n\n" << endl;
                }
            }
        }
        else
            break;
    }
    a.writeOutput();
}
