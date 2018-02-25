#include "CommandManager.h"
#include <fstream>
#include <string>

CommandManager::CommandManager() {

}


CommandManager::~CommandManager() {
    std::ofstream saveFile;
    saveFile.open("Hanoi.log");
    for (auto& command : _commandsIssued) {
        std::string res = command->toString();
        saveFile << command->toString() << std::endl;
    }
    saveFile.close();
}

void CommandManager::storeAndExecute(std::unique_ptr<Command> command) {
    if (command != nullptr) {
        command->execute();
        // If currentIndex does not correspond with commands issued length, it means that
        // the user has undone something, and everything from this point will need to be deleted
        while (_currentIndex < _commandsIssued.size()) {
            _commandsIssued.pop_back();
        }
        _commandsIssued.push_back(std::move(command));
        _currentIndex++;
    }
}

bool CommandManager::undoLast() {
    if (_currentIndex > 0 && _commandsIssued[_currentIndex - 1]->undoable()) {
        _currentIndex--;
        _commandsIssued[_currentIndex]->undo();
        return true;
    }
    // Implied else
    return false;
}

bool CommandManager::redo() {
    if (_currentIndex < _commandsIssued.size()) { // If there exist commands past _currentIndex
        _commandsIssued[_currentIndex]->execute();
        _currentIndex++;
        return true;
    }
    // Implied else
    return false;
}
