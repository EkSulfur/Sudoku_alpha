// MainMenuManager.h
#ifndef MAIN_MENU_MANAGER_H
#define MAIN_MENU_MANAGER_H

#include "MenuManager.h"

// 前向声明，避免循环依赖
class SudokuController;

class MainMenuManager : public MenuManager {
	SudokuController* controller;
    IOInterface* io;
    bool* isRunning;

public:
    MainMenuManager(SudokuController* controller, IOInterface* io, bool* isRunning);

    void buildMenu() override;
};

#endif // MAIN_MENU_MANAGER_H
