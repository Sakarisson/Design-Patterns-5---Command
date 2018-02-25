#include "MoveCommand.h"

MoveCommand::MoveCommand(int from, int to, HanoiEngine* hanoiEngine) {
    _hanoiEngine = hanoiEngine;
    _from = from;
    _to = to;
}

MoveCommand::~MoveCommand() {

}

void MoveCommand::execute() {
    _hanoiEngine->move(_from, _to);
}

void MoveCommand::undo() {
    _hanoiEngine->move(_to, _from);
}

std::string MoveCommand::toString() {
    return "move " + std::to_string(_from) + " " + std::to_string(_to);
}
