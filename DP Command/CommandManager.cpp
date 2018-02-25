#include "CommandManager.h"



CommandManager::CommandManager() {

}


CommandManager::~CommandManager() {

}

void CommandManager::storeAndExecute(std::unique_ptr<Command> command) {
    if (command != nullptr) {
        command->execute();
        _commandsIssued.push_back(std::move(command));
    }
}
