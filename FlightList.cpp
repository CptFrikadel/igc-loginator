#include "FlightList.hpp"
#include <cstddef>
#include <iomanip>
#include <sstream>


FlightList& FlightList::Append(const FlightData &flight)
{
    mTotalHours += flight.flight_duration / 3600;
    mTotalMinutes += ((int) flight.flight_duration % 3600) / 60;

    mTotalFlights++;

    flights.push_back(flight);

    return *this;
}


std::string FlightList::GetTotalDurationString() const
{
    auto totalHours = mTotalHours + (mTotalMinutes / 60);
    auto totalMinutes = mTotalMinutes % 60;

    std::stringstream ss;

    ss << std::setw(2) << totalHours << ":" << std::setfill('0') << std::setw(2) << totalMinutes;
    return ss.str();
}


unsigned long FlightList::GetNumberOfFlights() const
{
    return flights.size();
}
