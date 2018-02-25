#pragma once
#include "Command.h"

class MoveCommand : public Command {
public:
    MoveCommand();
    ~MoveCommand();

    void execute() override;
    bool undoable() override { return true; }
    void undo() override;
};
