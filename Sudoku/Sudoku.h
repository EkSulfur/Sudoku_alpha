
#ifndef SUDOKU_H
#define SUDOKU_H
/*
数独游戏主体
*/
#include "Cell.h"
#include "DerivedCellContainer.h"
#include "IOInterface.h"
#include "MenuManager.h"
#include "PuzzleLoader.h"
#include <string>
#include <vector>

/*
9月7日
删除Sudoku类中的displayboard函数（委托给io）
删除start函数，原有功能包含在play中
修改多个函数的返回值从void类型变为bool类型
添加自动更新候选值函数
删除配置菜单项函数
9月8日
添加析构函数（修正）
9月10日
添加MenuManager的使用
9月22日
TODO:更好地分离类的职责，禁止该禁止的拷贝构造。
添加获取列、九宫格、行的函数
*/

class Sudoku {
private:
    std::vector<std::vector<Cell>> board;  // 9x9的Cell指针矩阵
    std::vector<Row> rows;                  // 9个Row
    std::vector<Column> columns;            // 9个Column
    std::vector<Block> blocks;              // 9个Block
    int id;
    std::string difficulty;
    MenuManager menuManager;      // 管理菜单的实例
    PuzzleLoader* puzzleLoader;   // 题目库加载器的指针

    // 初始化Board，设置初始提示
    void initializeBoard(const std::vector<std::vector<int>>& boardData);

public:
    // 构造函数
    Sudoku(PuzzleLoader* loader);

    // 从文件加载游戏数据
    bool loadFromFile(PuzzleData puzzleData);

    // 保存当前游戏到文件
    bool saveToFile(int gameID);

    // 设置某个单元格的值
    bool setCellValue(int row, int col, int value);

    // 添加某个单元格的候选值
    bool addCellCandidate(int row, int col, int candidate);

    // 删除某个单元格的候选值
    bool removeCellCandidates(int row, int col, int candidate);

    // 检查游戏是否完成
    bool checkIfSolved() const;

    // 重置游戏
    bool reset();

    // 获取目前的id
    int getID() const;

    // 获取目前的难度
    std::string getDifficulty() const;

    // 设置目前的难度
    void setDifficulty(const std::string& difficulty);

    // 获取棋盘
    std::vector<std::vector<Cell>> getBoard() const;

    // 获取行
    Row getRow(int row) const;

    // 获取列
    Column getColumn(int column) const;

    // 获取九宫格
    Block getBlock(int block) const;
};

#endif // SUDOKU_H
