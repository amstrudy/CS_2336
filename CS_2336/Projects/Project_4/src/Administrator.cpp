// Project 4
// Anja Sheppard AMS180001

#include <iostream>
#include "Administrator.h"

Administrator::Administrator () : User ()
{

}

Administrator::Administrator (std::string user, std::string pass) : User (user, pass)
{

}

Administrator::~Administrator ()
{

}

void Administrator::printReport (Auditorium *auditorium1, Auditorium *auditorium2, Auditorium *auditorium3)
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

void Administrator::exitProgram (Auditorium *auditorium1, Auditorium *auditorium2, Auditorium *auditorium3)
{
   auditorium1->writeOutput(); 
   auditorium2->writeOutput(); 
   auditorium3->writeOutput(); 
   std::cout << "The files have been updated. The system will now exit." << std::endl;
   std::exit(0);
}
