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
    void setPrintPilot(const bool opt){print_pilot = opt;}

private:
    std::list<FlightData> flights;
    bool print_totals = true;
    bool print_pilot = false;

};

#endif
