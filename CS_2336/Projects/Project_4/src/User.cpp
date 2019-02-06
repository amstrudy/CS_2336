// Project 4
// Anja Sheppard AMS180001

#include <iostream>
#include <fstream>
#include "User.h"
#include "Seat.h"

void deleteOrder (Order ** &, unsigned int&, unsigned int);

User::User ()
{
    this->username = "";
    this->password = "";
    this->key = nullptr;
    this->ordersList1 = new Order*[0];
    this->ordersList2 = new Order*[0];
    this->ordersList3 = new Order*[0];
    this->ordersList1Length = 0;
    this->ordersList2Length = 0;
    this->ordersList3Length = 0;
    this->isAdmin = false;
}

User::User (std::string user, std::string pass, bool iA)
{
    this->username = user;
    this->password = pass;
    this->key = new String(this->username);
    this->ordersList1 = new Order*[0];
    this->ordersList2 = new Order*[0];
    this->ordersList3 = new Order*[0];
    this->ordersList1Length = 0;
    this->ordersList2Length = 0;
    this->ordersList3Length = 0;
    this->isAdmin = iA;
}

User::~User ()
{
    for (size_t i = 0; i < this->ordersList1Length; ++i)
    {
        delete [] this->ordersList1[i];
    }
    delete [] this->ordersList1;
    for (size_t i = 0; i < this->ordersList2Length; ++i)
    {
        delete [] this->ordersList2[i];
    }
    delete [] this->ordersList2;
    for (size_t i = 0; i < this->ordersList3Length; ++i)
    {
        delete [] this->ordersList3[i];
    }
    delete [] this->ordersList3;
    delete this->key;
}

void User::addOrder (auditorium a, Order *newOrder)
{
    if (a == A_ONE)
        this->append(1, newOrder);
    else if (a == A_TWO)
        this->append(2, newOrder);
    else if (a == A_THREE)
        this->append(3, newOrder);
    else
    {
        std::cerr << "This auditorium is invalid." << std::endl;
        exit(1);
    }
}

std::ostream& operator<< (std::ostream& out, const User& u)
{
    out << u.key->getDatum() << std::flush;
    return out;
}

