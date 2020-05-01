/*
    Logbook class
*/

#include <list>
#include "FlightData.hpp"

class Logbook {

public:

    void printLogbook();
    void appendFlight(FlightData flight);

private:
    std::list<FlightData> flights;

};
