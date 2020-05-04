#include <iostream>
#include <fstream>
#include <list>

#include "IGCReader.hpp"
#include "Logbook.hpp"

int main (int argc, char * argv[]){

    std::cout << "Yo Whaddup!" << std::endl;

    // check arguments
    if (argc < 2){
        std::cout << "Usage: " << argv[0] << " <flags>" << " <files>" << std::endl;
        return -1;
    }

    Logbook logbook;

    // Parse flags
    int i;
    for (i = 1; i < argc; i++){
        if (argv[i][0] == '-'){
            std::cout << "WOLOLOLO" << std::endl;

            std::string flag(argv[i]);

            if (flag == "-pilot" || flag == "-p"){
                logbook.setPrintPilot(true);
            } else if (flag == "-nopilot"){
                logbook.setPrintPilot(false);
            }

        } else {
            break;
        }
    }


    std::list<std::string> files(argv + i, argv + argc);

    // parse all files
    for (std::string f : files){

        IGCReader reader(f);

        logbook.appendFlight(reader.readIGC());

    }


    // Print result
    logbook.printLogbook();

    return 0;
}
