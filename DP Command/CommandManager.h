#pragma once

#include <vector>
#include <memory>

#include "Command.h"

class CommandManager {
public:
    CommandManager();
    ~CommandManager();
    void storeAndExecute(std::unique_ptr<Command>);
    bool undoLast();
    bool redo();
private:
    std::vector<std::unique_ptr<Command>> _commandsIssued;
    size_t _currentIndex = 0;
};

