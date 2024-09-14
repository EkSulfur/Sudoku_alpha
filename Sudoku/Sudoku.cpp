#include "Sudoku.h"
#include "BasicCommands.h"
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

bool Sudoku::loadFromFile(int gameID)
{
    std::vector<std::vector<int>> boardData; // 存储题目数据
    if(!(puzzleLoader->loadPuzzle("Puzzles.dat", id, boardData, difficulty))) return false;  // 加载棋盘信息
    initializeBoard(boardData);
    return true;
}

bool Sudoku::saveToFile(int gameID)
{
    std::vector<std::vector<int>> boardData(9, std::vector<int>(9));  // 创建9x9的boardData矩阵

    // 遍历数独棋盘，将每个Cell的值保存到boardData中
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            boardData[i][j] = board[i][j].getValue();  // 将每个Cell的值存入boardData
        }
    }

    // 调用puzzleLoader的savePuzzle函数，将棋盘信息保存到文件中
    return puzzleLoader->savePuzzle("Puzzles.dat", gameID, boardData, difficulty);
}

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

bool Sudoku::removeCellCandidates(int row, int col, int candidate)
{
    //把用户的输入转换成索引
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

bool Sudoku::autoUpdateCandidates()
{
    // 遍历数独棋盘中的每个Cell
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Cell *cell = &board[i][j];

            // 如果这个Cell已经确定了值，则跳过
            if (cell->isSolved()) {
                continue;
            }

            // 对于每个候选值1到9，检查它是否可以存在
            for (int candidate = 1; candidate <= 9; ++candidate) {
                // 如果行、列或块中已经有了这个值，则从候选值中删除
                if (rows[i].hasValue(candidate) ||
                    columns[j].hasValue(candidate) ||
                    blocks[(i / 3) * 3 + j / 3].hasValue(candidate)) {
                    cell->removeCandidate(candidate);
                }
            }
        }
    }
    return true;  //自动更新好，返回true
}

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

bool Sudoku::reset()
{
    std::vector<std::vector<int>> boardData; // 存储题目数据

    // 调用puzzleLoader加载数独题目
    if (!puzzleLoader->loadPuzzle("Puzzles.dat", id, boardData, difficulty)) {
        return false;
    }

    // 遍历board，修改已有的Cell，并调用resetCandidates
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int val = boardData[i][j];              // 从加载的数据获取新的值
            board[i][j].setValue(val);             // 修改已有的Cell的值
            board[i][j].resetCandidates();         // 重置Cell的候选值
        }
    }

    return true;  // 重置成功
}

int Sudoku::getID() const
{
    return this->id;
}

std::string Sudoku::getDifficulty() const
{
    return this->difficulty;
}

std::vector<std::vector<Cell>> Sudoku::getBoard() const
{
    return this->board;
}
