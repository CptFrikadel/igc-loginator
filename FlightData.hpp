/*
    Class file to represent the data of a single flight
*/

#ifndef FLIGHTDATA_HPP
#define FLIGHTDATA_HPP

#include <ctime>
#include <string>

struct  FlightData {

    std::tm takeoff_time;
    std::tm landing_time;
    double flight_duration; // in seconds

    std::string pilot_name = "";

};

#endif
