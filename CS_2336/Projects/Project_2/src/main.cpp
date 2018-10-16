#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include "Node.h"
#include "TheaterSeat.h"
#include "Auditorium.h"

using namespace std;

void reserve (Auditorium&);

int main()
{
    cout << "Hello world!" << endl;
    Auditorium *a = new Auditorium();
    cout << "\n\n" << a->getFirst()->getTicketType() <<  "\n\n" << endl;
    cout << "\n\n" << a->getFirst()->getRight()->getTicketType() <<  "\n\n" << endl;
    a->print();
    cout << a->getFirst()->getRight()->getTicketType() << endl;
    a->userPrint();



    return 0;
}

void reserve (Auditorium& a)
{
    string menuSelectionS, rowNumS, numAS, numCS, numSS, startingSeatLetterS;
    unsigned int menuSelection = 0, rowNum, numA, numC, numS;
    char startingSeatLetter;
    unsigned int totalA = 0, totalC = 0, totalS = 0;

    while (menuSelection != 2)
    {
        cout << "Welcome to the seat reservation program for The Avengers 4!\n1. Reserve Seats\n2.Save and exit\nPlease select a menu option.\n" << endl;
        while (true) // continues until valid menu selection
        {
            cin >> menuSelectionS;
            if (menuSelection = stoi(menuSelectionS))
                break;
            else
                cout << "Invalid menu option. Please try again.\n" << endl;
        }
        cout << "Please see the seating map below. Available seats are marked with \".\"." << endl;
        a.userPrint();
        cout << endl;

        // GET VALID DESIRED ROW AND TICKET INFORMATION

        cout << "Please decide on your row number, starting seat number, number of adult tickets, number of child tickets, and number of senior tickets and enter them below.\n" << endl; 
        cout << "Enter desired row number: " << endl;
        while (true) // get row number and validate
        {
            cin >> rowNumS;
            if (!(rowNum = stoi(rowNumS)) || ((rowNum-1) < 0 || ((rowNum - 1) >= a.getLength())))
                std::cout << "Invalid input. Please try again.\n" << endl;
            else break;
        }
        cout << "Enter desired starting seat letter: " << endl;
        while (true) // get starting seat letter
        {
            cin >> startingSeatLetterS;
            if (startingSeatLetterS.length() == 1)
                startingSeatLetter = startingSeatLetterS[0];
                if (isalpha(toupper(startingSeatLetter)))
                    break;
            else
                cout << "Invalid input. Please try again.\n" << endl;
        }
        cout << "Enter desired number of adult tickets: " << endl;
        while (true) // get number of adult tickets
        {
            cin >> numAS;
            if (numA = stoi(numAS) && numA < a.getLength())
                break;
            else
                cout << "Invalid input. Please try again.\n" << endl;
        }
        cout << "Enter desired number of child tickets: " << endl;
        while (true) // get number of child tickets
        {
            cin >> numCS;
            if (numC = stoi(numCS) && (numA + numC) < a.getLength())
                break;
            else
                cout << "Invalid input. Please try again.\n" << endl;
        }
        cout << "Enter desired number of senior tickets: " << endl;
        while (true) // get number of senior tickets
        {
            cin >> numSS;
            if (numS = stoi(numSS) && (numA + numC + numS) < a.getLength())
                break;
            else
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
                    reserveConfirm = toupper(reserveConfirmS[0]);
                    if (reserveConfirm == 'Y' || reserveConfirm == 'N')
                        break;
                }
                else
                    cout << "Invalid input. Please try again.\n" << endl;
            }
            if (reserveConfirm == 'Y')
            {
                for (size_t i = 0; i < numA; ++i) // write adults
                    a.goTo(rowNum-1, startingSeatLetter-65+i)->setTicketType('A');
                for (size_t i = 0; i < numC; ++i) // write children
                    a.goTo(rowNum-1, startingSeatLetter-65+numA+i)->setTicketType('C');
                for (size_t i = 0; i < numS; ++i) // write seniors
                    a.goTo(rowNum-1, startingSeatLetter-65+numA+numC+i)->setTicketType('S');
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
            cout << "The seat choice you requested was no available.\n" << endl;
            int bA[2] = a.bestAvailable(rowNum, static_cast<unsigned int>(numA+numC+numS));
            if (bA[0] >= 0)
            {
                cout << "Luckily there is another option in the auditorium." << endl;
                cout << "You optimal seating arrangement for " << numA << " adult(s), " << numC << " child(ren), and " << numS << "senior(s) is on row " bA[0] << " and starts on seat " static_cast<char>(bA[1]+65) << ".\n" << endl;
                rowNum = bA[0];
                startingSeatLetter = static_cast<char>(bA[1]+65);
                string reserveConfirmS;
                char reserveConfirm;
                while (true)
                {
                    cin >> reserveConfirmS;
                    if (reserveConfirmS.length() == 1)
                    {
                        reserveConfirm = toupper(reserveConfirmS[0]);
                        if (reserveConfirm == 'Y' || reserveConfirm == 'N')
                            break;
                    }
                    else
                        cout << "Invalid input. Please try again.\n" << endl;
                }
                if (reserveConfirm == 'Y')
                {
                    for (size_t i = 0; i < numA; ++i) // write adults
                        a.goTo(rowNum-1][startingSeatLetter-65+i] = 'A';
                    for (size_t i = 0; i < numC; ++i) // write children
                        a.goTo(rowNum-1][startingSeatLetter-65+numA+i] = 'C';
                    for (size_t i = 0; i < numS; ++i) // write seniors
                        a.goTo(rowNum-1][startingSeatLetter-65+numA+numC+i] = 'S';
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
    a.writeOutput();
}