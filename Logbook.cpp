#include "Logbook.hpp"
#include <iostream>
#include <stdio.h>
#include <iomanip>


void Logbook::printLogbook(){

    unsigned int date_width = 12, time_width = 11;
    constexpr unsigned int duration_width = 5;

    if (print_compact){
        date_width = 7;
        time_width = 8;
    }

    std::cout << std::left << "| "
        << std::setw(date_width) << "Date" << "| "
        << std::setw(time_width) << "Takeoff" << "| "
        << std::setw(time_width) << "Landing" << "| "
        << std::setw(duration_width) << "Time" << " |";

    if (print_pilot){
        std::cout << std::setw(20) << "Pilot";
    }

    std::cout << std::endl;

    std::cout <<  std::setfill('-');

    if (print_pilot){
        std::cout << std::setw(74);
    } else {
        std::cout << std::setw(date_width + 2*time_width + duration_width + 10);
    }
    std::cout << "-" << std::endl << std::setfill(' ');

    int total_time = 0;

    for (FlightData n : flights){

        char date[11];
        char takeof[10];
        char landing[10];
        int duration_hours;
        int duration_minutes;
        char duration[6];

        char date_format[] = "%d-%m"; //"%d-%m-'%y";
        char time_format[] = "%H:%M"; //"%H:%M:%S";

        std::strftime(date, 7, date_format, &n.takeoff_time);
        std::strftime(takeof, 6, time_format, &n.takeoff_time);
        std::strftime(landing, 6, time_format, &n.landing_time);

        duration_hours = n.flight_duration / 3600;
        duration_minutes = ((int) n.flight_duration % 3600) / 60;
        total_time += n.flight_duration;
        sprintf(duration, "%d:%02d", duration_hours, duration_minutes);

        std::cout << std::left << "| "
            << std::setw(date_width) << date << "| "
            << std::setw(time_width) <<  takeof << "| "
            << std::setw(time_width)  << landing << "| "
            << std::right << std::setw(duration_width) << duration << " | ";

        if (print_pilot){
            std::cout << n.pilot_name;
        }

        std::cout << std::endl;

    }

    if (print_totals){

        int total_hours = total_time / 3600;
        int total_minutes = ((int) total_time % 3600) / 60;

        char total_duration[8];
        sprintf(total_duration, "%d:%02d", total_hours, total_minutes);


        std::cout << std::setfill('-') << std::left << "| "
            << std::setw(date_width) << "Total:" << "| "
            << std::setw(time_width) <<  '-' << "| "
            << std::right << std::setw(time_width)  << '-' << "| "
            << std::setw(duration_width) << total_duration << " |"
            << std::setfill(' ') << std::endl;
    }

}

void Logbook::appendFlight(const FlightData _flight){

    flights.push_back(_flight);

}
