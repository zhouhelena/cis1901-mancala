#include "Pebble.hpp"

Pebble::Pebble(int color, int size) : color(color), size(size) 
{
    shape.setRadius(5.f); // TODO: Change size
    shape.setFillColor(sf::Color::Black); // TODO: Change color
}
