/*
    Logbook class
*/
#ifndef LOGBOOK_HPP
#define LOGBOOK_HPP

#include <list>
#include "FlightData.hpp"

class Logbook {

public:

    void printLogbook();
    void appendFlight(const FlightData flight);

private:
    std::list<FlightData> flights;
    bool print_totals = true;

};

#endif
