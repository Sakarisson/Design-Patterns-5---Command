#pragma once
#include "Command.h"
#include "HanoiEngine.h"

class ResetCommand : public Command {
public:
    ResetCommand(int, HanoiEngine*);
    ~ResetCommand();

    void execute() override;
    bool undoable() override { return false; }
    std::string toString() override;
private:
    HanoiEngine* _hanoiEngine;
    int _discSize;
};
