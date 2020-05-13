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

void Logbook::printASCIILogbook(){

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

void Logbook::printCursesLogbook(){

    CursesTable table;

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


        // Add to table
        table.addRow(item);

    }


    bool quit = false;
    while (!quit){

        switch (getch()){
        case 'q':
            quit = true;
            break;
        case 27:
            quit = true;
            break;


        }

    }
}

void Logbook::printLogbook(){

    printCursesLogbook();
}

void Logbook::appendFlight(const FlightData &_flight){

    flights.push_back(_flight);

}
