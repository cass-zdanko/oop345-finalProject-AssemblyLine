// Name: Pat Zdanko
// Seneca Student ID: 129430195
// Seneca email: pzdanko@myseneca.ca
// Date of completion: July 22 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"
#include <iostream>
#include <sstream>

char Utilities::m_delimiter = '\0';

void Utilities::setFieldWidth(size_t newWidth) {
    m_fieldWidth = newWidth;
}
size_t Utilities::getFieldWidth() const {
    return m_fieldWidth;
}
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
    std::string token = "\0";

    if (next_pos <= str.length()) {
        std::stringstream ss(str.substr(next_pos));
        std::getline(ss, token, m_delimiter);
        next_pos += token.length() + 1; //+1 to account for delimiter

        if (token.empty()) {
            more = false;
            throw str + "<-- ERROR: Token Failure";
        }

        if (m_fieldWidth < token.length()) {
            m_fieldWidth = token.length();
        }

        more = (next_pos <= str.length());
    }
    return token;
}
void Utilities::setDelimiter(char newDelimiter) {
    m_delimiter = newDelimiter;
}
char Utilities::getDelimiter() {
    return m_delimiter;
}
