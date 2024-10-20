// MainMenuManager.cpp
#include "MainMenuManager.h"
#include "SudokuController.h"
#include "BasicCommands.h"

MainMenuManager::MainMenuManager(SudokuController* controller, IOInterface* io, bool* isRunning)
    : controller(controller), io(io), isRunning(isRunning) {}

void MainMenuManager::buildMenu() {
    addOption("开始新游戏", new StartNewGameCommand(controller));
    addOption("退出程序", new ExitCommand(io, isRunning));
}
