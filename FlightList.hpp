#pragma once

#include "FlightData.hpp"

#include <cstddef>
#include <string>
#include <vector>


class FlightList
{

public:

    unsigned long GetNumberOfFlights() const;
    std::string GetNumberOfFlightsString() const;
    std::string GetTotalDurationString() const;

    const std::vector<FlightData>& Get() const { return flights; }

    FlightList& Append(const FlightData& flight);

private:

    std::vector<FlightData> flights;

    unsigned long mTotalHours = 0;
    unsigned long mTotalMinutes = 0;
    unsigned long mTotalFlights = 0;

};
