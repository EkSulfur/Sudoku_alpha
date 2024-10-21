// GameMenuManager.h
#ifndef GAME_MENU_MANAGER_H
#define GAME_MENU_MANAGER_H

#include "MenuManager.h"
#include "Sudoku.h"
#include "IOInterface.h"
#include "OperationRecorder.h"

class GameMenuManager : public MenuManager {
private:
    Sudoku* sudoku;
    IOInterface* io;
    OperationRecorder* operationRecorder;
    bool* isSudokuRunning;

public:
    GameMenuManager(Sudoku* sudoku, IOInterface* io, OperationRecorder* operationRecorder, bool* isSudokuRunning);

    int displayMenu(IOInterface* io);

    void buildMenu() override;
};

#endif // GAME_MENU_MANAGER_H
