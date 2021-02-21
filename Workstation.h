// Name: Pat Zdanko
// Seneca Student ID: 129430195
// Seneca email: pzdanko@myseneca.ca
// Date of completion: July 22 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef WORKSTATION_H
#define WORKSTATION_H

#include "CustomerOrder.h"
#include "Station.h"
#include <deque>
#include <iostream>
#include <string>

class Workstation : public Station {
    std::deque<CustomerOrder> m_orders;
    Workstation* m_pNextStation;

public:
    Workstation(const std::string& record) : Station(record) { m_pNextStation = nullptr; }
    Workstation(const Workstation& src) = delete;
    Workstation(Workstation&& src) noexcept = delete;
    Workstation& operator=(const Workstation& src) = delete;
    Workstation& operator=(Workstation&& src) noexcept = delete;
    void runProcess(std::ostream& os);
    bool moveOrder();
    void setNextStation(Workstation& station);
    const Workstation* getNextStation() const;
    bool getIfCompleted(CustomerOrder& order);
    void display(std::ostream& os) const;
    Workstation& operator+=(CustomerOrder&& newOrder);
};

#endif