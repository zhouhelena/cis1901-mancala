#ifndef BOARD
#define BOARD

#include <stdexcept>
#include <iostream>
#include <vector>

class Board
{
    private:
        std::vector<Pebble*> board;
        std::unique_ptr<int> currentPlayer;
        std::unique_ptr<int> score0;
        std::unique_ptr<int> score1;
        std::unique_ptr<bool> isGameOver;
    
    public:
        Board();
        bool move(int store);
        bool checkVictory();
        void print();
};

#endif