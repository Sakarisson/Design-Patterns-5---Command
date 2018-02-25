#pragma once

#include <ostream>
#include <iostream>
#include <deque>

class HanoiEngine {
public:
    HanoiEngine(int aLevels = 5);
    ~HanoiEngine() {}

    // Display the towers with the discs
    void show(std::ostream& aStrm = std::cout);

    // Move a disc from tower aFrom to tower aTo.
    // A successful move returns true
    bool move(int aFrom, int aTo);

    // Reset the game, start with aDiscs discs
    void reset(int aDiscs);

    // Is the game successfully finished?
    bool isDone();
private:
    enum { T1, T2, T3 };
    int iDiscs;
    int iMoves;
    std::deque<int> iTowers[3];
};
