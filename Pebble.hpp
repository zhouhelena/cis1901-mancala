#ifndef PEBBLE_HPP
#define PEBBLE_HPP
#include <SFML/Graphics.hpp>

class Pebble {
private:
    int color; 
    int size;  
    sf::CircleShape shape;

public:
    Pebble(int color, int size);
    // ~Pebble();

    int getColor() const { return color; }
    int getSize() const { return size; }
    const sf::CircleShape& getShape() const { return shape; }
};

#endif
