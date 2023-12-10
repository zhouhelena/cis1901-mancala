#include "Board.hpp"
#include <stdexcept>
#include <iostream>
#include <limits>
#include <cmath>
#include <SFML/Graphics.hpp>

int getPocketIndex(int x, int y);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mancala");
    Board board;

    sf::RectangleShape boardShape(sf::Vector2f(760, 260));
    boardShape.setPosition(20, 170);
    boardShape.setFillColor(sf::Color(139, 69, 19));

    // Pockets
    sf::CircleShape pockets[14];
    for (int i = 0; i < 14; ++i)
    {
        pockets[i].setRadius(30.f);
        pockets[i].setFillColor(sf::Color::White);
        // Set positions for pockets
        if (i == 13)
        { // Player 1's store
            pockets[i].setPosition(720.f, 250.f);
        } else if (i == 6)
        { // Player 0's store
            pockets[i].setPosition(40.f, 250.f);
        }
        else if (i < 6)
        { // Bottom row
            pockets[i].setPosition(120.f + i * 100, 300.f);
        }
        else if (i < 13)
        { // Top row
            pockets[i].setPosition(120.f + (i - 7) * 100, 200.f);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                int pocketIndex = getPocketIndex(event.mouseButton.x, event.mouseButton.y);
                if (board.canMove(pocketIndex))
                {
                    board.move(pocketIndex);
                    std::cout << "Picked pocket" << std::endl;

                    // TODO: Add code to update the graphical representation of pockets
                }
            }
        }

        window.clear();

        window.draw(boardShape);
        for (auto &pocket : pockets)
        {
            window.draw(pocket);
        }

        window.display();
    }

    return 0;
}

int getPocketIndex(int x, int y)
{
    const float radius = 30.f;
    const sf::Vector2f offset(120.f, 200.f); 
    const sf::Vector2f bottomRowOffset(120.f, 300.f); 
    const sf::Vector2f storeOffset(40.f, 250.f); 

    // Check top row (7-12)
    for (int i = 7; i < 13; ++i)
    {
        sf::Vector2f pocketCenter = offset + sf::Vector2f((i - 7) * 100, 0.f);
        if (std::hypot(pocketCenter.x - x, pocketCenter.y - y) <= radius)
            return i;
    }

    // Check bottom row (0-5)
    for (int i = 0; i < 6; ++i)
    {
        sf::Vector2f pocketCenter = bottomRowOffset + sf::Vector2f(i * 100, 0.f);
        if (std::hypot(pocketCenter.x - x, pocketCenter.y - y) <= radius)
            return i;
    }

    // Check Player 0's store (6)
    if (std::hypot(storeOffset.x - x, storeOffset.y - y) <= radius)
        return 6;

    // Check Player 1's store (13)
    sf::Vector2f player1Store = storeOffset + sf::Vector2f(680.f, 0.f);
    if (std::hypot(player1Store.x - x, player1Store.y - y) <= radius)
        return 13;

    return -1; // No valid pocket clicked
}

int simulateGame()
{
    Board board;
    board.print();
    board.printCurrPlayer();

    while (!board.checkVictory())
    {
        int move;
        std::cout << "Enter move: ";
        std::cin >> move;
        if (!board.canMove(move))
        {
            std::cout << "Invalid input. Please enter a valid pocket number: " << std::endl;
            std::cin.clear();
            std::cin >> move;
        }
        board.move(move);
        board.print();
        board.printCurrPlayer();
    }

    return 0;
}

// int main(void)
// {
//     Board board;
//     try
//     {
//         board = Board();
//     }
//     catch (std::runtime_error ex)
//     {
//         std::cout << ex.what() << std::endl;
//         return 1;
//     }

//     while (!*board.isGameOver)
//     {
//         board.print();
//         board.printCurrPlayer();

//         int pocketIndex;
//         std::cout << "Choose a pocket (0-5 for Player 0, 7-12 for Player 1): ";
//         while (!(std::cin >> pocketIndex) || !board.move(pocketIndex))
//         {
//             std::cout << "Invalid input. Please enter a valid pocket number: ";
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         }

//         board.move(pocketIndex);
//     }

//     board.print(); // Print final board state, final scores, etc.
//     return 0;
// }