void User::reserve (Auditorium *auditorium1, Auditorium *auditorium2, Auditorium *auditorium3)
{
    std::string auditoriumNumS, rowNumS, numAS, numCS, numSS, startingSeatLetterS; // first get all command line inputs as strings to check type
    unsigned int auditoriumNum, rowNum, numA, numC, numS;
    char startingSeatLetter;
    Auditorium *chosenAuditorium;

    // AUDITORIUM NUM
    while (true)
    {
        std::cout << "Please select which auditorium you would like to reserve seats from (1-3): " << std::flush;
        std::cin >> auditoriumNumS;
        if (auditoriumNumS == "1" || auditoriumNumS == "2" || auditoriumNumS == "3")
        {
            auditoriumNum = stoi(auditoriumNumS);
            if (auditoriumNum == 1)
                chosenAuditorium = auditorium1;
            else if (auditoriumNum == 2)
                chosenAuditorium = auditorium2;
            else if (auditoriumNum == 3)
                chosenAuditorium = auditorium3;
            else
                std::cerr << "There has been an error in selecting the auditorium." << std::endl;
            break;
        }
        else
        {
            std::cerr << "Not a valid auditorium choice. Please try again." << std::endl;
        }
    }

    std::cout << "Please see the seating map below for Auditorium #" << auditoriumNum << ". Available seats are marked with \".\"." << std::endl;
    chosenAuditorium->userPrint();
    std::cout << std::endl;

    // ROW NUMBER
    while (true)
    {
        std::cout << "Enter desired row number: " << std::flush;
        std::cin >> rowNumS;
        bool valid = true;
        for (size_t i = 0; i < rowNumS.length(); ++i)
        {
            if (!isdigit(rowNumS[i]))
            {
                std::cout << "Invalid input. Please try again.\n" << std::endl;
                valid = false;
            }
        }
        if (valid)
        {
            rowNum = stoi(rowNumS);
            if (rowNum > 0 && rowNum <= chosenAuditorium->getLength())
                break;
        }
    }

    // STARTING SEAT LETTER
    std::cout << "Enter desired starting seat letter: " << std::flush;
    while (true)
    {
        std::cin >> startingSeatLetterS;
        if (startingSeatLetterS.length() == 1)
        {
            startingSeatLetter = static_cast<char>(toupper(startingSeatLetterS[0]));
            if (isalpha(startingSeatLetter))
            {
                if (startingSeatLetter - 65 < static_cast<int>(chosenAuditorium->getLength()))
                    break;
            }
        }
        std::cout << "Invalid input. Please try again.\n" << std::endl;
    }
    
    // NUMBER ADULT
    std::cout << "Enter desired number of adult tickets: " << std::flush;
    while (true)
    {
        std::cin >> numAS;
        if (numAS.find_first_not_of("1234567890") == std::string::npos)
        {
            numA = stoi(numAS);
            if (numA <= chosenAuditorium->getLength())
                break;
        }
        std::cout << "Invalid input. Please try again.\n" << std::endl;
    }

    // NUMBER CHILD
    std::cout << "Enter desired number of child tickets: " << std::flush;
    while (true)
    {
        std::cin >> numCS;
        if (numCS.find_first_not_of("1234567890") == std::string::npos)
        {
            numC = stoi(numCS);
            if (numC <= chosenAuditorium->getLength())
                    break;
        }
        std::cout << "Invalid input. Please try again.\n" << std::endl;
    }
    
    // NUMBER SENIOR
    std::cout << "Enter desired number of senior tickets: " << std::flush;
    while (true)
    {
        std::cin >> numSS;
        if (numSS.find_first_not_of("1234567890") == std::string::npos)
        {
            numS = stoi(numSS);
            if (numS <= chosenAuditorium->getLength())
                break;
        }
        std::cout << "Invalid input. Please try again.\n" << std::endl;
    }

    // FIND BEST POSSIBLE OPTION

    if (chosenAuditorium->isAvailable(rowNum, startingSeatLetter, static_cast<unsigned int>(numA+numC+numS))) // chosen configuration is available
    {
        std::cout << "Congratulations! The seat choice you made is available. Enter \"Y\" if you would like to confirm your reservation and \"N\" if you want to cancel." << std::flush;
        std::string reserveConfirmS;
        char reserveConfirm;
        while (true)
        {
            std::cin >> reserveConfirmS;
            if (reserveConfirmS.length() == 1 && isalpha(reserveConfirmS[0]))
            {
                reserveConfirm = static_cast<char>(toupper(reserveConfirmS[0]));
                if (reserveConfirm == 'Y' || reserveConfirm == 'N')
                    break;
            }
                else
                    std::cout << "Invalid input. Please try again.\n" << std::endl;
        }
        if (reserveConfirm == 'Y')
        {
            for (size_t i = 0; i < numA; ++i) // write adults
            {
                chosenAuditorium->goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+i))->setTicketType('A');
                chosenAuditorium->goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+i))->setReserved(true);
            }
            for (size_t i = 0; i < numC; ++i) // write children
            {
                chosenAuditorium->goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+numA+i))->setTicketType('C');
                chosenAuditorium->goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+numA+i))->setReserved(true);
            }
            for (size_t i = 0; i < numS; ++i) // write seniors
            {
                chosenAuditorium->goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+numA+numC+i))->setTicketType('S');
                chosenAuditorium->goTo(rowNum-1, static_cast<unsigned int>(startingSeatLetter-65+numA+numC+i))->setReserved(true);
            }
            chosenAuditorium->setTotalA(chosenAuditorium->getTotalA() + numA);
            chosenAuditorium->setTotalC(chosenAuditorium->getTotalC() + numC);
            chosenAuditorium->setTotalS(chosenAuditorium->getTotalS() + numS);

            std::cout << "Your reservation was successful. Thank you!\n\n" << std::endl;
        }
        else
        {
            std::cout << "You have decided to cancel and will be taken back to the main menu.\n\n" << std::endl;
        }
    }
    else // chosen configuration is not available
    {
        std::cout << "The seat choice you requested was not available.\n" << std::endl;
        int *bA = chosenAuditorium->bestAvailable(static_cast<unsigned int>(numA+numC+numS));
        if (bA[0] >= 0)
        {
            std::cout << "Luckily there is another option in the auditorium." << std::endl;
            std::cout << "You optimal seating arrangement for " << numA << " adult(s), " << numC << " child(ren), and " << numS << " senior(s) is on row " << bA[0]+1 << " and starts on seat " << static_cast<char>(bA[1]+65) << ".\n" << std::endl;
            std::cout << "Enter \"Y\" if you would like to confirm your reservation and \"N\" if you want to decline.\n" << std::flush;
            rowNum = bA[0]+1;
            startingSeatLetter = static_cast<char>(bA[1]+65);
            std::string reserveConfirmS;
            char reserveConfirm;
            while (true)
            {
                std::cin >> reserveConfirmS;
                if (reserveConfirmS.length() == 1)
                {
                    reserveConfirm = static_cast<char>(toupper(reserveConfirmS[0]));
                    if (reserveConfirm == 'Y' || reserveConfirm == 'N')
                        break;
                }
                else
                    std::cout << "Invalid input. Please try again.\n" << std::endl;
            }
            if (reserveConfirm == 'Y')
            {
                for (size_t i = 0; i < numA; ++i) // write adults
                {
                    chosenAuditorium->goTo(rowNum-1, startingSeatLetter-65+static_cast<unsigned int>(i))->setTicketType('A');
                    chosenAuditorium->goTo(rowNum-1, startingSeatLetter-65+static_cast<unsigned int>(i))->setReserved(true);
                }
                for (size_t i = 0; i < numC; ++i) // write children
                {
                    chosenAuditorium->goTo(rowNum-1, startingSeatLetter-65+numA+static_cast<unsigned int>(i))->setTicketType('C');
                    chosenAuditorium->goTo(rowNum-1, startingSeatLetter-65+numA+static_cast<unsigned int>(i))->setReserved(true);
                }
                for (size_t i = 0; i < numS; ++i) // write seniors
                {
                    chosenAuditorium->goTo(rowNum-1, startingSeatLetter-65+numA+numC+static_cast<unsigned int>(i))->setTicketType('S');
                    chosenAuditorium->goTo(rowNum-1, startingSeatLetter-65+numA+numC+static_cast<unsigned int>(i))->setReserved(true);
                }
                chosenAuditorium->setTotalA(chosenAuditorium->getTotalA() + numA);
                chosenAuditorium->setTotalC(chosenAuditorium->getTotalC() + numC);
                chosenAuditorium->setTotalS(chosenAuditorium->getTotalS() + numS);
                std::cout << "Your reservation was successful. Thank you!\n\n" << std::endl;
            }
            else
            {
                std::cout << "You have decided to cancel and will be taken back to the main menu.\n\n" << std::endl;
                return;
            }
        }
        else
        {
           std::cout << "There are no possible configurations of the seats you chose. You will be taken back to the main menu.\n\n" << std::endl;
           return;
        }
    }

    Order *newOrder = new Order(auditoriumNum);
    char onChar = startingSeatLetter;
    for (size_t i = 0; i < numA; ++i)
    {
        Seat *newSeat = new Seat(chosenAuditorium->goTo(rowNum-1, static_cast<int>(onChar) - 65));
        newSeat->getTheaterSeat()->setReserved(true);
        newSeat->getTheaterSeat()->setTicketType('A');
        newOrder->appendSeat(newSeat);
        onChar++;
    }
    for (size_t i = 0; i < numC; ++i)
    {
        Seat *newSeat = new Seat(chosenAuditorium->goTo(rowNum-1, static_cast<int>(onChar) - 65));
        newSeat->getTheaterSeat()->setReserved(true);
        newSeat->getTheaterSeat()->setTicketType('C');
        newOrder->appendSeat(newSeat);
        onChar++;
    }
    for (size_t i = 0; i < numS; ++i)
    {
        Seat *newSeat = new Seat(chosenAuditorium->goTo(rowNum-1, static_cast<int>(onChar) - 65));
        newSeat->getTheaterSeat()->setReserved(true);
        newSeat->getTheaterSeat()->setTicketType('S');
        newOrder->appendSeat(newSeat);
        onChar++;
    }
    newOrder->setNumAdultTickets(numA);
    newOrder->setNumChildTickets(numC);
    newOrder->setNumSeniorTickets(numS);
    if (auditoriumNum == 1)
        this->append(1, newOrder);
    else if (auditoriumNum == 2)
        this->append(2, newOrder);
    else if (auditoriumNum == 3)
        this->append(3, newOrder);
}

