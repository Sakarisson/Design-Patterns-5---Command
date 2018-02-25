#include "HanoiEngine.h"
#include "MoveCommand.h"
#include "CommandManager.h"
#include <memory>

int main() {
    std::unique_ptr<HanoiEngine> he = std::make_unique<HanoiEngine>(10);
    he->move(0, 2);
    he->move(0, 1);
    he->move(2, 1);
    he->move(0, 2);
    he->move(1, 2);
    he->show();
    return 0;
}
