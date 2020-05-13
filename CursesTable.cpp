#include "CursesTable.hpp"

#include <curses.h>
#include <iostream>




void CursesTable::setHead(const std::vector<std::string>& head_items){

    num_columns = head_items.size();
    col_sizes.clear();

    // Copy header
    head = head_items;

    table_width = 0;

    // Set column widths to accomodate text
    for (unsigned int col = 0; col < num_columns; col++){

        col_sizes.push_back(head[col].length() + 3);

        table_width += col_sizes[col];

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