void User::view ()
{
    unsigned int count = 0;
    std::cout << "\n" << this->username << "'S ORDERS\n" << std::endl;
    std::cout << "Number\tAuditorium\tAdult\tChild\tSenior\t\tSeats" << std::endl;
    for (size_t i = 0; i < this->ordersList1Length; ++i)
    {
        std::cout << ++count << "\t" << *(this->ordersList1[i]) << std::endl;
    }
    for (size_t i = 0; i < this->ordersList2Length; ++i)
    {
        std::cout << ++count << "\t" << *(this->ordersList2[i]) << std::endl;
    }
    for (size_t i = 0; i < this->ordersList3Length; ++i)
    {
        std::cout << ++count << "\t" << *(this->ordersList3[i]) << std::endl;
    }
    if (this->ordersList1Length == 0 && this->ordersList2Length == 0 && this->ordersList3Length == 0)
        std::cout << "There are no orders to display." << std::endl;
}

void User::update (Auditorium *auditorium1, Auditorium *auditorium2, Auditorium *auditorium3)
{
    bool validInput = true, replaySubmenu = true;
    this->view();
    if (this->ordersList1Length == 0 && this->ordersList2Length == 0 && this->ordersList3Length == 0)
        return;
    std::string menuSelectionS = "";
    unsigned int menuSelection = 0;
    unsigned int cA = 0;
    Auditorium *currentAuditorium = nullptr;
    Order *currentOrder = nullptr;
    Order **currentOrdersList = nullptr;
    unsigned int currentOrdersListLength = 0;
    unsigned int index = 0;
    while (replaySubmenu)
    {
        replaySubmenu = false;
        while (true)
        {
            validInput = true;
            std::cout << "\nWhich order would you like to edit?" << std::flush; 
            std::cin >> menuSelectionS;
            for (size_t i = 0; i < menuSelectionS.length(); ++i)
            {
                if (static_cast<int>(menuSelectionS[i]) <= 47 || static_cast<int>(menuSelectionS[i]) >= 58)
                {
                    validInput = false;
                    break;
                }
            }
            if (validInput == false)
            {
                std::cout << "Invalid order number. Please try again." << std::endl;
            }
            else
            {
                menuSelection = stoi(menuSelectionS);
                if (menuSelection <= 0 || menuSelection > static_cast<unsigned int>(this->ordersList1Length+this->ordersList2Length+this->ordersList3Length))
                {
                    std::cout << "Invalid order number. Please try again." << std::endl;
                }
                else
                {
                    break;
                }
            }
        }

        // find order from order number
        if ((menuSelection - 1) < this->ordersList1Length) // part of the first list
        {
            index = menuSelection - 1;
            cA = 1;
            currentAuditorium = auditorium1;
            currentOrder = this->ordersList1[index];
            currentOrdersList = this->ordersList1;
            currentOrdersListLength = this->ordersList1Length;
        }
        else if ((menuSelection - 1) >= this->ordersList1Length && (menuSelection - 1) < this->ordersList2Length) // second list
        {
            index = menuSelection - 1 - this->ordersList1Length;
            cA = 2;
            currentAuditorium = auditorium2;
            currentOrder = this->ordersList2[index];
            currentOrdersList = this->ordersList2;
            currentOrdersListLength = this->ordersList2Length;
        }
        else if ((menuSelection - 1) >= (this->ordersList2Length+this->ordersList1Length) && (menuSelection - 1) < (this->ordersList3Length+this->ordersList2Length+this->ordersList1Length)) // second list
        {
            index = menuSelection - 1 - this->ordersList2Length - this->ordersList1Length;
            cA = 3;
            currentAuditorium = auditorium3;
            currentOrder = this->ordersList3[index];
            currentOrdersList = this->ordersList3;
            currentOrdersListLength = this->ordersList3Length;
        }

        while (true)
        {
            std::cout << "1. Add tickets to order\n2. Delete tickets from order\n3. Cancel order\n" << std::endl;
            std::cout << "Select an action: " << std::flush;
            std::cin >> menuSelectionS;
            if (menuSelectionS.length() == 1 && (menuSelectionS[0] == '1' || menuSelectionS[0] == '2' || menuSelectionS[0] == '3'))
            {
                menuSelection = stoi(menuSelectionS);
                break;
            }
            else
            {
                std::cout << "Invalid menu selection. Please try again." << std::endl;
            }
        }
        if (menuSelection == 1) // add to order
        {
            std::string rowNumS, numAS, numCS, numSS, startingSeatLetterS; // first get all command line inputs as strings to check type
            unsigned int rowNum, numA, numC, numS;
            char startingSeatLetter;

            // ROW NUMBER
            if (currentAuditorium == nullptr) std::cout << "NULL" << std::endl;

            std::cout << "Enter desired row number: " << std::flush;
            while (true)
            {
                std::cin >> rowNumS;
                if (rowNumS.find_first_not_of("1234567890") == std::string::npos)
                {
                    rowNum = stoi(rowNumS);
                    if (rowNum > 0 && rowNum <= currentAuditorium->getLength())
                        break;
                }
                else
                {
                    std::cout << "Invalid input. Please try again.\n" << std::endl;
                }
            }

            // STARTING SEAT LETTER
            std::cout << "Enter desired starting seat letter: " << std::flush;
            while (true)
            {
                std::cin >> startingSeatLetterS;
                if (startingSeatLetterS.length() == 1)
                {
                    startingSeatLetter = static_cast<char>(toupper(startingSeatLetterS[0]));
                    if (isalpha(startingSeatLetter))
                    {
                        if (startingSeatLetter - 65 < static_cast<int>(currentAuditorium->getLength()))
                            break;
                    }
                }
                std::cout << "Invalid input. Please try again.\n" << std::endl;
            }
    
            // NUMBER ADULT
            std::cout << "Enter desired number of adult tickets: " << std::flush;
            while (true)
            {
                std::cin >> numAS;
                if (numAS.find_first_not_of("1234567890") == std::string::npos)
                {
                    numA = stoi(numAS);
                    if (numA < currentAuditorium->getLength())
                        break;
                }
                std::cout << "Invalid input. Please try again.\n" << std::endl;
            }

            // NUMBER CHILD
            std::cout << "Enter desired number of child tickets: " << std::flush;
            while (true)
            {
                std::cin >> numCS;
                if (numCS.find_first_not_of("1234567890") == std::string::npos)
                {
                    numC = stoi(numCS);
                    if (numC < currentAuditorium->getLength())
                        break;
                }
                std::cout << "Invalid input. Please try again.\n" << std::endl;
            }
    
            // NUMBER SENIOR
            std::cout << "Enter desired number of senior tickets: " << std::flush;
            while (true)
            {
                std::cin >> numSS;
                if (numSS.find_first_not_of("1234567890") == std::string::npos)
                {
                    numS = stoi(numSS);
                    if (numS < currentAuditorium->getLength())
                        break;
                }
                std::cout << "Invalid input. Please try again.\n" << std::endl;
            }

            // CHECK IF OPEN
            if (currentAuditorium->isAvailable(rowNum, startingSeatLetter, 1))
            {
                char onChar = startingSeatLetter;
                for (size_t i = 0; i < numA; ++i)
                {
                    Seat *newSeat = new Seat(currentAuditorium->goTo(rowNum-1, static_cast<int>(onChar) - 65));
                    newSeat->getTheaterSeat()->setReserved(true);
                    newSeat->getTheaterSeat()->setTicketType('A');
                    currentOrder->appendSeat(newSeat);
                    onChar++;
                }
                for (size_t i = 0; i < numC; ++i)
                {
                    Seat *newSeat = new Seat(currentAuditorium->goTo(rowNum-1, static_cast<int>(onChar) - 65));
                    newSeat->getTheaterSeat()->setReserved(true);
                    newSeat->getTheaterSeat()->setTicketType('C');
                    currentOrder->appendSeat(newSeat);
                    onChar++;
                }
                for (size_t i = 0; i < numS; ++i)
                {
                    Seat *newSeat = new Seat(currentAuditorium->goTo(rowNum-1, static_cast<int>(onChar) - 65));
                    newSeat->getTheaterSeat()->setReserved(true);
                    newSeat->getTheaterSeat()->setTicketType('S');
                    currentOrder->appendSeat(newSeat);
                    onChar++;
                }
                currentOrder->setNumAdultTickets(currentOrder->getNumAdultTickets() + numA);
                currentOrder->setNumChildTickets(currentOrder->getNumChildTickets() + numC);
                currentOrder->setNumSeniorTickets(currentOrder->getNumSeniorTickets() + numS);
            }
            else
            {
                std::cout << "The seat you selected is not available." << std::endl;
                replaySubmenu = true;
            }
        }
        else if (menuSelection == 2) // DELETE
        {
            std::string rowNumS, seatLetterS; // first get all command line inputs as strings to check type
            unsigned int rowNum;
            char seatLetter;

            // ROW NUMBER
            while (true)
            {
                std::cout << "Enter desired row number: " << std::flush;
                std::cin >> rowNumS;
                bool valid = true;
                for (size_t i = 0; i < rowNumS.length(); ++i)
                {
                    if (!isdigit(rowNumS[i]))
                    {
                        std::cout << "Invalid input. Please try again.\n" << std::endl;
                    valid = false;
                    }
                }
                if (valid)
                {
                    rowNum = stoi(rowNumS);
                    if (rowNum > 0 && rowNum <= currentAuditorium->getLength())
                        break;
                }
            }

            // SEAT LETTER
            std::cout << "Enter seat letter: " << std::flush;
            while (true)
            {
                std::cin >> seatLetterS;
                if (seatLetterS.length() == 1)
                {
                    seatLetter = static_cast<char>(toupper(seatLetterS[0]));
                    if (isalpha(seatLetter))
                    {
                        if (seatLetter - 65 < static_cast<int>(currentAuditorium->getLength()))
                            break;
                    }
                }
                std::cout << "Invalid input. Please try again.\n" << std::endl;
            }
        
            // CHECK IF SEAT EXISTS
            Seat *found = nullptr;
            for (size_t i = 0; i < currentOrder->getNumSeats(); ++i)
            {
                if (currentOrder->getSeats()[i]->getTheaterSeat()->getRow() + 1 == rowNum && currentOrder->getSeats()[i]->getTheaterSeat()->getSeat() == seatLetter)
                {
                    found = currentOrder->getSeats()[i];
                    break;
                }
            }
            if (found == nullptr) // seat not in order
            {
                std::cout << "That seat doesn't exist. You will be returned to the update order submenu." << std::endl;
                replaySubmenu = true;
            }
            else // delete seat from order
            {
                TheaterSeat *curr = currentAuditorium->goTo(found->getTheaterSeat()->getRow(), static_cast<int>(found->getTheaterSeat()->getSeat()) - 65);
                if (curr->getTicketType() == 'A')
                    currentOrder->setNumAdultTickets(currentOrder->getNumAdultTickets() - 1);
                else if (curr->getTicketType() == 'C')
                    currentOrder->setNumChildTickets(currentOrder->getNumChildTickets() - 1);
                else if (curr->getTicketType() == 'S')
                    currentOrder->setNumSeniorTickets(currentOrder->getNumSeniorTickets() - 1);
                curr->setReserved(false);
                curr->setTicketType('.');
                currentOrder->deleteSeat(found);
                currentOrdersListLength--;
                std::cout << "The seat has been deleted." << std::endl;
                if (currentOrder->getNumSeats() == 0) // delete order if empty
                {
                    std::cout << currentOrdersListLength << std::endl;
                    deleteOrder(currentOrdersList, currentOrdersListLength, index);
                    std::cout << "The order has been deleted." << std::endl;
                }
            }
        }
        else if (menuSelection == 3) // delete order
        {
            for (size_t i = 0; i < currentOrder->getNumSeats(); ++i) // reset all seats in order
            {
                TheaterSeat *curr = currentOrder->getSeats()[i]->getTheaterSeat();
                if (curr->getTicketType() == 'A')
                    currentOrder->setNumAdultTickets(currentOrder->getNumAdultTickets() - 1);
                else if (curr->getTicketType() == 'C')
                    currentOrder->setNumChildTickets(currentOrder->getNumChildTickets() - 1);
                else if (curr->getTicketType() == 'S')
                    currentOrder->setNumSeniorTickets(currentOrder->getNumSeniorTickets() - 1);
                curr->setReserved(false);
                curr->setTicketType('.');
            }
            deleteOrder(currentOrdersList, currentOrdersListLength, index);
            if (cA == 1)
                this->ordersList1Length = currentOrdersListLength;
            else if (cA == 2)
                this->ordersList2Length = currentOrdersListLength;
            else if (cA == 3)
                this->ordersList3Length = currentOrdersListLength;
            std::cout << "The order has been deleted." << std::endl;
        }
    }
}

