#include "Logbook.hpp"
#include <iostream>

void Logbook::printLogbook(){

    for (FlightData n : flights){

        std::cout << n.flight_duration << std::endl;
    }

}

void Logbook::appendFlight(FlightData _flight){

    flights.push_back(_flight);

}
