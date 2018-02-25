#include "CommandManager.h"



CommandManager::CommandManager() {

}


CommandManager::~CommandManager() {

}

void CommandManager::storeAndExecute(std::unique_ptr<Command> command) {
    if (command != nullptr) {
        command->execute();
        // If currentIndex does not correspond with commands issued length, it means that
        // the user has undone something, and everything from this point will need to be deleted
        while (_currentIndex < _commandsIssued.size() - 1) {
            _commandsIssued.pop_back();
        }
        _commandsIssued.push_back(std::move(command));
        _currentIndex++;
    }
}

bool CommandManager::undoLast() {
    if (_currentIndex > 0 && _commandsIssued[_currentIndex - 1]->undoable()) {
        _commandsIssued[_currentIndex - 1]->undo();
        _currentIndex--;
        return true;
    }
    // Implied else
    return false;
}

bool CommandManager::redo() {
    if (_currentIndex < _commandsIssued.size() - 1) { // If there exist commands past _currentIndex
        _currentIndex++;
        _commandsIssued[_currentIndex]->execute();
        return true;
    }
    // Implied else
    return false;
}
