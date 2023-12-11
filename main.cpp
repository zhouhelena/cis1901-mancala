#include "Board.hpp"
#include "computer.hpp"
#include <stdexcept>
#include <iostream>
#include <limits>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "button.hpp"

int getButtonHit(int x, int y);

int renderSinglePlayerGame(sf::RenderWindow *window);
int renderTwoPlayerGame(sf::RenderWindow *window);
int getPocketIndex(int x, int y);

int main()
{
    sf::RenderWindow window(sf::VideoMode(820, 600), "Mancala");

    sf::Image background;
    if (!(background.loadFromFile("assets/backgroundtexture.jpg")))
        std::cout << "Error loading image" << std::endl;
    sf::Texture texture;
    texture.loadFromImage(background); // Load Texture from image

    sf::Sprite bgSprite;
    bgSprite.setTexture(texture);

    sf::Font font;
    if (!font.loadFromFile("assets/texastango.otf"))
        std::cout << "Error loading font" << std::endl;

    sf::Text text;
    text.setFont(font);
    text.setString("Mancala Game");
    text.setCharacterSize(56);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f{window.getSize() / 4u});

    sf::Image button;
    if (!(button.loadFromFile("assets/button.png")))
        std::cout << "Error loading image" << std::endl;

    sf::Texture buttonTexture;
    buttonTexture.loadFromImage(button);
    sf::Sprite onePlayerButtonSprite;
    onePlayerButtonSprite.setTexture(buttonTexture);
    onePlayerButtonSprite.setPosition(sf::Vector2f{150, 250});

    sf::Sprite twoPlayerButtonSprite;
    twoPlayerButtonSprite.setTexture(buttonTexture);
    twoPlayerButtonSprite.setPosition(sf::Vector2f{450, 250});

    sf::Text buttonLabels;
    buttonLabels.setFont(font);
    buttonLabels.setFillColor(sf::Color(250, 239, 219));
    buttonLabels.setString("One Player             Two Players");
    buttonLabels.setPosition(sf::Vector2f{190, 300});
    buttonLabels.setCharacterSize(24);

    int buttonHit = -1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) // handle close event
                window.close();

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (buttonHit == -1 && event.type == sf::Event::MouseButtonPressed)
                    buttonHit = getButtonHit(event.mouseButton.x, event.mouseButton.y);
            }
        }

        if (buttonHit != -1)
            break;

        window.clear();
        window.draw(bgSprite);
        window.draw(text);

        window.draw(onePlayerButtonSprite);
        window.draw(twoPlayerButtonSprite);
        window.draw(buttonLabels);

        window.display();
    }

    if (buttonHit == 0)
    {
        return renderSinglePlayerGame(&window);
    }
    else if (buttonHit == 1)
    {
        return renderTwoPlayerGame(&window);
    }

    return 0;
}

int getButtonHit(int x, int y)
{
    if (x > 150 && x < 380 && y > 250 && y < 380)
        return 0;
    else if (x > 450 && x < 680 && y > 250 && y < 380)
        return 1;
    else
        return -1;
}

