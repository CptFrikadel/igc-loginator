/*
    Logbook class
*/

#include <vector>
#include "FlightData.hpp"

class Logbook {

public:

    void printLogbook();
    void appendFlight(FlightData flight);

private:
    std::vector<FlightData> flights;

};
