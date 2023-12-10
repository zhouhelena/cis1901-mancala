#include "computer.hpp"

Computer::Computer(int playerNo) : playerNo(playerNo)
{
}

/// @brief calculates move for computer player
/// @param b the board
/// @return -1 if error, otherwise which pocket to move from
int Computer::getMove(Board b)
{
    int maxPocket = playerNo == 0 ? 5 : 12;
    int minPocket = playerNo == 0 ? 0 : 7;
    int store = playerNo == 0 ? 6 : 13;

    for (int i = maxPocket; i >= minPocket; i--)
    {
        // last pebble dropped in store
        if (b.countPebbles(i) == (store - i))
            return i;
    }

    for (int i = maxPocket; i >= minPocket; i--)
    {
        // last pebble in empty pocket (takes all pebbles from opposite pocket)
        if (b.countPebbles(i) == 0 && b.countPebbles(12 - i))
        {
            for (int j = i - 1; j >= minPocket; j++)
            {
                if (b.countPebbles(j) == (i - j))
                    return j;
            }
        }
    }

    // else just return the first pocket that has pebbles
    for (int i = maxPocket; i >= minPocket; i--)
    {
        if (b.countPebbles(i) > 0)
            return i;
    }
    return -1;
}