#pragma once
#include "Command.h"
#include "HanoiEngine.h"

class MoveCommand : public Command {
public:
    MoveCommand(HanoiEngine*);
    ~MoveCommand();

    void execute() override;
    bool undoable() override { return true; }
    void undo() override;

private:
    HanoiEngine* _hanoiEngine;
};
