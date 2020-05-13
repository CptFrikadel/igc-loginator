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
    for (int col = 0; col < num_columns; col++){

        col_sizes.push_back(head[col].length() + 3);

        table_width += col_sizes[col];

    }

    drawHead();
}

void CursesTable::addRow(const std::vector<std::string>& items){

    // TODO check number of columns
    rows.push_back(items);

    redraw();
}

void CursesTable::redraw(){

    drawHead();

    for (unsigned int i = 0; i < rows.size(); i++){
        drawRow(i);
    }
}

void CursesTable::drawHead(){

    move(0, 0);
    addch(ACS_VLINE);

    for (int col = 0; col < num_columns; col++){
        addch(' ');
        addstr(head[col].c_str());
        addch(' ');
        addch(ACS_VLINE);
    }

    move(1, 0);
    for (int i = 0; i < COLS && i < table_width; i++){
        addch(ACS_HLINE);
    }

    // Draw separators
    move(1,0);
    addch(ACS_LTEE);

    int pos = 0;
    for (int i = 0; i < num_columns -1; i ++){
        pos += col_sizes[i];
        move(1, pos);
        addch(ACS_PLUS);
    }
    move(1,table_width);
    addch(ACS_RTEE);

    refresh();
}

void CursesTable::drawRow(int row){


    int pos = 0;
    for (int col = 0; col < num_columns; col++){

        move(row + 2, pos);
        addch(ACS_VLINE);
        addch(' ');
        addstr(rows[row][col].c_str());
        addch(' ');
        pos += col_sizes[col];
    }

    move(row + 2, table_width);
    addch(ACS_VLINE);

}
