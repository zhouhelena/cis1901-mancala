#include "Board.hpp"
#include <iostream>

Board::Board()
{
    // Initialize the board with 4 pebbles in each pocket
    for (int i = 0; i <= 13; ++i)
    {
        std::vector<std::unique_ptr<Pebble>> pocket;
        if (i == 6 || i == 13) // Skip player 0 & 1's store
        {
            board.push_back(std::move(pocket));
            continue;
        }
        for (int j = 0; j < 4; ++j)
        {
            int randomColor = 1; /* Generate a random color */
            int randomSize = 1;  /* Generate a random size */

            pocket.push_back(std::make_unique<Pebble>(randomSize, randomColor));
        }
        board.push_back(std::move(pocket));
    }

    // Initialize scores and game state
    currentPlayer = std::make_unique<int>(0); // Player 0 always starts
    score0 = std::make_unique<int>(0);
    score1 = std::make_unique<int>(0);
    isGameOver = std::make_unique<bool>(false);
}

bool Board::move(int pocketIndex)
{
    if (!canMove(pocketIndex))
        return false;

    if (*currentPlayer == 0 && pocketIndex >= 6)
    {
        return false;
    }

    if (*currentPlayer == 1 && pocketIndex < 7)
    {
        return false;
    }

    // Grab pebbles from pocket
    std::vector<std::unique_ptr<Pebble>> hand;
    hand.swap(board[pocketIndex]);

    int currentIndex = pocketIndex;
    while (!hand.empty())
    {
        // Move to next pocket
        currentIndex = (currentIndex + 1) % 14;

        // Skip opponent's store
        if ((currentIndex == 13 && *currentPlayer == 0) || (currentIndex == 6 && *currentPlayer == 1))
            continue;

        // Place one pebble in the current pocket or store
        board[currentIndex].push_back(std::move(hand.back()));
        hand.pop_back();

        if (hand.empty())
        {
            // If the last pebble lands in an empty pocket on the player's side
            // and the opposite pocket is not empty, capture both pebbles and
            // place them in the player's store
            if (board[currentIndex].size() == 1 && !isStore(currentIndex) && !board[12 - currentIndex].empty())
            {
                // Grab pebbles from opposite pocket
                std::vector<std::unique_ptr<Pebble>> oppositePebbles;
                oppositePebbles.swap(board[12 - currentIndex]);

                // Place pebbles in player's store
                if (*currentPlayer == 0)
                {
                    for (int i = 0; i < oppositePebbles.size(); ++i)
                        board[6].push_back(std::move(oppositePebbles[i]));

                    hand.clear();
                    hand.swap(board[currentIndex]);
                    board[6].push_back(std::move(board[currentIndex].back()));
                }
                else
                {
                    for (int i = 0; i < oppositePebbles.size(); ++i)
                        board[13].push_back(std::move(oppositePebbles[i]));

                    hand.clear();
                    hand.swap(board[currentIndex]);
                    board[13].push_back(std::move(board[currentIndex].back()));
                }
            }
        }
    }

    // Switch current player if the last pebble did not land in the player's store
    if (!(currentIndex == 6 && *currentPlayer == 0) || !(currentIndex == 13 && *currentPlayer == 1))
    {
        *currentPlayer = (*currentPlayer + 1) % 2;
        std::cout << "Switched players: " << *currentPlayer << std::endl;
    }

    // Check if game over
    *isGameOver = checkVictory();

    return true;
}

bool Board::canMove(int pocketIndex)
{
    if (pocketIndex < 0 || pocketIndex >= 14)
        return false;

    if (isStore(pocketIndex))
        return false;

    if (board[pocketIndex].empty())
        return false;

    if (*currentPlayer == 0 && pocketIndex > 5)
        return false;

    if (*currentPlayer == 1 && pocketIndex < 7)
        return false;

    return true;
}

bool Board::checkVictory()
{
    // Check if all pockets on one side are empty
    bool side0Empty = true, side1Empty = true;
    for (int i = 0; i < 6; ++i)
    {
        if (!board[i].empty())
        {
            side0Empty = false;
            break;
        }
    }
    for (int i = 7; i < 13; ++i)
    {
        if (!board[i].empty())
        {
            side1Empty = false;
            break;
        }
    }

    if (side0Empty || side1Empty)
    {
        *score0 = board[6].size();
        *score1 = board[13].size();

        if (*score0 > *score1)
        {
            winner = std::make_unique<int>(0);
        }
        else if (*score1 > *score0)
        {
            winner = std::make_unique<int>(1);
        }
        else
        {
            winner = std::make_unique<int>(-1); // A tie
        }

        *isGameOver = true;
        return *isGameOver;
    }

    return false;
}

std::string formatPrint(int i, bool isStore = false)
{
    if (isStore)
        return i < 10 ? std::to_string(i) + " " : std::to_string(i);
    return i < 10 ? std::to_string(i) + "_" : std::to_string(i);
}

void Board::print()
{
    // Player 0
    // std::cout << "Player 0 Pockets: ";
    // for (int i = 0; i < 6; ++i)
    //     std::cout << board[i].size() << " ";
    // std::cout << "\nPlayer 0 Store: " << board[6].size() << std::endl;

    // Player 1
    // std::cout << "Player 1 Pockets: ";
    // for (int i = 7; i < 13; ++i)
    //     std::cout << board[i].size() << " ";
    // std::cout << "\nPlayer 1 Store: " << board[13].size() << std::endl;

    // Visual representation
    // I stole from https://ascii.co.uk/art/mancala
    std::cout << "__________________________________________________________________" << std::endl;
    std::cout << "/  ____     ____    ____    ____    ____    ____    ____          \\" << std::endl;
    std::cout << "/ |    |   [_" << formatPrint(board[12].size())
              << "_]  [_" << formatPrint(board[11].size())
              << "_]  [_" << formatPrint(board[10].size())
              << "_]  [_" << formatPrint(board[9].size())
              << "_]  [_" << formatPrint(board[8].size())
              << "_]  [_" << formatPrint(board[7].size())
              << "_]   ____  \\" << std::endl;
    std::cout << "/ | " << formatPrint(board[13].size(), true)
              << " |                                                   |    | \\" << std::endl;
    std::cout << "/ |____|    ____    ____    ____    ____    ____    ____   | "
              << formatPrint(board[6].size(), true)
              << " | \\" << std::endl;
    std::cout << "/          [_" << formatPrint(board[0].size())
              << "_]  [_" << formatPrint(board[1].size())
              << "_]  [_" << formatPrint(board[2].size())
              << "_]  [_" << formatPrint(board[3].size())
              << "_]  [_" << formatPrint(board[4].size())
              << "_]  [_" << formatPrint(board[5].size())
              << "_]  |____| \\" << std::endl;
    std::cout << "/_________________________________________________________________\\\n"
              << std::endl;
}

bool Board::isStore(int pocketIndex)
{
    return pocketIndex == 6 || pocketIndex == 13;
}

void Board::printCurrPlayer()
{
    std::cout << "Player " << *currentPlayer << "'s turn: " << std::endl;
}

int Board::countPebbles(int pocketIndex) const
{
    return board[pocketIndex].size();
}