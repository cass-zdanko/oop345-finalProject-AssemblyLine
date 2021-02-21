// Name: Pat Zdanko
// Seneca Student ID: 129430195
// Seneca email: pzdanko@myseneca.ca
// Date of completion: July 22 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H

#include <string>
#include <iostream>

const size_t ID_FW = 3;
const size_t SERIAL_FW = 6;

class Station {
    size_t m_id;
    std::string m_item;
    std::string m_desc;
    unsigned int m_serial;
    unsigned int m_quantity;
    static size_t m_fieldWidth;
    static size_t id_generator;

public:
    Station(const std::string& record);
    const std::string& getItemName() const;
    unsigned int getNextSerialNumber();
    unsigned int getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
};
#endif