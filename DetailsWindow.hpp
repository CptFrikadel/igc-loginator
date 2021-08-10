#ifndef __DETAILS_WINDOW_HPP
#define __DETAILS_WINDOW_HPP

#include <curses.h>

/*
 * Class to manage the details window.
 */
class DetailsWindow{

public:

    DetailsWindow(WINDOW * _window) :
	window(_window)
	{ getmaxyx(window, max_y, max_x);}

    ~DetailsWindow() = default;

    void Update();

protected:
    WINDOW * window;
    int max_x;
    int max_y;
};

#endif
