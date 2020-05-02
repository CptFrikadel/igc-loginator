/*
    Class defenition for an IGC reader object

    http://www.gliding.ch/images/news/lx20/fichiers_igc.htm#Hrec
*/

#ifndef IGCREADER_HPP
#define IGCREADER_HPP

#include "FlightData.hpp"
#include <string>
class IGCReader {

public:
    IGCReader(const std::string file);
    FlightData readIGC();

private:
    FlightData flight_data;
    std::string file_name;

};

#endif
