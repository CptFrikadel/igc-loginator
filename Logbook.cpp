#include "Logbook.hpp"
#include <iostream>
#include <stdio.h>
#include <iomanip>


void Logbook::printLogbook(){


    std::cout << std::left << "| "
        << std::setw(12) << "Date" << "| "
        << std::setw(11) << "Takeoff" << "| "
        << std::setw(11) << "Landing" << "| "
        << std::setw(9) << "Duration" << "| "
        << std::setw(20) << "Pilot"
        << std::endl;

    std::cout <<  std::setfill('-') << std::setw(74) << "-" << std::endl << std::setfill(' ');

    int total_time = 0;

    for (FlightData n : flights){

        char date[11];
        char takeof[10];
        char landing[10];
        int duration_hours;
        int duration_minutes;
        char duration[6];

        std::strftime(date, 10, "%d-%m-'%y", &n.takeoff_time);
        std::strftime(takeof, 9, "%H:%M:%S", &n.takeoff_time);
        std::strftime(landing, 9, "%T", &n.landing_time);

        duration_hours = n.flight_duration / 3600;
        duration_minutes = ((int) n.flight_duration % 3600) / 60;
        total_time += n.flight_duration;
        sprintf(duration, "%d:%02d", duration_hours, duration_minutes);

        std::cout << std::left << "| "
            << std::setw(12) << date << "| "
            << std::setw(11) <<  takeof << "| "
            << std::setw(11)  << landing << "| "
            << std::right << std::setw(8) << duration << " | "
            << n.pilot_name
            << std::endl;


    }

    if (print_totals){

        int total_hours = total_time / 3600;
        int total_minutes = ((int) total_time % 3600) / 60;

        char total_duration[8];
        sprintf(total_duration, "%d:%02d", total_hours, total_minutes);


        std::cout << std::setfill('-') << std::left << "| "
            << std::setw(12) << "Total:" << "| "
            << std::setw(11) <<  '-' << "| "
            << std::right << std::setw(11)  << '-' << "| "
            << std::setw(8) << total_duration << " |"
            << std::setfill(' ') << std::endl;
    }

}

void Logbook::appendFlight(const FlightData _flight){

    flights.push_back(_flight);

}
