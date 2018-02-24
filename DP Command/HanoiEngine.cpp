#include "HanoiEngine.h"

HanoiEngine::HanoiEngine() {

}

void HanoiEngine::show(std::ostream & aStrm) {
    aStrm << "hello" << std::endl;
}

bool HanoiEngine::move(int aFrom, int aTo) {
    return false;
}

void HanoiEngine::reset(int aDiscs) {

}

bool HanoiEngine::isDone() {
    return false;
}
