// SudokuController.h
#ifndef SUDOKU_CONTROLLER_H
#define SUDOKU_CONTROLLER_H

#include "Sudoku.h"
#include "IOInterface.h"
#include "OperationRecorder.h"
#include <vector>

// 前向声明，避免循环依赖
class MainMenuManager;
class GameMenuManager;

class SudokuController {
private:
    Sudoku* sudoku;
    IOInterface* io;
    MainMenuManager* mainMenuManager;
    GameMenuManager* gameMenuManager;
    bool isSudokuRunning;
    bool isRunning;
    OperationRecorder operationRecorder;

    bool getIDRange(int& minID, int& maxID);
    bool getAvailableIDs(std::vector<int>& availableIDs);

public:
    SudokuController(Sudoku* sudokuModel, IOInterface* ioInterface);
    ~SudokuController();

    void start();           // 主循环，包括主菜单

    void startGame();           // 主循环，包括主菜单

private:
    void loadGame();        // 载入游戏
    void gameLoop();   // 游戏主循环
    void handleMenuSelection();
};

#endif // SUDOKU_CONTROLLER_H
