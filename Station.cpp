// Name: Pat Zdanko
// Seneca Student ID: 129430195
// Seneca email: pzdanko@myseneca.ca
// Date of completion: July 22 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"
#include "Utilities.h"
#include <iomanip>
#include <string>

size_t Station::m_fieldWidth = 0;
size_t Station::id_generator = 1;

Station::Station(const std::string& record) {
    m_id = Station::id_generator++;
    Utilities recordReader;
    bool more = false; //set to false to make sure Utilities changes it
    size_t next_pos = 0;

    //extract item
    m_item = recordReader.extractToken(record, next_pos, more);

    //extract serial number
    if (more) {
        m_serial = std::stoi(recordReader.extractToken(record, next_pos, more));
    }

    //extract quantity
    if (more) {
        m_quantity = std::stoi(recordReader.extractToken(record, next_pos, more));
    }

    //update field width
    if (m_fieldWidth < recordReader.getFieldWidth()) {
        m_fieldWidth = recordReader.getFieldWidth();
    }

    //extract description
    if (more) {
        m_desc = recordReader.extractToken(record, next_pos, more);
    }
}
const std::string& Station::getItemName() const {
    return m_item;
}
unsigned int Station::getNextSerialNumber() {
    return m_serial++;
}
unsigned int Station::getQuantity() const {
    return m_quantity;
}
void Station::updateQuantity() {
    if (m_quantity > 0) {
        m_quantity--;
    }
}
void Station::display(std::ostream& os, bool full) const {
    os << "[" << std::setfill('0') << std::right << std::setw(ID_FW) << m_id << "] "
       << "Item: " << std::setfill(' ') << std::left << std::setw(m_fieldWidth) << m_item
       << " [" << std::setfill('0') << std::right << std::setw(SERIAL_FW) << m_serial << "]";

    if (full) {
        os << " Quantity: " << std::setfill(' ') << std::left << std::setw(m_fieldWidth) << m_quantity
           << " Description: " << m_desc;
    }

    os << std::endl;
}
