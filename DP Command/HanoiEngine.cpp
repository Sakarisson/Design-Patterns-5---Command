#include "HanoiEngine.h"
#include <fstream>
#include <iomanip>

using std::endl;

HanoiEngine::HanoiEngine(int aLevels) {
    iDiscs = aLevels;
    for (int i = iDiscs; i > 0; i--) {
        iTowers[T1].push_back(i);
    }
}

void HanoiEngine::show(std::ostream& aStrm) {
    int minWidth = 2;
    int spaceBetweenTowers = 2;
    for (int i = iDiscs; i > 0; i--) {
        int towerNumber = 0;
        for (auto tower : iTowers) {
            towerNumber++;
            if (tower.size() >= i) {
                int maxDiskWidth = iDiscs + minWidth;
                int halfDiskSize = tower.at(i - 1) + minWidth;
                int blankSpace = (maxDiskWidth - halfDiskSize) + 1;
                aStrm <<
                    std::setfill(' ') << std::setw(blankSpace) << "" <<
                    std::setfill('=') << std::setw(halfDiskSize) << "" <<
                    "||" <<
                    std::setfill('=') << std::setw(halfDiskSize) << "" <<
                    std::setfill(' ') << std::setw(blankSpace) << "";
                if (towerNumber < 3) {
                    aStrm << "#";
                }
            }
            else {
                aStrm <<
                    std::setfill(' ') << std::setw(iDiscs + minWidth + 1) << "" <<
                    "||" <<
                    std::setfill(' ') << std::setw(iDiscs + minWidth + 1) << "";
                if (towerNumber < 3) {
                    aStrm << "#";
                }
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

}

bool HanoiEngine::isDone() {
    return false;
}
