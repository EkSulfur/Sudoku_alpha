#ifndef SUDOKUCONTROLLER_H
#define SUDOLUCONTROLLER_H

#include "Sudoku.h"
#include "IOInterface.h"
#include "MenuManager.h"
#include "PuzzleLoader.h"
#include "OperationRecorder.h"

class SudokuController {
private:
    PuzzleData puzzleData;
    Sudoku* sudoku;
    IOInterface* io;
    MenuManager menuManager;
    bool isRunning;
    OperationRecorder operationRecorder;
  
public:
    // 构造函数
    SudokuController(Sudoku* sudokuModel, IOInterface* ioInterface);


    // 开始#include "MenuManager.h"游戏
    void startGame();

private:
    // 处理用户选择的菜单选项
    void handleMenuSelection();
};

#endif 
