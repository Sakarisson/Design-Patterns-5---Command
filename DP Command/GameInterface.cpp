#include "GameInterface.h"

#include <iostream>

using std::endl;

GameInterface::GameInterface() {
    _hanoiEngine = std::make_unique<HanoiEngine>();
    _commandManager = std::make_unique<CommandManager>();
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
}
