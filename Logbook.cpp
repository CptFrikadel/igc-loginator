#include "Logbook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <curses.h>
#include <utility>
#include <ranges>

#include "CursesTable.hpp"
#include "FlightList.hpp"

static constexpr char date_format[] = "%d-%m-%y'";
static constexpr char time_format[] = "%H:%M";

static std::string calcDuration(double flighttimeseconds){

    std::stringstream duration;

    int duration_minutes, duration_hours;

    duration_hours = flighttimeseconds / 3600;
    duration_minutes = ((int) flighttimeseconds % 3600) / 60;
    duration << std::setw(2) << duration_hours << ":" << std::setfill('0')
        << std::setw(2) << duration_minutes;

    return duration.str();
}


bool Logbook::Date::operator<(const Date &other) const
{

    if (year == other.year)
    {
        if (month == other.month)
        {
            return day < other.day;
        } else 
        {
            return month < other.month;
        }
    }

    return year < other.year;
}


void Logbook::BuildCursesLogbook(CursesTable& table){

    std::vector<std::string> head = {"Date   ", "Takeoff", "Landing", "Time"};

    if (print_pilot){
        head.push_back("Pilot");
    }

    table.setHead(head);

    for (auto const& [date, flightlist] : mFlightLists | std::views::reverse){
        for (auto flight : flightlist.Get())
        {
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
            item.push_back(calcDuration(flight.flight_duration));

            // Build pilot string
            if(print_pilot)
                item.push_back(flight.pilot_name.c_str());


            // Add to table
            table.addRow(item);
        }

        if (print_totals)
        {
            std::vector<std::string> total_row;
            total_row.push_back("Total"); //Date
            total_row.push_back("-----"); // Takeoff time
            total_row.push_back(flightlist.GetNumberOfFlightsString()); // Landing time
            total_row.push_back(flightlist.GetTotalDurationString()); // Duration

            if (print_pilot)
                total_row.push_back(""); // pilot

            table.addRow(total_row);

            table.addBlankRow();
        }
    }

    if (print_totals){
        std::vector<std::string> total_row;
        total_row.push_back("-----"); //Date
        total_row.push_back("-----"); // Takeoff time
        total_row.push_back("Total"); // Landing time
        total_row.push_back(getTotalDuration()); // Duration

        if (print_pilot)
            total_row.push_back(""); // pilot

        table.addRow(total_row);
    }

}


void Logbook::appendFlight(const FlightData &flight){

    total_hours += flight.flight_duration / 3600;
    total_minutes += ((int) flight.flight_duration % 3600) / 60;

    total_flights++;

    Date date;
    date.year = flight.landing_time.tm_year;
    date.day = flight.landing_time.tm_mday;
    date.month = flight.landing_time.tm_mon;

    auto search = mFlightLists.find(date);
    if ( search != mFlightLists.end())
    {
        search->second.Append(flight);
    } 
    else 
    {
        mFlightLists.emplace(std::make_pair(date, FlightList().Append(flight)));
    }
}


std::string Logbook::getTotalDuration(){

    total_hours += (total_minutes / 60);
    total_minutes = total_minutes % 60;

    std::stringstream ss;

    ss << total_hours << ":" << total_minutes;
    return ss.str();
}
