#include "CursesTable.hpp"

#include <curses.h>

CursesTable::CursesTable(const unsigned int _num_columns) : num_columns(_num_columns){

}

void CursesTable::draw(){


    wborder(stdscr, 0, 0, 0, 0, 0, 0, 0, 0);


}
