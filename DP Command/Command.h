#pragma once
#include <string>

class Command {
public:
    Command() {}
    virtual ~Command() {}

    virtual void execute() = 0;
    virtual bool undoable() = 0;
    virtual void undo() {} // By default, the undo method does nothing
    virtual std::string toString() = 0;
};
