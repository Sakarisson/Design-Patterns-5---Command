#pragma once
#include "Command.h"
#include "HanoiEngine.h"

class MoveCommand : public Command {
public:
    MoveCommand(int, int, HanoiEngine*);
    ~MoveCommand();

    void execute() override;
    bool undoable() override { return true; }
    void undo() override;
    std::string toString() override;
private:
    int _from;
    int _to;
    HanoiEngine* _hanoiEngine;
};
