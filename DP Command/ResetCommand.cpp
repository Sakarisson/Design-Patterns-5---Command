#include "ResetCommand.h"

ResetCommand::ResetCommand(int discSize, HanoiEngine* hanoiEngine) {
    _hanoiEngine = hanoiEngine;
    _discSize = discSize;
}

ResetCommand::~ResetCommand() {

}

void ResetCommand::execute() {
    _hanoiEngine->reset(_discSize);
}

std::string ResetCommand::toString() {
    return "reset " + std::to_string(_discSize);
}
