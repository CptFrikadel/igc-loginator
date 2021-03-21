#include "CursesTable.hpp"

#include <curses.h>
#include <iostream>


static constexpr int head_size = 3;

void CursesTable::adjustColumnsToFill(){

    // Adjust column sizes to fill the screen width
    int excess_cols = COLS - table_width;
    int col_adjust = excess_cols / col_sizes.size();
    int final_adjust = excess_cols % col_sizes.size();

    for (int i = 0; i < col_sizes.size(); i++){

        col_sizes[i] += col_adjust;
    }

    col_sizes.back() += final_adjust;

    table_width = COLS - 2;
}


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

    adjustColumnsToFill();

    drawHead();
}

void CursesTable::addRow(const std::vector<std::string>& items){

    // TODO check number of columns
    rows.push_back(items);

    // Check whether the table still fits on screen or if scrolling is necessary
    if (rows.size() >= LINES - 4){
        scrolling = true;
    }


    redraw();
}

void CursesTable::redraw(){

    erase();
    drawHead();


    // Draw as many rows as fit
    int i;
    for (i = scroll_pos; i < rows.size() && i - scroll_pos < LINES - 4; i++){
        drawRow(i);
    }

    if (scroll_pos > 0){
        move(head_size, table_width + 1);
        addch(ACS_UARROW);
    }

    // Check wether bottom is on screen or not
    if (i == rows.size()){
        drawBottomBorder(i + head_size - scroll_pos);
    } else {
        move(LINES - 1, table_width + 1);
        addch(ACS_DARROW);
    }

    refresh();
}

void CursesTable::drawHead(){

    //Draw top border line
    move(0, 0);
    for (int i = 0; i < COLS && i < table_width; i++){
        addch(ACS_HLINE);
    }

    // Draw separators in top line
    move(0,0);
    addch(ACS_ULCORNER);

    int pos = 0;
    for (int i = 0; i < num_columns -1; i ++){
        pos += col_sizes[i];
        move(0, pos);
        addch(ACS_TTEE);
    }
    move(0,table_width);
    addch(ACS_URCORNER);

    // Write the head entries

    pos = 0;
    for (int col = 0; col < num_columns; col++){
        move(1, pos);
        addch(ACS_VLINE);
        addch(' ');
        addstr(head[col].c_str());
        addch(' ');
        pos += col_sizes[col];
    }

    move(1, table_width);
    addch(ACS_VLINE);

    // Draw line below
    move(2, 0);
    for (int i = 0; i < COLS && i < table_width; i++){
        addch(ACS_HLINE);
    }

    // Draw separators
    move(2,0);
    addch(ACS_LTEE);

    pos = 0;
    for (int i = 0; i < num_columns -1; i ++){
        pos += col_sizes[i];
        move(2, pos);
        addch(ACS_PLUS);
    }
    move(2,table_width);
    addch(ACS_RTEE);

    refresh();
}

void CursesTable::drawRow(int row){

    int draw_row = row - scroll_pos + head_size;

    int pos = 0;
    for (int col = 0; col < num_columns; col++){

        move(draw_row, pos);
        addch(ACS_VLINE);
        addch(' ');
        addstr(rows[row][col].c_str());
        addch(' ');
        pos += col_sizes[col];
    }

    move(draw_row, table_width);
    addch(ACS_VLINE);

}

void CursesTable::drawBottomBorder(int row){


    move(row, 0);
    for (int i = 0; i < COLS && i < table_width; i++){
        addch(ACS_HLINE);
    }

    // Draw separators in top line
    move(row,0);
    addch(ACS_LLCORNER);

    int pos = 0;
    for (int i = 0; i < num_columns -1; i ++){
        pos += col_sizes[i];
        move(row, pos);
        addch(ACS_BTEE);
    }
    move(row,table_width);
    addch(ACS_LRCORNER);
}


void CursesTable::scroll_lines(int lines){

    if (!scrolling){
        return;
    }

    if (scroll_pos + lines <= 0){
        scroll_pos = 0;
    } else if (scroll_pos + lines >= rows.size() - (LINES - head_size) + 1){
        scroll_pos = rows.size() - LINES + head_size +1;
    } else {
        scroll_pos += lines;
    }

    redraw();

}
