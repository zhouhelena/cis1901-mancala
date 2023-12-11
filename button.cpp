#include "button.hpp"

Button::Button(sf::Image *normal, sf::Image *clicked, std::string text, sf::Vector2f location)
{
    sf::Texture normalTexture;
    normalTexture.loadFromImage(*normal);
    this->normal.setTexture(normalTexture);

    sf::Texture clickedTexture;
    clickedTexture.loadFromImage(*clicked);
    this->clicked.setTexture(clickedTexture);

    this->currentSpr = &this->normal;
    current = false;

    this->normal.setPosition(location);
    this->clicked.setPosition(location);

    // label.setFillColor(sf::Color(139, 69, 19));
    label.setFillColor(sf::Color::White);
    label.setString(text);
    // label.setPosition(sf::Vector2f{location.x + 3, location.y + 3});
    label.setPosition(location);
    label.setCharacterSize(36);

    std::cout << "Button created" << std::endl;
}

void Button::checkClick(sf::Vector2f mousePos)
{
    if (mousePos.x > currentSpr->getPosition().x && mousePos.x < (currentSpr->getPosition().x + currentSpr->getGlobalBounds().width))
    {
        if (mousePos.y > currentSpr->getPosition().y && mousePos.y < (currentSpr->getPosition().y + currentSpr->getGlobalBounds().height))
        {
            setState(!current);
            std::cout << "clicked" << std::endl;
        }
    }
}

void Button::setState(bool which)
{
    current = which;
    if (current)
    {
        currentSpr = &clicked;
        return;
    }
    currentSpr = &normal;
}

void Button::setText(std::string text)
{
    label.setString(text);
}

bool Button::getVar()
{
    return current;
}

sf::Sprite Button::getSprite()
{
    return *currentSpr;
}

sf::Text Button::getLabel()
{
    return label;
}