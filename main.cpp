#include "Board.hpp"
#include <stdexcept>
#include <iostream>

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
    }

    board.print();
    board.printCurrPlayer();

    board.move(1);
    board.print();
    board.printCurrPlayer();
}