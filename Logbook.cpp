#include "Logbook.hpp"
#include <iostream>
#include <stdio.h>
#include <iomanip>


void Logbook::printLogbook(){


    std::cout << std::left << std::setw(10) << "Date" << "|" << std::setw(11) << "Takeoff"
        << "|" << std::setw(11) << "Landing" << "|"<< std::setw(6) << "Duration" << std::endl;

    for (FlightData n : flights){

        char date[11];
        char takeof[10];
        char landing[10];
        int duration_hours;
        int duration_minutes;

        std::strftime(date, 10, "%d-%m-'%y", &n.takeoff_time);
        std::strftime(takeof, 9, "%H:%M:%S", &n.takeoff_time);
        std::strftime(landing, 9, "%T", &n.landing_time);

        duration_hours = n.flight_duration / 3600;
        duration_minutes = ((int) n.flight_duration % 3600) / 60;

        std::cout << date << " | " <<  takeof << " | " << landing << " | ";

        printf("%d:%02d\n", duration_hours, duration_minutes);
    }

}

void Logbook::appendFlight(const FlightData _flight){

    flights.push_back(_flight);

}