int renderSinglePlayerGame(sf::RenderWindow *window)
{
    Board board;
    Computer computer(1);

    sf::RectangleShape boardShape(sf::Vector2f(780, 230));
    boardShape.setPosition(20, 170);
    boardShape.setFillColor(sf::Color(139, 69, 19));

    sf::CircleShape pockets[14];
    for (int i = 0; i < 14; ++i)
    {
        pockets[i].setRadius(30.f);
        pockets[i].setFillColor(sf::Color::White);
        if (i == 6)
        { // Player 1's store
            pockets[i].setPosition(720.f, 250.f);
        }
        else if (i == 13)
        { // Player 0's store
            pockets[i].setPosition(40.f, 250.f);
        }
        else if (i < 6)
        { // Bottom row
            pockets[i].setPosition(130.f + i * 100, 300.f);
        }
        else if (i < 13)
        { // Top row
            pockets[i].setPosition(130.f + (12 - i) * 100, 200.f);
        }
    }

    sf::Font font;
    if (!font.loadFromFile("assets/texastango.otf"))
        std::cout << "Error loading font" << std::endl;

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) // handle close event
                window->close();

            if (board.getCurrentPlayer() == 0 && !board.getIsGameOver() && event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int pocketIndex = getPocketIndex(event.mouseButton.x, event.mouseButton.y);
                    if (board.canMove(pocketIndex))
                    {
                        std::cout << "Picked pocket " << pocketIndex << std::endl;
                        board.move(pocketIndex);
                        sf::sleep(sf::seconds(1));
                    }
                }
            }
        }

        if (board.getCurrentPlayer() == 1 && !board.getIsGameOver())
        {
            int computerMove = computer.getMove(board);
            if (computerMove != -1 && board.canMove(computerMove))
            {
                std::cout << "Computer picked pocket " << computerMove << std::endl;
                std::cout << "Current turn " << board.getCurrentPlayer() << std::endl;
                board.move(computerMove);
                sf::sleep(sf::seconds(1));
            }
        }

        board.getCurrentPlayer() == 0 ? text.setString("Player One's Turn to Move") : text.setString("Computer's Turn to Move");
        board.getCurrentPlayer() == 0 ? text.setPosition(sf::Vector2f(400, 410)) : text.setPosition(sf::Vector2f(20, 120));

        window->clear();
        window->draw(boardShape);
        window->draw(text);
        const auto &pocketsWithPebbles = board.getBoard();

        for (int i = 0; i < 14; ++i)
        {
            window->draw(pockets[i]);

            sf::Vector2f pocketCenter = pockets[i].getPosition();
            pocketCenter.x += pockets[i].getRadius();
            pocketCenter.y += pockets[i].getRadius();

            const auto &pebbles = pocketsWithPebbles[i];
            float angleIncrement = 360.0f / pebbles.size();
            float angle = 0.0f;

            for (const auto &pebble : pebbles)
            {
                float radianAngle = angle * 3.14159265f / 180.0f;
                float distanceFromCenter = 15.0f;
                float pebbleX = pocketCenter.x + distanceFromCenter * cos(radianAngle);
                float pebbleY = pocketCenter.y + distanceFromCenter * sin(radianAngle);

                sf::CircleShape pebbleShape = pebble->getShape();
                pebbleShape.setPosition(pebbleX, pebbleY);
                window->draw(pebbleShape);

                angle += angleIncrement;
            }
        }
        window->display();
    }
    return 0;
}

