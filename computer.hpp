#ifndef COMPUTER
#define COMPUTER

#include <iostream>
#include <vector>

#include "Board.hpp"
class Board;

class Computer
{
private:
    int playerNo;

public:
    Computer(int playerNo);
    // TODO: implement destructor
    // ~Computer() = default;

    int getMove(Board b);
};

#endif