/*
    Class defenition for an IGC reader object
*/
#include <fstream>
#include "FlightData.hpp"

class IGCReader {

public:
    IGCReader(std::ifstream file);
    void readIGC();

private:
    FlightData flight_data;
    std::ifstream file;

};
