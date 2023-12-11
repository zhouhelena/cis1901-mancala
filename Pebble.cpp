#include "Pebble.hpp"

Pebble::Pebble(int color, int size) : color(color), size(size) 
{
    shape.setRadius((rand() % 4) + 4);
    shape.setFillColor(sf::Color(rand() % 200, rand() % 200, rand() % 200));
}
