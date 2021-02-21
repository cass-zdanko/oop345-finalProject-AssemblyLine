// Name: Pat Zdanko
// Seneca Student ID: 129430195
// Seneca email: pzdanko@myseneca.ca
// Date of completion: July 22 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Station.h"

struct Item {
    std::string m_itemName;
    unsigned int m_serialNumber = 0;
    bool m_isFilled = false;

    Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
    std::string m_name;
    std::string m_product;
    unsigned int m_cntItem {0};
    Item** m_lstItem {nullptr};
    static size_t m_widthField;

public:
    CustomerOrder();
    CustomerOrder(const std::string& record);
    CustomerOrder(const CustomerOrder& src) { throw "----> ERROR: Cannot make copies."; }
    CustomerOrder& operator=(const CustomerOrder& src) = delete;
    CustomerOrder(CustomerOrder&& src) noexcept { *this = std::move(src); }
    CustomerOrder& operator=(CustomerOrder&& src) noexcept;
    ~CustomerOrder();
    void setEmpty();
    bool isOrderFilled() const;
    bool isItemFilled(const std::string& itemName) const;
    void fillItem(Station& station, std::ostream& os);
    void display(std::ostream& os) const;
};

#endif