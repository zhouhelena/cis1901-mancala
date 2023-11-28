#include "Pebble.hpp"

Pebble::Pebble(int color, int size) : color(color), size(size) {}

void Pebble::display(int y, int x) const {
    attron(COLOR_PAIR(color));
    mvaddch(y, x, ACS_DIAMOND);
    attroff(COLOR_PAIR(color));
}
