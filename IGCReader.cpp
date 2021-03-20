#include <cctype>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "IGCReader.hpp"

static std::tm parseTime(const std::string line){

    std::tm time;

    time.tm_sec = (line[5] - '0')*10 + (line[6] - '0');
    time.tm_min = (line[3] - '0')*10 + (line[4] - '0');
    time.tm_hour = (line[1] - '0')*10 + (line[2] - '0');

    return time;
}

static inline void rtrim(std::string &s){

	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch){
				return !std::isspace(ch);
	}).base(), s.end());

}

IGCReader::IGCReader(const std::string _file): file_name(_file){

}

FlightData IGCReader::readIGC(){

        std::ifstream igc_file(file_name);

        if (!igc_file.is_open()){
            std::cerr << "Unable to open file: " << file_name << std::endl;
            exit(-1);
        }

        std::string line;
        std::string time_line;
        std::string date;
        bool found_takeoff = false;

        // Parse file line by line
        while(std::getline(igc_file, line)){

            if (line[0] == 'B'){
                // line is a position report
                time_line = line;

                if (!found_takeoff){
                    // First position, set takeoff time

                    // TODO: add altitude condition
                    flight_data.takeoff_time = parseTime(line);
                    found_takeoff = true;
                }

            } else if (line[0] == 'H'){
                // Line is a header record

                if (line[1] == 'F' || line[1] == 'P'){
                    // source element, nex three bytes are a mnemonic
                    if (line.substr(2,3) == "DTE"){
                        // Line is a date record
                        date = line.substr(5,6);
                    } else if(line.substr(2,3) == "PLT"){
                        // Line is a Pilot record
                        flight_data.pilot_name = line.substr(line.find(':')+1);
						rtrim(flight_data.pilot_name);
                    }

                }

            }
        }

        igc_file.close();

        flight_data.landing_time = parseTime(time_line);

        // Set date in takeoff_time and landing_time
        flight_data.takeoff_time.tm_mday = (date[0] - '0')*10 + (date[1] - '0');
        flight_data.takeoff_time.tm_mon = (date[2] - '0')*10 + (date[3] - '0') - 1;
        flight_data.takeoff_time.tm_year = 100 + (date[4] - '0')*10 + (date[5] - '0'); // NOTE: assumes year > 2000

        flight_data.landing_time.tm_mday = (date[0] - '0')*10 + (date[1] - '0');
        flight_data.landing_time.tm_mon = (date[2] - '0')*10 + (date[3] - '0') - 1;
        flight_data.landing_time.tm_year = 100 + (date[4] - '0')*10 + (date[5] - '0'); // NOTE: assumes year > 2000

        // Calculate flight time
        flight_data.flight_duration = std::difftime(std::mktime(&flight_data.landing_time),
                                        std::mktime(&flight_data.takeoff_time));

        return flight_data;
}
