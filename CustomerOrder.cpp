// Name: Pat Zdanko
// Seneca Student ID: 129430195
// Seneca email: pzdanko@myseneca.ca
// Date of completion: July 22 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {
    setEmpty();
}
CustomerOrder::CustomerOrder(const std::string& record) {
    setEmpty();

    Utilities recordReader;
    bool more = false;
    size_t next_pos = 0;

    //get customer name
    m_name = recordReader.extractToken(record, next_pos, more);

    //get product name
    if (more) {
        m_product = recordReader.extractToken(record, next_pos, more);
    }

    //item count
    if (more) {
        m_cntItem = std::count(record.begin(), record.end(), recordReader.getDelimiter()) - 1;
        //-1 accounts for there being 1 less delimter than there are words, but 2 words are the customer name and product

        //get items
        m_lstItem = new Item*[m_cntItem];
        for (unsigned int i = 0; i < m_cntItem; i++) {
            m_lstItem[i] = new Item(recordReader.extractToken(record, next_pos, more));
        }
    }

    if (m_widthField < recordReader.getFieldWidth()) {
        m_widthField = recordReader.getFieldWidth();
    }
}
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
    m_name = src.m_name;
    m_product = src.m_product;

    if (m_lstItem) {
        for (unsigned int i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    m_cntItem = src.m_cntItem;
    m_lstItem = src.m_lstItem;

    src.setEmpty();
    return *this;
}
CustomerOrder::~CustomerOrder() {
    for (unsigned int i = 0; i < m_cntItem; i++) {
        delete m_lstItem[i];
    }
    delete[] m_lstItem;
}
void CustomerOrder::setEmpty() {
    m_name = "";
    m_product = "";
    m_cntItem = 0;
    m_lstItem = nullptr;
}
bool CustomerOrder::isOrderFilled() const {
    for (unsigned int i = 0; i < m_cntItem; i++) {
        if (!m_lstItem[i]->m_isFilled) {
            return false;
        }
    }
    return true;
}
bool CustomerOrder::isItemFilled(const std::string& itemName) const {
    for (unsigned int i = 0; i < m_cntItem; i++) {
        if (m_lstItem[i]->m_itemName == itemName) {
            return m_lstItem[i]->m_isFilled;
        }
    }
    return true;
}
void CustomerOrder::fillItem(Station& station, std::ostream& os) {
    for (unsigned int i = 0; i < m_cntItem; i++) {
        if (m_lstItem[i]->m_itemName == station.getItemName()) {
            if (station.getQuantity() > 0) {
                station.updateQuantity();
                m_lstItem[i]->m_isFilled = true;
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                os << "    Filled ";
            } else {
                os << "    Unable to fill ";
            }
            os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
        }
    }
}
void CustomerOrder::display(std::ostream& os) const {
    os << m_name << " - " << m_product << std::endl;
    for (unsigned int i = 0; i < m_cntItem; i++) {
        os << "[" << std::setw(SERIAL_FW) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
           << std::setw(CustomerOrder::m_widthField) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << " - "
           << (m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING") << std::endl;
    }
}
