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
    std::unique_ptr<int> winner;

    bool isStore(int pocketIndex);

public:
    Board();
    // TODO: implement destructor
    // ~Board() = default;

    bool canMove(int pocketIndex);
    bool move(int pocketIndex);
    bool checkVictory();
    void print();
    void printCurrPlayer();

    // Helpers
    int countPebbles(int pocketIndex);
    std::unique_ptr<bool> isGameOver;
    const std::vector<std::vector<std::unique_ptr<Pebble>>>& getBoard() const { return board; }

};

#endif