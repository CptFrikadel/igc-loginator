#include "CursesTable.hpp"

#include <curses.h>

CursesTable::CursesTable(const unsigned int _num_columns) : num_columns(_num_columns){

    dimensions = std::make_tuple(COLS, LINES);
}

CursesTable::CursesTable(const unsigned int _num_columns, const int width, const int height) :
    num_columns(_num_columns){

        dimensions = std::make_tuple(width, height);
    }

void CursesTable::draw(){


    wborder(stdscr, 0, 0, 0, 0, 0, 0, 0, 0);


}
