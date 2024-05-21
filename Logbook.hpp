/*
    Logbook class
*/
#ifndef LOGBOOK_HPP
#define LOGBOOK_HPP

#include <map>
#include "CursesTable.hpp"
#include "FlightData.hpp"
#include "FlightList.hpp"

class Logbook {

public:
    
    struct Date 
    {
	int year;
	int month;
	int day;

	bool operator<(const Date& other) const;
    };

    void BuildCursesLogbook(CursesTable& cursesTable);

    void appendFlight(const FlightData &flight);
    void setPrintPilot(const bool opt){print_pilot = opt;}
    void setPrintTotals(const bool opt){print_totals = opt;}

    std::string getTotalDuration();
    long getTotalFlights(){ return total_flights;}

private:
    std::map<Date, FlightList> mFlightLists;

    long total_hours = 0;
    long total_minutes = 0;
    long total_flights = 0;

    bool print_totals = true;
    bool print_pilot = false;
    bool print_compact = true;

};

#endif
