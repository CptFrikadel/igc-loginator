#include "DetailsWindow.hpp"
#include <curses.h>


void DetailsWindow::Update()
{
    box(window, 0, 0);
    wrefresh(window);
}
