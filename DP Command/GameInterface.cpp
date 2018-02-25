#include "GameInterface.h"

#include <iostream>
#include <string>

using std::endl;

GameInterface::GameInterface() {
    _hanoiEngine = std::make_unique<HanoiEngine>();
    _commandManager = std::make_unique<CommandManager>();
    lastMenuResult = "Welcome";
}

GameInterface::~GameInterface() {

}

void GameInterface::run() {
    while (!_hanoiEngine->isDone()) {
        this->tick();
    }
}

void GameInterface::showGame() {
    _hanoiEngine->show();
}

void GameInterface::showMenu() {
    std::cout <<
        lastMenuResult << endl <<
        "====================================" << endl <<
        "1. Replay last game" << endl <<
        "2. Move" << endl <<
        "3. Undo" << endl <<
        "4. Redo" << endl <<
        "5. Reset" << endl <<
        "What would you like to do? ";
}

int GameInterface::getUserInput() {
    int input;
    std::cin >> input;
    return input;
}

void GameInterface::tick() {
    std::cout <<
        "Towers of Hanoi" << endl <<
        "============================================================" << endl;
    this->showGame();
    std::cout <<
        "============================================================" << endl;
    this->showMenu();
    int choice = this->getUserInput();
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
    default:
        std::cout << "Invalid choice" << endl;
    }
    system("cls");
}

void GameInterface::replay() {

}

void GameInterface::move() {

}

void GameInterface::undo() {

}

void GameInterface::redo() {

}

void GameInterface::reset() {

}
