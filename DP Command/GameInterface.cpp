#include "GameInterface.h"
#include "MoveCommand.h"
#include "ResetCommand.h"

#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;

GameInterface::GameInterface() {
    _hanoiEngine = std::make_unique<HanoiEngine>(3);
    _commandManager = std::make_unique<CommandManager>();
    lastMenuResult = "";
    done = false;
    canReplay = true;
}

GameInterface::~GameInterface() {

}

void GameInterface::run() {
    while (!done) {
        this->tick();
    }
}

void GameInterface::showGame() {
    cout <<
        "Towers of Hanoi" << endl <<
        "============================================================" << endl;
    _hanoiEngine->show();
    cout <<
        "============================================================" << endl;
}

void GameInterface::showMenu() {
    if (canReplay) {
        cout << "1. Replay last game" << endl;
    }
    cout <<
        "2. Move" << endl <<
        "3. Undo" << endl <<
        "4. Redo" << endl <<
        "5. Reset" << endl <<
        "6. Quit" << endl;
    if (lastMenuResult != "") {
        cout <<
            "====================================" << endl <<
            lastMenuResult << endl <<
            "====================================" << endl;
    }
    cout <<
        "What would you like to do? ";
}

int GameInterface::getUserInput() {
    int input;
    std::cin >> input;
    return input;
}

void GameInterface::tick() {
    if (_hanoiEngine->isDone()) {
        lastMenuResult = "You win!";
    }
    this->showGame();
    this->showMenu();
    int choice = this->getUserInput();
    if (canReplay && choice != 1) { // Clear log file
        std::ofstream saveFile;
        saveFile.open("Hanoi.log");
        saveFile << "";
        saveFile.close();
    }
    switch (choice) {
    case 1:
        this->replay();
        break;
    case 2:
        this->move();
        break;
    case 3:
        this->undo();
        break;
    case 4:
        this->redo();
        break;
    case 5:
        this->reset();
        break;
    case 6:
        done = true;
        break;
    default:
        lastMenuResult = "Invalid choice";
        break;
    }
    getchar();
    system("cls");
    canReplay = false;
}

void GameInterface::replay() {
    if (!canReplay) {
        lastMenuResult = "You can't replay anymore...";
        return;
    }
    std::ifstream saveFile("Hanoi.log");
    if (!saveFile.good()) {
        lastMenuResult = "Could not open save file";
        return;
    }
    // Implied else
    std::string commandType;
    while (saveFile >> commandType) {
        std::unique_ptr<Command> command;
        if (commandType == "move") {
            int from, to;
            saveFile >> from >> to;
            command = std::make_unique<MoveCommand>(from, to, _hanoiEngine.get());
        }
        else if (commandType == "reset") {
            int discSize;
            saveFile >> discSize;
            command = std::make_unique<ResetCommand>(discSize, _hanoiEngine.get());
        }
        else if (commandType == "undo") {
            _commandManager->undoLast();
        }
        else if (commandType == "redo") {
            _commandManager->redo();
        }
        if (command != nullptr) {
            _commandManager->storeAndExecute(std::move(command), false);
        }
        system("cls");
        showGame();
        showMenu();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    saveFile.close();
}

void GameInterface::move() {
    int from, to;
    cout <<
        "From: ";
    std::cin >> from;
    cout <<
        "To: ";
    std::cin >> to;
    if (1 > from || 3 < from || 1 > to || 3 < to) {
        lastMenuResult = "Invalid tower. Please pick a number between 1 and 3";
        return;
    }
    // Implied else
    std::unique_ptr<MoveCommand> gameMove = std::make_unique<MoveCommand>(from - 1, to - 1, _hanoiEngine.get());
    _commandManager->storeAndExecute(std::move(gameMove));
    lastMenuResult = "Moved disc from tower " + std::to_string(from) + " to tower " + std::to_string(to);
}

void GameInterface::undo() {
    if (_commandManager->undoLast()) {
        lastMenuResult = "Undid last move";
    } else {
        lastMenuResult = "Unable to undo";
    }
}

void GameInterface::redo() {
    if (_commandManager->redo()) {
        lastMenuResult = "Redid last undo";
    } else {
        lastMenuResult = "Unable to redo";
    }
}

void GameInterface::reset() {
    int discNumber;
    cout <<
        "How many discs would you like in the new game? ";
    discNumber = this->getUserInput();
    if (discNumber < 3) {
        lastMenuResult = "Please choose at least 3 disks";
        return;
    }
    // Implied else
    std::unique_ptr<ResetCommand> resetCommand = std::make_unique<ResetCommand>(discNumber, _hanoiEngine.get());
    _commandManager->storeAndExecute(std::move(resetCommand));
    lastMenuResult = "New game started with " + std::to_string(discNumber) + " discs";
}
