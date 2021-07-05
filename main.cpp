#include <iostream>
#include <fstream>
#include <list>
#include <curses.h>

#include "IGCReader.hpp"
#include "Logbook.hpp"
#include "CursesTable.hpp"

static void printHelp(){

    std::cout   << "Welcome to the IGC logbook utility!" << std::endl
                << std::endl
                << "Usage: " << std::endl
                << "    logbook [FLAGS] [FILES]" << std::endl
                << std::endl
                << "Where [FLAGS] can be one or more of:" << std::endl
                << std::endl
                << "    -pilot -p               Print pilot name" << std::endl
                << "    -nototals               Don't print a totals row" << std::endl
                << "    --help -h               Print this help" << std::endl
                << std::endl
                << "Flights table is printed in the order [FILES] are supplied." << std::endl
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
            } else if (flag == "-nototals"){
                logbook.setPrintTotals(false);
            } else if (flag == "--help" || flag == "-h"){
                printHelp();
                return(0);
            } else {
                std::cout << "Unknown Option!" << std::endl;
                return(-1);
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


    // Parsing files might exit on error. Init ncurses only on succes
    initscr();
    setlocale(LC_ALL, "");
    cbreak();
    curs_set(0);
    noecho();
    keypad(stdscr, true);

    WINDOW *table_window = newwin(20, COLS, 0, 0);
    WINDOW *details = newwin(20, COLS -1, 21, 0);

    box(details, 0, 0);
    wrefresh(details);

    CursesTable table(table_window);
    logbook.printCursesLogbook(table);

    bool quit = false;
    while (!quit){

        switch (wgetch(table_window)){
            case 'q':
                quit = true;
                break;
            case 27:
                quit = true;
                break;
            case 'j':
                table.scroll_lines(1);
                break;
            case KEY_DOWN:
                table.scroll_lines(1);
                break;
            case 'k':
                table.scroll_lines(-1);
                break;
            case KEY_UP:
                table.scroll_lines(-1);
                break;
        }
    }



    endwin();
    return 0;
}
