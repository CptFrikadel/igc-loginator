/*
    Class file to represent the data of a single flight
*/
#include <ctime>

struct  FlightData {

    struct std::tm takeoff_time;
    struct std::tm landing_time;
    unsigned int flight_duration;

};
