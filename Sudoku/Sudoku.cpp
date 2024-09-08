#include "Sudoku.h"
#include <sstream>
#include <fstream>
#include <iostream>


/*
9月7日
完成目前Sudoku类的所有函数，游戏内部逻辑主体部分告成，未测试
9月8日
增加play函数中游戏开始前关于读取id和加载的循环
by lch
*/


void Sudoku::initializeBoard(const std::vector<std::vector<int>>& boardData)
{
    // 初始化board, rows, columns, blocks
    board.resize(9, std::vector<Cell*>(9));
    rows.resize(9);
    columns.resize(9);
    blocks.resize(9);

    // 填充Cell并绑定到rows, columns和blocks中
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int val = boardData[i][j];  // 从数据中获取数独的初始值
            Cell* cell = new Cell(val); // 使用new创建Cell对象
            board[i][j] = cell;         // 绑定到board矩阵

            // 绑定到对应的row, column和block
            rows[i].addCell(cell);      // 添加到对应的row
            columns[j].addCell(cell);   // 添加到对应的column
            blocks[(i / 3) * 3 + j / 3].addCell(cell);  // 添加到对应的block
        }
    }
}

Sudoku::Sudoku(IOInterface* ioInterface, PuzzleLoader* loader):io(ioInterface), puzzleLoader(loader)
{
    int id = 1; //先初始化id为1
}

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
            boardData[i][j] = board[i][j]->getValue();  // 将每个Cell的值存入boardData
        }
    }

    // 调用puzzleLoader的savePuzzle函数，将棋盘信息保存到文件中
    return puzzleLoader->savePuzzle("Puzzles.dat", gameID, boardData, difficulty);
}

void Sudoku::play() {
    //加载循环
    while (true) {
        // 选择游戏存档ID
        io->displayMessage("请选择存档编号：");
        std::string input = io->getUserInput();

        // 尝试将用户输入转换为整数ID
        try {
            id = std::stoi(input);  // 将输入的字符串转换为整数ID
        }
        catch (const std::invalid_argument&) {
            io->displayMessage("无效的输入，请输入正确的存档编号。");
            continue;
        }

        // 加载游戏
        if (!loadFromFile(id)) {
            io->displayMessage("无法加载数独游戏。");
            continue;
        }
        else break;
    }

    // 游戏循环
    while (true) {
        // 显示游戏信息和当前棋盘
        io->displayInfo(id, difficulty);
        io->displayBoard(board);

        // 检查游戏是否已经完成
        if (checkIfSolved()) {
            io->displayMessage("恭喜！你已经完成了数独！");
            break;
        }

        // 显示菜单并让玩家选择操作
        std::vector<std::string> options = {
            "输入一个数",      // 用户输入一个数到棋盘
            "擦去一个数",      // 擦去已输入的数
            "输入候选数",      // 输入一个候选数
            "删除候选数",      // 删除一个候选数
            "自动补充候选数",  // 自动更新所有单元格的候选数
            "保存游戏",        // 保存当前游戏
            "重置游戏",        // 重置游戏
            "退出"             // 退出游戏
        };
        int choice = io->displayMenu(options);

        switch (choice) {
        case 1: {  // 输入一个数
            io->displayMessage("请输入操作：行 列 数字");
            std::vector<int> operation = io->getOperation();
            if (operation.size() == 3) {
                int row = operation[0];
                int col = operation[1];
                int value = operation[2];

                // 设置指定位置的Cell值
                if (!setCellValue(row, col, value)) {
                    io->displayMessage("无效操作。请重新输入。");
                }
            }
            else {
                io->displayMessage("输入格式错误。请重试。");
            }
            break;
        }
        case 2: {  // 擦去一个数
            io->displayMessage("请输入操作：行 列（擦去对应位置的数）");
            std::vector<int> operation = io->getPosition();
            if (operation.size() == 2) {    // 这里逻辑判断有问题
                int row = operation[0];
                int col = operation[1];

                // 擦去指定位置的数，即设置为 0
                if (!setCellValue(row, col, 0)) {
                    io->displayMessage("无法擦去该位置的数。");
                }
            }
            else {
                io->displayMessage("输入格式错误。请重试。");
            }
            break;
        }
        case 3: {  // 输入候选数
            io->displayMessage("请输入操作：行 列 候选数");
            std::vector<int> operation = io->getOperation();
            if (operation.size() == 3) {
                int row = operation[0];
                int col = operation[1];
                int candidate = operation[2];

                // 添加指定位置的候选数
                if (!addCellCandidate(row, col, candidate)) {
                    io->displayMessage("无法添加该候选数。");
                }
            }
            else {
                io->displayMessage("输入格式错误。请重试。");
            }
            break;
        }
        case 4: {  // 删除候选数
            io->displayMessage("请输入操作：行 列 候选数（删除该候选数）");
            std::vector<int> operation = io->getOperation();
            if (operation.size() == 3) {
                int row = operation[0];
                int col = operation[1];
                int candidate = operation[2];

                // 删除指定位置的候选数
                if (!removeCellCandidates(row, col, candidate)) {
                    io->displayMessage("无法删除该候选数。");
                }
            }
            else {
                io->displayMessage("输入格式错误。请重试。");
            }
            break;
        }
        case 5: {  // 自动补充候选数
            if (autoUpdateCandidates()) {
                io->displayMessage("自动补充候选数完成！");
            }
            else {
                io->displayMessage("无法自动补充候选数。");
            }
            break;
        }
        case 6: {  // 保存游戏
            if (saveToFile(id)) {
                io->displayMessage("游戏已成功保存！");
            }
            else {
                io->displayMessage("保存失败。");
            }
            break;
        }
        case 7: {  // 重置游戏
            if (reset()) {
                io->displayMessage("游戏已重置！");
            }
            else {
                io->displayMessage("重置失败。");
            }
            break;
        }
        case 8: {  // 退出游戏
            io->displayMessage("退出游戏。");
            return;
        }
        default:
            io->displayMessage("无效选项。请重新选择。");
        }
    }
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

    // 如果是设置为 0，表示擦除对应位置的数值
    if (value == 0) {
        // 调用对应Cell的setValue函数，将值设为0
        board[row][col]->setValue(0);  // 擦除值
        return true;  // 擦除操作总是合法的
    }

    // 调用对应Cell的setValue函数，设置新值
    if (!board[row][col]->setValue(value)) {
        return false;
    }

    // 检查对应的行、列和块是否合法
    if (!rows[row].isValid()) {
        return false;
    }
    if (!columns[col].isValid()) {
        return false;
    }
    if (!blocks[(row / 3) * 3 + col / 3].isValid()) {
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
    if (!board[row][col]->addCandidate(candidate)) {
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
    if (!board[row][col]->removeCandidate(candidate)) {
        return false;
    }

    return true;
}

bool Sudoku::autoUpdateCandidates()
{
    // 遍历数独棋盘中的每个Cell
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            Cell* cell = board[i][j];

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
            board[i][j]->setValue(val);             // 修改已有的Cell的值
            board[i][j]->resetCandidates();         // 重置Cell的候选值
        }
    }

    return true;  // 重置成功
}

Sudoku::~Sudoku()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            delete board[i][j];
        }
    }
}