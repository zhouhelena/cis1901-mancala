#include "computer.hpp"

Computer::Computer(int playerNo) : playerNo(playerNo)
{
}

/// @brief calculates move for computer player
/// @param b the board
/// @return -1 if error, otherwise which pocket to move from
int Computer::getMove(Board b)
{
    if (playerNo == 0)
    {
        for (int i = 0; i < 6; i++)
        {
            if (b.countPebbles(i) > 0)
                // TODO: add smarter AI
                return i;

            // move the store that will allow the player to move again
            // if (b.countPebbles(i) == 0 && b.countPebbles(12 - i) > 0)
            //     return 12 - i;

            // take adv of the hop move rule thing
            // etc
        }
    }
    else
    {
        for (int i = 7; i < 13; i++)
        {
            if (b.countPebbles(i) > 0)
                // TODO: add smarter AI
                return i;
        }
    }
    return -1;
}