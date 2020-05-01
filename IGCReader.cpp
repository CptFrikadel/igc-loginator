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

        } else {
            std::cerr << "Unable to open file: " << file_name << std::endl;
            return;
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

                    std::cout << line << std::endl;
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
                    }

                }

            }
        }
        flight_data.landing_time = parseTime(time_line);
        std::cout << date << std::endl;


        igc_file.close();
}
