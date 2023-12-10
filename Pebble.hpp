#ifndef PEBBLE_HPP
#define PEBBLE_HPP

class Pebble {
private:
    int color; 
    int size;  

public:
    Pebble(int color, int size);
    // ~Pebble();

    int getColor() const { return color; }
    int getSize() const { return size; }

    void display(int y, int x) const;
};

#endif
