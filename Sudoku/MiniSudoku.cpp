#include "MiniSudoku.h"
#include <sstream>
#include <fstream>
#include <iostream>

// 构造函数
MiniSudoku::MiniSudoku(IOInterface* ioInterface, PuzzleLoader* loader)
    : io(ioInterface), puzzleLoader(loader), id(0), difficulty("Unknown") {
    setupMenu();  // 配置菜单项
    initializeBlock(std::vector<int>(9, 0));  // 初始化Block为全0
}

// 初始化Block，设置初始提示
void MiniSudoku::initializeBlock(const std::vector<int>& boardData) {
    if (block.getCells().empty()) {
        for (int i = 0; i < 9; ++i) {
            block.addCell(new Cell());  // 动态分配Cell对象并添加到Block中
        }
    }

    for (int i = 0; i < 9; ++i) {
        block.getCells()[i]->setValue(boardData[i]);
    }
}

// 显示当前Block状态
void MiniSudoku::displayBlock() const {
    io->displayMessage("Game ID: " + std::to_string(id) + " | Difficulty: " + difficulty);
    std::vector<int> board;
    for (const auto& cell : block.getCells()) {
        board.push_back(cell->getValue());
    }
    io->displayBoard(board);
}

// 配置菜单项
void MiniSudoku::setupMenu() {
    menuManager.addMenuItem("Set Value", [this]() {
        io->displayMessage("Enter row (1-3), column (1-3), and value (1-9): ");
        int row, col, value;
        std::cin >> row >> col >> value;
        setCellValue(row, col, value);
        });

    menuManager.addMenuItem("Reset Game", [this]() {
        reset();
        });

    menuManager.addMenuItem("Save Game", [this]() {
        saveToFile(this->id);
        });

    menuManager.addMenuItem("Quit", [this]() {
        io->displayMessage("Quitting game.");
        exit(0);
        });
}

// 从文件加载游戏数据
bool MiniSudoku::loadFromFile(int gameID) {
    std::vector<int> boardData;
    if (puzzleLoader->loadPuzzle("MiniPuzzles.dat", gameID, boardData, difficulty)) {
        id = gameID;
        initializeBlock(boardData);
        return true;
    }
    else {
        io->displayMessage("Failed to load game.");
        return false;
    }
}

// 保存当前游戏到文件
bool MiniSudoku::saveToFile(int gameID) {
    std::vector<int> boardData;
    for (const auto& cell : block.getCells()) {
        boardData.push_back(cell->getValue());
    }
    return puzzleLoader->savePuzzle("puzzles.dat", gameID, boardData, difficulty);
}

// 设置某个单元格的值
void MiniSudoku::setCellValue(int row, int col, int value) {
    int index = (row - 1) * 3 + (col - 1); // Convert 2D index to 1D
    if (index >= 0 && index < 9) {
        block.getCells()[index]->setValue(value);
    }
    else {
        std::cerr << "Invalid index: " << index << std::endl;
    }
}

// 检查游戏是否完成
bool MiniSudoku::checkIfSolved() const {
    return block.isSolved() && block.isValid();
}

// 重置游戏
void MiniSudoku::reset() {
    block.resetCandidates();
    // 可以在这里重新加载初始值或执行其他重置操作
}

// 开始游戏
void MiniSudoku::start() {
    while (!checkIfSolved()) {
        displayBlock();
        menuManager.displayMenu();
        io->displayMessage("Select an option:");
        std::string option = io->getUserInput();
        menuManager.executeMenuItem(option);
    }

    io->displayMessage("Congratulations! You solved the MiniSudoku!");
}
