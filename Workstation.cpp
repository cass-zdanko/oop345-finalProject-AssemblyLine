// Name: Pat Zdanko
// Seneca Student ID: 129430195
// Seneca email: pzdanko@myseneca.ca
// Date of completion: July 22 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"
#include "CustomerOrder.h"
#include "Station.h"
#include <deque>
#include <iostream>
#include <string>

void Workstation::runProcess(std::ostream& os) {
    if (!m_orders.empty()) {
        m_orders.front().fillItem(*this, os);
    }
}
bool Workstation::moveOrder() {
    if (m_pNextStation && !m_orders.empty() && m_orders.front().isItemFilled(getItemName())) {
        *m_pNextStation += std::move(m_orders.front());
        m_orders.pop_front();
        return true;
    }
    return false;
}
void Workstation::setNextStation(Workstation& station) {
    m_pNextStation = &station;
}
const Workstation* Workstation::getNextStation() const {
    return m_pNextStation;
}
bool Workstation::getIfCompleted(CustomerOrder& order) {
    if (!m_orders.empty() && m_orders.front().isOrderFilled()) {
        order = std::move(m_orders.front());
        m_orders.pop_front();
        return true;
    }
    return false;
}
void Workstation::display(std::ostream& os) const {
    os << getItemName() << " --> " << (m_pNextStation ? m_pNextStation->getItemName() : std::string("END OF LINE")) << std::endl;
}
Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
    m_orders.push_back(std::move(newOrder));
    return *this;
}
