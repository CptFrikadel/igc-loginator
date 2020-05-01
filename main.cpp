#include <iostream>
#include <fstream>
#include <list>

#include "IGCReader.hpp"

int main (int argc, char * argv[]){

    std::cout << "Yo Whaddup!" << std::endl;

    // check arguments
    if (argc < 2){
        std::cout << "Usage: " << argv[0] << " <files>" << std::endl;
        return -1;
    }

    std::list<std::string> files(argv + 1, argv + argc);

    // parse all files
    for (std::string f : files){

        IGCReader reader(f);

        reader.readIGC();
    }

    // generate Logbook

    // Print result

    return 0;
}
