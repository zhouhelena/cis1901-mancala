
#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
public:
    Button(sf::Image *normal, sf::Image *clicked, std::string, sf::Vector2f location);
    void checkClick(sf::Vector2f);
    void setState(bool);
    void setText(std::string);
    bool getVar();
    sf::Sprite getSprite();
    sf::Text getLabel();

private:
    sf::Sprite normal;
    sf::Sprite clicked;
    sf::Sprite *currentSpr;
    sf::Text label;
    bool current;
};

#endif