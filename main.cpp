#include "Board.hpp"
#include <stdexcept>
#include <iostream>
#include <limits>

int main(void)
{
    Board board;

    try
    {
        board = Board();
    }
    catch (std::runtime_error ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    while (!*board.isGameOver)
    {
        board.print();
        board.printCurrPlayer();

        int pocketIndex;
        std::cout << "Choose a pocket (0-5 for Player 0, 7-12 for Player 1): ";
        while (!(std::cin >> pocketIndex) || !board.move(pocketIndex))
        {
            std::cout << "Invalid input. Please enter a valid pocket number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        board.move(pocketIndex);
    }

    board.print(); // Print final board state, final scores, etc.
    return 0;
}