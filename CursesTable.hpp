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
    CursesTable(const unsigned int num_columns, const int width, const int height);
    void addRow(const std::vector<std::string>& items);
    void setHead(const std::vector<std::string>& head_items);
    void draw();

private:
    const unsigned int num_columns;
    std::vector<std::string> head;
    std::vector<std::string> rows;
    std::tuple<int, int> dimensions;

};

#endif