void User::display ()
{
    if (this->ordersList1Length == 0 && this->ordersList2Length == 0 && this->ordersList3Length == 0)
    {
        std::cout << "There are no orders to display. The total is $0." << std::endl;
        return;
    }
    unsigned int orderNum = 0;
    double sum = 0;
    std::cout << "\nRECEIPT FOR " << this->username << "\n" << std::endl;
    for (size_t i = 0; i < this->ordersList1Length; ++i)
    {
        std::cout << "Order #" << ++orderNum << ":" << std::endl;
        std::cout << "\tAuditorium: " << this->ordersList1[i]->getAuditorium() << std::endl;
        std::cout << "\tSeats: " << std::endl;
        for (size_t j = 0; j < this->ordersList1[i]->getNumSeats(); ++j)
        {
            std::cout << "\t\tSeat #" << j+1 << ":\tRow Number: " << this->ordersList1[i]->getSeats()[j]->getTheaterSeat()->getRow()+1 << "\tSeat Letter: " << this->ordersList1[i]->getSeats()[j]->getTheaterSeat()->getSeat() << "\tSeat Type: " << this->ordersList1[i]->getSeats()[j]->getTheaterSeat()->getTicketType() << std::endl;
        }
        std::cout << "\tAdult Tickets: " << this->ordersList1[i]->getNumAdultTickets() << std::endl;
        std::cout << "\tChild Tickets: " << this->ordersList1[i]->getNumChildTickets() << std::endl;
        std::cout << "\tSenior Tickets: " << this->ordersList1[i]->getNumSeniorTickets() << std::endl;
        std::cout << "\tSubtotal...................................$" << (this->ordersList1[i]->getNumAdultTickets() * 10 + this->ordersList1[i]->getNumChildTickets() * 5 + this->ordersList1[i]->getNumSeniorTickets() * 7.5) << std::endl;
        sum += this->ordersList1[i]->getNumAdultTickets() * 10 + this->ordersList1[i]->getNumChildTickets() * 5 + this->ordersList1[i]->getNumSeniorTickets() * 7.5;
    }
    for (size_t i = 0; i < this->ordersList2Length; ++i)
    {
        std::cout << "Order #" << ++orderNum << ":" << std::endl;
        std::cout << "\tAuditorium: " << this->ordersList2[i]->getAuditorium() << std::endl;
        std::cout << "\tSeats: " << std::endl;
        for (size_t j = 0; j < this->ordersList2[i]->getNumSeats(); ++j)
        {
            std::cout << "\t\tSeat #" << j+1 << ":\tRow Number: " << this->ordersList2[i]->getSeats()[j]->getTheaterSeat()->getRow()+1 << "\tSeat Letter: " << this->ordersList2[i]->getSeats()[j]->getTheaterSeat()->getSeat() << "\tSeat Type: " << this->ordersList2[i]->getSeats()[j]->getTheaterSeat()->getTicketType() << std::endl;
        }
        std::cout << "\tAdult Tickets: " << this->ordersList2[i]->getNumAdultTickets() << std::endl;
        std::cout << "\tChild Tickets: " << this->ordersList2[i]->getNumChildTickets() << std::endl;
        std::cout << "\tSenior Tickets: " << this->ordersList2[i]->getNumSeniorTickets() << std::endl;
        std::cout << "\tSubtotal...................................$" << (this->ordersList2[i]->getNumAdultTickets() * 10 + this->ordersList2[i]->getNumChildTickets() * 5 + this->ordersList2[i]->getNumSeniorTickets() * 7.5) << std::endl;
        sum += this->ordersList2[i]->getNumAdultTickets() * 10 + this->ordersList2[i]->getNumChildTickets() * 5 + this->ordersList2[i]->getNumSeniorTickets() * 7.5;
    }
    for (size_t i = 0; i < this->ordersList3Length; ++i)
    {
        std::cout << "Order #" << ++orderNum << ":" << std::endl;
        std::cout << "\tAuditorium: " << this->ordersList3[i]->getAuditorium() << std::endl;
        std::cout << "\tSeats: " << std::endl;
        for (size_t j = 0; j < this->ordersList3[i]->getNumSeats(); ++j)
        {
            std::cout << "\t\tSeat #" << j+1 << ":\tRow Number: " << this->ordersList3[i]->getSeats()[j]->getTheaterSeat()->getRow()+1 << "\tSeat Letter: " << this->ordersList3[i]->getSeats()[j]->getTheaterSeat()->getSeat() << "\tSeat Type: " << this->ordersList3[i]->getSeats()[j]->getTheaterSeat()->getTicketType() << std::endl;
        }
        std::cout << "\tAdult Tickets: " << this->ordersList3[i]->getNumAdultTickets() << std::endl;
        std::cout << "\tChild Tickets: " << this->ordersList3[i]->getNumChildTickets() << std::endl;
        std::cout << "\tSenior Tickets: " << this->ordersList3[i]->getNumSeniorTickets() << std::endl;
        std::cout << "\tSubtotal...................................$" << (this->ordersList3[i]->getNumAdultTickets() * 10 + this->ordersList3[i]->getNumChildTickets() * 5 + this->ordersList3[i]->getNumSeniorTickets() * 7.5) << std::endl;
        sum += this->ordersList3[i]->getNumAdultTickets() * 10 + this->ordersList3[i]->getNumChildTickets() * 5 + this->ordersList3[i]->getNumSeniorTickets() * 7.5;
    }
    std::cout << "Total..............................................$" << sum << std::endl;
}

