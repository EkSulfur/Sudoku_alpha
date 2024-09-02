#ifndef MINI_SUDOKU_H
#define MINI_SUDOKU_H

#include "Block.h"
#include "IOInterface.h"
#include "MenuManager.h"
#include "PuzzleLoader.h"
#include <string>

class MiniSudoku {
private:
    int id;
    std::string difficulty;
    Block block;
    IOInterface* io;              // 指向IO接口的指针
    MenuManager menuManager;      // 管理菜单的实例
    PuzzleLoader* puzzleLoader;   // 题目库加载器的指针

    // 初始化Block，设置初始提示
    void initializeBlock(const std::vector<int>& boardData);

    // 显示当前Block状态
    void displayBlock() const;

    // 配置菜单项
    void setupMenu();

public:
    // 构造函数
    MiniSudoku(IOInterface* ioInterface, PuzzleLoader* loader);

    // 从文件加载游戏数据
    bool loadFromFile(int gameID);

    // 保存当前游戏到文件
    bool saveToFile(int gameID);

    // 开始游戏
    void start();

    // 设置某个单元格的值
    void setCellValue(int row, int col, int value);

    // 检查游戏是否完成
    bool checkIfSolved() const;

    // 重置游戏
    void reset();
};

#endif // MINI_SUDOKU_H
