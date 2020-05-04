#include <iostream>
#include <fstream>
#include <list>

#include "IGCReader.hpp"
#include "Logbook.hpp"

static void printHelp(){

    std::cout   << "Welcome to the IGC logbook utility!" << std::endl
                << std::endl
                << "Usage: " << std::endl
                << "    logbook [FLAGS] [FILES]" << std::endl
                << std::endl
                << "Where [FLAGS] can be one or more of:" << std::endl
                << std::endl
                << "    -pilot -p               Print pilot name" << std::endl
                << "    -nopilot                Don't print pilot name (DEFAULT)" << std::endl
                << "    -totals -t              Print totals at the bottom of the table" << std::endl
                << "    -nototals               Don't print a totals row" << std::endl
                << std::endl
                << "[FILES] are printed in the order they are supplied." << std::endl
                << std::endl << std::endl
                << "K thx byee!"
                << std::endl;
}

int main (int argc, char * argv[]){

    std::cout << "Yo Whaddup!" << std::endl;

    // check arguments
    if (argc < 2){
        printHelp();
        return -1;
    }

    Logbook logbook;

    // Parse flags
    int i;
    for (i = 1; i < argc; i++){
        if (argv[i][0] == '-'){
            std::string flag(argv[i]);

            if (flag == "-pilot" || flag == "-p"){
                logbook.setPrintPilot(true);
            } else if (flag == "-nopilot"){
                logbook.setPrintPilot(false);
            } else if (flag == "-totals" || flag == "-t"){
                logbook.setPrintTotals(true);
            } else if (flag == "-nototals"){
                logbook.setPrintTotals(false);
            } else if (flag == "--help" || flag == "-h"){
                printHelp();
                return(0);
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
