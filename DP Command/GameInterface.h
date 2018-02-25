#pragma once

#include "HanoiEngine.h"
#include "CommandManager.h"

#include <memory>

class GameInterface {
public:
    GameInterface();
    ~GameInterface();
    void run();
private:
    void showGame();
    void showMenu();
    int getUserInput();
    void tick(); // A single game "tick" - i.e. show game, get user input, process input
private:
    std::unique_ptr<HanoiEngine> _hanoiEngine;
    std::unique_ptr<CommandManager> _commandManager;
};