void User::append (unsigned int listNum, Order *newOrder)
{
    Order **newOrdersList;
    if (listNum == 1)
    {
        newOrdersList = new Order*[this->ordersList1Length+1];
        for (size_t i = 0; i < this->ordersList1Length; ++i)
        {
            newOrdersList[i] = this->ordersList1[i];
        }
        this->ordersList1Length++;
        newOrdersList[this->ordersList1Length-1] = newOrder;
        this->ordersList1 = newOrdersList;
    }
    else if (listNum == 2)
    {
        newOrdersList = new Order*[this->ordersList2Length+1];
        for (size_t i = 0; i < this->ordersList2Length; ++i)
        {
            newOrdersList[i] = this->ordersList2[i];
        }
        this->ordersList2Length++;
        newOrdersList[this->ordersList2Length-1] = newOrder;
        this->ordersList2 = newOrdersList;
    }
    else if (listNum == 3)
    {
        newOrdersList = new Order*[this->ordersList3Length+1];
        for (size_t i = 0; i < this->ordersList3Length; ++i)
        {
            newOrdersList[i] = this->ordersList3[i];
        }
        this->ordersList3Length++;
        newOrdersList[this->ordersList3Length-1] = newOrder;
        this->ordersList3 = newOrdersList;
    }
}

