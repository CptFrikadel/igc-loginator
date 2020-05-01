#include <iostream>
#include <fstream>
#include "IGCReader.hpp"

static std::tm parseTime(std::string line){

    std::tm time;

    time.tm_sec = (line[5] - '0')*10 + (line[6] - '0');
    time.tm_min = (line[3] - '0')*10 + (line[4] - '0');
    time.tm_hour = (line[1] - '0')*10 + (line[2] - '0');

    std::cout << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << std::endl;

    return time;
}

IGCReader::IGCReader(std::string _file): file_name(_file){

}

void IGCReader::readIGC(){

        std::ifstream igc_file(file_name);

        if (igc_file.is_open()){
            std::cout << "Parsing: " << file_name << std::endl;


            std::string line;
            std::string time_line;
            bool found_takeoff = false;

            // Parse file line by line
            while(std::getline(igc_file, line)){

                if (line[0] == 'B'){
                    // line is a position report
                    time_line = line;

                    if (!found_takeoff){
                        // First position, set takeoff time

                        // TODO: add altitude condition

                        std::cout << line << std::endl;
                        flight_data.takeoff_time = parseTime(line);
                        found_takeoff = true;
                    }
                }
            }
            flight_data.landing_time = parseTime(time_line);

        } else {
            std::cerr << "Unable to open file: " << file_name << std::endl;
        }

        igc_file.close();
}
