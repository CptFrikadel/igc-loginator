/*
    Logbook class
*/
#ifndef LOGBOOK_HPP
#define LOGBOOK_HPP

#include <list>
#include <curses.h>
#include "FlightData.hpp"
#include "CursesTable.hpp"

class Logbook {

public:

    void printLogbook(WINDOW * win);
    void printCursesLogbook(CursesTable& table);
    void appendFlight(const FlightData &flight);
    void setPrintPilot(const bool opt){print_pilot = opt;}
    void setPrintTotals(const bool opt){print_totals = opt;}

private:
    std::list<FlightData> flights;
    bool print_totals = true;
    bool print_pilot = false;
    bool print_compact = true;

};

#endif
