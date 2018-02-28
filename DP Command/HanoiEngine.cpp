#include "HanoiEngine.h"
#include <fstream>
#include <iomanip>

using std::endl;

HanoiEngine::HanoiEngine(int aLevels) {
    iDiscs = aLevels;
    this->addDiscs();
}

void HanoiEngine::show(std::ostream& aStrm) {
    int minWidth = 2;
    int spaceBetweenTowers = 2;
    char blankCharacter = ' ';
    char diskCharacter = '=';
    char towerCharacter = '|';
    char separatingCharacter = '#';
    for (int i = iDiscs; i > 0; i--) {
        int towerNumber = 0;
        for (auto tower : iTowers) {
            towerNumber++;
            if (tower.size() >= i) {
                int maxDiskWidth = iDiscs + minWidth;
                int halfDiskSize = tower.at(i - 1) + minWidth;
                int blankSpace = (maxDiskWidth - halfDiskSize) + 1;
                aStrm <<
                    std::setfill(blankCharacter) << std::setw(blankSpace) << "" <<
                    std::setfill(diskCharacter) << std::setw(halfDiskSize) << "" <<
                    towerCharacter << towerCharacter <<
                    std::setfill(diskCharacter) << std::setw(halfDiskSize) << "" <<
                    std::setfill(blankCharacter) << std::setw(blankSpace) << "";
            }
            else {
                aStrm <<
                    std::setfill(blankCharacter) << std::setw(iDiscs + minWidth + 1) << "" <<
                    towerCharacter << towerCharacter <<
                    std::setfill(blankCharacter) << std::setw(iDiscs + minWidth + 1) << "";
            }
            if (towerNumber < 3) {
                aStrm << separatingCharacter;
            }
        }
        aStrm << endl;
    }
}

bool HanoiEngine::move(int aFrom, int aTo) {
    if (iTowers[aFrom].empty()) {
        return false;
    }
    else if (!iTowers[aTo].empty() && iTowers[aFrom].back() >= iTowers[aTo].back()) {
        return false;
    }
    // Implied else
    int value = iTowers[aFrom].back();
    iTowers[aFrom].pop_back();
    iTowers[aTo].push_back(value);
    return true;
}

void HanoiEngine::reset(int aDiscs) {
    for (auto& tower : iTowers) {
        tower.clear();
    }
    iDiscs = aDiscs;
    this->addDiscs();
}

bool HanoiEngine::isDone() {
    return iTowers[T1].empty() && iTowers[T2].empty();
}

void HanoiEngine::addDiscs() {
    for (int i = iDiscs; i > 0; i--) {
        iTowers[T1].push_back(i);
    }
}
