#include "Board.hpp"
#include "Pebble.hpp"
#include <ncurses.h>
#include <iostream>

Board::Board() {
    // Initialize the board with 4 pebbles in each pocket
    for (int i = 0; i < 12; ++i) {
        std::vector<Pebble*> pocket;
        for (int j = 0; j < 4; ++j) {
            pocket.push_back(new Pebble(1, 1)); // TODO: Randomize colors & sizes
        }
        board.push_back(pocket);
    }

    // Initialize scores and game state
    currentPlayer = std::make_unique<int>(0); // Player 0 always starts
    score0 = std::make_unique<int>(0);
    score1 = std::make_unique<int>(0);
    isGameOver = std::make_unique<bool>(false);
}

bool Board::move(int pocketIndex) {
    // Validate the selected pocket index
    if (*isGameOver || pocketIndex < 0 || pocketIndex >= 14 || board[pocketIndex].empty() || pocketIndex == 6 || pocketIndex == 13) {
        return false;
    }

    std::vector<Pebble*> hand;
    hand.swap(board[pocketIndex]);

    int currentIndex = pocketIndex;
    while (!hand.empty()) {
        // Move to next pocket
        currentIndex = (currentIndex + 1) % 14;

        // Skip opponent's store
        if ((currentIndex == 13 && *currentPlayer == 0) || (currentIndex == 6 && *currentPlayer == 1)) {
            continue;
        }

        // Place one pebble in the current pocket or store
        board[currentIndex].push_back(hand.back());
        hand.pop_back();
    }

    // Switch current player if the last pebble did not land in the player's store
    if ((currentIndex != 6 || *currentPlayer != 0) && (currentIndex != 13 || *currentPlayer != 1)) {
        *currentPlayer = (*currentPlayer + 1) % 2;
    }

    // Check if game over
    *isGameOver = checkVictory();

    return true;
}


bool Board::checkVictory() {
    // Check if all pockets on one side are empty
    bool side0Empty = true, side1Empty = true;
    for (int i = 0; i < 6; ++i) { 
        if (!board[i].empty()) {
            side0Empty = false;
            break;
        }
    }
    for (int i = 7; i < 13; ++i) { 
        if (!board[i].empty()) {
            side1Empty = false;
            break;
        }
    }

    if (side0Empty || side1Empty) {
        *score0 = board[6].size();
        *score1 = board[13].size();

        if (*score0 > *score1) {
            winner = std::make_unique<int>(0);
        } else if (*score1 > *score0) {
            winner = std::make_unique<int>(1);
        } else {
            winner = std::make_unique<int>(-1); // A tie
        }

        *isGameOver = true;
        return *isGameOver;
    }
}

void Board::print() {
    // Player 0
    std::cout << "Player 0 Pockets: ";
    for (int i = 0; i < 6; ++i) {
        std::cout << board[i].size() << " ";
    }
    std::cout << "\nPlayer 0 Store: " << board[6].size() << std::endl;

    // Player 1
    std::cout << "Player 1 Pockets: ";
    for (int i = 7; i < 13; ++i) {
        std::cout << board[i].size() << " ";
    }
    std::cout << "\nPlayer 1 Store: " << board[13].size() << std::endl;
}
