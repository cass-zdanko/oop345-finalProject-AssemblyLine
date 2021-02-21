// Name: Pat Zdanko
// Seneca Student ID: 129430195
// Seneca email: pzdanko@myseneca.ca
// Date of completion: July 22 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "LineManager.h"
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"
#include "Workstation.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

LineManager::LineManager(std::string file, std::vector<Workstation*>& stations, std::vector<CustomerOrder>& orders) {
    Utilities myUtil;

    std::ifstream ifs(file);
    if (!ifs.is_open()) {
        throw std::string("ERROR:  Failed to open the file [") + file + "].";
    }

    std::string record = "";
    std::string CurrentStation = "";
    std::string NextStation = "";
    size_t next_pos;
    bool more;

    //Configure the assembly line
    while (!ifs.eof()) {
        next_pos = 0;
        std::getline(ifs, record);

        CurrentStation = myUtil.extractToken(record, next_pos, more);
        if (more)
            NextStation = myUtil.extractToken(record, next_pos, more);
        else
            NextStation = "";

        //Loop through the stations vector space and set the information
        for (size_t i = 0; i < stations.size(); i++) {
            if (stations[i]->getItemName() == CurrentStation) {
                for (size_t y = 0; y < stations.size(); y++) {
                    if (stations[y]->getItemName() == NextStation) {
                        stations[i]->setNextStation(*stations[y]);
                        break;
                    }
                }

                if (m_firstStation == nullptr)
                    m_firstStation = stations[i];
            }
        }
    }
    ifs.close();

    //Move all the loaded customer orders into the ToBeFilled queue
    for (size_t x = 0; x < orders.size(); x++)
        ToBeFilled.push_back(std::move(orders[x]));

    //Store the number of orders to be filled
    m_cntCustomerOrder = ToBeFilled.size();

    //Make a local copy of the address to the assembly line stations
    AssemblyLine = stations;
}
bool LineManager::run(std::ostream& os) {
    static unsigned int iteration = 0;
    iteration++;

    os << "Line Manager Iteration: " << iteration << std::endl;

    //moving customer orders onto the line
    if (!ToBeFilled.empty()) {
        *m_firstStation += std::move(ToBeFilled.front());
        ToBeFilled.pop_front();
    }

    for (size_t i = 0u; i < AssemblyLine.size(); i++) {
        AssemblyLine[i]->runProcess(os);
    }
    for (size_t i = 0u; i < AssemblyLine.size(); i++) {
        //the station is not the end of the line
        if(AssemblyLine[i]->getNextStation()){
            AssemblyLine[i]->moveOrder();
        } else{ //the station is at the end of the line
            CustomerOrder t_order;
            //orders get checked for completion at the end of the line
            if(AssemblyLine[i]->getIfCompleted(t_order)){
                Completed.push_back(std::move(t_order));
            }
        }
    }
    
    //check if completed queue has all orders
    if(Completed.size() == m_cntCustomerOrder){
        return true;
    }
    return false;
}
void LineManager::displayCompletedOrders(std::ostream& os) const {
    for (size_t i = 0u; i < Completed.size(); i++) {
        Completed[i].display(os);
    }
}
void LineManager::displayStations() const {
    for (size_t i = 0u; i < AssemblyLine.size(); i++) {
        AssemblyLine[i]->display(std::cout);
    }
}
void LineManager::displayStationsSorted() const {
    const Workstation* t_station = m_firstStation;
    while (t_station != nullptr) {
        t_station->display(std::cout);
        t_station = t_station->getNextStation();
    }
}