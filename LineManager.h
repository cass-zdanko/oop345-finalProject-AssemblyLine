// Name: Pat Zdanko
// Seneca Student ID: 129430195
// Seneca email: pzdanko@myseneca.ca
// Date of completion: July 22 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include "CustomerOrder.h"
#include "Workstation.h"
#include <iostream>
#include <string>
#include <vector>

class LineManager {
    std::vector<Workstation*> AssemblyLine;
    std::deque<CustomerOrder> ToBeFilled;
    std::deque<CustomerOrder> Completed;
    unsigned int m_cntCustomerOrder;
    Workstation* m_firstStation {nullptr};

public:
    LineManager(std::string file, std::vector<Workstation*>& stations, std::vector<CustomerOrder>& orders);
    bool run(std::ostream& os);
    void displayCompletedOrders(std::ostream& os) const;
    void displayStations() const;
    void displayStationsSorted() const;
};
#endif