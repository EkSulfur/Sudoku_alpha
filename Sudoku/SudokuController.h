#ifndef SUDOKU_CONTROLLER_H
#define SUDOKU_CONTROLLER_H

#include "Sudoku.h"
#include "IOInterface.h"
#include "MenuManager.h"
#include "PuzzleLoader.h"
#include "OperationRecorder.h"
#include "Timer.h"
#include "Counter.h"
#include "PuzzleData.h"
#include <string>
#include <vector> // 添加以支持 std::vector

class SudokuController {
private:
    // 计时器、记步器和PuzzleData和StateManager类组合，使用单例模式
    Sudoku* sudoku;                         // 内部数独的实现
    int archieve;                           // 存档编号
    IOInterface* io;                        // io接口
    MenuManager gameMenuManager;            // 游戏菜单
    MenuManager mainMenuManager;            // 主菜单 
    bool isSudokuRunning;                   // 数独是否运行
    bool isRunning;                         // 程序是否运行（对应主菜单界面）
    OperationRecorder operationRecorder;    // 记录游戏中的操作

    // 存档文件路径
    const std::string SAVE_FILE_PATH = "Puzzles.dat";

    // 私有成员函数
    bool getIDRange(int& minID, int& maxID);
    bool getAvailableIDs(std::vector<int>& availableIDs); // 新增声明

public:
    // 构造函数
    SudokuController(Sudoku* sudokuModel, IOInterface* ioInterface);

    void startGame();

private:
    // 处理用户选择的菜单选项
    void handleMenuSelection();
};

#endif // SUDOKU_CONTROLLER_H
