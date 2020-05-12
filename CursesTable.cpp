#include "CursesTable.hpp"

#include <curses.h>
#include <iostream>

CursesTable::CursesTable(const unsigned int _num_columns) :
    num_columns(_num_columns),
    width(COLS){

    initTable();
}

CursesTable::CursesTable(const unsigned int _num_columns, const unsigned int _width) :
    num_columns(_num_columns),
    width(_width){

    initTable();

}

void CursesTable::initTable(){

    for (unsigned int i = 0; i < num_columns; i++){
        col_sizes.push_back(0);
    }
}

void CursesTable::setHead(const std::vector<std::string>& head_items){

    if (head_items.size() > num_columns){
        std::cerr << "Not enough columns yo!" << std::endl;
    }

    // Copy header
    head = head_items;

    // Set column widths to accomodate text
    for (unsigned int col = 0; col < num_columns; col++){

        head[col] = head_items[col];

        if (col_sizes[col] < head[col].length()){
            col_sizes[col] += head[col].length() - col_sizes[col] + 2;
            table_width += col_sizes[col];
        }
    }

    drawHead();
}

void CursesTable::drawHead(){

    move(0, 0);

    for (unsigned int col = 0; col < num_columns; col++){
        addstr(head[col].c_str());
        addstr(" ");
        addch(ACS_VLINE);
    }

    move(1, 0);
    for (unsigned int i = 0; i < width || i < table_width; i++){
        addch(ACS_S1);
    }

    refresh();
}
