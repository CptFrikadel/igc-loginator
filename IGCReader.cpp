#include <iostream>
#include <fstream>
#include "IGCReader.hpp"

IGCReader::IGCReader(std::string _file): file_name(_file){

}

void IGCReader::readIGC(){

        std::ifstream igc_file(file_name);

        if (igc_file.is_open()){
            std::cout << "Parsing: " << file_name << std::endl;
        } else {
            std::cerr << "Unable to open file: " << file_name << std::endl;
        }

        igc_file.close();
}