int renderTwoPlayerGame(sf::RenderWindow *window)
{
    Board board;
    sf::RectangleShape boardShape(sf::Vector2f(780, 230));
    boardShape.setPosition(20, 170);
    boardShape.setFillColor(sf::Color(139, 69, 19));

    sf::CircleShape pockets[14];
    for (int i = 0; i < 14; ++i)
    {
        pockets[i].setRadius(30.f);
        pockets[i].setFillColor(sf::Color::White);
        if (i == 6)
        { // Player 1's store
            pockets[i].setPosition(720.f, 250.f);
        }
        else if (i == 13)
        { // Player 0's store
            pockets[i].setPosition(40.f, 250.f);
        }
        else if (i < 6)
        { // Bottom row
            pockets[i].setPosition(130.f + i * 100, 300.f);
        }
        else if (i < 13)
        { // Top row
            pockets[i].setPosition(130.f + (12 - i) * 100, 200.f);
        }
    }

    sf::Font font;
    if (!font.loadFromFile("assets/texastango.otf"))
        std::cout << "Error loading font" << std::endl;

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    while (window->isOpen())
    {
        if (board.getIsGameOver())
        {
            std::cout << "Game over" << std::endl;
            std::cout << "Player 0 score: " << board.getScore(0) << std::endl;
            std::cout << "Player 1 score: " << board.getScore(1) << std::endl;
            if (board.getScore(0) > board.getScore(1))
                text.setString("Player One wins!");
            else if (board.getScore(1) > board.getScore(0))
                text.setString("Player Two wins!");
            else
                text.setString("Tie game!");
            text.setPosition(sf::Vector2f(300, 300));
            window->clear();
            window->draw(boardShape);
            window->draw(text);
            window->display();
            sf::sleep(sf::seconds(10));
            break;
        }

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) // handle close event
                window->close();

            if (!board.getIsGameOver() && event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int pocketIndex = getPocketIndex(event.mouseButton.x, event.mouseButton.y);
                    if (board.canMove(pocketIndex))
                    {
                        std::cout << "Picked pocket " << pocketIndex << std::endl;
                        board.move(pocketIndex);
                        sf::sleep(sf::seconds(1));
                    }
                }
            }
        }

        board.getCurrentPlayer() == 0 ? text.setString("Player One's Turn to Move") : text.setString("Player Two's Turn to Move");
        board.getCurrentPlayer() == 0 ? text.setPosition(sf::Vector2f(400, 410)) : text.setPosition(sf::Vector2f(20, 120));

        // render board
        window->clear();
        window->draw(boardShape);
        window->draw(text);
        const auto &pocketsWithPebbles = board.getBoard();
        for (int i = 0; i < 14; ++i)
        {
            window->draw(pockets[i]);

            sf::Vector2f pocketCenter = pockets[i].getPosition();
            pocketCenter.x += pockets[i].getRadius();
            pocketCenter.y += pockets[i].getRadius();

            const auto &pebbles = pocketsWithPebbles[i];
            if (pebbles.size() == 0)
                continue;
            float angleIncrement = 360.0f / pebbles.size();
            float angle = 0.0f;

            for (const auto &pebble : pebbles)
            {
                float radianAngle = angle * 3.14159265f / 180.0f;
                float distanceFromCenter = 15.0f;
                float pebbleX = pocketCenter.x + distanceFromCenter * cos(radianAngle);
                float pebbleY = pocketCenter.y + distanceFromCenter * sin(radianAngle);

                sf::CircleShape pebbleShape = pebble->getShape();
                pebbleShape.setPosition(pebbleX, pebbleY);
                window->draw(pebbleShape);

                angle += angleIncrement;
            }
        }

        window->display();
    }
    return 0;
}

int getPocketIndex(int x, int y)
{
    const float radius = 50.f;
    const float diameter = 2 * radius;
    sf::Vector2f offset(130.f + radius, 200.f + radius);
    sf::Vector2f bottomRowOffset(130.f + radius, 300.f + radius);
    sf::Vector2f storeOffset(40.f + radius, 250.f + radius);

    // Check top row (7-12)
    for (int i = 7; i < 13; ++i)
    {
        sf::Vector2f pocketCenter = offset + sf::Vector2f((12 - i) * diameter, 0.f);
        // std::cout << "Checking pocket " << i << " at (" << pocketCenter.x << ", " << pocketCenter.y << ") against click (" << x << ", " << y << ")" << std::endl;
        if (std::hypot(pocketCenter.x - x, pocketCenter.y - y) <= radius)
        {
            return i;
        }
    }

    // Check bottom row (0-5)
    for (int i = 0; i < 6; ++i)
    {
        sf::Vector2f pocketCenter = bottomRowOffset + sf::Vector2f(i * diameter, 0.f);
        if (std::hypot(pocketCenter.x - x, pocketCenter.y - y) <= radius)
        {
            return i;
        }
    }

    // Check Player 0's store (6)
    if (std::hypot(storeOffset.x - x, storeOffset.y - y) <= radius)
        return 6;

    // Check Player 1's store (13)
    sf::Vector2f player1Store = storeOffset + sf::Vector2f(680.f, 0.f);
    if (std::hypot(player1Store.x - x, player1Store.y - y) <= radius)
        return 13;

    return -1;
}