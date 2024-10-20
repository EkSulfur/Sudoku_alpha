#include "Sudoku.h"
#include "BasicCommands.h"
#include "StateManager.h"
#include <sstream>
#include <fstream>
#include <iostream>


/*
9月7日
完成目前Sudoku类的所有函数，游戏内部逻辑主体部分告成，未测试
9月8日
增加play函数中游戏开始前关于读取id和加载的循环
9月10日
更改play函数，分离各个菜单选项选项和play函数，实现命令模式
9月14日
修复了无法删除数时不会显示信息的bug
by lch
*/

// 初始化棋盘
void Sudoku::initializeBoard(const std::vector<std::vector<int>>& boardData)
{
    // 初始化board, rows, columns, blocks
    board.resize(9, std::vector<Cell>(9));
    rows.resize(9);
    columns.resize(9);
    blocks.resize(9);

    // 填充Cell并绑定到rows, columns和blocks中
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int val = boardData[i][j];  // 从数据中获取数独的初始值
            Cell cell = Cell(val); // 使用new创建Cell对象
            board[i][j] = cell;         // 绑定到board矩阵

            // 绑定到对应的row, column和block
            rows[i].addCell(&board[i][j]);      // 添加到对应的row
            columns[j].addCell(&board[i][j]);   // 添加到对应的column
            blocks[(i / 3) * 3 + j / 3].addCell(&board[i][j]);  // 添加到对应的block
        }
    }
}

Sudoku::Sudoku(PuzzleLoader* loader):puzzleLoader(loader), id(1) {} // 默认初始化的id为1

// 从文件中读取数据到puzzleData
bool Sudoku::loadFromFileToData(PuzzleData& puzzleData)
{
    if (!puzzleLoader->loadPuzzle(puzzleData)) return false;
    return true;
}

// 从Data中读取数据到Sudoku的数据成员中
bool Sudoku::loadFromData(PuzzleData& puzzleData)
{
    // 创建一个9x9的棋盘矩阵
    std::vector<std::vector<int>> boardData(9, std::vector<int>(9));

    // 加载成功后，用 puzzleData 中的数据初始化游戏棋盘
    initializeBoard(puzzleData.board);  // 使用加载的棋盘数据
    setDifficulty(puzzleData.difficulty);
    return true;
}

// 保存游戏
bool Sudoku::saveToFile(int gameID)
{
    // 创建9x9的棋盘数据矩阵
    std::vector<std::vector<int>> boardData(9, std::vector<int>(9));

    // 遍历数独棋盘，将每个Cell的值保存到boardData中
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            boardData[i][j] = board[i][j].getValue();  // 将Cell的值存入boardData
        }
    }

    // 创建一个 PuzzleData 对象，封装要保存的棋盘信息
    PuzzleData* puzzleData= &StateManager::getInstance().puzzleData;
    puzzleData->board = boardData;

    // 调用 puzzleLoader 的 savePuzzle 函数保存数独数据
    return puzzleLoader->savePuzzle(*puzzleData);
}

// 设置某一单元的值（设为0为擦去）
bool Sudoku::setCellValue(int row, int col, int value)
{
    //把用户的输入转换成索引
    row -= 1;
    col -= 1;

    // 检查行列是否越界
    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        return false;
    }

    // 如果Cell中数字是固定的，返回false
    if (board[row][col].isFixed()) return false;

    // 如果是设置为 0，表示擦除对应位置的数值
    if (value == 0) {
        // 调用对应Cell的setValue函数，将值设为0
        board[row][col].setValue(0);  // 擦除值
        return true;  // 擦除操作总是合法的
    }

    // 调用对应Cell的setValue函数，设置新值
    if (!board[row][col].setValue(value)) {
        return false;
    }

    // 检查对应的行、列和块是否合法
    if (!rows[row].isValid()) {
        board[row][col].setValue(0); // 重新设置值为0
        return false;
    }
    if (!columns[col].isValid()) {
        board[row][col].setValue(0); // 重新设置值为0
        return false;
    }
    if (!blocks[(row / 3) * 3 + col / 3].isValid()) {
        board[row][col].setValue(0); // 重新设置值为0
        return false;
    }

    // 如果所有检查都通过，则返回true
    return true;
}

// 添加候选数
bool Sudoku::addCellCandidate(int row, int col, int candidate)
{
    //把用户的输入转换成索引
    row -= 1;
    col -= 1;

    // 检查行列是否越界
    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        return false;
    }

    // 调用对应Cell的addCandidate函数，添加新值
    if (!board[row][col].addCandidate(candidate)) {
        return false;
    }

    return true;
}

// 删除候选数
bool Sudoku::removeCellCandidates(int row, int col, int candidate)
{
    //把用户的输入转换成索引  注意此处！！！
    row -= 1;
    col -= 1;

    // 检查行列是否越界
    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        return false;
    }

    // 调用对应Cell的removeCandidate函数，移除候选值
    if (!board[row][col].removeCandidate(candidate)) {
        return false;
    }

    return true;
}

// 检查是否已经完成
bool Sudoku::checkIfSolved() const
{
    // 检查每一个row是否已经完成
    for (int i = 0; i < 9; ++i) {
        if (!rows[i].isSolved()) {
            return false;
        }
    }

    // 9个row都填完代表游戏已经完成
    return true;
}

// 重置游戏（从Data中读取原来的棋盘）
bool Sudoku::reset()
{
    // 创建一个9x9的棋盘矩阵来存储题目数据
    std::vector<std::vector<int>> boardData(9, std::vector<int>(9));

    PuzzleData* puzzleData = &StateManager::getInstance().puzzleData;

    // 调用 puzzleLoader 来加载数独题目
    if (!puzzleLoader->loadPuzzle(*puzzleData)) {
        return false;  // 如果加载失败，返回false
    }

    // 遍历棋盘，重置每个Cell的值和候选值
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int val = (*puzzleData).board[i][j];       // 从加载的数据获取新的值
            board[i][j].setValue(val);             // 设置Cell的值
            board[i][j].resetCandidates();         // 重置Cell的候选值
        }
    }

    return true;  // 重置成功
}


int Sudoku::getID() const
{
    return this->id;
}

std::string Sudoku::getDifficulty()const 
{    
    return this->difficulty;
}

void Sudoku::setDifficulty(const std::string& difficulty)
{
     this->difficulty=difficulty;
}

std::vector<std::vector<Cell>> Sudoku::getBoard() const
{
    return this->board;
}

Row Sudoku::getRow(int row) const
{
    return this->rows[row];
}

Column Sudoku::getColumn(int column) const
{
    return this->columns[column];
}

Block Sudoku::getBlock(int block) const
{
    return this->blocks[block];
}
