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
    CursesTable(const unsigned int num_columns);
    CursesTable(const unsigned int num_columns, const unsigned int width);
    void addRow(const std::vector<std::string>& items);
    void setHead(const std::vector<std::string>& head_items);

private:
    void reDraw();
    void drawTable();
    void drawHead();
    void initTable();
    const unsigned int num_columns;
    const unsigned int width;
    unsigned int table_width = 0;
    std::vector<std::string> head;
    std::vector<std::string> rows;
    std::vector<int> col_sizes;

};

#endif
