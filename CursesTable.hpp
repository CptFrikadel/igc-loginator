/*
    Class definition for the ncurses style logbook table
*/

#ifndef CURSESTABLE_HPP
#define CURSESTABLE_HPP

#include <vector>
#include <string>
#include <tuple>

class CursesTable {

public:
    void addRow(const std::vector<std::string>& items);
    void setHead(const std::vector<std::string>& head_items);

private:
    void redraw();
    void drawRow(int row);
    void drawHead();
    void drawBottomBorder(int row);
    int num_columns;
    int table_width;
    std::vector<std::string> head;
    std::vector<std::vector<std::string>> rows;
    std::vector<int> col_sizes;

};

#endif
