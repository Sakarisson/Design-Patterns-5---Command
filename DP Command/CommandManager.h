#pragma once

#include <vector>
#include <memory>

#include "Command.h"

class CommandManager {
public:
    CommandManager();
    ~CommandManager();
    void storeAndExecute(std::unique_ptr<Command>);
private:
    std::vector<std::unique_ptr<Command>> _commandsIssued;
};

