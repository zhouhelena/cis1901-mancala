#include "Board.hpp"
#include <stdexcept>
#include <iostream>

int main(void)
{
    std::cout << "main" << std::endl;
    Board board;

    try {
        board = Board();
    } catch (std::runtime_error ex) {
        std::cout << ex.what() << std::endl;
    }

    std::cout << "made board" << std::endl;
    board.print();
    std::cout << "printed" << std::endl;
}