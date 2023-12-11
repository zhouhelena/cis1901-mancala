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
    std::unique_ptr<bool> isGameOver;
    bool isStore(int pocketIndex);
    bool extraTurn0 = false;
    bool extraTurn1 = false;

public:
    Board();
    // TODO: implement destructor
    // ~Board() = default;

    bool canMove(int pocketIndex);
    bool move(int pocketIndex);
    bool checkVictory();
    void print();
    void printCurrPlayer();
    int getScore(int player);

    // Helpers
    int countPebbles(int pocketIndex) const;
    bool hasExtraTurn0() const { return extraTurn0; }
    bool hasExtraTurn1() const { return extraTurn1; }
    int getCurrentPlayer() const { return *currentPlayer; }
    bool getIsGameOver() const { return *isGameOver; }
    const std::vector<std::vector<std::unique_ptr<Pebble>>>& getBoard() const { return board; }
};

#endif