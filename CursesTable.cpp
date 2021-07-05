#include "CursesTable.hpp"

#include <curses.h>
#include <iostream>

static constexpr int head_size = 3;

void CursesTable::adjustColumnsToFill(){

    // Adjust column sizes to fill the screen width
    int excess_cols = max_x - table_width;
    int col_adjust = excess_cols / col_sizes.size();
    int final_adjust = excess_cols % col_sizes.size();

    for (int i = 0; i < col_sizes.size(); i++){

        col_sizes[i] += col_adjust;
    }

    col_sizes.back() += final_adjust;

    table_width = max_x - 2;
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
    if (rows.size() >= max_y - 4){
        scrolling = true;
    }


    redraw();
}

void CursesTable::redraw(){

    werase(win);
    drawHead();


    // Draw as many rows as fit
    int i;
    for (i = scroll_pos; i < rows.size() && i - scroll_pos < max_y - 4; i++){
        drawRow(i);
    }

    if (scroll_pos > 0){
        wmove(win, head_size, table_width + 1);
        waddch(win, ACS_UARROW);
    }

    // Check wether bottom is on screen or not
    if (i == rows.size()){
        drawBottomBorder(i + head_size - scroll_pos);
    } else {
        wmove(win, max_y - 1, table_width + 1);
        waddch(win, ACS_DARROW);
    }

    wrefresh(win);
}

void CursesTable::drawHead(){

    //Draw top border line
    wmove(win, 0, 0);
    for (int i = 0; i < max_x && i < table_width; i++){
        waddch(win, ACS_HLINE);
    }

    // Draw separators in top line
    wmove(win, 0,0);
    waddch(win, ACS_ULCORNER);

    int pos = 0;
    for (int i = 0; i < num_columns -1; i ++){
        pos += col_sizes[i];
        wmove(win, 0, pos);
        waddch(win, ACS_TTEE);
    }
    wmove(win, 0,table_width);
    waddch(win, ACS_URCORNER);

    // Write the head entries

    pos = 0;
    for (int col = 0; col < num_columns; col++){
        wmove(win, 1, pos);
        waddch(win, ACS_VLINE);
        waddch(win, ' ');
        waddstr(win, head[col].c_str());
        waddch(win, ' ');
        pos += col_sizes[col];
    }

    wmove(win, 1, table_width);
    waddch(win, ACS_VLINE);

    // Draw line below
    wmove(win, 2, 0);
    for (int i = 0; i < max_x && i < table_width; i++){
        waddch(win, ACS_HLINE);
    }

    // Draw separators
    wmove(win, 2,0);
    waddch(win, ACS_LTEE);

    pos = 0;
    for (int i = 0; i < num_columns -1; i ++){
        pos += col_sizes[i];
        wmove(win, 2, pos);
        waddch(win, ACS_PLUS);
    }
    wmove(win, 2,table_width);
    waddch(win, ACS_RTEE);

    wrefresh(win);
}

void CursesTable::drawRow(int row){

    int draw_row = row - scroll_pos + head_size;

    int pos = 0;
    for (int col = 0; col < num_columns; col++){

        wmove(win, draw_row, pos);
        waddch(win, ACS_VLINE);
        waddch(win, ' ');
        waddstr(win, rows[row][col].c_str());
        waddch(win, ' ');
        pos += col_sizes[col];
    }

    wmove(win, draw_row, table_width);
    waddch(win, ACS_VLINE);

}

void CursesTable::drawBottomBorder(int row){


    wmove(win, row, 0);
    for (int i = 0; i < max_x && i < table_width; i++){
        waddch(win, ACS_HLINE);
    }

    // Draw separators in top line
    wmove(win, row,0);
    waddch(win, ACS_LLCORNER);

    int pos = 0;
    for (int i = 0; i < num_columns -1; i ++){
        pos += col_sizes[i];
        wmove(win, row, pos);
        waddch(win, ACS_BTEE);
    }
    wmove(win, row,table_width);
    waddch(win, ACS_LRCORNER);
}


void CursesTable::scroll_lines(int lines){

    if (!scrolling){
        return;
    }

    if (scroll_pos + lines <= 0){
        scroll_pos = 0;
    } else if (scroll_pos + lines >= rows.size() - (max_y - head_size) + 1){
        scroll_pos = rows.size() - max_y + head_size +1;
    } else {
        scroll_pos += lines;
    }

    redraw();

}
