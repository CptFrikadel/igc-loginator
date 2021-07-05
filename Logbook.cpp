#include "Logbook.hpp"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <curses.h>

#include "CursesTable.hpp"

static constexpr char date_format[] = "%d-%m";
static constexpr char time_format[] = "%H:%M";

static std::string calcDuration(const FlightData& flight){

    std::stringstream duration;

    int duration_minutes, duration_hours;

    duration_hours = flight.flight_duration / 3600;
    duration_minutes = ((int) flight.flight_duration % 3600) / 60;
    duration << std::setw(2) << duration_hours << ":" << std::setfill('0')
        << std::setw(2) << duration_minutes;

    return duration.str();
}


void Logbook::printCursesLogbook(CursesTable& table){

    std::vector<std::string> head = {"Date", "Takeoff", "Landing", "Time"};

    if (print_pilot){
        head.push_back("Pilot");
    }

    table.setHead(head);

    for (FlightData flight : flights){

        std::vector<std::string> item;

        // Build date string
        std::stringstream date;
        date << std::put_time(&flight.takeoff_time, date_format);
        item.push_back(date.str());

        // Build takeoff time
        std::stringstream takeoff;
        takeoff << std::put_time(&flight.takeoff_time, time_format);
        item.push_back(takeoff.str());

        // Build landing time string
        std::stringstream landing;
        landing << std::put_time(&flight.landing_time, time_format);
        item.push_back(landing.str());

        // Build Duration string
        item.push_back(calcDuration(flight));

        // Build pilot string
        if(print_pilot)
            item.push_back(flight.pilot_name.c_str());


        // Add to table
        table.addRow(item);

    }

}

void Logbook::printLogbook(WINDOW * win){

    //printCursesLogbook(win);
}

void Logbook::appendFlight(const FlightData &_flight){

    flights.push_back(_flight);

}
