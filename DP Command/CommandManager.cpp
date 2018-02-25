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

void CommandManager::storeAndExecute(std::unique_ptr<Command> command, bool log) {
    if (command != nullptr) {
        command->execute();
        if (log) {
            this->logChange(command->toString());
        }
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
        this->logChange("undo");
        return true;
    }
    // Implied else
    return false;
}

void CommandManager::logChange(std::string change) {
    std::ifstream ifs("Hanoi.log");
    std::string logContents((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));

    std::ofstream logFile;
    logFile.open("Hanoi.log");
    logFile <<
        logContents <<
        change << std::endl;
    logFile.close();
}

bool CommandManager::redo() {
    if (_currentIndex < _commandsIssued.size()) { // If there exist commands past _currentIndex
        _commandsIssued[_currentIndex]->execute();
        _currentIndex++;
        this->logChange("redo");
        return true;
    }
    // Implied else
    return false;
}
