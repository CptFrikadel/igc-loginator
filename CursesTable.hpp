
/*
Class definition for the ncurses style logbook table
*/

#ifndef CURSESTABLE_HPP
#define CURSESTABLE_HPP

#include <vector>
#include <string>
#include <tuple>
#include <curses.h>

class CursesTable {

    public:
	CursesTable(WINDOW *_win) :
	    win(_win)
	{ getmaxyx(win, max_y, max_x);}

	void addRow(const std::vector<std::string>& items);
	void setHead(const std::vector<std::string>& head_items);
	void scroll_lines(int lines);

    private:
	WINDOW * win;
	int max_y = 0;
	int max_x = 0;
	void redraw();
	void drawRow(int row);
	void drawHead();
	void drawBottomBorder(int row);
	void adjustColumnsToFill();
	int num_columns;
	int table_width;
	std::vector<std::string> head;
	std::vector<std::vector<std::string>> rows;
	std::vector<int> col_sizes;
	bool scrolling = false;
	int scroll_pos = 0;

};

#endif
