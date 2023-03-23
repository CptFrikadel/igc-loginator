/*
    Logbook class
*/
#ifndef LOGBOOK_HPP
#define LOGBOOK_HPP

#include <list>
#include "CursesTable.hpp"
#include "FlightData.hpp"

class Logbook {

public:

    void BuildCursesLogbook(CursesTable& cursesTable);

    void appendFlight(const FlightData &flight);
    void setPrintPilot(const bool opt){print_pilot = opt;}
    void setPrintTotals(const bool opt){print_totals = opt;}

    std::string getTotalDuration();
    long getTotalFlights(){ return total_flights;}

private:
    std::list<FlightData> flights;

    long total_hours = 0;
    long total_minutes = 0;
    long total_flights = 0;

    bool print_totals = true;
    bool print_pilot = false;
    bool print_compact = true;

};

#endif
