#ifndef BOARD
#define BOARD

#include <memory>
#include <vector>
#include "Pebble.hpp"

class Pebble;

class Board
{
private:
    std::vector<std::vector<std::unique_ptr<Pebble>>> board;
    std::unique_ptr<int> currentPlayer;
    std::unique_ptr<int> score0;
    std::unique_ptr<int> score1;
    std::unique_ptr<bool> isGameOver;
    std::unique_ptr<int> winner;

    bool isStore(int pocketIndex);

public:
    Board();
    // ~Board();

    bool move(int pocketIndex);
    bool checkVictory();
    void print();
};

#endif