void deleteOrder (Order ** & ordersList, unsigned int& listLength, unsigned int index)
{
    if (listLength == 0)
    {
        Order **newOrdersList = new Order*[0];
        ordersList = newOrdersList;
        return;
    }
    Order **newOrdersList = new Order*[listLength-1];
    for (size_t i = index; i < listLength-1; ++i)
    {
        ordersList[i] = ordersList[i+1];
    }
    for (size_t i = 0; i < listLength-1; ++i)
    {
        newOrdersList[i] = ordersList[i];
    }
    listLength--;
    delete [] ordersList;
    ordersList = newOrdersList;
}

// ADMIN FUNCTIONS

void User::printReport (Auditorium *auditorium1, Auditorium *auditorium2, Auditorium *auditorium3)
{
    Auditorium *currentAuditorium = nullptr;
    for (size_t i = 0; i < 3; ++i)
    {
        if (i == 0) currentAuditorium = auditorium1;
        else if (i == 1) currentAuditorium = auditorium2;
        else if (i == 2) currentAuditorium = auditorium3;
        currentAuditorium->setNumOpenSeats(0);
        currentAuditorium->setNumReservedSeats(0);
        currentAuditorium->setTotalA(0);
        currentAuditorium->setTotalC(0);
        currentAuditorium->setTotalS(0);
        for (size_t j = 0; j < currentAuditorium->getHeight(); ++j)
        {
            for (size_t k = 0; k < currentAuditorium->getLength(); ++k)
            {   
                TheaterSeat *curr = currentAuditorium->goTo(static_cast<int>(j), static_cast<int>(k));
                if (curr->getReserved())
                {
                    currentAuditorium->setNumReservedSeats(currentAuditorium->getNumReservedSeats() + 1);
                    if (curr->getTicketType() == 'A')
                        currentAuditorium->setTotalA(currentAuditorium->getTotalA() + 1);
                    else if (curr->getTicketType() == 'C')
                        currentAuditorium->setTotalC(currentAuditorium->getTotalC() + 1);
                    else if (curr->getTicketType() == 'S')
                        currentAuditorium->setTotalS(currentAuditorium->getTotalS() + 1);
                }
                else
                {
                    currentAuditorium->setNumOpenSeats(currentAuditorium->getNumOpenSeats() + 1);
                }
            }
        }
    }
    std::cout << "\t\tAUDITORIUM 1\t\tAUDITORIUM 2\t\tAUDITORIUM 3\t\tTOTAL" << std::endl;
    std::cout << "Open Seats:\t" << auditorium1->getNumOpenSeats() << "\t\t\t" << auditorium2->getNumOpenSeats() << "\t\t\t" << auditorium3->getNumOpenSeats() << "\t\t\t" << (auditorium1->getNumOpenSeats() + auditorium2->getNumOpenSeats() + auditorium3->getNumOpenSeats()) << std::endl;
    std::cout << "Reserved Seats:\t" << auditorium1->getNumReservedSeats() << "\t\t\t" << auditorium2->getNumReservedSeats() << "\t\t\t" << auditorium3->getNumReservedSeats() << "\t\t\t" << (auditorium1->getNumReservedSeats() + auditorium2->getNumReservedSeats() + auditorium3->getNumReservedSeats()) << std::endl;
    std::cout << "Total Adults:\t" << auditorium1->getTotalA() << "\t\t\t" << auditorium2->getTotalA() << "\t\t\t" << auditorium3->getTotalA() << "\t\t\t" << (auditorium1->getTotalA() + auditorium2->getTotalA() + auditorium3->getTotalA()) << std::endl;
    std::cout << "Total Children:\t" << auditorium1->getTotalC() << "\t\t\t" << auditorium2->getTotalC() << "\t\t\t" << auditorium3->getTotalC() << "\t\t\t" << (auditorium1->getTotalC() + auditorium2->getTotalC() + auditorium3->getTotalC()) << std::endl;
    std::cout << "Total Seniors:\t" << auditorium1->getTotalS() << "\t\t\t" << auditorium2->getTotalS() << "\t\t\t" << auditorium3->getTotalS() << "\t\t\t" << (auditorium1->getTotalS() + auditorium2->getTotalS() + auditorium3->getTotalS()) << std::endl;
    double t1 = 10*auditorium1->getTotalA() + 5*auditorium1->getTotalC() + 7.5*auditorium1->getTotalS(); 
    double t2 = 10*auditorium2->getTotalA() + 5*auditorium2->getTotalC() + 7.5*auditorium2->getTotalS(); 
    double t3 = 10*auditorium3->getTotalA() + 5*auditorium3->getTotalC() + 7.5*auditorium3->getTotalS(); 
    std::cout << "Total Cost:\t" << "$" << t1 << "\t\t\t$" << t2 << "\t\t\t$" << t3 << "\t\t\t$" << (t1+t2+t3) << std::endl;
}

void User::exitProgram (Auditorium *auditorium1, Auditorium *auditorium2, Auditorium *auditorium3)
{
   auditorium1->writeOutput(); 
   auditorium2->writeOutput(); 
   auditorium3->writeOutput(); 
   std::cout << "The files have been updated. The system will now exit." << std::endl;
   std::exit(0);
}
