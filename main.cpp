#include "Board.hpp"
#include <stdexcept>
#include <iostream>
#include <limits>
#include <SFML/Graphics.hpp>

int simulateGame();

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

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mancala");

    sf::RectangleShape board(sf::Vector2f(760, 260));
    board.setPosition(20, 170);
    board.setFillColor(sf::Color(139, 69, 19));

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

        window.clear();

        window.draw(board);
        for (auto &pocket : pockets)
        {
            window.draw(pocket);
        }

        window.display();
    }

    return 0;
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
