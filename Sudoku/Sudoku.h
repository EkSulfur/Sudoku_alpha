
#ifndef SUDOKU_H
#define SUDOKU_H
/*
数独游戏主体
*/
#include "Cell.h"
#include "Block.h"
#include "Row.h"
#include "Column.h"
#include "IOInterface.h"
#include "MenuManager.h"
#include "PuzzleLoader.h"
#include <string>
#include <vector>

class Sudoku {
private:
    std::vector<std::vector<Cell*>> board;  // 9x9的Cell指针矩阵
    std::vector<Row> rows;                  // 9个Row
    std::vector<Column> columns;            // 9个Column
    std::vector<Block> blocks;              // 9个Block
    int id;
    std::string difficulty;
    IOInterface* io;              // 指向IO接口的指针
    MenuManager menuManager;      // 管理菜单的实例
    PuzzleLoader* puzzleLoader;   // 题目库加载器的指针

    // 初始化Board，设置初始提示
    void initializeBoard(const std::vector<int>& boardData);

    // 显示当前Board状态
    void displayBoard() const;

    // 配置菜单项
    void setupMenu();

public:
    // 构造函数
    Sudoku(IOInterface* ioInterface, PuzzleLoader* loader);

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

#endif // SUDOKU_H
