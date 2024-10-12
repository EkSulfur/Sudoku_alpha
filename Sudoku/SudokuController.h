#ifndef SUDOKU_CONTROLLER_H
#define SUDOKU_CONTROLLER_H

#include "Sudoku.h"
#include "IOInterface.h"
#include "MenuManager.h"
#include "PuzzleLoader.h"
#include "OperationRecorder.h"
#include "Timer.h"
#include "Counter.h"

class SudokuController {
private:
    PuzzleData puzzleData;                  // 对应当前数独的所有信息（难度、题号等）
    Sudoku* sudoku;                         // 内部数独的实现
    int archieve;                           // 存档编号
    IOInterface* io;                        // io接口
    MenuManager gameMenuManager;            // 游戏菜单
    MenuManager mainMenuManager;            // 主菜单 
    bool isSudokuRunning;                   // 数独是否运行
    bool isRunning;  
    Timer timer;  // 组合 Timer 类
    Counter counter;  // 组合 Counter 类// 游戏是否运行（对应主菜单界面）
    OperationRecorder operationRecorder;    // 记录游戏中和设置每个单元中值、删除值相关的操作
  
public:
    // 构造函数
    SudokuController(Sudoku* sudokuModel, IOInterface* ioInterface);

    void displayTimeAndMoves();
    // 开始#include "MenuManager.h"游戏
    void startGame();

private:
    // 处理用户选择的菜单选项
    void handleMenuSelection();
};

#endif 
