#include <iostream>
#include <fstream>
#include <list>

#include "IGCReader.hpp"
#include "Logbook.hpp"

int main (int argc, char * argv[]){

    std::cout << "Yo Whaddup!" << std::endl;

    // check arguments
    if (argc < 2){
        std::cout << "Usage: " << argv[0] << " <files>" << std::endl;
        return -1;
    }

    std::list<std::string> files(argv + 1, argv + argc);

    Logbook logbook;
    // parse all files
    for (std::string f : files){

        IGCReader reader(f);

        logbook.appendFlight(reader.readIGC());

    }


    // Print result
    logbook.printLogbook();

    return 0;
}
